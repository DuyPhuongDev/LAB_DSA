#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;

class node {
public:
    int x, y;
    int dir;
    node(int i, int j)
    {
        x = i;
        y = j;
  
        // Initially direction
        // set to 0
        dir = 0;
    }
};
bool reached(node* curr, int fx, int fy){
    return curr->x==fx && curr->y==fy; // true if mouse reached food
}

bool wayIsvalid(node* way, int maze[5][5], bool check[5][5]){
    return way->x<5 && way->y<5 && way->x>-1 && way->y>-1 && maze[way->x][way->y] && !check[way->x][way->y];
}
bool canEatFood(int maze[5][5], int fx, int fy){
    bool check[5][5]={0};
    stack<node*> visited;
    visited.push(new node(0,0)); // begin 
    check[0][0]=1;
    node* mem = nullptr;
    while(!visited.empty()){
        if(reached(visited.top(), fx, fy)) return true;

        if(visited.top()->dir==0){
            visited.top()->dir++;
            node* way = new node(visited.top()->x-1,visited.top()->y);
            if(wayIsvalid(way,maze,check)) {
                visited.push(way);
                check[way->x][way->y]=1;
            }
            else delete way;
        }else if(visited.top()->dir == 1){
            visited.top()->dir++;
            node* way = new node(visited.top()->x,visited.top()->y-1);
            if(wayIsvalid(way,maze,check)) {
                visited.push(way);
                check[way->x][way->y]=1;
            }
            else delete way;
        }else if(visited.top()->dir == 2){
            visited.top()->dir++;
            node* way = new node(visited.top()->x+1,visited.top()->y);
            if(wayIsvalid(way,maze,check)) {
                visited.push(way);
                check[way->x][way->y]=1;
            }
            else delete way;
        }else if(visited.top()->dir==3){
            visited.top()->dir++;
            node* way = new node(visited.top()->x,visited.top()->y+1);
            if(wayIsvalid(way,maze,check)) {
                visited.push(way);
                check[way->x][way->y]=1;
            }
            else delete way;
        }else if(visited.top()->dir>3) visited.pop();
    }
    return false;
}

int main(){
    // Maze matrix
    int maze[5][5] = {
        { 1, 0, 1, 1, 0 },
        { 1, 1, 1, 0, 1 },
        { 0, 1, 0, 1, 1 },
        { 1, 1, 1, 1, 0 },
        { 1, 0, 0, 1, 0 }
    };

    // Food coordinates
    int fx = 1, fy = 4;

    cout << canEatFood(maze, fx, fy);
    return 0;
}