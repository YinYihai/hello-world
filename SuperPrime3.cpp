//作业：大整数，比如9081321110693270343633073697474256143563558458718976746753830538032062222085722974121768604305613921745580037409259811952655310075487163797179490457039169594160088430571674960498834085812920457916453747019461644031395307920624947349951053530086146486307198155590763466429392673709525428510973272600608981219760099374675982933766845473509473676470788342281338779191792495900393751209539300628363443012 6538005862664913074813656220643842443844131905754565672075358391135537108795991638155474452610874309742867231360502542308382199053675592825240788613991898567277116881793749340807728335795394301261629479870548736450984003401594705923178314906195914825136973281314862289454100745237769034410057080703111299605127114594552921209928891515242515620324828055912854227507525717981351447473570262981491527798
//重新设计下面的代码，使其可以处理大整数的素数与超级素数
//同时仔细理解面向对象的编程方式

#include <iostream>
#include <cstring>
#include <string>
#include <utility>
using namespace std;

/*************************************************************/
/* 这段代码用于进行大数的加法,乘法,除法 */
int a[500], b[500], c[500], d[500], e[1000];

string strAdd(const string& s1, const string& s2) //字符串的加法
{   // 这里不进行运算符重载，是因为string类本身就进行过 “+” 的重载
    int m, n, v, t;
    m = s1.length();
    n = s2.length();
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int i = 0; i < m; i++) {
        a[m - 1 - i] = s1[i] - '0';
    }
    for (int i = 0; i < n; i++) {
        b[n - 1 - i] = s2[i] - '0';
    }
    m = max(m, n);
    m++;
    memset(c, 0, sizeof(c));
    for (int i = 0; i < m; i++) {
        v = a[i] + b[i];
        if ((c[i] + v) < 10)
            c[i] += v;
        else {
            c[i + 1] += (c[i] + v) / 10;
            c[i] = (c[i] + v) % 10;
        }
    }
    if (c[m - 1] == 0)    m--;
    string result;
    for (int i = m - 1; i >= 0; i--) result.push_back(c[i] + '0');
    return result;
}

string operator*(const string& a, const string& b) //字符串的乘法
{
    int i, j, u, v, w;
    u = a.length();
    v = b.length();
    memset(c, 0, sizeof(c));
    for (i = 0; i < u; i++)
        c[u - 1 - i] = a[i] - '0';
    for (i = 0; i < v; i++)
        d[v - 1 - i] = b[i] - '0';
    for (i = 0; i < u; i++) {
        for (j = 0; j < v; j++) {
            w = c[i] * d[j];
            if (e[i + j] + w < 10)    e[i + j] += w;
            else {
                e[i + j + 1] += (e[i + j] + w) / 10;
                e[i + j] = (e[i + j] + w) % 10;
            }
        }
    }
    for (i = u + v - 1; i > 0 && e[i] == 0; i--);
    string temp;
    for (; i >= 0; i--) temp.push_back(e[i] + '0');
    return temp;
}

bool operator<(const string& s1, const string& s2)  // 字符串的大小比较
{
    if (s1.length() < s2.length()) return true;
    else if (s1.length() > s2.length()) return false;
    else return s1 < s2;
}

bool compare(int a[], int b[])
{
    if (a[0] != b[0])  return a[0] > b[0];
    for (int i = a[0]; i > 0; --i)
    {
        if (a[i] != b[i])
            return a[i] > b[i];
    }
    return true;
}

pair<string, string>
operator/(const string& s1, const string& s2)  // 字符串的除法
{
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(c, 0, sizeof(c));
    a[0] = s1.length();
    b[0] = s2.length();
    for (int i = 1; i <= a[0]; ++i) a[i] = s1[a[0] - i] - '0';
    for (int i = 1; i <= b[0]; ++i) b[i] = s2[b[0] - i] - '0';
    c[0] = a[0] - b[0] + 1;
    for (int i = c[0]; i > 0; --i)
    {
        memset(d, 0, sizeof(d));
        for (int j = 1; j <= b[0]; j++)
            d[j + i - 1] = b[j];
        d[0] = b[0] + i - 1;
        while (compare(a, d))
        {
            c[i]++;
            for (int i = 1; i <= a[0]; i++)
            {
                a[i] -= d[i];
                if (a[i] < 0)
                {
                    a[i + 1]--;
                    a[i] += 10;
                }
            }
            while (a[0] > 0 && a[a[0]] == 0)    a[0]--;
        }
    }
    while (c[0] > 1 && c[c[0]] == 0)    c[0]--;
    string Quotient;
    for (int i = c[0]; i > 0; --i)  Quotient.push_back(c[i] + '0');
    string Remainder;
    for (int i = a[0]; i > 0; --i)  Remainder.push_back(a[i] + '0');
    return { Quotient, Remainder };
}
/*************************************************************/

class BigPrime {
public:
    BigPrime(string n = string("")) : num(n) {  }
    virtual bool isPrime() const
    {
        if (num[0] == '-') return false;
        else if (num < "2") return false;
        else
        {
            for (string s = "2"; s < num; s = strAdd(s, "1"))
            {
                auto temp = num / s;
                if (temp.first == string("0"))
                    return false;
            }
            return true;
        }
    }
    virtual ~BigPrime() {}
    const string valueOf() {
        return num;
    }
protected:
    const string num;
};

class BigSuperPrime : public BigPrime {
public:
    BigSuperPrime(string n = string("")) :
        BigPrime(n), sum("0"), mul("1"), squ("0") {  }
    virtual bool isPrime() override
    {
        for (int i = 0; i < num.length(); ++i)
        {
            string temp; temp.push_back(num[i]);
            sum = strAdd(sum, temp);
            mul = sum * temp;
            squ = strAdd(squ, temp*temp);
        }
        BigPrime b0(sum);
        BigPrime b1(mul);
        BigPrime b2(squ);
        if (BigPrime::isPrime() && b0.isPrime() && b1.isPrime() && b2.isPrime())
            return true;
        else return false;
    }
private:
    string sum;
    string mul;
    string squ;
};

template <typename T>
class Set {
public:
    Set(int sz);
    ~Set();
    bool add(T* bp);
    bool remove(T* bp);
    int count() const {
        int ret = 0;
        for (int i = 0; i < index; i++) {
            if (pset[i]->isPrime())
                ret += 1;
        }
        return ret;
    }
    int sum() const {
        return 0;
    }
private:
    T** pset;
    int size, index;
};

int main() {
    Set<BigPrime> set(1000);
    BigSuperPrime bp("212121221111111212211211212221"), bp1("3231122122222212111111111112221221");
    set.add(&bp);
    set.add(&bp1);
    std::cout << set.count() << std::endl;
    return 0;
}

template <typename T>
Set<T>::Set(int sz) :size(sz) {
    index = 0;
    pset = new T * [size];  //分配存储空间
}

template <typename T>
Set<T>::~Set() {
    delete[] pset;  //回收
}

template <typename T>
bool Set<T>::add(T* bp) {
    pset[index++] = bp;
    return true;
}
