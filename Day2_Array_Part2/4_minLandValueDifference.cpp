/*44.开发商购买土地
给定一个城市区域，划分为 n * m 的区块，每个区块有不同的土地价值。需要将区域
通过横向【或】纵向切割成两个连续的子区域，并且每个子区域必须包含至少一个区块。要求找到
一种切割方式，是两个子区域的土地总价值差最小，输出这个最小差值。
1.第一行输入两个正整数，代表 n 和 m；
2.接下来的 n 行，每行输入 m 个正整数，代表每个区块的土地价值；
3.输出一个整数，代表两个子区域土地总价值的最小差值。*/

#include<iostream>
#include<vector>
#include<climits>
using namespace std;

// 版本一:先统计横向、列向累计值并存储在horizontal和vertical数组中，再遍历寻找最小差值

int main_c() {
    // 读取区域大小
    int n, m;
    cin >> n >> m;
    vector<vector<int>> vec(n, vector<int>(m, 0));
    int sum = 0;
    // 读取土地价值并计算总和
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> vec[i][j];
            sum += vec[i][j];
        }
    }
    // 统计横向
    vector<int> horizontal(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            horizontal[i] += vec[i][j];
        }
    }
    // 统计纵向
    vector<int> vertical(m, 0);
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            vertical[j] += vec[i][j];
        }
    }
    // 横向切割的最小差值
    int result = INT_MAX;
    int horizontalCut = 0;
    // i + 1 < n: 在第 i 行之后切割，下面至少要留一行
    for (int i = 0; i + 1 < n; i++) {
        horizontalCut += horizontal[i];
        // ⭐当 i 行及以上分配给A公司，A获得的土地总价值是horizontalCut
        // 此时B获得的土地总价值是sum - horizontalCut
        result = min(result, abs(sum - horizontalCut - horizontalCut));
    }
    // 纵向切割的最小差值
    int verticalCut = 0;
    // j + 1 < m: 在第 j 列之后切割，右边至少要留一列
    for (int j = 0; j + 1 < m; j++) {
        verticalCut += vertical[j];
        result = min(result, abs(sum - verticalCut - verticalCut));
    }
    cout << result << endl;

    return 0;
}

// 版本二：遍历过程中直接通过行末、列末的累计值计算子区域差值

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> vec(n, vector<int>(m, 0));
    int sum = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> vec[i][j];
            sum += vec[i][j];
        }
    }
    int result = INT_MAX;
    int count = 0; // 统计遍历过的行
    for (int i = 0; i + 1 < n; i++) {
        for(int j = 0; j < m; j++){
            count += vec[i][j];
            // 遍历到行末尾的时候开始计算
            if (j == m - 1){
                result = min(result, abs(sum - count - count));
            }
        }
    }
    count = 0; // 统计遍历过的列
    for (int j = 0; j + 1 < m; j++) {
        for(int i = 0; i < n; i++){
            count += vec[i][j];
            // 遍历到列末尾的时候开始计算
            if (i == n - 1){
                result = min(result, abs(sum - count - count));
            }
        }
    }
    cout << result << endl;

    return 0;
}