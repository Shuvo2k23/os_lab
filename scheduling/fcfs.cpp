#include<bits/stdc++.h>

using namespace std;

struct process{
    int id,burst,arr,wt,tt,ct;
};

bool com(process &a, process &b){
    if(a.arr==b.arr) return a.id<b.id;
    return a.arr<b.arr;
}

void calculate(vector<process>&pr){
    int current_time = 0;

    for(auto &proc : pr){
        if(current_time < proc.arr){
            current_time = proc.arr ;
        }

        proc.wt = current_time - proc.arr;
        current_time += proc.burst;
        proc.ct = current_time;
        proc.tt = proc.ct - proc.arr;
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
    calculate(pr);

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