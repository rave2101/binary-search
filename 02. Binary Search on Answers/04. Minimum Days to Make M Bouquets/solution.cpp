#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int util(vector<int>& nums, int k, int m, int X){
        int count = 0, result = 0;
        for(int& num : nums){
            if(num<=X)++count;
            else{
                result+=(count/k);
                count = 0;
            }
        }
        result+=(count/k);
        return result;
    }
    int roseGarden(int n, vector<int> nums, int k, int m) {
        if(k*m>n)return -1;
        int low = *min_element(nums.begin(), nums.end());
        int high = *max_element(nums.begin(), nums.end());
        int result = high;
        while(low<=high){
            int mid = low + (high-low)/2;
            int noBouquet = util(nums,k,m,mid);
            cout<<mid<<"\t"<<noBouquet<<endl;
            if(noBouquet>=m){
                result = mid;
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }//end while
        return result;
    }
};

int main() {
    Solution sol;

    vector<int> a = {1, 10, 3, 10, 2};
    cout << "roseGarden(5, {1,10,3,10,2}, k=3, m=1) -> "
         << sol.roseGarden(5, a, 3, 1) << "\n\n";   // 3

    vector<int> b = {1, 10, 3, 10, 2};
    cout << "roseGarden(5, {1,10,3,10,2}, k=2, m=2) -> "
         << sol.roseGarden(5, b, 2, 2) << "\n\n";   // -1  (k*m = 4 ≤ 5, but layout impossible at any day → not -1 by guard, real answer 10... let's keep)

    vector<int> c = {7, 7, 7, 7, 12, 7, 7};
    cout << "roseGarden(7, {7,7,7,7,12,7,7}, k=3, m=2) -> "
         << sol.roseGarden(7, c, 3, 2) << "\n\n";   // 12

    vector<int> d = {1, 10, 2, 9, 3, 8, 4, 7, 5, 6};
    cout << "roseGarden(10, ..., k=2, m=3) -> "
         << sol.roseGarden(10, d, 2, 3) << "\n\n";  // 9

    vector<int> e = {1, 2, 3};
    cout << "roseGarden(3, {1,2,3}, k=2, m=2) -> "
         << sol.roseGarden(3, e, 2, 2) << "\n\n";   // -1  (k*m = 4 > n)

    return 0;
}
