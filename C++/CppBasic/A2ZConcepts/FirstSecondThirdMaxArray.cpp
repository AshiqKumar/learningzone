#include <iostream>
#include <climits>

void findTopThree(const int arr[], int size) {
    int first = INT_MIN, second = INT_MIN, third = INT_MIN;

    for (int i = 0; i < size; ++i) {
        int num = arr[i];
        if (num > first) {
            third = second;
            second = first;
            first = num;
        } else if (num > second && num < first) {
            third = second;
            second = num;
        } else if (num > third && num < second) {
            third = num;
        }
    }

    std::cout << "1st max: " << first << "\n";
    std::cout << "2nd max: " << second << "\n";
    std::cout << "3rd max: " << third << "\n";

    if (second == INT_MIN || third == INT_MIN) {
        std::cout << "Not enough unique elements for 2nd or 3rd max.\n";
    }
}

int main() {
    int arr[] = {10, 20, 20, 5, 15, 8};
    int size = sizeof(arr) / sizeof(arr[0]);

    findTopThree(arr, size);
    return 0;
}
