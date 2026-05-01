#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
    [1,2,1,1,4,5,6,7,1,2,3,4]
    */
    int findPeakElement(vector<int> &nums) {
        int SIZE = nums.size();
        if(SIZE==1 || nums[0]>nums[1])return 0;
        if(nums[SIZE-1]>nums[SIZE-2])return SIZE-1;

        int low = 1, high = SIZE-2;
        while(low<=high){
            int mid = low + (high-low)/2;
            if(nums[mid]>nums[mid-1] && nums[mid]>nums[mid+1])return mid;
            if(nums[mid]>nums[mid-1])low = mid+1;
            else high = mid-1;
        }
        return -1;
    }
};

int main() {
    Solution sol;

    vector<int> a = {1, 2, 3, 1};
    cout << "peak in [1,2,3,1]                       -> " << sol.findPeakElement(a) << "\n"; // 2

    vector<int> b = {1, 2, 1, 3, 5, 6, 4};
    cout << "peak in [1,2,1,3,5,6,4]                 -> " << sol.findPeakElement(b) << "\n"; // 1 or 5

    vector<int> c = {1, 2, 1, 1, 4, 5, 6, 7, 1, 2, 3, 4};
    cout << "peak in [1,2,1,1,4,5,6,7,1,2,3,4]       -> " << sol.findPeakElement(c) << "\n"; // 1, 7, or 11

    vector<int> d = {1};
    cout << "peak in [1]                             -> " << sol.findPeakElement(d) << "\n"; // 0

    vector<int> e = {2, 1};
    cout << "peak in [2,1]                           -> " << sol.findPeakElement(e) << "\n"; // 0

    vector<int> f = {1, 2};
    cout << "peak in [1,2]                           -> " << sol.findPeakElement(f) << "\n"; // 1

    vector<int> g = {1, 2, 3, 4, 5};
    cout << "peak in [1,2,3,4,5]                     -> " << sol.findPeakElement(g) << "\n"; // 4

    vector<int> h = {5, 4, 3, 2, 1};
    cout << "peak in [5,4,3,2,1]                     -> " << sol.findPeakElement(h) << "\n"; // 0

    return 0;
}
