/*LeetCode704.二分查找
给定一个n个元素【有序】（升序）整型数组nums和一个目标值target，写一个函数
搜索nums中的target，如果目标值存在返回下标，否则返回-1。

假设：1.nums中所有元素【不重复】；
2.n在[1，10000]之间；3.nums中每个元素都在[-9999，9999]之间。*/

/*二分法：用于在有序数组中查找特定元素。思路是将数组分成两半，
通过比较中间元素与目标值，确定下一步查找的二分之一区间。
1.初始化：定义两个下标left和right，分别表示当前查找的区间的边界
         ⭐指针为【绝对内存地址】，可以通过 nums.data() + left 获取。
2.循环条件：在每次迭代中，检查left和right的关系，以决定是否继续查找；
3.计算中间值：在查找过程中，计算中间位置middle；
4.比较并调整区间：
    如果middle值大于target，则目标值在左半边，调整right；
    如果middle值小于target，则目标值在右半边，调整left；
    如果middle值等于目标值，则返回中间值。*/

/*易错点：1.while(left<=right) or while(left<right)
2.right=middle-1 or right=middle */

#include<iostream>
#include<vector>
using namespace std;

class Solution{ //定义Solution类，用于封装特定算法或解决方案，提供外部调用接口，适合单元测试和调试
public:

//第一种写法：左闭右闭区间[left,right]

    int search1(vector<int>& nums, int target) {
        /*⭐ vector<int>：表示一个整型的动态向量；在c++中，vector是一种常用的容器，用来存储可变数量的元素。
          &：表示引用传递，意味着函数内部对nums的任何修改都会反映在原始数组上，而不是创建一个副本*/

        int left = 0;
        int right = nums.size() - 1; //定义左闭右闭区间[left,right]；⭐.size()返回值通常是size_t类型（无符号整数）

        while (left <= right) { //left == right 时，区间依然有效，所以用<=；⭐ 区间的定义为循环不变量，循环的意义是更新搜索区间
            int middle = left + (right - left) / 2; //防止溢出（指 left+right 超出 int 范围）；
            // ⭐ C++ 整数除法是【向零截断】。这里被除数非负，所以结果恰好等于向下取整。

            if (nums[middle] > target) {
                right = middle - 1; //⭐target在左1/2区间，在[left, middle - 1]中
            } else if (nums[middle] < target) {
                left = middle + 1; //target在右1/2区间，在[middle + 1, right]中
            } else { //nums[middle] == target
                return middle; //找到目标值，返回下标
            }
        }

        return -1; //left > right时，搜索范围内没有元素可以查找，返回-1以指示未找到目标值
    }

//第二种写法：左闭右开区间[left,right)

    int search2(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size(); //定义左闭右开区间[left,right)

        while (left < right) { //left == right时，[left,right)是无效空间，所以用<
            int middle = left + ((right - left) >> 1); // >>1表示二进制右移一位；相当于除以2，并向下取整

            if (nums[middle] > target) {
                right = middle; //target在左1/2区间，在[left, middle)中
            } else if (nums[middle] < target) {
                left = middle + 1; //target在右1/2区间，在[middle + 1, right)中
            } else { //nums[middle] == target
                return middle;
            }
        }

        return -1;
    }

};

int main() {
    Solution solution; // ⭐创建Solution类的实例，以调用非静态成员函数
    vector<int> nums = {-1, 0 , 3, 5, 9, 12};
    int target = 9;

    int result = solution.search1(nums, target);

    if (result != -1) {
        cout << "Target found at index: " << result << endl;
    } else {
        cout << "Target not found." << endl;
    }
    /*⭐cout 是C++中的标准输出流（Standard Output Stream），位于std命名空间。
      相比于C语言的 printf 需要格式控制符（如 %d），cout 通过流插入运算符 << 自动识别类型。
      基本语法：std::cout << 数据1 << 数据2 << std::endl; 其中endl表示换行并刷新缓冲区。*/

    return 0; //返回0表示程序成功结束
}