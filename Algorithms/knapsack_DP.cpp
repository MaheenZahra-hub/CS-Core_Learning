#include <iostream>
#include <string>

using namespace std;

int main() {
    // 1. Data Setup
    string names[] = {"", "S1", "S2", "S3", "S4", "S5", "S6"};
    int bw[] = {0, 4, 1, 5, 3, 2, 3};      // Bandwidth (Weights)
    int priority[] = {0, 8, 3, 9, 6, 4, 5}; // Priority Scores (Values)
    
    int maxW = 10; // Max Bandwidth Capacity
    int n = 6;     // Total number of services
    int dp[7][11]; // The DP Table (7 rows for services, 11 columns for capacity)

    // 2. Fill DP Table with 0s for the first row and column
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= maxW; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }
            else if (bw[i] <= w) {
                // If the service fits, take the max of:
                // (Value of current service + Value of remaining space) OR (Value without current service)
                int include = priority[i] + dp[i-1][w - bw[i]];
                int exclude = dp[i-1][w];
                
                if (include > exclude) dp[i][w] = include;
                else dp[i][w] = exclude;
            } 
            else {
                // Doesn't fit, take value from row above
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    // 3. Print the DP Table 
    cout << "=== DP TABLE (Capacity 0 to 10) ===" << endl;
    for (int i = 0; i <= n; i++) {
        cout << names[i] << "\t";
        for (int w = 0; w <= maxW; w++) {
            cout << dp[i][w] << " ";
        }
        cout << endl;
    }

    // 4. Backtracking to find which services were chosen
    cout << "\n=== SELECTED SERVICES ===" << endl;
    int resW = maxW;
    int totalBW = 0;
    
    for (int i = n; i > 0; i--) {
        // If the value is different from the row above, it means service 'i' was picked
        if (dp[i][resW] != dp[i-1][resW]) {
            cout << names[i] << " (Bandwidth: " << bw[i] << ", Priority: " << priority[i] << ")" << endl;
            totalBW += bw[i];
            resW -= bw[i];
        }
    }

    cout << "\nTotal Priority: " << dp[n][maxW] << endl;
    cout << "Total Bandwidth Used: " << totalBW << " Mbps" << endl;

    return 0;
}