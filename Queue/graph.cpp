#include<iostream>
#include<vector>
#include<queue>
#include<deque>
using namespace std;

bool isBipartite(vector<vector<int>> graph) {
    int color[10001] = {0}; // 2:red 1:blue 0:none
    queue<int> q;
    
    int n = graph.size();

    for( int i = 0;i<n;i++){
        if(q.empty()){
            q.push(i);
            color[q.front()]==2;
        }else{
            while(!q.empty()){
                int v = q.front(); q.pop(); // get vertical from q
                for(int x : graph[v]){
                if(color[x]==0) {
                        color[x] = color[v]==1? 2:1;
                        q.push(x);
                }
                else if(color[x] == color[v]) return false;
                }
            }
        }

        
    }
    return true;
}

void bfs(vector<vector<int>> graph, int start) {
	int visited[1001]={0};
    queue<int> q;

    q.push(start);
    visited[start] =1;
    while(!q.empty()){
        cout<<q.front()<<" ";
        int v = q.front(); q.pop();
        for( int x:graph[v]){
            if(!visited[x]){
                visited[x]=1;
                q.push(x);
            }
        }
    }
    cout<<'\n';
}

int secondsToBeRotten(vector<vector<int>>& grid) {
    bool visited[1001]={0}; // all cell was not visited
    queue<int> q;
    return 0;
}

int sumOfMaxSubarray(vector<int>& nums, int k) {
    // STUDENT ANSWER
    int max = 0;
    deque<int> dq;
    for(int i=0;i<k;i++) {
        max+=nums[i];
        dq.push_back(nums[i]);
    }

    int curMax = max;
    for(int i=k;i<nums.size();i++){
        curMax+=nums[i];
        curMax-=dq.front();
        max = curMax>max? curMax:max;
        dq.push_back(nums[i]);
    }
    return max;
}

int  main(){
	
vector<int> nums {8016};
int k = 1;
cout << sumOfMaxSubarray(nums, k);
    return 0;
}