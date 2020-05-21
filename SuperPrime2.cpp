//作业：删除多余的集合类，使用继承方法实现相同的功能。
#include <iostream>
class Prime {
public:
    Prime():number(0) { }
    Prime(int n):number(n) { }
    virtual ~Prime() { }
    virtual bool isPrime() {
        if (number <= 1) return false;
        else {
        	for (int i = 2; i < number; ++i) {
        		if (!(number % i))
        			return false;
        	}
        	return true;
        }
    }
    operator int() const {
        return number;
    }
private:
    const int number;
};
class PrimeSet {
public:
    PrimeSet(int size) {
        set = new Prime*[size];
        this->size = size;
        index = 0;
    }
    ~PrimeSet() {
        delete[] set;
    }
    int count() {
        int count = 0;
        for (int i = 0; i < size; i++)
            if(set[i]->isPrime())
                count += 1;
        return count;
    }

    bool add(Prime *p) {
        if(index == size)  return false;
        set[index] = p;
        index += 1;
        return true;
    }
    bool isAllPrime() {
        for(int i = 0; i < index; i++)
            if (!set[i]->isPrime())
                return false;
        return true;
    }
    const int operator[](int n) {
    	if (n > index - 1 ||  n < 0)
    		throw "IndexOutOfBounds";
    	return *set[n];
    }
    const int length() const {
    	return index;
    }
private:
    Prime **set;
    int size, index;
};
class SuperPrime : public Prime {
public:
    SuperPrime():Prime(0), pset(3) {  }
    SuperPrime(int n):Prime(n), pset(3) {
        int temp = n;
        while(temp > 0) {
            int t = temp % 10;
            temp /= 10;
            pset.add(new Prime(t));
        }
    }
    ~SuperPrime() {
    }
    virtual bool isPrime() override{
    	PrimeSet set(3);
    	set.add(new Prime(sum()));
    	set.add(new Prime(multi()));
    	set.add(new Prime(squareSum()));
        if (Prime::isPrime() && set.isAllPrime())
            return true;
        return false;
    }
private:
    PrimeSet pset;
    int sum() {
    	int sum = 0;
    	for (int i = 0; i < pset.length(); ++i)
    		sum += pset[i];
        return sum;
    }
    int multi() {
    	int mul = 1;
    	for (int i = 0; i < pset.length(); ++i)
    		mul *= pset[i];
        return mul;
    }
    int squareSum() {
    	int squ = 0;
    	for (int i = 0; i < pset.length(); ++i)
    		squ +=  pset[i] * pset[i];
        return squ;
    }
};
int main() {
    SuperPrime p(13);
    SuperPrime sp(113);
    PrimeSet set(2);
    set.add(&sp);
    set.add(&p);
    std::cout << "How Many : " << set.count() << std::endl;
    return 0;
}
