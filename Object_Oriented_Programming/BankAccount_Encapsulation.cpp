#include <iostream>
#include <string> // Essential for using the string data_type
using namespace std;

/**
 * BankAccount Class
 * Demonstrates Encapsulation, Static Members, and Object Interaction.
 */
class BankAccount {
private:
    // Static variable shared by all instances to track total account count
    static int totalAccounts;
    
    // Private attributes (Encapsulation: hidden from direct outside access)
    int accountID;
    string accountHolder;
    double accountBalance;

public:
    /**
     * Constructor: Initializes a new account and increments the global count.
     */
    BankAccount(int id, string holder, double balance) 
    {
        accountID = id;
        accountHolder = holder;
        accountBalance = balance;
        totalAccounts++; // Increment shared counter when an account is created
    } 

    /**
     * Destructor: Automatically called when an object goes out of scope.
     * Decrements the global count and prints a closing message.
     */
    ~BankAccount() {
        cout << "Account " << accountID << " is closed." << endl;
        totalAccounts--; // Decrement shared counter
    }

    /**
     * transferMoney: Transfers a specified amount to another BankAccount object.
     * Uses pass-by-reference (&receiver) to modify the actual target object.
     */
    void transferMoney(BankAccount &receiver, double amount) {
        // Validation: Ensure the sender has enough funds
        if (accountBalance >= amount) {
            accountBalance -= amount;           // Deduct from sender
            receiver.accountBalance += amount;  // Add to receiver
            cout << "Transferred " << amount << " from " << accountHolder
                 << " to " << receiver.accountHolder << endl;
        } else {
            cout << "Balance is insufficient!!!" << endl;
        }
    }

    /**
     * display: Prints the account details to the console.
     * 'const' ensures this function doesn't accidentally modify the data.
     */
    void display() const {
        cout << "--- Account Details ---" << endl;
        cout << "Account ID: " << accountID << endl;
        cout << "Holder:     " << accountHolder << endl;
        cout << "Balance:    $" << accountBalance << endl;
        cout << "-----------------------" << endl;
    }

    /**
     * showTotalAccounts: Static function to display the global account count.
     */
    static void showTotalAccounts() {
        cout << "\n>>> Total Active Accounts: " << totalAccounts << " <<<\n" << endl;
    }
};

// Initialize the static member outside the class
int BankAccount::totalAccounts = 0;

int main() {
    // 1. Create account instances
    BankAccount maheen(1987345, "Maheen Zahra", 500305);
    BankAccount dania(1026764, "Dania Shahid", 300670);
    
    // 2. Display initial state
    maheen.display();
    dania.display();
    
    // 3. Perform a transaction
    // 'maheen' is the caller, 'dania' is passed as the receiver
    maheen.transferMoney(dania, 5980);
    
    // 4. Display updated state
    maheen.display();
    dania.display();
    
    // 5. Check global account count
    BankAccount::showTotalAccounts();
    
    return 0; // Destructors for 'maheen' and 'dania' will run automatically here
}
