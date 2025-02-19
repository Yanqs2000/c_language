#include <iostream>
#include <stdexcept>

using namespace std;

// 双链表实现
template <typename E>
class MyLinkedList
{
    // 虚拟头尾节点
    struct Node
    {
        E value;
        Node* next;
        Node* prev;

        Node(E value) : value(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    MyLinkedList()
    {
        head = new Node(E()); // 虚拟头节点
        tail = new Node(E()); // 虚拟尾节点
        head->next = tail;
        tail->prev = head;
        size = 0;
    }

    // -----增-----

    void addLast(E e)
    {
        Node* x = new Node(e);
        Node* temp = tail->prev;
        // temp <-> x

        temp->next = x;
        x->prev = temp;
        x->next = tail;
        tail->prev = x;
        // temp <-> x <-> tail
        size++;
    }

    void addFirst(E e)
    {
        Node* x = new Node(e);
        Node* temp = head->next;
        // head <-> temp

        temp->prev = x;
        x->next = temp;
        x->prev = head;
        head->next = x;

        // head <-> x <-> temp
        size++;
    }

    void add(int index, E element)
    {
        checkPositionIndex(index);
        if(index == size)
        {
            addLast(element);
            return;
        }

        // 找到index对应的node
        Node* p = getNode(index);
        Node* temp = p->prev;
        // temp <-> p

        // 新要插入的Node
        Node* x = new Node(element);
        p->prev = x;
        temp->next = x;

        x->prev = temp;
        x->next = p;
        // temp <-> x <-> p
        size++;
    }

    // -----删-----

    E removeFirst()
    {
        if(size < 1)
        {
            throw out_of_range("No elements to remove");
        }

        Node* x = head->next;
        Node* temp = x->next;
        // head <-> x <-> temp

        head->next = temp;
        temp->prev = head;

        delete x;
        // head <-> temp

        size--;
        return x->value;
    }

    E removeLast() 
    {
        if (size < 1) 
        {
            throw out_of_range("No elements to remove");
        }
        Node* x = tail->prev;
        Node* temp = tail->prev->prev;
        // temp <-> x <-> tail

        tail->prev = temp;
        temp->next = tail;

        delete x;
        // temp <-> tail

        size--;
        return temp->val;
    }

    E remove(int index)
    {
        checkElementIndex(index);
        // 找到index对应的node
        Node* x = getNode(index);
        Node* prev = x->prev;
        Node* next = x->next;
        // prev <-> x <-> next

        prev->next = next;
        next->prev = prev;

        delete x;
        // prev <-> next

        size--;
        return x->value;
    }

    // -----查-----
    E get(int index)
    {
        checkElementIndex(index);
        return getNode(index)->value;
    }

    E getFirst() 
    {
        if (size < 1) 
        {
            throw out_of_range("No elements in the list");
        }

        return head->next->val;
    }

    E getLast() 
    {
        if (size < 1) 
        {
            throw out_of_range("No elements in the list");
        }

        return tail->prev->val;
    }

    // -----改-----
    E set(int index, E val)
    {
        checkElementIndex(index);
        Node* x = getNode(index);

        E oldVal = x->value;
        x->value = val;

        return oldVal;
    }

    // -----其他工具函数-----

    int getsize() const
    {
        return size;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

private:
    Node* getNode(int index)
    {
        checkElementIndex(index);
        Node* p = head->next;

        for (int i = 0; i < index; i++)
        {
            p = p->next;
        }
        return p; // 返回index对应的node
    }

    bool isPositionIndex(int index) const
    {
        return index >= 0 && index <= size;
    }

    bool isElementIndex(int index) const
    {
        return index >= 0 && index < size;
    }

    // 检查index索引位置是否可以存在元素
    void checkElementIndex(int index) const
    {
        if(!isElementIndex(index))
            throw out_of_range("Index: " + to_string(index) + ", Size: " + to_string(size));
    }

    // 检查index索引位置是否可以添加元素
    void checkPositionIndex(int index) const
    {
        if(!isPositionIndex(index))
            throw out_of_range("Index: " + to_string(index) + ", Size: " + to_string(size));
    }

public:
    void display()
    {
        cout << "size: " << size << endl;
        for(Node* p = head->next; p != tail; p = p->next)
        {
            cout << p->value << " ";
        }
        cout << endl;
    }

    ~MyLinkedList()
    {
        while(size > 0)
        {
            removeFirst();
        }
        delete head;
        delete tail;
    }
};

int main()
{
    MyLinkedList<int> list;
    list.addLast(1);
    list.addLast(2);
    list.addLast(3);
    list.addFirst(0);
    list.add(2, 100);

    list.display();
    
    return 0;
}