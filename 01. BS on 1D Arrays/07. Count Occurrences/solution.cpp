#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int util(vector<int> nums, int x, bool isFirst){
        int SIZE = nums.size();
        int low = 0, high = SIZE-1, result = -1;
        while(low<=high){
            int mid = low + (high-low)/2;
            if(nums[mid]==x){
                if(isFirst){
                    result = mid;
                    high = mid-1;
                }
                else{
                    result = mid;
                    low = mid+1;
                }
            }//end if

            else if(nums[mid] < x)low=mid+1;
            else high = mid-1;
        }//end while
        return result;
    }
    int countOccurrences(vector<int>& arr, int target) {
        int first = util(arr,target,true);
        if(first==-1)return 0;
        int last = util(arr,target,false);
        return (last-first)+1;
    }
};

int main() {
    Solution sol;

    vector<int> a = {2, 4, 4, 4, 7};
    cout << "x=4 in [2,4,4,4,7]   -> " << sol.countOccurrences(a, 4) << "\n"; // 3
    cout << "x=2 in [2,4,4,4,7]   -> " << sol.countOccurrences(a, 2) << "\n"; // 1
    cout << "x=7 in [2,4,4,4,7]   -> " << sol.countOccurrences(a, 7) << "\n"; // 1
    cout << "x=5 in [2,4,4,4,7]   -> " << sol.countOccurrences(a, 5) << "\n"; // 0

    vector<int> b = {1, 1, 1, 1, 1};
    cout << "x=1 in [1,1,1,1,1]   -> " << sol.countOccurrences(b, 1) << "\n"; // 5

    vector<int> empty;
    cout << "x=0 in []            -> " << sol.countOccurrences(empty, 0) << "\n"; // 0

    return 0;
}
