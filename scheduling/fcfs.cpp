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
    int current_time = 0;

    for(auto &proc : pr){
        if(current_time < proc.arr){
            if(!gantt.empty() && gantt.back().pid == 0){
                gantt.back().end = proc.arr;
            }else{
                gantt.push_back({0, current_time, proc.arr});
            }
            current_time = proc.arr;
        }

        int start = current_time;
        current_time += proc.burst;
        gantt.push_back({proc.id, start, current_time});

        proc.ct = current_time;
        proc.tt = proc.ct - proc.arr;
        proc.wt = proc.tt - proc.burst;
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
    calculate(pr, gantt);
    printGantt(gantt);
    printTable(pr);
}