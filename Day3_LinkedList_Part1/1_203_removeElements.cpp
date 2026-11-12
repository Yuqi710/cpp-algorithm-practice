/*LeetCode203.移除链表元素
删除链表中等于给定值val的所有节点。

示例1：输入：head = [1,2,6,3,4,5,6], val = 6 输出：[1,2,3,4,5]
示例2：输入：head = [], val = 1 输出：[]
示例3：输入：head = [7,7,7,7], val = 7 输出：[] */

/*1.链表删除节点的本质:修改前驱节点的 next 指针
2.虚拟头结点：给头结点增加一个前驱节点，统一头结点和普通节点的处理逻辑 */

#include<iostream>
using namespace std;

struct ListNode {
    int val;                                    //数据域
    ListNode* next;                             //指针域
    ListNode(int x) : val(x), next(nullptr) {}  //构造函数
};

class Solution {
public:

    // 方法一：直接操作原链表
    ListNode* removeElements1(ListNode* head, int val) {
        //删除头结点
        while (head != nullptr && head->val == val) {  //⭐可能连续出现目标值，因此用while
            ListNode* tmp = head;
            head = head->next;  //【删除头结点】将head指针向后移动一位
            delete tmp;
        }

        //删除非头结点
        ListNode* cur = head;  //用cur遍历，保留链表入口head
        while (cur != nullptr && cur->next != nullptr) {  //⭐删除节点需要修改前驱节点的next指针，因此cur始终指向前驱节点、检查cur->next
            if (cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;  //【删除普通节点】链接前驱节点和后继节点，跳过待删除节点
                delete tmp;
            } else {
                cur = cur->next;  //cur继续向后遍历
            }
        }
        return head;
    }

    // 方法二：虚拟头结点
    ListNode* removeElements2(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(0);  //创建虚拟头结点
        dummyHead->next = head;  //⭐将虚拟头结点设置为原头结点的前驱节点

        ListNode* cur = dummyHead;  //cur依然始终指向待检查节点的前驱节点
        while(cur->next != nullptr) {
            if(cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        head = dummyHead->next;  //⭐原头结点可能已被删除，更新head为当前真正的头结点地址
        delete dummyHead;  //释放dummy节点，避免内存泄漏
        return head;
    }
};