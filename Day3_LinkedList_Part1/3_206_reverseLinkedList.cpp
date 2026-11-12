/*Leetcode206.反转链表
反转一个单链表head，返回反转后的链表。

示例1：输入：head = [1,2,3,4,5] 输出：[5,4,3,2,1]
示例2：输入：head = [] 输出：[] */

using namespace std;

class Solution {
public:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    // 方法1：双指针
    // 维护pre和cur两个指针，每次保存cur的后继节点，将cur指向pre完成反转，然后推进pre和cur，直至cur为空。
    ListNode* reverseList1(ListNode* head) {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        ListNode* tmp;
        while(cur) {
            tmp = cur->next;  //保存后继节点
            cur->next = pre;  //反转当前节点
            pre = cur;  //推进前驱指针
            cur = tmp;  //推进当前指针
        }
        return pre;  //cur为空指针时，原链表指针全部完成反转，【pre】成为新链表头节点
    }

    // 方法2：递归法
    // ⭐通过递归调用的参数传递完成双指针法的状态推进（循环推进 → 函数栈推进）
    ListNode* reverse(ListNode* pre, ListNode* cur) {
        if (cur == nullptr) return pre;  //⭐cur为空指针时，递归到达原链表末尾，pre成为新链表头节点，开始逐层返回
        // 反转逻辑与双指针法一致
        ListNode* tmp = cur->next;
        cur->next = pre;
        return reverse(cur, tmp); //本轮的cur和tmp成为下一轮的pre和cur
    }
    ListNode* reverseList2(ListNode* head) {
        // 初始化逻辑与双指针法一致
        // ListNode* pre = nullptr;
        // ListNode* cur = head;
        return reverse(nullptr, head);
    }
};