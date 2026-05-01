#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int SIZE = arr.size();
        int low = 0, high = SIZE-1;
        while(low<=high){
            int mid = low + (high-low)/2;
            if(arr[mid]-mid-1<k)low=mid+1;
            else high = mid-1;
        }
        return k+high+1;
    }
};

int main() {
    Solution sol;

    vector<int> a = {2, 3, 4, 7, 11};
    cout << "findKthPositive({2,3,4,7,11}, 5)  -> " << sol.findKthPositive(a, 5)  << "\n"; // 9

    vector<int> b = {1, 2, 3, 4};
    cout << "findKthPositive({1,2,3,4}, 2)     -> " << sol.findKthPositive(b, 2)  << "\n"; // 6

    vector<int> c = {3, 5, 7, 10};
    cout << "findKthPositive({3,5,7,10}, 6)    -> " << sol.findKthPositive(c, 6)  << "\n"; // 9

    return 0;
}
