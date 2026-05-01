#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int> &nums)  {
      int ans = INT_MAX, SIZE = nums.size();
      int low = 0, high = SIZE-1, result = SIZE-1;
      while(low<=high){
        int mid = low + (high-low)/2;
        if(nums[low]<=nums[mid]){
            int mini = min(nums[low],nums[mid]);
            if(ans>mini){
                ans = mini;
                result = (mini == nums[low])?low:mid;
            }
            low = mid+1;
        }
        else{
            int mini = min(nums[mid],nums[high]);
            if(ans>mini){
                ans = mini;
                result = (mini == nums[mid])?mid:high;
            }
            high = mid-1;
        }
      }//end while
      return result;
    }
    int findKRotation(vector<int> &nums)  {
        int minIdx = findMin(nums);
        return minIdx;
    }
};

int main() {
    Solution sol;

    vector<int> a = {4, 5, 6, 7, 0, 1, 2};
    cout << "k for [4,5,6,7,0,1,2]   -> " << sol.findKRotation(a) << "\n"; // 4

    vector<int> b = {3, 4, 5, 1, 2};
    cout << "k for [3,4,5,1,2]       -> " << sol.findKRotation(b) << "\n"; // 3

    vector<int> c = {11, 13, 15, 17};
    cout << "k for [11,13,15,17]     -> " << sol.findKRotation(c) << "\n"; // 0 (no rotation)

    vector<int> d = {2, 1};
    cout << "k for [2,1]             -> " << sol.findKRotation(d) << "\n"; // 1

    vector<int> e = {1};
    cout << "k for [1]               -> " << sol.findKRotation(e) << "\n"; // 0

    vector<int> f = {5, 1, 2, 3, 4};
    cout << "k for [5,1,2,3,4]       -> " << sol.findKRotation(f) << "\n"; // 1

    return 0;
}
