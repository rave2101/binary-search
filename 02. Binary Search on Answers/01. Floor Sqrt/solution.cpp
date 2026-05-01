#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int floorSqrt(int n)  {
      if(n==1 || n==0)return n;
      int low = 1, high = n;
      int result = 1;
      while(low<=high){
        int mid = low + (high-low)/2;
        long long square = (long long)mid*mid;
        if(square == n)return mid;
        if(square>n)high = mid-1;
        else {
            result = mid;
            low = mid+1;
        }
      }
      return result;
    }
};

int main() {
    Solution sol;

    cout << "floorSqrt(0)        -> " << sol.floorSqrt(0) << "\n";
    cout << "floorSqrt(1)        -> " << sol.floorSqrt(1) << "\n";
    cout << "floorSqrt(28)       -> " << sol.floorSqrt(28) << "\n";    // 5
    cout << "floorSqrt(36)       -> " << sol.floorSqrt(36) << "\n";    // 6
    cout << "floorSqrt(2147395600) -> " << sol.floorSqrt(2147395600) << "\n"; // 46340
    cout << "floorSqrt(2147483647) -> " << sol.floorSqrt(2147483647) << "\n"; // 46340

    return 0;
}
