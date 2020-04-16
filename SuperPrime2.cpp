//作业：面向对象设计以下框架的代码细节，程序能编译运行得到正确结果
#include <iostream>
class SuperPrime {
public:
    SuperPrime() :number(0) {  //为什么必须有？
        size = 0;
    }
    SuperPrime(int n) :number(n) {
        size = 0;
    }
    ~SuperPrime() {
        for (int i = 0; i < size; ++i)  //销毁对象
            delete N[i];
    }
    operator int() const {
        return number;
    }
    bool isSuperPrime() {
    	split();  //它就是构造对象
        SuperPrime a(this->sum());  //将普通整数转变为对象
        SuperPrime b(this->multi());
        SuperPrime c(this->squareSum());
        bool flag = false;
        if (isPrime() && a.isPrime() && b.isPrime() && c.isPrime())
            flag = true;
        return flag;
    }
private:
    const int number;
    SuperPrime* N[5] = { };
    int size;
    bool isPrime() {
        int n = number;
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
    void split() {   //工厂方法设计模式
        // number split into N
        int temp = number;
        while (temp > 0) {
            int n = temp % 10;
            temp /= 10;
            N[size] = new SuperPrime(n);   //构造对象
            size += 1;
        }
    }
    int sum() {
        int s = 0;
        for (int i = 0; i < size; ++i)
            s += *N[i];
        return s;
    }
    int multi() {
        int m = 1;
        for (int i = 0; i < size; ++i)
            m *= (*N[i]);
        return m;
    }
    int squareSum() {
        int s = 0;
        for (int i = 0; i < size; ++i)
            s += (*N[i]) * (*N[i]);
        return s;
    }
};
class Set {
public:
    Set(int from, int to) {
        size = 0;
    }
    ~Set() {
    }
    int count() {
        int count = 0;
        for (int i = 0; i < size; i++)
            if(set[i].isSuperPrime())
                count += 1;
        return count;
    }
    int sum() {
        int sum = 0;
        /*
        for (int i = 0; i < size; i++)
          if(set[i].isSuperPrime())
            sum += set[i];
            */
        return sum;
    }
private:
    SuperPrime set[1000];
    int size;
};
int main() {
    SuperPrime sp(113);
    if (sp.isSuperPrime())
        std::cout << "113 is SuperPrime" << std::endl;
    else
        std::cout << "113 is NOT SuperPrime" << std::endl;
    return 0;
}
