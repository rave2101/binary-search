#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int> &nums, int target) {
        int SIZE = nums.size();
        int low = 0, high = SIZE - 1, result = SIZE;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target) return mid;

            if (nums[mid] < target) low = mid + 1;
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

    vector<int> a = {1, 3, 5, 6};
    cout << "target=5 in [1,3,5,6] -> " << sol.searchInsert(a, 5) << "\n";   // 2 (found)
    cout << "target=2 in [1,3,5,6] -> " << sol.searchInsert(a, 2) << "\n";   // 1
    cout << "target=7 in [1,3,5,6] -> " << sol.searchInsert(a, 7) << "\n";   // 4
    cout << "target=0 in [1,3,5,6] -> " << sol.searchInsert(a, 0) << "\n";   // 0

    vector<int> b = {1, 3, 5, 5, 5, 6};
    cout << "target=5 in [1,3,5,5,5,6] -> " << sol.searchInsert(b, 5) << "\n"; // 2,3, or 4 (any match — this code returns first hit found by BS)

    vector<int> empty;
    cout << "target=1 in []        -> " << sol.searchInsert(empty, 1) << "\n"; // 0

    return 0;
}
