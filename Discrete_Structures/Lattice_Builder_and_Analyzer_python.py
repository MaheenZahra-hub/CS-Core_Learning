# poset_lattice_gui.py
# Simple Poset -> Lattice checker with Tkinter visualization
# Supports string elements (a, b, c) and integers (keeps GUI/graphics unchanged)

import tkinter as tk
from tkinter import ttk, messagebox, scrolledtext

# ---------- Algorithms (matrix-based) ----------

def parse_elements(text):   #Converts the user input of elements into a Python list
    """Parse elements, supporting {}, {a}, {a,b}, and {a} {b} formats."""
    text = text.strip()
    if not text or text == "{}":
        return []
    
    # Replace all '{' and '}' with spaces
    text = text.replace("{", " ").replace("}", " ")
    
    # Split on comma or space
    tokens = [t.strip() for t in text.replace(",", " ").split() if t.strip()]
    
    # Remove duplicates
    out = []
    seen = set()
    for t in tokens:
        if t in seen:
            raise ValueError(f"Duplicate element: {t}")
        seen.add(t)
        out.append(t)
    
    return out

def token_type(tok):
    """Return 'int' for integer, 'alpha' for alphabet; raise error for other symbols."""
    if not tok:
        raise ValueError("Empty element is not allowed.")
    try:
        int(tok)
        return 'int'
    except Exception:
        if tok.isalpha():
            return 'alpha'
        else:
            raise ValueError(f"Invalid element '{tok}': symbols are not allowed.")

def parse_relations(text, elements):   #Converts the user input of relations into a list of pairs.
    """Parse relations: each line 'a b', disallow mixing int and alpha."""
    lines = [l.strip() for l in text.splitlines() if l.strip()]
    rels = []
    elemset = set(elements)
    
    for ln in lines:
        parts = ln.split()
        if len(parts) != 2:
            raise ValueError(f"Invalid relation line: '{ln}'. Use 'a b'.")
        a, b = parts
        if a not in elemset or b not in elemset:
            raise ValueError(f"Relation ({a},{b}) uses unknown element.")
        
        ta = token_type(a)
        tb = token_type(b)
        if (ta == 'int' and tb == 'alpha') or (ta == 'alpha' and tb == 'int'):
            raise ValueError(f"Invalid relation '{ln}': cannot mix integer and alphabetic elements.")
        
        rels.append((a, b))
    
    return rels

def make_index_map(elements):  #Maps each element to an index
    """Maps each element to a matrix index."""
    # Map element to its index for matrix representation
    return {elements[i]: i for i in range(len(elements))}

def closure_reflexive_transitive(n, mat):  #Adds reflexive pairs and computes transitive closure
    """Adds reflexive pairs and computes transitive closure."""
    # Add reflexive pairs (x,x)
    for i in range(n):
        mat[i][i] = 1
    # Compute transitive closure
    for k in range(n):
        for i in range(n):
            if mat[i][k]:
                for j in range(n):
                    if mat[k][j]:
                        mat[i][j] = 1
    return mat

def check_reflexive(n, mat):    #Checks if every element relates to itself
    """Checks if every element relates to itself."""
    # Check that all diagonal entries are 1 (x ≤ x)
    for i in range(n):
        if mat[i][i] == 0:
            return False
    return True

def check_transitive(n, mat):  #Checks if the relation satisfies transitivity
    """Checks if the relation satisfies transitivity."""
    # Check that if x ≤ y and y ≤ z then x ≤ z
    for i in range(n):
        for j in range(n):
            if mat[i][j]:
                for k in range(n):
                    if mat[j][k] and not mat[i][k]:
                        return False
    return True

def is_antisymmetric(n, mat):    #Checks if the relation is antisymmetric
    """Checks if the relation is antisymmetric."""
    for i in range(n):
        for j in range(n):
            if i != j and mat[i][j] and mat[j][i]:
                return False
    return True

