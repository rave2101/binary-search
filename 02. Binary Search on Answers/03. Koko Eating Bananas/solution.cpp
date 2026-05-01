#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
long long rateHours(vector<int>& nums, int X){
    long long result = 0;
    for(int& num : nums) result+=(num+X-1)/X;
    return result;
}
int minimumRateToEatBananas(vector<int> nums, int h) {
        int low = 1, high = *max_element(nums.begin(), nums.end()), result;
        while(low<=high){
            int mid = low + (high-low)/2;
            long long current = rateHours(nums,mid);

            if(current>h) low = mid+1;
            else{
                result = mid;
                high = mid-1;
            }
        }
        return result;
    }
};

int main() {
    Solution sol;

    vector<int> a = {3, 6, 7, 11};
    cout << "koko({3,6,7,11}, 8)         -> " << sol.minimumRateToEatBananas(a, 8) << "\n";   // 4

    vector<int> b = {30, 11, 23, 4, 20};
    cout << "koko({30,11,23,4,20}, 5)    -> " << sol.minimumRateToEatBananas(b, 5) << "\n";   // 30
    cout << "koko({30,11,23,4,20}, 6)    -> " << sol.minimumRateToEatBananas(b, 6) << "\n";   // 23

    vector<int> c = {1};
    cout << "koko({1}, 1)                -> " << sol.minimumRateToEatBananas(c, 1) << "\n";   // 1

    vector<int> d = {1000000000};
    cout << "koko({1e9}, 2)              -> " << sol.minimumRateToEatBananas(d, 2) << "\n";   // 5e8

    vector<int> e = {312884470};
    cout << "koko({312884470}, 312884469)-> " << sol.minimumRateToEatBananas(e, 312884469) << "\n"; // 2

    return 0;
}
