#include<bits/stdc++.h>
using namespace std;
class Custom{
    public:
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int tat;
    int rt;
    int wt;
};


int main(){
    cout<<"Round robin\n";
    int n;
    cout<<"Enter the number of process\n";
    cin>>n;
    Custom process[n];
    int btime[n];
    int demo[n];
    for(int i=0;i<n;i++){
        cout<<"Enter the arrival time for the process "<<i+1<<"\n";
        cin>>process[i].arrival_time;
        cout<<"Enter the burst time\n";
        cin>>process[i].burst_time;
        btime[i] = process[i].burst_time;
        process[i].pid = i+1;
    }
    queue<int> q;
    int visited[n];
    int start_time = process[0].arrival_time;
    for(int i=0;i<n;i++){
        visited[i] =-1;
        demo[i] =-1;
    }
    for(int i=0;i<n;i++){
        if(process[i].arrival_time <= start_time){
            q.push(i);
            visited[i] = 0;
        }
    }
    
    
    int tq = 2;
    while(!q.empty()){
        int k = q.front();
        if(process[k].burst_time>tq){
            if(visited[k] ==-1){
                visited[k] = start_time;
            }
            if(demo[k] ==-1){
                demo[k]  = start_time;
            }
            start_time +=tq;
            process[k].burst_time -= tq;
            q.pop();
            for(int i=k+1;i<n;i++){
                if(process[i].arrival_time<=start_time && (visited[i] == -1)){
                    visited[i] = start_time; 
                    q.push(i);
                }
            }
            q.push(k);
        }
        else{
            if(visited[k] == -1){
                visited[k] = start_time;
            }
            if(demo[k] == -1){
                demo[k] = start_time;
            }
            start_time += process[k].burst_time;
            process[k].burst_time = 0;
            process[k].completion_time = start_time;
            process[k].tat = process[k].completion_time - process[k].arrival_time;
            process[k].wt = process[k].tat - btime[k];
            process[k].rt = visited[k]- process[k].arrival_time; 
            q.pop();
            for(int i=k+1;i<n;i++){
                if(process[i].arrival_time<=start_time && (visited[i] == -1)){
                    visited[i] = start_time; 
                    q.push(i);
                }
            }
        }
    }
		float awt=0,ata=0;
    for(auto it:visited){cout<<it<<" ";}cout<<"\n";
        cout<<"PID\t AT\t BT\t ct\t TAT\t WT\t RT\n";
        for(int i=0;i<n;i++){
            cout<<process[i].pid<<"\t"<<process[i].arrival_time<<"\t"<<btime[i]<<"\t"<<process[i].completion_time<<"\t"<<process[i].tat<<"\t"<<process[i].wt<<"\t"<<demo[i]-process[i].arrival_time<<"\n";
            awt+=process[i].wt;
            ata+=process[i].tat;
        }
    cout<<"\nAvg waiting time : "<<awt/n;
    cout<<"\nAvg tat : "<<ata/n;
    
    return 0;
}