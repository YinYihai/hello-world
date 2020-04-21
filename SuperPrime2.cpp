//作业：面向对象设计以下框架的代码细节，程序能编译运行得到正确结果
#include <iostream>
class Prime {
public:
	Prime() :
			number(0) {
	}
	Prime(int n) :
			number(n) {
	}
	~Prime() {
	}
	bool isPrime() const { //2到number-1的因子
		if (number < 0)
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
	friend class SuperPrime;
public:
	PrimeSet(int size) {
		//集合的构造什么？
		N = new Prime*[size];
		this->size = size;
		index = 0;
	}
	~PrimeSet() {
		for (int i = 0; i < index; ++i)  //销毁对象
			delete N[i];
		delete[] N;
	}
	bool add(int n) {
		if (index == size)
			return false;
		Prime *p = new Prime(n);
		N[index] = p;
		index += 1;
		return true;
	}
	bool isAllPrime() {
		for (int i = 0; i < index; i++)
			if (!N[i]->isPrime())
				return false;
		return true;
	}
private:
	Prime **N;
	int size, index;
};
class SuperPrime {
public:
	SuperPrime() :
			number(0), pset(3) {  //为什么必须有？
	}
	SuperPrime(int n) :
			number(n), pset(3) {
		split();  //它就是构造对象
	}
	~SuperPrime() {
	}
	bool isSuperPrime() { //怎么使用pset？
		PrimeSet set(4);
		set.add(number);
		set.add(sum());
		set.add(multi());
		set.add(squareSum());

		if (set.isAllPrime())
			return true;
		return false;
	}
private:
	const int number;
	PrimeSet pset;
	void split() {   //工厂方法设计模式
		// number split into N
		int temp = number;
		while (temp > 0) {
			int n = temp % 10;
			temp /= 10;
			pset.add(n);  //作业：单个数字为对象？还是和/积/平方和为对象？
		}
	}
	int sum() {
		int sum = 0;
		for (int i = 0; i < pset.index; ++i)
			sum += *(pset.N[i]);
		return sum;
	}
	int multi() {
		int multi = 1;
		for (int i = 0; i < pset.index; ++i)
			multi *= *(pset.N[i]);
		return multi;
	}
	int squareSum() {
		int squareSum = 0;
		for (int i = 0; i < pset.index; ++i)
			squareSum += (*(pset.N[i])) * (*(pset.N[i]));
		return squareSum;
	}
};
class SuperPrimeSet {
public:
	SuperPrimeSet(int from, int to) {
		size = to - from;
		set = new SuperPrime*[size];
		for (int i = from; i < to; i++)
			set[i - from] = new SuperPrime(i);
		index = 0;
	}
	~SuperPrimeSet() {
		for (int i = 0; i < size; i++)
			delete set[i];
		delete[] set;
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

