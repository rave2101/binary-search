#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int upperBound(vector<int> &nums, int x) {
        int SIZE = nums.size();
        int low = 0, high = SIZE - 1, result = SIZE;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] <= x) low = mid + 1;
            else {
                result = mid;
                high = mid - 1;
            }
        }
        return result;
    }
};

int main() {
    Solution sol;

    vector<int> a = {1, 2, 3, 3, 5};
    cout << "x=3 in [1,2,3,3,5]   -> " << sol.upperBound(a, 3) << "\n";   // 4
    cout << "x=4 in [1,2,3,3,5]   -> " << sol.upperBound(a, 4) << "\n";   // 4
    cout << "x=5 in [1,2,3,3,5]   -> " << sol.upperBound(a, 5) << "\n";   // 5 (no element > 5)
    cout << "x=0 in [1,2,3,3,5]   -> " << sol.upperBound(a, 0) << "\n";   // 0
    cout << "x=6 in [1,2,3,3,5]   -> " << sol.upperBound(a, 6) << "\n";   // 5

    vector<int> b = {2, 2, 2, 2};
    cout << "x=2 in [2,2,2,2]     -> " << sol.upperBound(b, 2) << "\n";   // 4 (all equal, none >)
    cout << "x=1 in [2,2,2,2]     -> " << sol.upperBound(b, 1) << "\n";   // 0

    vector<int> empty;
    cout << "x=1 in []            -> " << sol.upperBound(empty, 1) << "\n"; // 0

    return 0;
}
