#include <queue>
#include <iostream>
#include <set>
#include <unordered_map>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct file
{
	int priority;
	string filename;
	file(int priority, string filename): priority(priority), filename(filename){}
};

class maxheap{
private:
    vector<file*> v;
protected:
    bool compare(file* a, file* b){
		return a->priority>b->priority;
	}
    void reheapUp(int pos){
       int par = (pos-1)/2;
       if(pos>0 && compare(v[pos], v[par])){
            swap(v[par], v[pos]);
            reheapUp(par);
       } 
    }
    void reheapDown(int pos){
        int l = pos*2+1;
        int r = pos*2+2;
        int sm = pos;
        if(l<v.size() && compare(v[l], v[sm])) sm = l;
        if(r<v.size() && compare(v[r], v[sm])) sm = r;
        if(sm!=pos){
            swap(v[sm], v[pos]);
            reheapDown(sm);
        }
    }
public:
    void insert(file* item){
        v.push_back(item);
        reheapUp(v.size()-1);
    }
    bool isEmpty(){return v.size()?0:1;}
    file* pop(){
        if(v.empty()) return nullptr;
        file* item = v[0];
        swap(v[0], v.back());
        v.pop_back();
        reheapDown(0);
        return item;
    }
};
class PrinterQueue
{
    // your attributes
	maxheap heap;
	
public:
    // your methods
    //PrinterQueue(){ heap = new maxheap();}
    void addNewRequest(int priority, string fileName)
    {
        // your code here
		file *item = new file(priority, fileName);
		heap.insert(item);
    }

    void print()
    {
        // your code here
        // After some logic code, you have to print fileName with endline 
		if(heap.isEmpty()){
			cout<<"No file to print\n";
			return;
		}
		file* item = heap.pop();
		cout<<item->filename<<"\n";
    }
};



int leastAfter(vector<int>& nums, int k) {
    // STUDENT ANSWER
    multiset<int> mlts(nums.begin(), nums.end());
    
    while(k>0){
        int item = *mlts.begin();
        mlts.erase(mlts.begin());
        mlts.insert(item*2);
        --k;
    }
    return *mlts.begin();
}
bool findPairs(int arr[], int n, pair<int,int>& pair1, pair<int, int>& pair2){
   // TODO: If there are two pairs satisfy the condition, assign their values to pair1, pair2 and return true. Otherwise, return false.
   unordered_map<int, pair<int, int>> umap;
   bool flag = false;
   for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
        int sum = arr[i]+arr[j];
        if(umap.find(sum)==umap.end()){
            // don't find
            umap[sum]={arr[i], arr[j]};
        }else{
            pair1 = {umap[sum].first, umap[sum].second};
            pair2 = {arr[i], arr[j]};
            flag = true;
        }
    }
   }
   return flag;
}

int reduceSum(vector<int>& nums) {
    // STUDENT ANSWER
    int cost=0;
    multiset<int> mlts(nums.begin(), nums.end());
    while(mlts.size()>1){
        // pick num1
        int item1 = *mlts.begin();
        mlts.erase(mlts.begin());
        // pick num2
        int item2 = *mlts.begin();
        mlts.erase(mlts.begin());
        cost += (item1+item2);
        mlts.insert(item1+item2);
    }
    return cost;
}
int maxDivide(int a, int b)
{
    while (a % b == 0)
        a = a / b;
         
    return a;
}
bool isUgly(vector<int>v, int n){
    for(unsigned int i=0; i<v.size();++i){
        n = maxDivide(n, v[i]);
    }
    return n==1?1:0;
}
int uglyNumberIndex(int n) {
    // STUDENT ANSWER
    vector<int> v{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    int i = 1;
     
    // Ugly number count
    int count = 1; 
 
    // Check for all integers until ugly
    // count becomes n
    while (n >= count) {
        i++;
        if (isUgly(v,i)) count++;
    }
    return i;
}
int main(){
	clock_t start, end;
    double duration;
    start = clock();
    int n = 100000;
    cout << uglyNumberIndex(n)<<endl;
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("interchangeSort take %f seconds", duration);
return 0;
}