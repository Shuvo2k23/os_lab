#include<bits/stdc++.h>

using namespace std;

struct Process{
    int id,burst,arr,pr,wt,tt,ct;
};

struct GanttEntry{
    int pid;
    int start;
    int end;
};

bool com(Process &a, Process &b){
    if(a.arr==b.arr) return a.id<b.id;
    return a.arr<b.arr;
}

void calculate(vector<Process>&pr, vector<GanttEntry>&gantt){
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
                if(pick == -1 || rem[i] < rem[pick] ){
                    pick = i;
                }
            }
        }

        int runPid = 0; //initially choose as idle mode
        if(pick != -1){
            rem[pick]--;    //decrement  te remaining time
            runPid = pr[pick].id;   //save pid for gantt chart
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

void printGantt(const vector<GanttEntry>&gantt){
    cout << "\nGantt Chart:\n";
    for(auto &g : gantt){
        if(g.pid == 0) cout << "[IDLE: " << g.start << "-" << g.end << "] ";
        else cout << "[P" << g.pid << ": " << g.start << "-" << g.end << "] ";
    }
    cout << "\n\n";
}

void printTable(const vector<Process>&pr){
    cout << "Process Arrival Burst Priority Completion Waiting Turnaround\n";
    for(auto x:pr){
        cout << "P" << x.id << "\t"
             << x.arr << "\t"
             << x.burst << "\t"
             << x.pr << "\t   "
             << x.ct << "\t   "
             << x.wt << "\t   "
             << x.tt << endl;
    }

    double avgWt = 0, avgTt = 0;
    for(auto x:pr){ avgWt += x.wt; avgTt += x.tt; }
    cout << "\nAverage Waiting Time   : " << fixed << setprecision(2) << avgWt/pr.size() << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << avgTt/pr.size() << endl;
}

int main(){
    int n;
    cout<<"Enter number of process: ";
    cin>>n;
    vector<Process>pr(n);
    for(int i=0;i<n;i++){
        cout<<"Enter arrival time, burst time for process "<<i+1<<" : ";
        cin>>pr[i].arr>>pr[i].burst;
        pr[i].id = i+1;
        pr[i].pr = 0;
    }
    sort(pr.begin(),pr.end(),com);
    vector<GanttEntry> gantt;
    calculate(pr,gantt);
    printGantt(gantt);
    printTable(pr);
}