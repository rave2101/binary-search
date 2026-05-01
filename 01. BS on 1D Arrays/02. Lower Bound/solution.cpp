#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lowerBound(vector<int> &nums, int x) {
        int SIZE = nums.size();
        int high = SIZE - 1, low = 0, result = SIZE;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] >= x) {
                result = mid;
                high = mid - 1;
            }
            else low = mid + 1;
        }
        return result;
    }
};

int main() {
    Solution sol;

    vector<int> a = {1, 2, 3, 3, 5};
    cout << "x=3 in [1,2,3,3,5]   -> " << sol.lowerBound(a, 3) << "\n";   // 2
    cout << "x=4 in [1,2,3,3,5]   -> " << sol.lowerBound(a, 4) << "\n";   // 4
    cout << "x=0 in [1,2,3,3,5]   -> " << sol.lowerBound(a, 0) << "\n";   // 0
    cout << "x=6 in [1,2,3,3,5]   -> " << sol.lowerBound(a, 6) << "\n";   // 5 (not found)

    vector<int> b = {2, 2, 2, 2};
    cout << "x=2 in [2,2,2,2]     -> " << sol.lowerBound(b, 2) << "\n";   // 0

    vector<int> empty;
    cout << "x=1 in []            -> " << sol.lowerBound(empty, 1) << "\n"; // 0

    return 0;
}
