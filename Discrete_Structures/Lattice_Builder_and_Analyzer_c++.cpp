#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Poset {
private:
    static const int MAX = 20;

    int size = 0;                 // number of elements in the poset
    int elements[MAX];            // stores actual element values
    int rel[MAX][MAX];            // relation matrix: rel[a][b] = 1 means a ≤ b

    // Find the index of a given element value
    int indexOf(int value) const {
        for (int i = 0; i < size; i++)
            if (elements[i] == value)
                return i;
        return -1;
    }

public:

    // Constructor: initialize relation matrix with zeros
    Poset() {
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                rel[i][j] = 0;
    }

    // Read elements of the poset
    bool readElements() {
        cout << "Enter number of elements (max " << MAX << "): ";
        cin >> size;
        if (size <= 0 || size > MAX) return false;

        cout << "Enter the elements:\n";
        for (int i = 0; i < size; i++) {
            cin >> elements[i];

            // reject duplicate elements
            for (int j = 0; j < i; j++)
                if (elements[i] == elements[j]) {
                    cout << "Duplicate detected.\n";
                    return false;
                }
        }
        return true;
    }

    // Read user-defined relations a ≤ b
    bool readRelations() {
        int m;
        cout << "Enter number of relations: ";
        cin >> m;
        cout << "Enter each relation (a b):\n";

        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;

            int ia = indexOf(a), ib = indexOf(b);
            if (ia == -1 || ib == -1) return false;  // invalid element

            rel[ia][ib] = 1;  // store relation
        }
        return true;
    }

    // Make the relation reflexive: every a ≤ a must hold
    void makeReflexive() {
        for (int i = 0; i < size; i++)
            rel[i][i] = 1;
    }

    // Compute transitive closure
    // ensures: if a ≤ b and b ≤ c then a ≤ c
    void makeTransitive() {
        for (int k = 0; k < size; k++)
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    rel[i][j] = rel[i][j] || (rel[i][k] && rel[k][j]);
    }

    // Check antisymmetry: if a ≤ b and b ≤ a then a == b
    bool isAntisymmetric() const {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (i != j && rel[i][j] && rel[j][i])
                    return false;
        return true;
    }

    // Compute meet (greatest lower bound)
    int computeMeet(int x, int y) const {
        int ix = indexOf(x), iy = indexOf(y);
        int ans = -1;

        // k must satisfy k ≤ x and k ≤ y
        for (int k = 0; k < size; k++) {
            if (rel[k][ix] && rel[k][iy]) {
                if (ans == -1 || rel[ans][k])   // choose the greatest one
                    ans = k;
            }
        }

        return ans == -1 ? -1 : elements[ans];
    }

    // Compute join (least upper bound)
    int computeJoin(int x, int y) const {
        int ix = indexOf(x), iy = indexOf(y);
        int ans = -1;

        // k must satisfy x ≤ k and y ≤ k
        for (int k = 0; k < size; k++) {
            if (rel[ix][k] && rel[iy][k]) {
                if (ans == -1 || rel[k][ans])  // choose the smallest one
                    ans = k;
            }
        }

        return ans == -1 ? -1 : elements[ans];
    }

    // A poset is a lattice iff every pair has meet and join
    bool isLattice() const {
        for (int i = 0; i < size; i++)
            for (int j = i; j < size; j++)
                if (computeMeet(elements[i], elements[j]) == -1 ||
                    computeJoin(elements[i], elements[j]) == -1)
                    return false;
        return true;
    }

    // Print meet and join results for all element pairs
    void displayMeetJoin() const {
        cout << "\nMeet & Join Table:\n";
        cout << "Pair\tMeet\tJoin\n";

        for (int i = 0; i < size; i++)
            for (int j = i; j < size; j++) {
                int m = computeMeet(elements[i], elements[j]);
                int jn = computeJoin(elements[i], elements[j]);
                cout << "(" << elements[i] << "," << elements[j] << ")\t";
                cout << m << "\t" << jn << "\n";
            }
    }

    // Print the Hasse diagram using vertical edges
    void printHasse() const {
        cout << "\nHasse Diagram:\n";

        int cover[MAX][MAX] = {0};

        // Determine cover relations (immediate edges)
        for (int a = 0; a < size; a++) {
            for (int b = 0; b < size; b++) {
                if (a != b && rel[a][b]) {
                    bool isCover = true;

                    // check if some k lies strictly between a and b
                    for (int k = 0; k < size; k++)
                        if (k != a && k != b && rel[a][k] && rel[k][b])
                            isCover = false;

                    if (isCover)
                        cover[a][b] = 1;
                }
            }
        }

        // Assign "levels" for vertical diagram printing
        int level[MAX];
        fill(level, level + size, -1);

        // level 0 = minimal elements (no incoming cover edges)
        for (int i = 0; i < size; i++) {
            bool minimal = true;
            for (int j = 0; j < size; j++)
                if (cover[j][i]) minimal = false;
            if (minimal) level[i] = 0;
        }

        // propagate levels upward through the cover graph
        bool change = true;
        while (change) {
            change = false;
            for (int a = 0; a < size; a++) {
                if (level[a] != -1) continue;
                for (int b = 0; b < size; b++)
                    if (cover[b][a] && level[b] != -1) {
                        level[a] = level[b] + 1;
                        change = true;
                    }
            }
        }

        // find highest level
        int maxL = 0;
        for (int i = 0; i < size; i++)
            maxL = max(maxL, level[i]);

        // Print nodes level by level
        for (int L = 0; L <= maxL; L++) {

            // print nodes in this level
            for (int i = 0; i < size; i++)
                if (level[i] == L)
                    cout << "(" << elements[i] << ")   ";
            cout << "\n";

            // print vertical connectors to next level
            for (int i = 0; i < size; i++)
                if (level[i] == L)
                    for (int j = 0; j < size; j++)
                        if (cover[i][j])
                            cout << " |    ";
            cout << "\n";
        }

        // final: list all edges
        cout << "\nEdges:\n";
        for (int a = 0; a < size; a++)
            for (int b = 0; b < size; b++)
                if (cover[a][b])
                    cout << elements[a] << " -> " << elements[b] << "\n";
    }
};


// ==================================================
// MAIN PROGRAM: runs the poset functions in order
// ==================================================
int main() {
    Poset p;

    if (!p.readElements()) return 0;    // read elements
    if (!p.readRelations()) return 0;   // read relations

    p.makeReflexive();                  // ensure a ≤ a
    p.makeTransitive();                 // ensure closure

    if (!p.isAntisymmetric()) {         // check antisymmetry
        cout << "Invalid Poset.\n";
        return 0;
    }

    cout << "\nValid Poset.\n";

    p.displayMeetJoin();                // show meet/join table

    if (p.isLattice())
        cout << "\nThis poset IS a lattice.\n";
    else
        cout << "\nThis poset is NOT a lattice.\n";

    p.printHasse();                     // print diagram

    cout << "\nPress any key to exit...\n";
    system("pause");
    return 0;
}
