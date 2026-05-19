#include <iostream>
#include <string>

using namespace std;

int main() {
    // 1. Data Setup
    string names[] = {"", "S1", "S2", "S3", "S4", "S5", "S6"};
    int bw[] = {0, 4, 1, 5, 3, 2, 3};      // Bandwidth
    int priority[] = {0, 8, 3, 9, 6, 4, 5}; // Priority Scores
    int n = 6;
    int maxW = 10;

    // Calculate Ratios (Priority / Bandwidth)
    double ratio[7];
    for (int i = 1; i <= n; i++) {
        ratio[i] = (double)priority[i] / bw[i];
    }

    // 2. Manual Bubble Sort (Arranging services by highest ratio)
    // We sort names, bw, priority, and ratio arrays together so they stay aligned
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= n - i; j++) {
            if (ratio[j] < ratio[j + 1]) {
                // Swap Ratio
                double tempRatio = ratio[j];
                ratio[j] = ratio[j + 1];
                ratio[j + 1] = tempRatio;

                // Swap Names
                string tempName = names[j];
                names[j] = names[j + 1];
                names[j + 1] = tempName;

                // Swap Bandwidth
                int tempBw = bw[j];
                bw[j] = bw[j + 1];
                bw[j + 1] = tempBw;

                // Swap Priority
                int tempPriority = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = tempPriority;
            }
        }
    }

    // 3. Select Services using Greedy Strategy
    cout << "=== GREEDY APPROACH SELECTED SERVICES ===" << endl;
    int currentBW = 0;
    int totalPriority = 0;

    for (int i = 1; i <= n; i++) {
        // Check if the service fits in the remaining space
        if (currentBW + bw[i] <= maxW) {
            cout << names[i] << " (Bandwidth: " << bw[i] << ", Priority: " << priority[i] << ", Ratio: " << ratio[i] << ")" << endl;
            currentBW += bw[i];
            totalPriority += priority[i];
        }
    }

    // 4. Print Final Totals
    cout << "\nTotal Priority: " << totalPriority << endl;
    cout << "Total Bandwidth Used: " << currentBW << " Mbps" << endl;

    return 0;
}