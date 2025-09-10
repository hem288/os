#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void FCFS(vector<int> &p, vector<int> &AT, vector<int> &BT,
          vector<int> &CT, vector<int> &TAT, vector<int> &WT, vector<string> &sequence) {

    int n = p.size();

    // Sort by Arrival Time (keeping PIDs in sync)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (AT[j] < AT[i]) {
                swap(AT[i], AT[j]);
                swap(BT[i], BT[j]);
                swap(p[i], p[j]);
            }
        }
    }

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < AT[i]) current_time = AT[i]; // CPU idle till process arrives
        current_time += BT[i];
        CT[i] = current_time;
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];

        sequence.push_back("P" + to_string(p[i]));
    }
}

int main() {
    int n;
    cout << "Enter the Number of processes: ";
    cin >> n;

    vector<int> p(n), AT(n), BT(n);
    vector<int> CT(n, 0), TAT(n, 0), WT(n, 0);
    vector<string> sequence;

    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
        cout << "Enter Arrival Time for P" << p[i] << ": ";
        cin >> AT[i];
        cout << "Enter Burst Time for P" << p[i] << ": ";
        cin >> BT[i];
    }

    cout << "\nProcess Details:\n";
    cout << "PID\tAT\tBT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i] << "\t" << AT[i] << "\t" << BT[i] << "\n";
    }

    // Run FCFS
    FCFS(p, AT, BT, CT, TAT, WT, sequence);

    cout << "\nExecution Sequence: ";
    for (auto s : sequence) cout << s << " ";
    cout << "\n";

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i] << "\t" << AT[i] << "\t" << BT[i] << "\t"
             << CT[i] << "\t" << TAT[i] << "\t" << WT[i] << "\n";
    }

    double avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) {
        avgWT += WT[i];
        avgTAT += TAT[i];
    }
    cout << "\nAverage WT: " << avgWT / n;
    cout << "\nAverage TAT: " << avgTAT / n << "\n";

    return 0;
}
