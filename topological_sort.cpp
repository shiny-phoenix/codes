#include<bits/stdc++.h>
using namespace std;
vector<int>arr[1000];
int ind[1000];
int n,m;

int main(){
	
	cout<<"enter the no. of nodes : ";
	cin>>n;
	cout<<"enter the no. of edges : ";
	cin>>m;
	for(int i=0;i<m;i++){
		int a,b;
		cin>>a>>b;
		arr[a].push_back(b);
		ind[b]++;
	}
	queue<int>q;
	for(int i=0;i<n;i++){
		if(ind[i]==0){
			q.push(i);
		}
	}
	cout<<"Topological sort :"; 
	while(!q.empty()){
		int ver=q.front();
		q.pop();
		for(int i=0;i<arr[ver].size();i++){
			ind[arr[ver][i]]--;
			if(ind[arr[ver][i]]==0){
				q.push(arr[ver][i]);
			}
		}
		cout<<ver<<" ";
	}
	return 0;
}
