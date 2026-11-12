/*LeetCode27.移除元素
给定一个数组nums和一个值val，请【原地】移除所有数值等于val的元素，并返回
nums中与val不同的元素的数量k。移除后，nums前k个元素应为包含不等于val的元素。
元素的顺序可以发生改变。

示例：输入：nums = [0,1,2,2,3,0,4,2], val = 2
输出：5, nums = [0,1,4,0,3,_,_,_]

提示：数组在地址空间上是连续的 → 不能单独删除某数组元素，只能覆盖*/

/*双指针法：
快指针：用于遍历数组，寻找所有有效的元素；
慢指针：用于更新有效元素的位置，使其保持在数组的前面。
这种方法的优点在于只需要一次遍历（O(n)时间复杂度）且在原地操作（O(1)空间复杂度）*/

#include<iostream>
#include<vector>
#include<algorithm> //用于std:sort
#include<cassert> //用于断言
using namespace std;

class Solution{
public:

//暴力解法：依次搜索，整体移动

    int removeElement1(vector<int>& nums, int val) {
        int size = nums.size();
        for (int i = 0; i < size; i++) { //依次搜索
            if (nums[i] == val) { //发现需要移除的元素，就将后续数组集体向前移动一位（只能覆盖，不能删除）
                for (int j = i + 1; j < size; j++) {
                    nums[j - 1] = nums[j];
                }
                i--; //⭐如果不执行i--，在下一个循环中，i会自增为i+1，导致跳过了覆盖了i位置的新元素的检查
                size--;
            }
        }
        return size; //返回k值
    }

//第二种解法：双指针

    int removeElement2(vector<int>& nums, int val) {
        int slowIndex = 0;
        for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {  //快指针遍历
            if (nums[fastIndex] != val) {
                nums[slowIndex++] = nums[fastIndex];  //慢指针记录
                //⭐i++后置自增，++i前置自增
            }
        }
        return slowIndex;
    }

};

int main() {
    Solution solution;

    vector<int> nums= {0,1,2,2,3,0,4,2};
    int val = 2;
    vector<int> expectedNums = {0,1,3,0,4};

    int k = solution.removeElement1(nums, val);
    assert(k==expectedNums.size()); //验证返回的长度是否正确
    for (int i = 0; i < k; i++) {
        assert (nums[i] == expectedNums[i]); //验证内容是否与预期相符
    }
    cout << "removeElement passed!" << endl;

    return 0;
}

//注意：两种实现方法都没有改变元素的相对位置