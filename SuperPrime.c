//超级素数：它本身，各位数字的和，各位数字的平方和，都是素数。
//求 100~10000 内的所有超级素数，及它们的平均数。
#include <stdio.h>
#include <string.h>

int splitNumber[5] = {0};

int isPrime(int x)
{
    if (x <= 1) return 0;
    else
    {
        int flag = 1;
        for (int i = 2; i < x; ++i)
            if (!(x % i))
            {
                flag = 0;
                break;
            }
        return flag;
    }
}
int splitNum(int x, int* num)
{
    memset(num, 0, 5*sizeof(int));
    int bit = 0;
    while (x)
    {
        int i = x % 10;
        num[bit++] =  i;
        x /= 10;
    }
    return bit;
}


int main()
{
    int total = 0, cnt = 0;
    for (int i = 10; i <= 10000; ++i)
    {
        int bit = splitNum(i, splitNumber);
        int sum0 = 0, sum1 = 0;

        for (int j = bit-1; j >= 0; --j)
        {
            sum0 += splitNumber[j];
            sum1 += splitNumber[j]*splitNumber[j];
        }
        if (isPrime(i) && isPrime(sum0) && isPrime(sum1))
        {
            printf("%d\n", i);
            total += i;
            ++cnt;
        }
    }
    printf("average = %f\n", total/(cnt*1.0));
    printf("\n");
    return 0;
}
