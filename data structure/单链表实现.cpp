#include <iostream>
#include <stdexcept>

template <typename E>
class MyLinkedList2 
{
private:
    // 节点结构
    struct Node 
    {
        E val;
        Node* next;

        Node(E value) : val(value), next(nullptr) {}
    };

    Node* head;
    // 实际的尾部节点引用
    Node* tail;
    int size_;

public:
    MyLinkedList2() 
    {
        head = new Node(E());
        tail = head;
        size_ = 0;
    }

    void addFirst(E e) 
    {
        Node* newNode = new Node(e);
        newNode->next = head->next;
        head->next = newNode;
        if (size_ == 0) 
        {
            tail = newNode;
        }
        size_++;
    }

    void addLast(E e) 
    {
        Node* newNode = new Node(e);
        tail->next = newNode;
        tail = newNode;
        size_++;
    }

    void add(int index, E element) 
    {
        checkPositionIndex(index);

        if (index == size_) 
        {
            addLast(element);
            return;
        }

        Node* prev = head;
        for (int i = 0; i < index; i++) 
        {
            prev = prev->next;
        }
        Node* newNode = new Node(element);
        newNode->next = prev->next;
        prev->next = newNode;
        size_++;
    }

    E removeFirst() 
    {
        if (isEmpty()) 
        {
            throw std::out_of_range("No elements to remove");
        }
        Node* first = head->next;
        head->next = first->next;
        if (size_ == 1) 
        {
            tail = head;
        }
        size_--;
        E val = first->val;
        delete first;
        return val;
    }

    E removeLast() 
    {
        if (isEmpty()) 
        {
            throw std::out_of_range("No elements to remove");
        }

        Node* prev = head;
        while (prev->next != tail) 
        {
            prev = prev->next;
        }
        E val = tail->val;
        delete tail;
        prev->next = nullptr;
        tail = prev;
        size_--;
        return val;
    }

    E remove(int index) 
    {
        checkElementIndex(index);

        Node* prev = head;
        for (int i = 0; i < index; i++) 
        {
            prev = prev->next;
        }

        Node* nodeToRemove = prev->next;
        prev->next = nodeToRemove->next;
        // 删除的是最后一个元素
        if (index == size_ - 1) 
        {
            tail = prev;
        }
        size_--;
        E val = nodeToRemove->val;
        delete nodeToRemove;
        return val;
    }

    // ***** 查 *****

    E getFirst() 
    {
        if (isEmpty()) 
        {
            throw std::out_of_range("No elements in the list");
        }
        return head->next->val;
    }

    E getLast() 
    {
        if (isEmpty()) 
        {
            throw std::out_of_range("No elements in the list");
        }
        return getNode(size_ - 1)->val;
    }

    E get(int index) 
    {
        checkElementIndex(index);
        Node* p = getNode(index);
        return p->val;
    }

    // ***** 改 *****

    E set(int index, E element) 
    {
        checkElementIndex(index);
        Node* p = getNode(index);

        E oldVal = p->val;
        p->val = element;

        return oldVal;
    }

    // ***** 其他工具函数 *****
    int size() 
    {
        return size_;
    }

    bool isEmpty() 
    {
        return size_ == 0;
    }

private:
    bool isElementIndex(int index) 
    {
        return index >= 0 && index < size_;
    }

    bool isPositionIndex(int index) 
    {
        return index >= 0 && index <= size_;
    }

    // 检查 index 索引位置是否可以存在元素
    void checkElementIndex(int index) 
    {
        if (!isElementIndex(index)) 
        {
            throw std::out_of_range("Index: " + std::to_string(index) + ", size_: " + std::to_string(size_));
        }
    }

    // 检查 index 索引位置是否可以添加元素
    void checkPositionIndex(int index) 
    {
        if (!isPositionIndex(index)) 
        {
            throw std::out_of_range("Index: " + std::to_string(index) + ", size_: " + std::to_string(size_));
        }
    }

    // 返回 index 对应的 Node
    // 注意：请保证传入的 index 是合法的
    Node* getNode(int index) 
    {
        Node* p = head->next;
        for (int i = 0; i < index; i++) 
        {
            p = p->next;
        }
        return p;
    }
};

int main() {
    MyLinkedList2<int> list;
    list.addFirst(1);
    list.addFirst(2);
    list.addLast(3);
    list.addLast(4);
    list.add(2, 5);

    std::cout << list.removeFirst() << std::endl; // 2
    std::cout << list.removeLast() << std::endl; // 4
    std::cout << list.remove(1) << std::endl; // 5

    std::cout << list.getFirst() << std::endl; // 1
    std::cout << list.getLast() << std::endl; // 3
    std::cout << list.get(1) << std::endl; // 3

    return 0;
}