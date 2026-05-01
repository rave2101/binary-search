#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
 bool searchMatrix(vector<vector<int>> &matrix, int target){
      int R = matrix.size(), C = matrix[0].size();
      int i = 0, j = C-1;
      while(i>=0 && i<R && j>=0 && j<C){
        if(matrix[i][j]==target)return true;
        if(matrix[i][j]<target)i++;
        else j--;
      }
      return false;
 }
};

int main() {
    Solution sol;

    vector<vector<int>> a = {
        {1, 4, 7,11,15},
        {2, 5, 8,12,19},
        {3, 6, 9,16,22},
        {10,13,14,17,24},
        {18,21,23,26,30}
    };
    cout << "search(5)  -> " << sol.searchMatrix(a, 5)  << "\n"; // 1
    cout << "search(20) -> " << sol.searchMatrix(a, 20) << "\n"; // 0
    cout << "search(30) -> " << sol.searchMatrix(a, 30) << "\n"; // 1

    return 0;
}
