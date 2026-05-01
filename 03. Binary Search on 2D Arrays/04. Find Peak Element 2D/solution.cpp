#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMaxElementIdx(vector<vector<int>>& mat, int R, int col){
        int result = -1, maxi = INT_MIN;
        for(int i=0;i<R;i++){
            if(mat[i][col]>maxi){
                maxi = mat[i][col];
                result = i;
            }
        }
        return result;
    }
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int R = mat.size(), C = mat[0].size();
        int low = 0, high = C-1;
        while(low<=high){
            int mid = low + (high-low)/2;
            int idx = findMaxElementIdx(mat,R,mid);

            int left = (mid-1>=0)?mat[idx][mid-1]:-1;
            int right = (mid+1<C)?mat[idx][mid+1]:-1;


            if(mat[idx][mid]>left && mat[idx][mid]>right)return {idx,mid};
            else if(mat[idx][mid]<left)high = mid-1;
            else low = mid+1;
        }
        return {-1,-1};
    }
};

int main() {
    Solution sol;

    vector<vector<int>> a = {{1,4},{3,2}};
    auto p1 = sol.findPeakGrid(a);
    cout << "peak in [[1,4],[3,2]] -> (" << p1[0] << "," << p1[1] << ")\n"; // (0,1) — value 4

    vector<vector<int>> b = {{10,20,15},{21,30,14},{ 7,16,32}};
    auto p2 = sol.findPeakGrid(b);
    cout << "peak -> (" << p2[0] << "," << p2[1] << ") value=" << b[p2[0]][p2[1]] << "\n";

    vector<vector<int>> c = {{1,2,3,4,5}};
    auto p3 = sol.findPeakGrid(c);
    cout << "peak in single-row -> (" << p3[0] << "," << p3[1] << ")\n"; // (0,4)

    return 0;
}
