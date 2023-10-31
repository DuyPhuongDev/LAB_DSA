#include<iostream>
#include<queue>
#include<vector>
#include<stdlib.h>
#include<time.h>
using namespace std;

int dx[4] = {-1,0,0,1};
int dy[4] = {0,-1,1,0};
bool visited[500][500] = {false};
bool isValid(int i, int j, vector<vector<int>> grid){
    return i>-1 && j>-1 && i<grid.size() && j<grid[0].size();
}

void bfs(int i, int j, vector<vector<int>> grid){
    queue<pair<int, int>> q;
    q.push(make_pair(i,j));
    visited[i][j]=true;
    while(!q.empty()){
        pair<int, int> cur = q.front(); q.pop();
        for(int k=0;k<4;k++){
            int i1 = i + dx[k];
            int j1 = j + dy[k];
            if(isValid(i1,j1,grid) && !visited[i1][j1] && grid[i1][j1]==1){
                q.push({i1,j1});
                visited[i1][j1]=true;
            }
        }
    }

}

int secondsToBeRotten(vector<vector<int>>& grid) {
    int sec = 0;
    int row = grid.size();
    int col = grid[0].size();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){

        }
    }

    return sec;
}

int main(){
    int rows, cols;
    cin >> rows >> cols;
    srand(time(NULL));
    vector<vector<int>> grid(rows, vector<int>(cols));
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) grid[i][j] = rand()%3;
    }

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) cout<<grid[i][j]<<" ";
        cout<<endl;
    }
    cout << secondsToBeRotten(grid);
    return 0;
}