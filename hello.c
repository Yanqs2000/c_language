#include <stdio.h>
#include <string.h>  // 为了使用 strlen 函数

struct Node{
    int a;
    struct Node *next;
};

typedef struct LinkList{
    struct Node *head;
    int size;
}LinkList;

int main() {
    struct Node node1 = {10, NULL};  // 初始化 node1 的 a 为 10，next 为 NULL
    struct Node node2 = {20, NULL};  // 初始化 node2 的 a 为 20，next 为 NULL
    node1.next = &node2;

    LinkList list;
    list.head = &node1;  // 将 node1 作为链表的头
    list.size = 2;       // 链表大小为 2

    return 0;
}