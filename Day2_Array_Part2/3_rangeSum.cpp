/*58.区间和
输入一个长度为 n 的整数数组 nums，输出每个查询区间 [a, b] 内数组元素的总和。*/

#include<iostream>
#include<vector>
using namespace std;

// 方法一：暴力求和

int main_c() {
    int n, a, b;
    cin >> n; // 从输入读取数组长度 n
    vector<int> nums(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> nums[i]; // 依次将输入的整数存入向量的第 i 个位置
    }
    while (cin >> a >> b)
    // cin >> a >> b 返回输入流的引用；用在 while 条件中时，根据流状态判断读取是否成功。
    {   int sum = 0;
        for (int k = a; k <= b; k++) {
            sum += nums[k];
        }
        cout << sum << endl;
    }
    return 0;
}

// 方法二：前缀和（空间换时间）

int main() {
    int n, a, b;
    cin >> n;
    vector<int> nums(n);
    vector<int> p(n);
    int presum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]); // 读取一个整数（"%d"）并存储到 nums[i] 中
        presum +=nums[i];
        p[i] = presum; // 前缀和组成的数组
    }
    while (scanf("%d%d", &a, &b) == 2) {
        // ⭐scanf需要修改变量的值，所以必须知道变量的地址（&）
        int sum;
        if (a == 0) {
            sum = p[b];
        } else {
            sum = p[b] - p[a - 1];
        } // ⭐提前计算、保存结果，再次查询时不需要遍历求和，只需要 O(1) 的减法操作
        printf("%d\n", sum); // \n是换行符
    }
    return 0;
}

/*
scanf("%d%d", &a, &b) 返回成功读取并赋值的整数个数。
因此用 == 2，确保两个下标都读成功后才进入循环。
*/