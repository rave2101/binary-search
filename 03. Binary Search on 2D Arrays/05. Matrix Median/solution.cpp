#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int minElement(vector<vector<int>>& matrix) {
        int mini = INT_MAX, R = matrix.size(), C = matrix[0].size();
        for (int i = 0; i < R; i++) {
            mini = min(mini, matrix[i][0]);
        }
        return mini;
    }

    int maxElement(vector<vector<int>>& matrix) {
        int maxi = INT_MIN, R = matrix.size(), C = matrix[0].size();
        for (int i = 0; i < R; i++) {
            maxi = max(maxi, matrix[i][C - 1]);
        }
        return maxi;
    }

    int upperBound(vector<int>& temp, int X) {
        int SIZE = temp.size();
        int low = 0, high = SIZE - 1, result = SIZE;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (temp[mid] <= X) low = mid + 1;
            else {
                result = mid;
                high = mid - 1;
            }
        }
        return result;
    }

    int countLessThanEqual(vector<vector<int>>& matrix, int X) {
        int count = 0;
        for (int i = 0; i < matrix.size(); i++) {
            count += upperBound(matrix[i], X);
        }
        return count;
    }

public:
    int findMedian(vector<vector<int>>& matrix) {
        int R = matrix.size(), C = matrix[0].size();
        int low = minElement(matrix);
        int high = maxElement(matrix);
        int req = (R * C) / 2;
        int result;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (countLessThanEqual(matrix, mid) <= req) low = mid + 1;
            else {
                result = mid;
                high = mid - 1;
            }
        }
        return result;
    }
};

int main() {
    Solution s;

    vector<vector<int>> m1 = {{1, 3, 5}, {2, 6, 9}, {3, 6, 9}};
    cout << "median([[1,3,5],[2,6,9],[3,6,9]]) -> " << s.findMedian(m1) << endl;

    vector<vector<int>> m2 = {{1, 4, 9}, {2, 5, 6}, {3, 7, 8}};
    cout << "median([[1,4,9],[2,5,6],[3,7,8]]) -> " << s.findMedian(m2) << endl;

    vector<vector<int>> m3 = {{1, 3, 8}, {2, 3, 4}, {1, 2, 5}};
    cout << "median([[1,3,8],[2,3,4],[1,2,5]]) -> " << s.findMedian(m3) << endl;

    return 0;
}
