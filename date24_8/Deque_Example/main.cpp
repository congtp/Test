#include <iostream>
#include <deque>
#include <vector>

std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
    std::deque<int> dq; // store indices of useful elements in current window
    std::vector<int> result;

    // for (int i = 0; i < nums.size(); ++i) {
    //     // Remove elements not within the current window
    //     if (!dq.empty() && dq.front() == i - k) {
    //         dq.pop_front();
    //     }

    //     // Remove elements smaller than the current element (since they are useless)
    //     while (!dq.empty() && nums[dq.back()] < nums[i]) {
    //         dq.pop_back();
    //     }

    //     // Add current element at the back of the deque
    //     dq.push_back(i);

    //     // The front of the deque is the largest element of the window
    //     if (i >= k - 1) {
    //         result.push_back(nums[dq.front()]);
    //     }
    // }

    // 1 push the first value and assume it is the largest value
    dq.push_back(0); // index

    for (int i = 1; i < nums.size(); i++){
        // push the next value
        //dq.push_back(i);    
        
        // check if the size is == k
        if (dq.front() <= i - k){
            dq.pop_front();
        }

        // Remove useless elements from the back of the deque
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back(); // Remove smaller elements since they are not useful
        }

        // add the new 
        dq.push_back(i);

        // add the new value when size is enough
        if (i >= k - 1){
            result.push_back(nums[dq.front()]);
        }
    }

    return result;
}

int main() {
    std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    std::vector<int> result = maxSlidingWindow(nums, k);
    
    for (int num : result) {
        std::cout << num << " ";
    }
    
    return 0;
}
