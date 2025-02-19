#include <iostream>
#include <vector>

using namespace std;

class ListNode
{
public:
    int val;
    ListNode* next;

    ListNode(int x): val(x), next(NULL){}; //初始化列表
};


template <typename E>
class Node
{
public:
    E val;
    Node* prev;
    Node* next;

    Node(Node* prev, E val, Node* next)
    {
        this->prev = prev;
        this->val = val;
        this->next = next;
    }
};

ListNode* createLinkList(vector<int> arr)
{
    if(arr.empty())
    {
        return nullptr;
    }

    ListNode* head = new ListNode(arr[0]);
    ListNode* cur = head; //cur指向当前节点
    for(int i = 1; i < arr.size(); i++)
    {
        cur->next = new ListNode(arr[i]);
        cur = cur->next;
    }
    return head;
}

// 打印链表的值
void printLinkList(ListNode* head)
{
    for(ListNode* p = head; p != nullptr; p = p->next)
    {
        cout << p->val << " ";
    }
    cout << endl;
}

// 查/改
void test01()
{
    vector<int> arr = {1, 2, 3, 4, 5};
    ListNode* head = createLinkList(arr);
    // 遍历整个链表
    for (ListNode* p = head; p != nullptr; p = p->next)
    {
        cout << p->val << " ";
    }
    cout << endl;
}

// 增/删
void test02()
{
    ListNode* head = createLinkList({1, 2, 3, 4, 5});

    // 在头部插入
    ListNode* newHead = new ListNode(10);  
    newHead->next = head;
    head = newHead;
    
    // 遍历整个链表
    printLinkList(head);

    // 在尾部插入
    ListNode* p = head;
    while(p->next != nullptr)
    {
        p = p->next; 
    }
    ListNode* newTail = new ListNode(20);
    p->next = newTail;
    printLinkList(head);

    // 删除中间节点
    ListNode* p1 = head;
    for(int i = 0; i < 2; i++)
    {
        p1 = p1->next;
    }

    p1->next = p1->next->next;
    printLinkList(head);
}

int main()
{
    test02();
    return 0;
}
