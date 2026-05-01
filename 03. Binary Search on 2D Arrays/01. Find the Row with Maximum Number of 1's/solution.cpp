#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int lowerBound(vector<int>&temp, int SIZE, int X){
    int low = 0, high = SIZE-1, firstOne = -1;
    while(low<=high){
        int mid = low + (high-low)/2;
        if(temp[mid]>=X){
            firstOne = mid;
            high=mid-1;
        }
        else{
            low = mid+1;
        }
    }//end while
    //cout<<SIZE-track<<endl;
    return (firstOne==-1)?0:SIZE-firstOne;
  }
  int rowWithMax1s(vector < vector < int >> & mat) {
    int R = mat.size(), C = mat[0].size(), maxi = 0, result=-1;
    for(int i=0;i<R;i++){
        //maxi = max(maxi,util(mat[i],C));
        int current = lowerBound(mat[i],C,1);
        if(current>maxi){
            maxi = current;
            result = i;
        }
    }
    return result;
  }
};

int main() {
    Solution sol;

    vector<vector<int>> a = {{0,1,1,1},{0,0,1,1},{1,1,1,1},{0,0,0,0}};
    cout << "rowWithMax1s -> " << sol.rowWithMax1s(a) << "\n"; // 2

    vector<vector<int>> b = {{0,0},{0,0}};
    cout << "rowWithMax1s (all zeros) -> " << sol.rowWithMax1s(b) << "\n"; // -1

    vector<vector<int>> c = {{0,0,0,1},{0,0,0,0},{0,0,1,1}};
    cout << "rowWithMax1s -> " << sol.rowWithMax1s(c) << "\n"; // 2

    return 0;
}
