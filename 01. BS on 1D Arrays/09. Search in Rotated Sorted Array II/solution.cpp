#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool searchInARotatedSortedArrayII(vector<int> &nums, int k)  {
       int SIZE = nums.size();
       int low = 0, high = SIZE-1;
       while(low<=high){
            int mid = low + (high-low)/2;
            if(nums[mid]==k)return true;
            if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
                low++;
                high--;
                continue;
            }

            if(nums[low]<=nums[mid]){
                if(k>=nums[low] && k<nums[mid])high = mid-1;
                else low = mid+1;
            }
            else{
                if(k>nums[mid] && k<=nums[high])low=mid+1;
                else high = mid-1;
            }
       }//end while
       return false;
    }
};

int main() {
    Solution sol;

    vector<int> a = {2, 5, 6, 0, 0, 1, 2};
    cout << "k=0 in [2,5,6,0,0,1,2]         -> " << boolalpha << sol.searchInARotatedSortedArrayII(a, 0) << "\n"; // true
    cout << "k=3 in [2,5,6,0,0,1,2]         -> " << boolalpha << sol.searchInARotatedSortedArrayII(a, 3) << "\n"; // false

    vector<int> b = {1, 0, 1, 1, 1};
    cout << "k=0 in [1,0,1,1,1]             -> " << boolalpha << sol.searchInARotatedSortedArrayII(b, 0) << "\n"; // true
    cout << "k=2 in [1,0,1,1,1]             -> " << boolalpha << sol.searchInARotatedSortedArrayII(b, 2) << "\n"; // false

    vector<int> c = {3, 1, 2, 3, 3, 3, 3};
    cout << "k=2 in [3,1,2,3,3,3,3]         -> " << boolalpha << sol.searchInARotatedSortedArrayII(c, 2) << "\n"; // true
    cout << "k=4 in [3,1,2,3,3,3,3]         -> " << boolalpha << sol.searchInARotatedSortedArrayII(c, 4) << "\n"; // false

    vector<int> d = {1};
    cout << "k=1 in [1]                     -> " << boolalpha << sol.searchInARotatedSortedArrayII(d, 1) << "\n"; // true

    vector<int> e;
    cout << "k=0 in []                      -> " << boolalpha << sol.searchInARotatedSortedArrayII(e, 0) << "\n"; // false

    return 0;
}
