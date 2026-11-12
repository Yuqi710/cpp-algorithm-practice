#include<iostream>
using namespace std;

//void表示这个函数没有返回值
void test_array(){
    int array[2][3] = {  //定义二维数组
        {0,1,2},
        {3,4,5}
    };
    cout << &array[0][0] << " " << &array[0][1] << " " << &array[0][2] << endl;
    cout << &array[1][0] << " " << &array[1][1] << " " << &array[1][2] << endl;
    //使用cout打印数组元素的地址
    //数组下标从0开始
}

int main(){
    test_array();
}

//地址为16进制，每个int元素占用4个字节
//运行结果表明：c++中二维数组在地址空间上是连续的 → 在删除或增添元素时，需要移动其他元素的地址