#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    bool searchMatrix(vector<vector<int>> &mat, int target){
        int R = mat.size(), C = mat[0].size();
        int low = 0, high = (R*C)-1;
        while(low<=high){
            int mid = low + (high-low)/2;
            int i = (mid/C), j = (mid%C);
            if(mat[i][j]==target)return true;
            else if(mat[i][j]>target)high=mid-1;
            else low = mid+1;
        }
        return false;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> a = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    cout << "search(3)  -> "  << sol.searchMatrix(a, 3)  << "\n"; // 1
    cout << "search(13) -> "  << sol.searchMatrix(a, 13) << "\n"; // 0
    cout << "search(60) -> "  << sol.searchMatrix(a, 60) << "\n"; // 1

    return 0;
}
