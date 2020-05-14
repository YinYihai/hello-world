//作业：删除多余的集合类，使用继承方法实现相同的功能。 
#include <iostream>

class Prime {
public:
	Prime() :number(0) {
	}
	Prime(int n) :number(n) {
	}
	~Prime() {
	}
	operator int() const {
		return number;
	}
	bool isPrime() {
		if (number <= 1)
			return false;
		else {
			bool flag = true;
			for (int i = 2; i < number; ++i) {
				if (!(number % 2)) {
					flag = false;
					break;
				}
			}
			return flag;
		}
	}
private:
	const int number;
};

class PrimeSet {  //PrimeSet既可以装入Prime对象，也可以装入Prime的派生类对象
public:
	PrimeSet(int size) {
		//集合的构造什么？ 
		set = new Prime * [size];
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
		if (index == size)  return false;
		Prime* p = new Prime(n);
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
	int length() const {
		return size;
	}
	Prime** FAddress() const {
		return static_cast<Prime** const>(set);
	}

	bool addItem(Prime* item) { //这个函数既可以用于添加Prime对象，也可用于添加Prime的任何派生类对象。
		if (index == size) return false;
		set[index++] = item;
		return true;
	}

private:
	Prime** set;
	int size, index;
};

class SuperPrime : public Prime {
public:
	SuperPrime() :Prime(0), pset(3) {  //为什么必须有？ 
	}
	SuperPrime(int n) :Prime(n), pset(3) {
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
	bool isPrime() {   //类/对象的接口，更抽象说是外观 
		PrimeSet set(3); 
		set.add(sum());
		set.add(multi());
		set.add(squareSum());
		if (Prime::isPrime() && set.isAllPrime())
			return true;
		return false;
	}
private:
	PrimeSet pset;
	int sum() {
		int sum = 0;
		for (int i = 0; i < pset.length(); ++i)
			sum += *(pset.FAddress()[i]);
		return sum;
	}
	int multi() {
		int mul = 1;
		for (int i = 0; i < pset.length(); ++i)
			mul *= *(pset.FAddress()[i]);
		return mul;
	}
	int squareSum() {
		int squ = 0;
		for (int i = 0; i < pset.length(); ++i)
			squ += *(pset.FAddress()[i]) * *(pset.FAddress()[i]);
		return squ;
	}
};
int main() {
	SuperPrime sp(113);
	if (sp.isPrime())
		std::cout << "113 is SuperPrime" << std::endl;
	else
		std::cout << "113 is NOT SuperPrime" << std::endl;
	return 0;
}
