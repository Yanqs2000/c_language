#include <iostream>
#include <memory>

int main(){
    std::priority_queue<int> pq; // 创建一个空的优先级队列

    pq.push(10);
    pq.push(20);
    pq.push(30);
    pq.push(0);

    std::cout << pq.top() << std::endl; // 输出优先级最高的元素，即30

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq2;
    pq2.push(10);
    pq2.push(20);
    pq2.push(30);
    pq2.push(0);
    std::cout << pq2.top() << std::endl; // 输出优先级最高的元素，即0
    return 0;
}