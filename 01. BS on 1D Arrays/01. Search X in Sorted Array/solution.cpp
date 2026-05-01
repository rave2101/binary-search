#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int util(vector<int> &nums, int target, int low, int high) {
        if (low > high) return -1;

        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] > target) return util(nums, target, low, mid - 1);
        return util(nums, target, mid + 1, high);
    }

    int search(vector<int> &nums, int target) {
        int SIZE = nums.size();
        return util(nums, target, 0, SIZE - 1);
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {-1, 0, 3, 5, 9, 12};
    cout << "Example 1: target=9  -> index = " << sol.search(nums1, 9) << "\n";   // 4
    cout << "Example 1: target=2  -> index = " << sol.search(nums1, 2) << "\n";   // -1

    vector<int> nums2 = {1, 3, 5, 7, 9};
    cout << "Example 2: target=1  -> index = " << sol.search(nums2, 1) << "\n";   // 0
    cout << "Example 2: target=9  -> index = " << sol.search(nums2, 9) << "\n";   // 4

    return 0;
}
