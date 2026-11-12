/*LeetCode977.有序数组的平方
给定一个按【非递减顺序】排序的整数数组nums，返回每个数字的平方组成的新数组，要求也按【非递减顺序】排序。

示例：输入：nums = [-4, -1, 0, 1, 3, 10]
输出：[0, 1, 1, 9, 16, 100]   */

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution{
public:

// 暴力解法：逐个平方，然后排序

    vector<int> sortedSquares1(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            nums[i] *= nums[i];
            /* ⭐ *= 是c++中的复合赋值运算符，用于将左侧变量的值与右侧表达式的值相乘，
            并将结果存回【左侧】变量，如 a *= b 等价于 a = a * b。 */
        }
        sort (nums.begin(), nums.end());
        return nums;
    }

// 第二种解法：双指针
/*思路：比较左右两侧的平方，选择较大的放入result数组右侧，向左依次递减*/

    vector<int> sortedSquares2(vector<int>& nums) {
        vector<int> result(nums.size(), 0); // ⭐一维vector的定义：vector<数据类型> 变量名(元素个数, 初始值);
        int k = nums.size() - 1; // k指向result数组的终止位置
        // for循环基本语法：for (初始化语句; 条件表达式; 更新语句) {}
        for (int i = 0, j = nums.size() - 1; i<=j;) { // i指向nums的起始位置，j指向nums的终止位置
            if(nums[i] * nums[i] < nums[j] * nums[j]) {
                result[k--] = nums[j] * nums [j]; //首先使用 k 的当前值，执行完代码后k的值减 1
                j--;
            } else {
                result[k--] = nums[i] * nums[i];
                i++;
            }
        }
        return result;
    }

};

int main() {
    Solution solution;
    vector<int> nums = {-4, -1, 0, 1, 3, 10};

    vector<int> results = solution.sortedSquares2(nums);

    cout << "平方后的排序数组是：";
    for (int num : results) {
        // 这是一种范围-based for循环，它遍历results向量中的每一个元素
        // int num 是一个临时变量，在每次迭代中，它会被赋值为result中的当前元素
        cout << num << " ";
        //将当前元素num输出到控制台，并在每个元素后面添加一个空格
    }
    cout << endl;

    return 0;
}