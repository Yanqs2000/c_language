#include <iostream>
#include <vector>

using namespace std;

class DoublyListNode
{
public:
    int val;
    DoublyListNode* prev;
    DoublyListNode* next;
    DoublyListNode(int val): val(val), prev(NULL), next(NULL) {}
};

//创建双链表
DoublyListNode* createDoublyList(vector<int> arr)
{
    if(arr.empty())
    {
        return NULL;
    }
    DoublyListNode* head = new DoublyListNode(arr[0]);
    DoublyListNode* cur = head;
    for(int i = 1; i < arr.size(); i++)
    {
        DoublyListNode* newNode = new DoublyListNode(arr[i]);
        cur->next = newNode;
        newNode->prev = cur;
        cur = cur->next;
    }
    return head;
}

// 打印链表的值
void printLinkList_head(DoublyListNode* head)
{
    for(DoublyListNode* p = head; p != nullptr; p = p->next)
    {
        cout << p->val << " ";
    }
    cout << endl;
}

// 打印链表的值
void printLinkList_tail(DoublyListNode* tail)
{
    for(DoublyListNode* p = tail; p != nullptr; p = p->prev)
    {
        cout << p->val << " ";
    }
    cout << endl;
}

// 查/改
void test01()
{
    DoublyListNode* head = createDoublyList({1, 2, 3, 4, 5});
    DoublyListNode* tail = nullptr;

    // 从头向尾遍历
    for(DoublyListNode* p = head; p != nullptr; p = p->next)
    {
        cout << p->val << " ";
        tail = p; // 记录最后一个节点
    }
    cout << endl;

    // 从尾向头遍历
    for(DoublyListNode* p = tail; p != nullptr; p = p->prev)
    {
        cout << p->val << " ";
    }
    cout << endl;
}

// 在双链表头部插入节点
void test02()
{
    DoublyListNode* head = createDoublyList({1, 2, 3, 4, 5});
    DoublyListNode* newNode = new DoublyListNode(0);
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
    printLinkList_head(head);
}

// 在双链表尾部插入节点
void test03()
{
    DoublyListNode* head = createDoublyList({1, 2, 3, 4, 5});
    DoublyListNode* tail = head;
    DoublyListNode* newNode = new DoublyListNode(6);

    while(tail->next != nullptr)
    {
        tail = tail->next;
    }

    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    printLinkList_head(head); 
    printLinkList_tail(tail);
}

// 在双链表中间插入节点
void test04()
{
    DoublyListNode* head = createDoublyList({1, 2, 3, 4, 5});
    DoublyListNode* newNode = new DoublyListNode(6);
    DoublyListNode* p = head;

    for(int i = 0; i < 2; i++)
    {
        p = p->next;
    }

    // 首先处理新的节点
    newNode->prev = p;
    newNode->next = p->next;
    // 处理前后节点的关系
    p->next = newNode;
    newNode->next->prev = newNode;
    printLinkList_head(head);
}

// 在双链表中删除节点
void test05()
{
    DoublyListNode* head = createDoublyList({1, 2, 3, 4, 5});
    DoublyListNode* p = head;

    for(int i = 0; i < 3; i++)
    {
        p = p->next;
    }

    p->prev->next = p->next;
    p->next->prev = p->prev;
    
    p->next = nullptr;
    p->prev = nullptr;

    printLinkList_head(head);
}

int main()
{
    test04();
    return 0;
}