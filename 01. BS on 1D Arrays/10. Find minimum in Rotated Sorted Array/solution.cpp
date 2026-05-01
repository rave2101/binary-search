#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int> &nums)  {
      int ans = INT_MAX, SIZE = nums.size();
      int low = 0, high = SIZE-1;
      while(low<=high){
        int mid = low + (high-low)/2;
        if(nums[low]<=nums[mid]){
            ans=min({ans,nums[low],nums[mid]});
            low = mid+1;
        }
        else{
            ans=min({ans,nums[mid],nums[high]});
            high = mid-1;
        }
      }//end while
      return ans;
    }
};

int main() {
    Solution sol;

    vector<int> a = {4, 5, 6, 7, 0, 1, 2};
    cout << "min of [4,5,6,7,0,1,2]   -> " << sol.findMin(a) << "\n"; // 0

    vector<int> b = {3, 4, 5, 1, 2};
    cout << "min of [3,4,5,1,2]       -> " << sol.findMin(b) << "\n"; // 1

    vector<int> c = {11, 13, 15, 17};
    cout << "min of [11,13,15,17]     -> " << sol.findMin(c) << "\n"; // 11 (no rotation)

    vector<int> d = {2, 1};
    cout << "min of [2,1]             -> " << sol.findMin(d) << "\n"; // 1

    vector<int> e = {1};
    cout << "min of [1]               -> " << sol.findMin(e) << "\n"; // 1

    vector<int> f = {5, 1, 2, 3, 4};
    cout << "min of [5,1,2,3,4]       -> " << sol.findMin(f) << "\n"; // 1

    return 0;
}
