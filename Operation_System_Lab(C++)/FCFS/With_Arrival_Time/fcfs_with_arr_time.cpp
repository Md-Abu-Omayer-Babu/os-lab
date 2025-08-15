#include<bits/stdc++.h>
using namespace std;

int main(){
    freopen("2.txt", "r", stdin);

    int n;
    cin >> n;
    
    vector<string> process, grantt;
    vector<int> burst_time, arrival_time, completion_time(n), turn_around_time(n), waiting_time(n);

    for(int i = 0; i < n; i++){
        string proc;
        int arrtime, bursttime;

        cin >> proc;
        cin >> arrtime >> bursttime;

        process.push_back(proc);
        arrival_time.push_back(arrtime);
        burst_time.push_back(bursttime);
    }



    // sort
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(arrival_time[i] > arrival_time[j]){
                swap(process[i], process[j]);
                swap(arrival_time[i], arrival_time[j]);
                swap(burst_time[i], burst_time[j]);
            }
        }
    }
    
    if(arrival_time[0] != 0){
        grantt.push_back("idle");
    }
    
    completion_time[0] = arrival_time[0] + burst_time[0];
    grantt.push_back(process[0]);

    for(int i = 1; i < n; i++){
        if(completion_time[i - 1] >= arrival_time[i]){
            grantt.push_back(process[i]);
            completion_time[i] = completion_time[i - 1] + burst_time[i];
        }else{
            grantt.push_back("idle");
            completion_time[i] = arrival_time[i] + burst_time[i];
        }
    }
    

    // tat, wt
    for(int i = 0; i < n; i++){
        turn_around_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turn_around_time[i] - burst_time[i];
    }

    for(auto p : grantt){
        cout << p << " => ";
    }
    cout << "end" << endl;

    float average_TAT = (accumulate(turn_around_time.begin(), turn_around_time.end(), 0.0)) / n;
    float average_WT = (accumulate(waiting_time.begin(), waiting_time.end(), 0.0)) / n;


    cout << "Process\t" << "BT\t" << "CT\t" << "TT\t" << "WT\t" << endl;

    for(int i = 0; i < n; i++){
        cout << process[i]  << "\t" << burst_time[i] << "\t" << completion_time[i] << "\t" << turn_around_time[i] << "\t" << waiting_time[i] << "\t" << endl << endl;
    }


    cout << "Average Turn Around Time: " << average_TAT << endl << endl;
    cout << "Average Waiting Time: " << average_WT << endl << endl;

    return 0;
}