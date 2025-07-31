
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int findMax(const vector<int>& v) {
    if (v.empty()) throw runtime_error("Vector is empty.");
    int maxVal = v[0];
    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i] > maxVal) maxVal = v[i];
    }
    return maxVal;
}

int findSecondMax(const vector<int>& v) 
{
    if (v.size() < 2) throw runtime_error("Not enough elements for 2nd max.");
    int maxVal = INT_MIN, secondMax = INT_MIN;
    for (int x : v) {
        if (x > maxVal) {
            secondMax = maxVal;
            maxVal = x;
        } else if (x < maxVal && x > secondMax) {
            secondMax = x;
        }
    }
    if (secondMax == INT_MIN) throw runtime_error("No 2nd max (all elements are equal).");
    return secondMax;
}

int findThirdMax(const vector<int>& v) {
    if (v.size() < 3) throw runtime_error("Not enough elements for 3rd max.");
    int maxVal = INT_MIN, secondMax = INT_MIN, thirdMax = INT_MIN;
    for (int x : v) {
        if (x > maxVal) {
            thirdMax = secondMax;
            secondMax = maxVal;
            maxVal = x;
        } else if (x < maxVal && x > secondMax) {
            thirdMax = secondMax;
            secondMax = x;
        } else if (x < secondMax && x > thirdMax) {
            thirdMax = x;
        }
    }
    // Check for uniqueness
    if (thirdMax == INT_MIN || thirdMax == secondMax || thirdMax == maxVal)
        throw runtime_error("No 3rd max (not enough unique values).");
    return thirdMax;
}


int main() {
    vector<int> v = {10, 5, 8, 20, 15, 8, 20, 7};
    cout << "Vector: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // Find max
    try {
        cout << "Max element: " << findMax(v) << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Find 2nd max
    try {
        cout << "2nd max element: " << findSecondMax(v) << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Find 3rd max
    try {
        cout << "3rd max element: " << findThirdMax(v) << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    return 0;
}
