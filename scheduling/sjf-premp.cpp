#include<bits/stdc++.h>

using namespace std;

struct process{
    int id,burst,arr,wt,tt,ct;
};

struct GanttEntry{
    int pid;
    int start;
    int end;
};

bool com(process &a, process &b){
    if(a.arr==b.arr) return a.id<b.id;
    return a.arr<b.arr;
}

void calculate(vector<process>&pr, vector<GanttEntry>&gantt){
    int n = pr.size();
    vector<int> rem(n);
    for(int i = 0; i < n; i++) rem[i] = pr[i].burst;

    int time = 0;
    int done = 0;

    while(done < n){
        int pick = -1;

        // Pick process with shortest remaining time among arrived processes.
        for(int i = 0; i < n; i++){
            if(pr[i].arr <= time && rem[i] > 0){
                if(pick == -1 || rem[i] < rem[pick] || (rem[i] == rem[pick] && pr[i].id < pr[pick].id)){
                    pick = i;
                }
            }
        }

        int runPid = 0;
        if(pick != -1){
            rem[pick]--;
            runPid = pr[pick].id;
            if(rem[pick] == 0){
                pr[pick].ct = time + 1;
                done++;
            }
        }

        // Merge adjacent same-process entries in Gantt chart.
        if(gantt.empty() || gantt.back().pid != runPid){
            gantt.push_back({runPid, time, time + 1});
        }else{
            gantt.back().end = time + 1;
        }

        time++;
    }

    for(int i = 0; i < n; i++){
        pr[i].tt = pr[i].ct - pr[i].arr;
        pr[i].wt = pr[i].tt - pr[i].burst;
    }
}

int main(){
    int n;
    cout<<"Enter number of process: ";
    cin>>n;
    vector<process>pr(n);
    for(int i=0;i<n;i++){
        cout<<"Enter arrival time, burst time for process "<<i+1<<" : ";
        cin>>pr[i].arr>>pr[i].burst;
        pr[i].id = i+1;
    }
    sort(pr.begin(),pr.end(),com);
    vector<GanttEntry> gantt;
    calculate(pr,gantt);

    cout << "\nGantt Chart:\n";
    for(auto &g : gantt){
        if(g.pid == 0) cout << "[IDLE: " << g.start << "-" << g.end << "] ";
        else cout << "[P" << g.pid << ": " << g.start << "-" << g.end << "] ";
    }
    cout << "\n\n";

    cout << "Process Arrival Burst Completion Waiting Turnaround\n";
    for(auto x:pr){
        cout << "P" << x.id << "\t"
             << x.arr << "\t"
             << x.burst << "\t"
             << x.ct << "\t   "
             << x.wt << "\t   "
             << x.tt << endl;
    }
}