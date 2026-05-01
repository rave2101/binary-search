#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  long long powUtil(long long int a, int pow, int M){
    long long result = 1;
    while(pow){
        if(pow%2){
            result*=a;
            if (result > M) return result;
            pow-=1;
        }
        else{
            a*=a;
            if (a > M) return a;
            pow/=2;
        }
    }
    return result;
  }
  int NthRoot(int N, int M) {
    if(N==1)return M;

    int low = 1,high = M, result = -1;
    while(low<=high){
        int mid = low + (high-low)/2;
        long long current = powUtil(mid,N,M);
        if(current==M)return mid;
        if(current>M)high = mid-1;
        else low = mid+1;
    }
    return result;
  }
};

int main() {
    Solution sol;

    cout << "NthRoot(2, 9)      -> " << sol.NthRoot(2, 9) << "\n";       // 3
    cout << "NthRoot(3, 27)     -> " << sol.NthRoot(3, 27) << "\n";      // 3
    cout << "NthRoot(4, 69)     -> " << sol.NthRoot(4, 69) << "\n";      // -1
    cout << "NthRoot(1, 42)     -> " << sol.NthRoot(1, 42) << "\n";      // 42
    cout << "NthRoot(5, 243)    -> " << sol.NthRoot(5, 243) << "\n";     // 3
    cout << "NthRoot(30, 1)     -> " << sol.NthRoot(30, 1) << "\n";      // 1
    cout << "NthRoot(2, 2147395600) -> " << sol.NthRoot(2, 2147395600) << "\n"; // 46340

    return 0;
}
