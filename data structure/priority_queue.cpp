#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#include <map>

using namespace std;

class MaxSlideWindow{
private:
    class MyQueue{
        public:
            deque<int> queue;
            void push(int val){
                while(!queue.empty() && val > queue.back()){
                    queue.pop_back();
                }
                queue.push_back(val);
            }

            void pop(int val){
                if (!queue.empty() && val == queue.front()){
                    queue.pop_front();
                }
            }

            int front(){
                return queue.front();
            }
    };

public:
    vector<int> maxSlideWindow(vector<int>& nums, int k){
        vector<int> result;
        MyQueue maxHeap;
        for(int i = 0; i < k; i++){
            maxHeap.push(nums[i]);
        }
        result.push_back(maxHeap.front());
        for(int i = k; i < nums.size(); i++){
            maxHeap.pop(nums[i - k]);
            maxHeap.push(nums[i]);
            result.push_back(maxHeap.front());
        }
        return result;
    }
};

class MyCompare{
public:
    bool operator()(const pair<int, int> &map1, const pair<int, int> &map2){
        return map1.second > map2.second;
    }
};

class Solution {
public:
    vector<int> TopKElements(vector<int>& nums, int k){
        vector<int> result(k);
        unordered_map<int, int> countMap;
        for(int num : nums){
            countMap[num]++;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, MyCompare> minHeap;
        for(unordered_map<int, int>::iterator it = countMap.begin(); it != countMap.end(); it++){
            minHeap.push(*it);
            if(minHeap.size() > k){
                minHeap.pop();
            }
        }
        for(int i = k - 1; i >= 0; i--){
            result[i] = minHeap.top().first;
            minHeap.pop();
        }
        return result;
    }
};

int main(){
    vector<int> nums = {1,1,1,2,2,3};
    int k = 2;
    Solution solution;
    vector<int> result = solution.TopKElements(nums, k);
    for(int num : result){
        cout << num << " ";
    }
    cout << endl;
    return 0;
}