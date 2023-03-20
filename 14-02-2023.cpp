#include <bits/stdc++.h>
using namespace std;
bool cmp(pair<int,int>&a,pair<int,int>&b)
{
    return a.second<b.second;
}
int main()
{
    vector<pair<int,int>> arr(5);
    arr[0]={6,2};
    arr[1]={2,5};
    arr[2]={8,1};
    arr[3]={3,0};
    arr[4]={4,4};
    sort(arr.begin(),arr.end(),cmp);
    int turnaroundtime=0;
    int waitingtime=0;
    for(int i=0;i<5;i++)
    {
        waitingtime+=turnaroundtime-arr[i].second;
        turnaroundtime+=arr[i].first;
    }
    cout<<"turnaroundtime : "<<turnaroundtime<<endl;
    cout<<"total waiting time : "<<waitingtime<<endl;
    cout<<"average waiting time : "<<(double)waitingtime/5;
    return 0;
}
















// #include<bits/stdc++.h>
// using namespace std;
// int main()
// {
//     int n,bt,at;
//     string r="P";
//     map<int,pair<string,int>> m;
//     m[2]={"P1",6};
//     m[5]={"P2",2};
//     m[1]={"P3",8};
//     m[0]={"P4",3};
//     m[4]={"P5",4};
//     // cout<<"\nEnter the no of processes in your system : ";
//     // cin>>n;
//     // for(int i=0;i<n;i++)
//     // {
//     //     cout<<"\nEnter Arival Time for Process "<<i+1<<" : ";
// 	// 	cin>>at;
// 	// 	cout<<"\nEnter Burst Time for Process "<<i+1<<" : ";
// 	// 	cin>>bt;
//     //     pair<string,char> temp; 
//     //     temp.first=r+to_string(i+1);
//     //     temp.second=bt;
// 	// 	m[at]=temp;
//     // }
//     // int sum = 0;
// 	// sum = sum + p[0].at;
// 	// for(int i = 0;i<n;i++)
//     // {
// 	// 	sum = sum + p[i].bt;
// 	// 	p[i].ct = sum;
// 	// 	p[i].tat = p[i].ct - p[i].at;
// 	// 	p[i].wt = p[i].tat - p[i].bt;
// 	// 	if(sum<p[i+1].at){
// 	// 		int t = p[i+1].at-sum;
// 	// 		sum = sum+t;
// 	// 	}
// 	// }
//     int sum = 0,ct,tat,wt;
// 	sum = sum + m.begin()->first;
// 	for(auto it:m)
//     {
// 		sum = sum + p[i].bt;
// 		ct = sum;
// 		tat = ct - it.first;
// 		wt = tat - it.second.second;
// 		if(sum<p[i+1].at)
//         {
// 			int t = p[i+1].at-sum;
// 			sum = sum+t;
// 		}
// 	}
//     cout<<"\nProcess        Burst Time        Arrival Time\n";
//     for(auto it:m)
//     {
//         cout<<"\n"<<it.second.first<<"             "<<it.second.second<<"                 "<<it.first;
//     }
//     cout<<endl;
//     return 0;
// }