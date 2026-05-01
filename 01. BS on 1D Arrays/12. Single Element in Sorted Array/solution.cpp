#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNonDuplicate(vector<int> &nums) {
        int SIZE = nums.size();
        if(SIZE==1 || nums[0]!=nums[1])return nums[0];
        if(nums[SIZE-1]!=nums[SIZE-2])return nums[SIZE-1];

        int low = 1, high = SIZE-2;

        while(low<=high){
            int mid = low + (high-low)/2;
            if(nums[mid]!=nums[mid-1] && nums[mid]!=nums[mid+1])return nums[mid];
            if(mid%2){
                if(nums[mid-1]==nums[mid])low = mid+1;
                else high = mid-1;
            }
            else{
                if(nums[mid+1]==nums[mid])low = mid+1;
                else high = mid-1;
            }
        }//end while
        return -1;
    }
};

int main() {
    Solution sol;

    vector<int> a = {1, 1, 2, 3, 3, 4, 4, 8, 8};
    cout << "single in [1,1,2,3,3,4,4,8,8]   -> " << sol.singleNonDuplicate(a) << "\n"; // 2

    vector<int> b = {3, 3, 7, 7, 10, 11, 11};
    cout << "single in [3,3,7,7,10,11,11]    -> " << sol.singleNonDuplicate(b) << "\n"; // 10

    vector<int> c = {1};
    cout << "single in [1]                   -> " << sol.singleNonDuplicate(c) << "\n"; // 1

    vector<int> d = {1, 2, 2};
    cout << "single in [1,2,2]               -> " << sol.singleNonDuplicate(d) << "\n"; // 1

    vector<int> e = {1, 1, 2};
    cout << "single in [1,1,2]               -> " << sol.singleNonDuplicate(e) << "\n"; // 2

    vector<int> f = {1, 1, 2, 2, 3, 3, 4, 4, 5};
    cout << "single in [1,1,2,2,3,3,4,4,5]   -> " << sol.singleNonDuplicate(f) << "\n"; // 5

    vector<int> g = {0, 1, 1, 2, 2, 3, 3};
    cout << "single in [0,1,1,2,2,3,3]       -> " << sol.singleNonDuplicate(g) << "\n"; // 0

    return 0;
}