def cover_edges(n, mat):   #Finds direct relations for Hasse diagram (removes transitive edges)
    """Finds direct relations for Hasse diagram (removes transitive edges)."""
    cover = [[0]*n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if i != j and mat[i][j]:
                is_cover = True
                # If there exists an intermediate k where i < k < j, it's not a cover
                for k in range(n):
                    if k != i and k != j and mat[i][k] and mat[k][j]:
                        is_cover = False
                        break
                if is_cover:
                    cover[i][j] = 1
    return cover

def all_lower_bounds(n, mat, a_idx, b_idx):
    """Return indices of elements x where x ≤ a and x ≤ b."""
    return [i for i in range(n) if mat[i][a_idx] and mat[i][b_idx]]

def all_upper_bounds(n, mat, a_idx, b_idx):
    """Return indices of elements x where a ≤ x and b ≤ x."""
    return [i for i in range(n) if mat[a_idx][i] and mat[b_idx][i]]

def greatest_of(n, mat, candidates):
    """Return the greatest element among candidates (upper bound of all)."""
    for c in candidates:
        if all(mat[d][c] for d in candidates):
            return c
    return None

def least_of(n, mat, candidates):
    """Return the least element among candidates (lower bound of all)."""
    for c in candidates:
        if all(mat[c][d] for d in candidates):
            return c
    return None

# ---------- GUI ----------

class PosetApp:
    def __init__(self, root):   #Initializes the GUI window
        """Initializes the GUI window."""
        self.root = root
        root.title("Poset → Lattice Checker (Meet & Join + Hasse)")
        self.build_ui()

    def build_ui(self):   #Creates all input fields, buttons, results, and canvas
        """Creates all input fields, buttons, results, and canvas."""
        # Main frame
        frm = ttk.Frame(self.root, padding=8)
        frm.grid(sticky="nsew")
        self.root.rowconfigure(0, weight=1)
        self.root.columnconfigure(0, weight=1)

        # Entry for elements
        ttk.Label(frm, text="Elements (letters or numbers):").grid(column=0, row=0, sticky="w")
        self.elem_entry = ttk.Entry(frm, width=60)
        self.elem_entry.grid(column=0, row=1, sticky="we", pady=2)

        # Entry for relations
        ttk.Label(frm, text="Relations (one per line):").grid(column=0, row=2, sticky="w")
        self.rels_text = scrolledtext.ScrolledText(frm, width=60, height=8)
        self.rels_text.grid(column=0, row=3, pady=2, sticky="we")

        # Compute button
        ttk.Button(frm, text="Compute & Visualize", command=self.on_compute).grid(column=0, row=4, pady=6, sticky="w")

        # Results area
        ttk.Label(frm, text="Results / Meet & Join Table:").grid(column=1, row=0, sticky="w")
        self.result_text = scrolledtext.ScrolledText(frm, width=60, height=18)
        self.result_text.grid(column=1, row=1, rowspan=4, padx=6, sticky="nsew")

        # Canvas for Hasse diagram
        ttk.Label(frm, text="Hasse Diagram:").grid(column=0, row=5, sticky="w", pady=(8, 0))
        self.canvas = tk.Canvas(frm, width=760, height=380, bg="white")
        self.canvas.grid(column=0, columnspan=2, row=6, pady=4)

        frm.columnconfigure(1, weight=1)
        frm.rowconfigure(6, weight=1)

    def on_compute(self):   #Main function: validates poset, computes meet/join, and draws Hasse diagram
        """Main function: validates poset, computes meet/join, and draws Hasse diagram."""
        # Clear previous output
        self.result_text.delete('1.0', tk.END)
        self.canvas.delete("all")

        # Parse elements and relations
        try:
            elements = parse_elements(self.elem_entry.get())
            relations = parse_relations(self.rels_text.get('1.0', tk.END), elements)
        except ValueError as e:
            messagebox.showerror("Input Error", str(e))
            return

        n = len(elements)
        idx = make_index_map(elements)

        # Build relation matrix from user input (no closure yet)
        mat = [[0]*n for _ in range(n)]
        for a, b in relations:
            mat[idx[a]][idx[b]] = 1

        # Strict checks Poset properties
        reflexive_ok = check_reflexive(n, mat)
        transitive_ok = check_transitive(n, mat)
        antisym_ok = is_antisymmetric(n, mat)

        # Display validation results
        if reflexive_ok and transitive_ok and antisym_ok:
            self.result_text.insert(tk.END, "✓ Valid poset (reflexive, antisymmetric, transitive)\n\n")
            poset_valid = True
        else:
            poset_valid = False
            self.result_text.insert(tk.END, "✗ Not a poset. Failed property(s):\n")
            if not reflexive_ok:
                self.result_text.insert(tk.END, " - Reflexivity missing: some (x,x) are not present.\n")
            if not antisym_ok:
                self.result_text.insert(tk.END, " - Antisymmetry violated: found a≠b with a≤b and b≤a.\n")
            if not transitive_ok:
                self.result_text.insert(tk.END, " - Transitivity missing: some (a,b) and (b,c) exist but (a,c) does not.\n")
            self.result_text.insert(tk.END, "\nHasse diagram and meet/join table will NOT be drawn because input is not a valid poset.\n")
            return  # stop here — do not compute further or draw Hasse

        # If valid poset, proceed exactly as before (but use closure for computations)
        closure_reflexive_transitive(n, mat)

        # MEET / JOIN TABLE
        self.result_text.insert(tk.END, "Meet & Join Table:\n")
        self.result_text.insert(tk.END, "-"*60 + "\n")
        all_pairs_ok = True

        for i in range(n):
            for j in range(i, n):
                lbs = all_lower_bounds(n, mat, i, j)
                meet_idx = greatest_of(n, mat, lbs)

                ubs = all_upper_bounds(n, mat, i, j)
                join_idx = least_of(n, mat, ubs)

                meet = elements[meet_idx] if meet_idx is not None else "-"
                join = elements[join_idx] if join_idx is not None else "-"

                if meet == "-" or join == "-":
                    all_pairs_ok = False

                self.result_text.insert(tk.END,
                    f"({elements[i]}, {elements[j]}) -> meet: {meet} , join: {join}\n"
                )

        self.result_text.insert(tk.END, "-"*60 + "\n\n")

        if all_pairs_ok:
            self.result_text.insert(tk.END, "✓ This poset IS a lattice (every pair has meet & join).\n\n")
        else:
            self.result_text.insert(tk.END, "✗ This poset is NOT a lattice (some pair lacks meet or join).\n\n")

        # ------------------- Hasse Diagram -------------------
        cover = cover_edges(n, mat)

        level = [-1]*n
        for i in range(n):
            if not any(cover[j][i] for j in range(n)):
                level[i] = 0

        changed = True
        while changed:
            changed = False
            for i in range(n):
                if level[i] != -1:
                    continue
                preds = [j for j in range(n) if cover[j][i]]
                if preds and all(level[p] != -1 for p in preds):
                    level[i] = max(level[p] for p in preds) + 1
                    changed = True

        for i in range(n):
            if level[i] == -1:
                level[i] = 0

        groups = {}
        for i in range(n):
            groups.setdefault(level[i], []).append(i)

        canvas_w = int(self.canvas['width'])
        canvas_h = int(self.canvas['height'])
        radius = 20
        node_pos = {}

        levels_sorted = sorted(groups.keys())
        vgap = canvas_h // (len(levels_sorted) + 1)

        for li, level_val in enumerate(levels_sorted, start=1):
            nodes = groups[level_val]
            hgap = canvas_w // (len(nodes) + 1)
            for i, node in enumerate(nodes, start=1):
                x = i * hgap
                y = li * vgap
                node_pos[node] = (x, y)

        for i in range(n):
            for j in range(n):
                if cover[i][j]:
                    x1, y1 = node_pos[i]
                    x2, y2 = node_pos[j]
                    self.canvas.create_line(x1, y1+radius, x2, y2-radius, width=2, arrow=tk.LAST)

        for i in range(n):
            x, y = node_pos[i]
            self.canvas.create_oval(x-radius, y-radius, x+radius, y+radius, fill="#e0f7ff")
            self.canvas.create_text(x, y, text=str(elements[i]), font=("Arial", 10, "bold"))

        self.result_text.insert(tk.END, "\nHasse edges:\n")
        for i in range(n):
            for j in range(n):
                if cover[i][j]:
                    self.result_text.insert(tk.END, f"{elements[i]} -> {elements[j]}\n")

def main():  #Starts the GUI application
    """Starts the GUI application."""
    root = tk.Tk()
    app = PosetApp(root)
    root.geometry("1200x720")
    root.mainloop()

if __name__ == "__main__":
    main()