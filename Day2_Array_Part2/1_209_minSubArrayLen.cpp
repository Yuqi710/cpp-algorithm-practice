/*LeetCode209.长度最小的子数组
给定一个含有n个【正整数】的数组nums和一个正整数target，找出该数组中满足：
其总和>=target、长度最小的连续子数组，并返回这个子数组的长度。
若不存在符合条件的子数组则返回0。*/

#include<iostream>
#include<vector>
#include<cstdint>
using namespace std;

class Solution {
public:

//暴力解法：两个for循环，遍历所有区间

    int minSubArrayLen1(vector<int>& nums, int target) {
        int result = INT32_MAX; // 所求最小子数组长度；⭐【INT32_MAX】表示32位有符号整数能表示的最大值（2^31-1），常用于最小值问题的初始化
        int sum = 0; // 子数组的数值之和
        int subLength = 0; // 子数组的长度
        for (int i = 0; i < nums.size(); i++) {  // 设置子数组起点为i
            sum = 0;
            for (int j = i; j < nums.size(); j++) {  // 设置子数组终点为j
                sum += nums[j];
                if (sum >= target) {  // 一旦发现子数组数值和超过了target，更新result
                    subLength = j - i + 1;
                    result = result < subLength ? result : subLength;
                    // 等同于取 min(result, subLength)：如果result的值小于subLength，那么result保持不变；否则，result将被设置为subLength
                    break; // ⭐ 一旦符合条件就break（结束j的后续枚举）（在i起点下的序列完成检索，进入i+1起点）
                }
            }
        }
        return result == INT32_MAX ? 0 : result;
        // 如果result没有被赋值，则返回0，表示没有符合条件的子序列
    }

//滑动窗口：右指针负责让窗口合法，左指针负责让窗口最优

    int minSubArrayLen2(const vector<int>& nums, int target) {
        int result = INT32_MAX;
        int sum = 0; // 滑动窗口中数值之和sum
        int subLength = 0; // 滑动窗口的长度
        int i = 0; // 滑动窗口左指针i
        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j]; // sum < target时，扩张窗口右边界（j++）
            while (sum >= target) { // ⭐⭐ 使用while（反复判断）而不是if（只判断一次条件），不断检查子序列是否符合条件
                // sum >= target时，更新最小长度、收缩窗口左边界（i++）
                subLength = j - i + 1;
                result = result < subLength ? result : subLength;
                sum -= nums[i++];
            }
        }
        return result == INT32_MAX ? 0 : result;
    }

};

int main() {
    Solution solution;
    vector<int> nums = {2, 3, 1, 2, 4, 3};
    int target = 7;

    int result = solution.minSubArrayLen2(nums, target);
    cout << "符合条件的子数组的最小长度为：" << result << endl;

    return 0;
}