#include <iostream>
#include <string>
using namespace std;

// ------------------- Operator Stack -------------------
// Handles all operator characters (+, -, *, /, ^, parentheses)
class OperatorStack {
    char arr[100];   // array to store operators
    int top;         // index of the top element
public:
    OperatorStack() { top = -1; }

    // Push operator onto stack
    void push(char c) {
        if (top == 99) {
            cout << "Operator Stack Overflow!" << endl;
            return;
        }
        arr[++top] = c;
    }

    // Pop operator from stack
    char pop() {
        if (top == -1) return '\0';
        return arr[top--];
    }

    // Peek at top operator without removing
    char peek() {
        if (top == -1) return '\0';
        return arr[top];
    }

    // Check if stack is empty
    bool isEmpty() { return top == -1; }

    // Reset stack
    void clear() { top = -1; }
};

// ------------------- Operand Stack -------------------
// Handles all operands (letters or digits)
class OperandStack {
    string arr[100]; // array to store operands
    int top;         // index of top element
public:
    OperandStack() { top = -1; }

    // Push operand onto stack
    void push(string s) {
        if (top == 99) {
            cout << "Operand Stack Overflow!" << endl;
            return;
        }
        arr[++top] = s;
    }

    // Pop operand from stack
    string pop() {
        if (top == -1) return "";
        return arr[top--];
    }

    // Check if stack is empty
    bool isEmpty() { return top == -1; }

    // Reset stack
    void clear() { top = -1; }
};

// ------------------- Converter -------------------
// Handles conversion of infix expression to postfix and prefix
class Converter {
    OperatorStack opStack;       // Stack for operators
    OperandStack operandStack;   // Stack for operands

    // Return precedence value of operator
    int getPrecedence(char c) {
        if (c == '^') return 3;
        if (c == '*' || c == '/') return 2;
        if (c == '+' || c == '-') return 1;
        return -1;
    }

    // Check if character is an operator
    bool isOperator(char c) {
        return (c=='+'||c=='-'||c=='*'||c=='/'||c=='^');
    }

    // Check if character is an operand (letter or digit)
    bool isOperand(char c) {
        return ((c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                (c >= '0' && c <= '9'));
    }

    // Reverse a string (helper for prefix conversion)
    string reverseString(string s) {
        int n = s.length();
        for (int i = 0; i < n/2; i++) 
            swap(s[i], s[n-i-1]);
        return s;
    }

public:
    // Convert infix to postfix
    string toPostfix(string infix) {
        opStack.clear();       // Clear operator stack
        operandStack.clear();  // Clear operand stack

        string result = "";

        for (char c : infix) {
            if (isOperand(c)) {
                // Push operand to operand stack
                operandStack.push(string(1, c));
            }
            else if (c == '(') {
                opStack.push(c);  // Push left parenthesis
            }
            else if (c == ')') {
                // Pop operators until '('
                while (!opStack.isEmpty() && opStack.peek() != '(') {
                    string op2 = operandStack.pop();      // 1. Pop the second operand
                    string op1 = operandStack.pop();      // 2. Pop the first operand
                    string oper(1, opStack.pop());        // 3. Pop the operator 
                    operandStack.push(op1 + op2 + oper);  //4.Combine operands with operator
                }
                opStack.pop(); // Remove '('
            }
            else if (isOperator(c)) {
                // Pop operators with higher or equal precedence
                while (!opStack.isEmpty() && getPrecedence(opStack.peek()) >= getPrecedence(c)) {
                    if (c == '^' && opStack.peek() == '^') break; // Right-associative
                    string op2 = operandStack.pop();            // Pop second operand
                    string op1 = operandStack.pop();            // Pop first operand
                    string oper(1, opStack.pop());              // Pop operator
                    operandStack.push(op1 + op2 + oper);        // Combine as postfix
                }
                opStack.push(c); // Push current operator
            }
        }

        // Pop any remaining operators
        while (!opStack.isEmpty()) {
            string op2 = operandStack.pop();
            string op1 = operandStack.pop();
            string oper(1, opStack.pop());
            operandStack.push(op1 + op2 + oper);
        }

        if (!operandStack.isEmpty()) result = operandStack.pop();
        return result;
    }

    // Convert infix to prefix
    string toPrefix(string infix) {
        // Step 1: Reverse infix
        string rev = reverseString(infix);

        // Step 2: Swap parentheses
        for (int i = 0; i < rev.length(); i++) {
            if (rev[i] == '(') rev[i] = ')';
            else if (rev[i] == ')') rev[i] = '(';
        }

        // Step 3: Convert reversed infix to postfix
        string postfix = toPostfix(rev);

        // Step 4: Reverse postfix to get prefix
        return reverseString(postfix);
    }
};

// ------------------- Main Function -------------------
int main() {
    Converter conv; 
    string infix;
    char choice;

    cout << "==============================\n";
    cout << " Infix to Postfix & Prefix Converter \n";
    cout << "==============================\n";

    do {
        // Ask user for input
        cout << "\nEnter a valid infix expression: ";
        cin >> infix;

        // Display results
        cout << "\n--- Conversion Results ---\n";
        cout << "Infix   : " << infix << endl;
        cout << "Postfix : " << conv.toPostfix(infix) << endl;
        cout << "Prefix  : " << conv.toPrefix(infix) << endl;

        // Ask if user wants to convert another expression
        cout << "\nDo you want to convert another expression? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "\nThank you for using the converter!\n";
    return 0;
}

