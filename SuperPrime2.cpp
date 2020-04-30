//作业：面向对象设计以下框架的代码细节，程序能编译运行得到正确结果
#include <iostream>
class PrimeSet;
class Prime {
	friend class PrimeSet;
public:
	Prime() :
			number(0) {
	}
	Prime(int n) :
			number(n) {
	}
	~Prime() {
	}
	bool isPrime() {
		if (number <= 1)
			return false;
		else {
			bool flag = true;
			for (int i = 2; i < number; ++i) {
				if (!(number % i)) {
					flag = false;
					break;
				}
			}
			return flag;
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
		//集合的构造什么？
		set = new Prime*[size];
		this->size = size;
		index = 0;
	}
	~PrimeSet() {
		for (int i = 0; i < index; ++i)  //销毁对象
			delete set[i];
		delete[] set;
	}
	int count() {
		int count = 0;
		for (int i = 0; i < size; i++)
			if (set[i]->isPrime())
				count += 1;
		return count;
	}

	bool add(int n) {
		if (index == size)
			return false;
		Prime *p = new Prime(n);
		set[index] = p;
		index += 1;
		return true;
	}
	bool isAllPrime() {
		for (int i = 0; i < index; i++)
			if (!set[i]->isPrime())
				return false;
		return true;
	}
	Prime** value() const {
		return set;
	}
private:
	Prime **set;
	int size, index;
};
class SuperPrime: public Prime {
public:
	SuperPrime() :
			Prime(0), pset(3) {  //为什么必须有？
	}
	SuperPrime(int n) :
			Prime(n), pset(3) {
		// number split into N
		int temp = n;
		while (temp > 0) {
			int t = temp % 10;
			temp /= 10;
			pset.add(t);  //作业：单个数字为对象？还是和/积/平方和为对象？
		}
	}
	~SuperPrime() {
	}
	bool isSuperPrime() {
		PrimeSet tempSet(3);
		tempSet.add(sum());
		tempSet.add(multi());
		tempSet.add(squareSum());
		if (Prime::isPrime() && tempSet.isAllPrime())
			return true;
		return false;
	}
private:
	PrimeSet pset;
	int sum() {
		int sum = 0;
		for (int i = 0; i < 3; ++i)
			sum += **(pset.value() + i);
		return sum;
	}
	int multi() {
		int mul = 1;
		for (int i = 0; i < 3; ++i)
			mul *= **(pset.value() + i);
		return mul;
	}
	int squareSum() {
		int squ = 0;
		for (int i = 0; i < 3; ++i)
			squ += **(pset.value() + i) * **(pset.value() + i);
		return squ;
	}
};
class SuperPrimeSet {
public:
	SuperPrimeSet(int from, int to) {
		size = to - from;
		for (int i = from; i < to; i++)
			set[i - from] = new SuperPrime(i);
	}
	~SuperPrimeSet() {
		for (int i = 0; i < size; i++)
			delete set[i];
	}
	int count() {
		int count = 0;
		for (int i = 0; i < size; i++)
			if (set[i]->isSuperPrime())
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
	SuperPrime **set;
	int size, index;
};
int main() {
	SuperPrime sp(113);
	if (sp.isSuperPrime())
		std::cout << "113 is SuperPrime" << std::endl;
	else
		std::cout << "113 is NOT SuperPrime" << std::endl;
	return 0;
}
