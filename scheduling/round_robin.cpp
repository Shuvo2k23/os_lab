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

void calculate(vector<Process>&pr, vector<GanttEntry>&gantt, int quantum){
    int n = pr.size();
    vector<int> rem(n);
    for(int i = 0; i < n; i++) rem[i] = pr[i].burst;

    int time = 0;
    int done = 0;
    queue<int> readyQ;   // indices into pr[]
    int nextCheck = 0;   // index of next Process (sorted by arrival) to enqueue

    // Enqueue all Processes that have already arrived at time 0.
    while(nextCheck < n && pr[nextCheck].arr <= time){
        readyQ.push(nextCheck);
        nextCheck++;
    }

    while(done < n){
        if(readyQ.empty()){
            // CPU is idle; jump to next arrival.
            int runLen = pr[nextCheck].arr - time;
            gantt.push_back({0, time, pr[nextCheck].arr});
            time = pr[nextCheck].arr;
            // Enqueue all Processes arriving at this time.
            while(nextCheck < n && pr[nextCheck].arr <= time){
                readyQ.push(nextCheck);
                nextCheck++;
            }
            continue;
        }

        int idx = readyQ.front();
        readyQ.pop();

        // Run for min(quantum, remaining burst).
        int slice = min(quantum, rem[idx]);
        int start = time;
        time += slice;
        rem[idx] -= slice;

        // Merge or append Gantt entry.
        if(!gantt.empty() && gantt.back().pid == pr[idx].id){
            gantt.back().end = time;
        }else{
            gantt.push_back({pr[idx].id, start, time});
        }

        // Enqueue newly arrived Processes during this slice (before re-queuing current).
        while(nextCheck < n && pr[nextCheck].arr <= time){
            readyQ.push(nextCheck);
            nextCheck++;
        }

        if(rem[idx] == 0){
            pr[idx].ct = time;
            done++;
        }else{
            // Re-enqueue current Process at the back.
            readyQ.push(idx);
        }
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
    cout<<"Enter number of Process: ";
    cin>>n;
    vector<Process>pr(n);
    for(int i=0;i<n;i++){
        cout<<"Enter arrival time, burst time for Process "<<i+1<<" : ";
        cin>>pr[i].arr>>pr[i].burst;
        pr[i].id = i+1;
        pr[i].pr = 0;
    }

    int quantum;
    cout<<"Enter time quantum: ";
    cin>>quantum;

    sort(pr.begin(),pr.end(),com);

    vector<GanttEntry> gantt;
    calculate(pr, gantt, quantum);
    printGantt(gantt);
    printTable(pr);
}
