//超级素数：它本身，各位数字的和，各位数字的平方和，都是素数。
//求 100~10000 内的所有超级素数，及它们的平均数。

public class SuperPrime {
    static boolean isPrime(int x) {
        if (x <= 1) return false;
        else
        {
            boolean flag = true;
            for (int i = 2; i < x; ++i) {
                if (x%i == 0) {
                    flag = false;
                    break;
                }
            }
            return flag;
        }
    }
    public static void main(String[] args) {
        int total = 0; int cnt = 0;
        for (int i = 10; i <= 10000; ++i)
        {
            int sum0 = 0, sum1 = 0;
            String num = String.valueOf(i);
            for (int j = 0; j < num.length(); ++j)
            {
                int n = (int)(num.charAt(j))-(int)('0');
                sum0 += n;
                sum1 += n*n;
            }
            if (isPrime(i) && isPrime(sum0) && isPrime(sum1)) {
                System.out.println(i);
                total += i; ++cnt;
            }
        }
        System.out.println("average = " + total/(double)cnt);
    }
}