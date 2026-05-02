#include <iostream>
#include <string>
using namespace std;

#define MAX 100   // maximum size of stack

// Array stack
char stackArr[MAX];
int top = -1;   // top of stack (-1 means empty)

// Push: add element on top
void push(char c) {
    if (top == MAX - 1) {
        cout << "Stack Overflow!" << endl;
        return;
    }
    top = top + 1;         // move top up
    stackArr[top] = c;     // store element
}

// Pop: remove element from top
char pop() {
    if (top == -1) {
        cout << "Stack Underflow!" << endl;
        return '\0';       // return null if empty
    }
    char temp = stackArr[top]; // take top element
    top = top - 1;             // move top down
    return temp;               // return removed element
}

// Peek: look at top element (without removing it)
char peek() {
    if (top == -1) {
        return '\0';       // empty
    }
    return stackArr[top];
}

// Check if stack is empty
bool isEmpty() {
    return (top == -1);
} 

// Precedence of operators
int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return -1;
}

// Check if operator
bool isOperator(char c) {
    return (c=='+'||c=='-'||c=='*'||c=='/'||c=='^');
}

// Check if operand (letter or digit)
bool isOperand(char c) {
    return ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            (c >= '0' && c <= '9'));
}

// Convert Infix → Postfix (step by step)
string infixToPostfix(string infix) {
    string result = "";   // this will store the final postfix
    top = -1;             // reset stack (empty)

    // Go through each character of the infix expression
    for (char c : infix) {
        
        // 1. If it's an operand (a, b, c, 1, 2 ...), add to result
        if (isOperand(c)) {
            result += c;
        }

        // 2. If it's '(', push to stack
        else if (c == '(') {
            push(c);
        }

        // 3. If it's ')', pop until '('
        else if (c == ')') {
            while (!isEmpty() && peek() != '(') {
                result += pop();   // pop operators into result
            }
            pop();  // remove the '(' from stack
        }

        // 4. If it's an operator (+, -, *, /)
        else if (isOperator(c)) {
            // While stack not empty AND top of stack has
            // higher/equal precedence than current operator
            while (!isEmpty() && precedence(peek()) >= precedence(c)) {
                // Special case: for ^ (right-associative), stop popping
                if (c == '^' && peek() == '^') break;
                result += pop();   // pop operators into result
            }
            push(c);  // finally push the current operator
        }
    }

    // 5. After the loop, pop all remaining operators
    while (!isEmpty()) {
        result += pop();
    }

    return result;
}


// Helper: reverse a string
string reverseStr(string s) {
    int n = s.length();
    for (int i = 0; i < n/2; i++) {
        swap(s[i], s[n-i-1]);
    }
    return s;
}

// Convert Infix → Prefix (step by step)
string infixToPrefix(string infix) {
    // 1. Reverse the infix expression
    string rev = reverseStr(infix);

    // 2. Swap '(' with ')' and vice versa
    for (int i = 0; i < rev.length(); i++) {
        if (rev[i] == '(') rev[i] = ')';
        else if (rev[i] == ')') rev[i] = '(';
    }

    // 3. Convert the modified expression into postfix
    string postfix = infixToPostfix(rev);

    // 4. Reverse the postfix result → this is prefix
    string prefix = reverseStr(postfix);

    return prefix;
}


// Main program
int main() {
    string infix;
    cout << "Enter infix expression: ";
    cin >> infix;

    cout << "Postfix: " << infixToPostfix(infix) << endl;
    cout << "Prefix: " << infixToPrefix(infix) << endl;

    system("pause");
    return 0;
}