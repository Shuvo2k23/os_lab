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

void calculate(vector<Process>&pr, vector<GanttEntry>&gantt, bool preemptive){
    int n = pr.size();
    int time = 0;
    int done = 0;

    if(preemptive){
        vector<int> rem(n);
        for(int i = 0; i < n; i++) rem[i] = pr[i].burst;

        while(done < n){
            int pick = -1;

            // Pick process with highest priority (lower value) among arrived processes.
            for(int i = 0; i < n; i++){
                if(pr[i].arr <= time && rem[i] > 0){
                    if(pick == -1 || pr[i].pr < pr[pick].pr ||
                       (pr[i].pr == pr[pick].pr )){
                        pick = i;
                    }
                }
            }

            int runPid = 0; // initially choose idle
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
    }else{
        vector<bool> finished(n, false);

        while(done < n){
            int pick = -1;

            for(int i = 0; i < n; i++){
                if(!finished[i] && pr[i].arr <= time){
                    if(pick == -1 || pr[i].pr < pr[pick].pr ||
                       (pr[i].pr == pr[pick].pr && pr[i].arr < pr[pick].arr) ){
                        pick = i;
                    }
                }
            }

            if(pick == -1){     //for Idle period
                int nextArr = INT_MAX;
                for(int i = 0; i < n; i++){
                    if(!finished[i]) nextArr = min(nextArr, pr[i].arr);
                }
                if(nextArr > time){
                    if(!gantt.empty() && gantt.back().pid == 0){
                        gantt.back().end = nextArr;
                    }else{
                        gantt.push_back({0, time, nextArr});
                    }
                    time = nextArr;
                }
                continue;
            }

            int start = time;
            time += pr[pick].burst;
            gantt.push_back({pr[pick].id, start, time});

            pr[pick].ct = time;
            finished[pick] = true;
            done++;
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
    cout<<"Enter number of process: ";
    cin>>n;

    int mode;
    cout<<"Enter mode (1 = preemptive, 2 = non-preemptive): ";
    cin>>mode;
    bool preemptive = (mode == 1);

    vector<Process>pr(n);
    for(int i=0;i<n;i++){
        cout<<"Enter arrival time, burst time, priority for process "<<i+1<<" : ";
        cin>>pr[i].arr>>pr[i].burst>>pr[i].pr;
        pr[i].id = i+1;
    }

    sort(pr.begin(),pr.end(),com);

    vector<GanttEntry> gantt;
    calculate(pr, gantt, preemptive);
    printGantt(gantt);
    printTable(pr);
}