//作业：完成以下框架的代码细节，程序能编译运行得到正确结果 
#include <iostream>
#include <cstring>
class SuperPrime {
public:
    SuperPrime(int n = 0) :number(n) {
        memset(N, 0, 100 * sizeof(int));
        size = 0;
    }
	operator int() const {
        return number;
    }
    ~SuperPrime() = default;
    bool isSuperPrime() {
        split();
        int a = sum();
        int b = multi();
        int c = squareSum();
        return isPrime(number) && isPrime(a) && isPrime(b) && isPrime(c);
    }
private:
    int number; // tip : change one
    int N[100]{}, size;
    bool isPrime(int n) {
        if (n <= 1) return false;
        else
        {
            bool flag = true;
            for (int i = 2; i < n; ++i)
                if (!(n % i))
                {
                    flag = false;
                    break;
                }
            return flag;
        }
    }
    void split() {
        int x = number;
        memset(N, 0, 100 * sizeof(int));
        size = 0;
        while (x)
        {
            int i = x % 10;
            N[size++] = i;
            x /= 10;
        }
    }
    int sum() {
        int s = 0;
        for (int i = 0; i < size; ++i)
            s += N[i];
        return s;
    }
    int multi() {
        int m = 1;
        for (int i = 0; i < size; ++i)
            m *= N[i];
        return m;
    }
    int squareSum() {
        int s = 0;
        for (int i = 0; i < size; ++i)
            s += N[i] * N[i];
        return s;
    }
};
class Set {
public:
    Set(int from, int to) {
        if (to <= from)
            throw std::exception();
        else
        {
            size = to - from;
            for (int i = 0; i < size; ++i)
                set[i] = from + i;
        }
    }
    ~Set() = default;
    int count() {
        int count = 0;
        for (int i = 0; i < size; ++i)
        {
            if (set[i].isSuperPrime())
                count += 1;
        }
        return count;
    }
    int sum() {
        int sum = 0;
        for (int i = 0; i < size; ++i)
            if (set[i].isSuperPrime())
                sum += set[i];
        return sum;
    }
private:
    SuperPrime set[1000];
    int size;
};
int main() {
    Set ss(100, 999);
    std::cout << "How Many: " << ss.count() << std::endl;
    std::cout << "Sum is " << ss.sum() << std::endl;
    return 0;
}
