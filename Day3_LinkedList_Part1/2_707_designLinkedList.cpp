/*Leetcode707.设计链表
你可以选择使用单链表或者双链表，设计并实现自己的链表。
单链表中的节点应该具备两个属性：val 和 next 。val 是当前节点的值，next 是指向下一个节点的指针。
如果是双向链表，则还需要属性 prev 指向链表中的上一个节点。假设链表中的所有节点下标从 0 开始。

实现 MyLinkedList 类：
MyLinkedList() 初始化 MyLinkedList 对象。
int get(int index) 获取链表中下标为 index 的节点的值。如果下标无效，则返回 -1 。
void addAtHead(int val) 将一个值为 val 的节点插入到链表中第一个元素之前。在插入完成后，新节点会成为链表的第一个节点。
void addAtTail(int val) 将一个值为 val 的节点追加到链表中作为链表的最后一个元素。
void addAtIndex(int index, int val) 将一个值为 val 的节点插入到链表中下标为 index 的节点之前。如果 index 等于链表的长度，那么该节点会被追加到链表的末尾。如果 index 比长度更大，该节点将不会插入到链表中。
void deleteAtIndex(int index) 如果下标有效，则删除链表中下标为 index 的节点。

示例：
输入
["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
[[], [1], [3], [1, 2], [1], [1], [1]]
输出
[null, null, null, null, 2, null, 3]
解释
MyLinkedList myLinkedList = new MyLinkedList();
myLinkedList.addAtHead(1);
myLinkedList.addAtTail(3);
myLinkedList.addAtIndex(1, 2);    // 链表变为 1->2->3
myLinkedList.get(1);              // 返回 2
myLinkedList.deleteAtIndex(1);    // 现在，链表变为 1->3
myLinkedList.get(1);              // 返回 3

提示：请不要使用内置的 LinkedList 库。
*/

#include<iostream>
using namespace std;

/*三个遍历：

1.找index节点（查询）：
    cur = _dummyHead->next;
    while(index--) cur = cur->next;

2.找index前驱节点（插入/删除）：
    cur = _dummyHead;
    while(index--) cur = cur->next;

3.找尾节点（尾插）：
    cur = _dummyHead;
    while(cur->next != nullptr) cur = cur->next;

两个模板：

1.插入节点（cur已指向前驱节点）：
    newNode->next = cur->next;
    cur->next = newNode;

2.删除节点（cur已指向前驱节点）：
    tmp = cur->next;
    cur->next = cur->next->next;
    delete tmp;
*/

class MyLinkedList {
public:
    // 定义链表结构体
    struct ListNode {
        int val;
        ListNode* next;
        ListNode(int x) : val(x), next(nullptr){}
    };

    // 链表初始化
    MyLinkedList() {
        _dummyHead = new ListNode(0);  //⭐创建虚拟头结点，执行后内存状态：dummy->null
        _size = 0;                     //初始化之后，真实链表为空
    }

    // ⭐析构函数：对象生命周期结束（作用域结束/被delete）时自动调用
    // 作用：释放所有动态申请的内存，避免内存泄漏

    /*  情况一：局部变量（栈上对象）
        void func() {
            MyLinkedList list;  // 创建对象
            list.addAtHead(1);  // 使用对象
            list.addAtHead(2);
        }   // 作用域结束 → 对象自动销毁 → 调用~MyLinkedList()

        情况二：new（堆上对象）
        MyLinkedList* list = new MyLinkedList();
        delete list;  // 手动释放 → 触发~MyLinkedList()
    */
    ~MyLinkedList() {
        ListNode* cur = _dummyHead;
        while (cur != nullptr) {
            ListNode* tmp = cur;  // 保存当前节点
            cur = cur->next;
            delete tmp;
        }
    }

    // 获取下标为index的节点的值
    int get(int index) {
        if (index >= _size || index < 0) {  //先判断index合法性
            return -1;
        }
        ListNode* cur = _dummyHead->next;
        while (index--) {  //若写成while(--index)，当index=0时会先变成-1，非0即true，可能导致死循环
            cur = cur->next;  //⭐从真实头结点开始走index步，最终停在下标为index的节点
        }
        return cur->val;
    }

    // 在链表最前面插入一个节点，使之成为链表的新头结点
    void addAtHead(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = _dummyHead->next;
        _dummyHead->next = newNode;
        _size++;
    }

    // 在链表最后面添加一个节点
    void addAtTail(int val) {
        ListNode* newNode = new ListNode(val);
        ListNode* cur = _dummyHead;  //⭐统一处理空链表和非空链表，最终找到尾节点
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = newNode;
        _size++;
    }

    // 在下标为index的节点之前插入一个值为val的节点
    // 如果index等于0，那么新插入的节点为链表的新头节点
    // 如果index等于链表的长度，那么新插入的节点为链表的尾结点
    // 如果index大于链表的长度，则返回空
    // 如果index小于0，则在头部插入节点
    void addAtIndex(int index, int val) {
        if (index > _size) return;
        if (index < 0) index = 0;
        ListNode* newNode = new ListNode(val);
        ListNode* cur = _dummyHead;
        while (index--) {  //⭐从dummy开始走index步，最终停在index的前驱节点
            cur = cur->next;
        }
        newNode->next = cur->next;  //⭐插入节点
        cur->next = newNode;
        _size++;
    }

    // 删除下标为index的节点
    // 如果index大于等于链表的长度或小于0，直接返回
    void deleteAtIndex(int index) {
        if (index >= _size || index < 0) {
            return;
        }
        ListNode* cur = _dummyHead;
        while (index--) {
            cur = cur->next;  //⭐从dummy开始走index步，最终停在index的前驱节点
        }
        ListNode* tmp = cur->next;
        cur->next = cur->next->next;  //⭐删除节点
        delete tmp;
        tmp = nullptr;  //良好编程习惯，避免野指针
        _size--;
    }

    // 打印链表
    void printLinkedList() {
        ListNode* cur = _dummyHead;
        while (cur->next != nullptr) {
            cout << cur->next->val << " ";
            cur = cur->next;
        }
        cout << endl;
    }

private:
    int _size;
    ListNode* _dummyHead;
    //private表示只能在类内部访问
    //下划线_是一种编程习惯，标识类的成员变量（member variable）
    //_size记录当前链表的长度，便于判断操作是否合法
    //_dummyHead指向虚拟头结点，_dummyHead->next始终指向真实头结点
};