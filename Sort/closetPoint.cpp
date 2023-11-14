#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Point{
   public:
   int x, y;
   Point(int x = 0, int y = 0){
      this->x = x;
      this->y = y;
   }
   void display(){
      cout << "("<<x<<", "<<y<<")";
   }
};
/* Your helping functions go here */
double calDis(Point a, Point b){
    double x=b.x-a.x;
    double y = b.y-a.y;
    return sqrt(pow(x,2)+pow(y,2));
}
bool compare(pair<Point,double>a, pair<Point, double>b){
    return a.second<b.second;
}
void closestKPoints(Point points[], int n, Point &des_point, int k){
    //TODO
    vector<pair<Point,double>> v;
    for(int i=0;i<n;++i){
        double dis = calDis(des_point,points[i]);
        v.push_back({points[i],dis});
    }

    stable_sort(v.begin(), v.end(), compare);
    for(int i=0;i<k;++i){
        v[i].first.display();
        cout<<endl;
    }
}

int main(){
    Point points[] = {{3, 3},{5, -1},{-2, 4}};
int n = sizeof(points)/sizeof(points[0]);
int k = 2;
Point des_point = {0,2};
closestKPoints(points, n, des_point, k);
return 0;
}