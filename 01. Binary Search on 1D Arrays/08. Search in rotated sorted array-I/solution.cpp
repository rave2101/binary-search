#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int> &nums, int k) {
       int SIZE = nums.size();
       int low = 0, high = SIZE-1;
       while(low<=high){
            int mid = low + (high-low)/2;
            if(nums[mid]==k)return mid;

            if(nums[low]<=nums[mid]){
                if(k>=nums[low] && k<nums[mid])high = mid-1;
                else low = mid+1;
            }
            else{
                if(k>nums[mid] && k<=nums[high])low = mid+1;
                else high = mid-1;
            }
        }
        return -1;
    }
};

int main() {
    Solution sol;

    vector<int> a = {4, 5, 6, 7, 0, 1, 2};
    cout << "k=0 in [4,5,6,7,0,1,2]   -> " << sol.search(a, 0) << "\n"; // 4
    cout << "k=4 in [4,5,6,7,0,1,2]   -> " << sol.search(a, 4) << "\n"; // 0
    cout << "k=2 in [4,5,6,7,0,1,2]   -> " << sol.search(a, 2) << "\n"; // 6
    cout << "k=3 in [4,5,6,7,0,1,2]   -> " << sol.search(a, 3) << "\n"; // -1

    vector<int> b = {1, 3};
    cout << "k=3 in [1,3]             -> " << sol.search(b, 3) << "\n"; // 1

    vector<int> c = {5, 1, 2, 3, 4};
    cout << "k=1 in [5,1,2,3,4]       -> " << sol.search(c, 1) << "\n"; // 1

    vector<int> d = {1};
    cout << "k=0 in [1]               -> " << sol.search(d, 0) << "\n"; // -1

    return 0;
}
