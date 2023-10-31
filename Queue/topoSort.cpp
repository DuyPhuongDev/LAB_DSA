#include<iostream>
#include<queue>
#include<vector>
#include<stdlib.h>
#include<time.h>
using namespace std;

vector<int> topologicalSorting(vector<vector<int>> graph) {
    vector<int> indegree(graph.size(),0); // mang luu tru ban bac vao
    queue<int> q; // hang doi luu tru cac vertical
    vector<int> topo;
    for(int i=0;i<graph.size();i++){
        for(int v:graph[i]) indegree[v]++;
    }

    for(int i=0;i<graph.size();i++) if(!indegree[i]) q.push(i);

    while(!q.empty()){
        int v = q.front(); q.pop();
        topo.push_back(v);
        for( int x : graph[v]){
            indegree[x]--;
            if(!indegree[x]) q.push(x);
        }
    }
    if(topo.size()<graph.size()) topo.clear();
    return topo;
}
int main(){
    int n; cin>>n;
    srand(time(NULL));
    vector<vector<int>> G(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
           G[i][j] = rand()%2;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
           cout<<G[i][j]<<" ";
        }
        cout<<endl;
    }

    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (G[i][j] == 1) graph[i].push_back(j);
        }
    }

    for (int i = 0; i < n; ++i) {
        for(int x:graph[i]) cout<<i<<" "<<x<<endl;
    }
    vector<int> res = topologicalSorting(graph);
    if (res.empty()) printf("-1");
    else {
        for (int e : res) printf("%d ", e);
    }
    return 0;
}