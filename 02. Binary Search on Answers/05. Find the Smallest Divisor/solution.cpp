#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  bool util(vector<int> &nums, int limit, int X){
    int result = 0;
    for(int& num : nums){
        result=result+((num+X-1)/X);
    }
    return result<=limit;
  }
  int smallestDivisor(vector<int> &nums, int limit) {
       int low = 1, high = *max_element(nums.begin(),nums.end());
       int result = 1;
       while(low<=high){
            int mid = low + (high-low)/2;
            if(util(nums,limit,mid)){
                result = mid;
                high = mid-1;
            }
            else low = mid+1;
       }
       return result;
  }
};

int main() {
    Solution sol;

    vector<int> a = {1, 2, 5, 9};
    cout << "smallestDivisor({1,2,5,9}, 6)       -> " << sol.smallestDivisor(a, 6) << "\n";   // 5

    vector<int> b = {44, 22, 33, 11, 1};
    cout << "smallestDivisor({44,22,33,11,1}, 5) -> " << sol.smallestDivisor(b, 5) << "\n";   // 44

    vector<int> c = {21212, 10101, 12121};
    cout << "smallestDivisor({21212,10101,12121}, 1000000) -> "
         << sol.smallestDivisor(c, 1000000) << "\n";                                          // 1

    vector<int> d = {1};
    cout << "smallestDivisor({1}, 1)             -> " << sol.smallestDivisor(d, 1) << "\n";   // 1

    vector<int> e = {1000000};
    cout << "smallestDivisor({1000000}, 1)       -> " << sol.smallestDivisor(e, 1) << "\n";   // 1000000

    return 0;
}
