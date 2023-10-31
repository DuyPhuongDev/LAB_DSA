#include<iostream>
#include<queue>
#include<vector>
#include<stdlib.h>
#include<time.h>
using namespace std;

bool isValid(int i, int j, vector<vector<int>> grid){
    return i>-1 && j>-1 && i<grid.size() && j<grid[0].size();
}

int secondsToBeRotten(vector<vector<int>>& grid) {
    int sec = 0;
    int row = grid.size();
    int col = grid[0].size();
    vector<vector<bool>> visited(row,vector<bool>(col,false));
    queue<pair<int,int>> rotAp;
    int freshA=0; // num of Fresh Apple in grid

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(grid[i][j]==2) { rotAp.push({i,j});}
            else if(grid[i][j]==1) freshA++;
        }
    }
    
    int dx[4] = {-1,0,0,1};
    int dy[4] = {0,-1,1,0};
    while(!rotAp.empty()){
        sec++;
        int turn = rotAp.size();
        while(turn>0){
            pair<int,int> v = rotAp.front(); rotAp.pop();
            visited[v.first][v.second]=true;
            for(int k=0;k<4;k++){
                int i=v.first+dx[k];
                int j=v.second+dy[k];
                if(isValid(i,j,grid) && !visited[i][j] && grid[i][j]==1){
                    rotAp.push({i,j});
                    grid[i][j]=2;
                    freshA--;
                }
                if(!freshA) return sec;
            }
            turn--;
        }
    }
    if(freshA) sec=-1;
    return sec;
}

int main(){
	
    int rows, cols;
    cin >> rows >> cols;
    vector<vector<int>> grid(rows, vector<int>(cols));
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) cin >> grid[i][j];
    }
    cout << secondsToBeRotten(grid);
    return 0;
}