#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int util(vector<int> nums, int x, bool isFloor) {
        int SIZE = nums.size();
        int low = 0, high = SIZE - 1, result = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == x) return nums[mid];

            if (isFloor) {
                if (nums[mid] < x) {
                    result = nums[mid];
                    low = mid + 1;
                }
                else high = mid - 1;
            }
            else {
                if (nums[mid] > x) {
                    result = nums[mid];
                    high = mid - 1;
                }
                else low = mid + 1;
            }
        }
        return result;
    }

    vector<int> getFloorAndCeil(vector<int> nums, int x) {
        vector<int> result(2, -1);
        result[0] = util(nums, x, true);
        result[1] = util(nums, x, false);
        return result;
    }
};

void print(const vector<int>& fc) {
    cout << "[" << fc[0] << ", " << fc[1] << "]";
}

int main() {
    Solution sol;

    vector<int> a = {3, 4, 4, 7, 8, 10};
    cout << "x=5  in [3,4,4,7,8,10]   -> "; print(sol.getFloorAndCeil(a, 5));  cout << "\n";  // [4, 7]
    cout << "x=4  in [3,4,4,7,8,10]   -> "; print(sol.getFloorAndCeil(a, 4));  cout << "\n";  // [4, 4]
    cout << "x=2  in [3,4,4,7,8,10]   -> "; print(sol.getFloorAndCeil(a, 2));  cout << "\n";  // [-1, 3]
    cout << "x=11 in [3,4,4,7,8,10]   -> "; print(sol.getFloorAndCeil(a, 11)); cout << "\n";  // [10, -1]
    cout << "x=10 in [3,4,4,7,8,10]   -> "; print(sol.getFloorAndCeil(a, 10)); cout << "\n";  // [10, 10]

    vector<int> empty;
    cout << "x=1  in []               -> "; print(sol.getFloorAndCeil(empty, 1)); cout << "\n"; // [-1, -1]

    return 0;
}
