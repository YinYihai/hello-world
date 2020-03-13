//超级素数：它本身，各位数字的和，各位数字的平方和，都是素数。
//求 100~10000 内的所有超级素数，及它们的平均数。

//要安装python运行环境，注意python2与python3的区别挺大的
def isPrime(x):
    if x <= 1:
        return False
    else:
        flag = True
        for i in range(2, x):
            if x % i == 0:
                flag = False
                break
        return flag

if __name__ == '__main__':
    total = 0
    cnt = 0
    for x in range(10, 10001, 1):
        s = str(x)
        sum0, sum1 = 0, 0
        for e in s:
            n = int(e)
            sum0 += n
            sum1 += n**2
        if isPrime(x) and isPrime(sum0) and isPrime(sum1):
            print(x)
            total += x;
            cnt += 1;
    print("average = ",total/cnt);
