/*LeetCode59.螺旋矩阵II
给定一个正整数n，生成一个包含 1 到 n^2 所有元素、且元素按顺时针顺序螺旋排列的 n×n 正方形矩阵。
示例：输入：n = 3
输出：[[1, 2, 3],
       [8, 9, 4],
       [7, 6, 5]]

提示：从外向内顺时针画圈；每一圈的四条边统一采取左闭右开。 */

#include<vector>
#include<iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix (int n) {
        vector<vector<int>> result (n, vector<int> (n, 0)); // 用vector定义一个二维数组
        int loop = n / 2; // 计算需要循环的圈数
        int startx = 0, starty = 0; // 定义每循环一个圈的起始位置（左上角坐标）
        int offset = 1; // ⭐控制每一条边需要遍历的长度，每次循环右边界收缩一位
        int count = 1; // 用于追踪当前填入的数字，从 1 开始递增
        int mid = n / 2; // 记录矩阵中心的位置（⭐处理 n 为奇数的情况）
        /*若 n 为奇数，中心只会有一个元素；若 n 为偶数，中心会形成一个 2*2 的区域。*/
        int i, j;
        while (loop--) { // 当loop的值大于0时，循环会继续执行
            i = startx;
            j = starty;

            // 下面四个for循环就是模拟转了一圈
            // 模拟填充上行从左到右 [左闭右开）
            for (j; j < n - offset; j++) { // 每次循环，j 先参与当前循环体的操作，然后自增 1；所以循环结束时 j 为 n - offset
                result[i][j] = count++;
            }
            // 模拟填充右列从上到下 [左闭右开）
            for (i; i < n - offset; i++) {
                result[i][j] = count++;
            }
            // 模拟填充下行从右到左 [左闭右开）
            for (j; j > starty; j--) {
                result[i][j] = count++;
            }
            // 模拟填充左列从下到上 [左闭右开）
            for (i; i > startx; i--) {
                result[i][j] = count++;
            }

            // 下一圈开始的时候，行列起始位置各自要加 1
            startx++;
            starty++;

            // 下一圈每条边遍历长度也要缩短
            offset += 1; // 如：第一圈上行从 0 到 n-1，第二圈上行从 1 到 n-2
        }

        // 如果 n 为奇数，需要单独给矩阵的中心位置赋值
        if (n % 2) {
            result[mid][mid] = count;
        }
        return result;
    }
};

int main() {
    Solution solution;
    int n = 5;
    vector<vector<int>> matrix = solution.generateMatrix(n);

    for (const auto& row : matrix) { // 遍历matrix的每一行
    //const auto& 表示 row 是一个常量引用，自动推断出类型

        for (int num : row) { // 遍历当前row的每一个元素
            cout << num << " ";
        }
        cout << endl;

    }

    return 0;
}

/* 关于vector<vector<int>> result (n, vector<int> (n, 0)):
⭐ result[i][j]本质是先取第i个vector<int>，再取其中第j个元素；在刷题时视为矩阵的第i行第j列。*/