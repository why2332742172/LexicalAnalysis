#include <stdio.h>

int main(int a){
    double x = -1.234;
    x++;
    x+=-1.2345;
    printf("x = %d",x);
    fuc(x);
    return 0;
}

void fuc(double a){
    printf("x = %d",x);
}

//问题 参数无法解释类型