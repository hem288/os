#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

void SJF(vector<int> &p, vector<int> &AT, vector<int> &BT, vector<int> &CT, vector<int> &TAT, vector<int> &WT, vector<string> &sequence) {
 
   int n = p.size();
   vector<bool> completed(n, false);
   int completedCount = 0;
   int current_time = 0;
   
   while(completedCount < n){
      int idx = -1;
      int minBT = INT_MAX;
      
      for(int i = 0; i < n; i++){
          if(!completed[i] && AT[i] <= current_time){
              if(BT[i] < minBT) {
                  minBT = BT[i];
                  idx = i;
              } else if (BT[i] == minBT && AT[i] < AT[idx]) {
              
                  idx = i;
              }
          }
      }

      if(idx != -1) {
           current_time += BT[idx];
           CT[idx]   = current_time;
           TAT[idx] = CT[idx] - AT[idx];
           WT[idx]  =  TAT[idx] - BT[idx];
           completed[idx] = true;
           completedCount ++;
         
          sequence.push_back("P" + to_string(p[idx]));
      } else {
          current_time ++;
     }
  }
}

int main(){
  int n;
  cout << "Enter the Number of process : ";
  cin >> n;
  
  vector<int> p(n);   //process id
  vector<int> AT(n);  // Arrival Times
  vector<int> BT(n);  // Burst Times

  vector<int> CT(n, 0), TAT(n,0), WT(n, 0);
 
  vector<string> sequence;

  for(int i = 0; i < n; i++){
     p[i] = i + 1; 
     cout << "Enter Arrival Time for P" << p[i] << ": ";
     cin >> AT[i];
     cout << "Enter Burst Time for P" << p[i] << ": ";
     cin >> BT[i];
  }

  cout <<"\nProcess Details:\n";
  cout <<"Process\tArrivalTime\tBurst Time\n";

  for(int i = 0; i < n; i++){
     cout << "p" << p[i] << "\t" << AT[i] << "\t\t" << BT[i] << "\n";
  }

  
  SJF(p, AT, BT, CT, TAT, WT, sequence);

  cout << "\nExecution Sequence: ";
    for (auto s : sequence) cout << s << " ";
    cout << "\n";


    cout << "\nPID\tAT\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i] << "\t" << AT[i] << "\t" << BT[i] << "\t"
             << WT[i] << "\t" << TAT[i] << "\n";
    }

   
    double avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) {
        avgWT += WT[i];
        avgTAT += TAT[i];
    }
    cout << "\nAverage WT: " << avgWT/n;
    cout << "\nAverage TAT: " << avgTAT/n << "\n";
    

  return 0;
}
