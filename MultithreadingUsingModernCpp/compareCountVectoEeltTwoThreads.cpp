#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

int main() {
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> vec2 = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int count = 0;
    std::mutex count_mutex;

    // The original code compares elements of vec1 with elements of vec2 for same index

    // auto compare_and_count = [&](int start, int end) {
    //     for (int i = start; i < end; ++i) {
    //         if (vec1[i] == vec2[i]) {
    //             std::lock_guard<std::mutex> lock(count_mutex);
    //             count++;
    //         }
    //     }
    // };

    // The modified code compares elements of vec1 with elements of vec2 for any index
        auto compare_and_count = [&](int start, int end) {
        for (int i = start; i < end; ++i) {
            for (int j = 0; j < vec2.size(); ++j) {
                if (vec1[i] == vec2[j]) {
                    std::lock_guard<std::mutex> lock(count_mutex);
                    count++;
                    break; // Only count once per element in vec1
                }
            }
        }
    };

    int mid = vec1.size() / 2;
    std::thread thread1(compare_and_count, 0, mid);
    std::thread thread2(compare_and_count, mid, vec1.size());

    thread1.join();
    thread2.join();

    std::cout << "Number of matching elements: " << count << std::endl;

    return 0;
}