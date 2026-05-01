#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int util(vector<int> nums, int x, bool isFirst) {
        int SIZE = nums.size();
        int low = 0, high = SIZE - 1, result = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == x) {
                if (isFirst) {
                    result = mid;
                    high = mid - 1;
                }
                else {
                    result = mid;
                    low = mid + 1;
                }
            }
            else if (nums[mid] < x) low = mid + 1;
            else high = mid - 1;
        }
        return result;
    }

    vector<int> searchRange(vector<int> &nums, int target) {
        vector<int> result(2, -1);
        result[0] = util(nums, target, true);
        result[1] = util(nums, target, false);
        return result;
    }
};

void print(const vector<int>& r) {
    cout << "[" << r[0] << ", " << r[1] << "]";
}

int main() {
    Solution sol;

    vector<int> a = {2, 4, 4, 4, 7};
    cout << "x=4 in [2,4,4,4,7]   -> "; print(sol.searchRange(a, 4));  cout << "\n"; // [1, 3]
    cout << "x=2 in [2,4,4,4,7]   -> "; print(sol.searchRange(a, 2));  cout << "\n"; // [0, 0]
    cout << "x=7 in [2,4,4,4,7]   -> "; print(sol.searchRange(a, 7));  cout << "\n"; // [4, 4]
    cout << "x=5 in [2,4,4,4,7]   -> "; print(sol.searchRange(a, 5));  cout << "\n"; // [-1, -1]

    vector<int> b = {1, 1, 1, 1, 1};
    cout << "x=1 in [1,1,1,1,1]   -> "; print(sol.searchRange(b, 1));  cout << "\n"; // [0, 4]

    vector<int> empty;
    cout << "x=0 in []            -> "; print(sol.searchRange(empty, 0)); cout << "\n"; // [-1, -1]

    return 0;
}
