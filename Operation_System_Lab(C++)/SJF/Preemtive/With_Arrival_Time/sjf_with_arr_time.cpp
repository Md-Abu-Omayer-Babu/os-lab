#include<bits/stdc++.h>
using namespace std;

int main(){
    freopen("2.txt", "r", stdin);

    int n;
    cin >> n;

    int total_process = n;

    vector<string> process(n), gantt_chart;
    vector<int> arrival_time(n), burst_time(n), completion_time(n), turn_around_time(n), waiting_time(n);

    for(int i = 0; i < n; i++){
        cin >> process[i] >> arrival_time[i] >> burst_time[i];
    }

    vector<int> rem_burst_time = burst_time;

    int completed = 0, current_time = 0;

    while(completed < n){
        int index = -1;
        int min_rem_BT = INT_MAX;
        
        for(int i = 0; i < n; i++){
            if(rem_burst_time[i] > 0 &&
            rem_burst_time[i] < min_rem_BT &&
            arrival_time[i] <= current_time)
            {
                index = i;
                min_rem_BT = rem_burst_time[i];
            }
        }

        if(index == -1){
            current_time++;
            gantt_chart.push_back("idle");
            continue;
        }

        current_time++;
        gantt_chart.push_back(process[index]);
        rem_burst_time[index]--;

        if(rem_burst_time[index] == 0){
            completed++;
            completion_time[index] = current_time;
        }
    }

    for(int i = 0; i < n; i++){
        turn_around_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turn_around_time[i] - burst_time[i];
    }

    float average_TAT = (accumulate(turn_around_time.begin(), turn_around_time.end(), 0.0)) / n;
    float average_WT = (accumulate(waiting_time.begin(), waiting_time.end(), 0.0)) / n;


    cout << "Gantt Chart: \ni";
    for(auto &it : gantt_chart){
        cout << it << " => ";
    }
    cout << "end" << endl;

    cout << "Process\t" << "AT\t" << "BT\t" << "CT\t"
         << "TAT\t" << "WT\t" << endl;
    
    
    for(int i = 0; i < n; i++){
        cout << process[i] << "\t"
            << arrival_time[i] << "\t"
            << burst_time[i] << "\t"
            << completion_time[i] << "\t"
            << turn_around_time[i] << "\t"
            << waiting_time[i] << "\n";
    }
    cout << endl << endl;


    cout << "Average TAT: " << average_TAT << endl;
    cout << "Average WT: " << average_WT << endl;

    return 0;
}