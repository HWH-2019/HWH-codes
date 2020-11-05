#include<iostream>
using namespace std;

template<class T>
class ShareStack {
private:
	int headtop;		//前端栈顶指针
	int tailtop;		//后端栈顶指针
	int maxSize;		//存储空间大小
	T* elems;			//元素存储空间
public:
	ShareStack(int size = 100);
	virtual ~ShareStack() { delete[] elems; }
	bool Push(int k, const T& e);
	bool Pop(int k, T& e);
	bool IsEmpty();
	bool IsFull();
	void Show(int k);
	T& operator[](int i) { return elems[i]; }
};

template<class T>
ShareStack<T>::ShareStack(int size) {
	headtop = -1;
	tailtop = size;
	maxSize = size;
	elems = new T(size);
}

template<class T>
bool ShareStack<T>::Push(int k, const T& e) {
	if (IsFull()) {
		return false;
	}
	else {
		if (k == 0) {
			elems[++headtop] = e;
			return true;
		}
		else {
			elems[--tailtop] = e;
			return true;
		}
	}
}

template<class T>
bool ShareStack<T>::Pop(int k, T& e) {
	if (k == 0) {
		if (headtop == -1) {
			return false;
		}
		else {
			e = elems[headtop--];
			return true;
		}
	}
	else {
		if (tailtop == maxSize) {
			return false;
		}
		else {
			e = elems[tailtop++];
			return true;
		}
	}
}

template<class T>
bool ShareStack<T>::IsEmpty() {
	if (headtop == -1 && tailtop == maxSize) {
		return true;
	}
	else {
		return false;
	}
}

template<class T>
bool ShareStack<T>::IsFull() {
	if (headtop == tailtop - 1) {
		return true;
	}
	else {
		return false;
	}
}

template<class T>
void ShareStack<T>::Show(int k) {
	if (k == 0) {
		for (int i = 0; i <= headtop; i++) {
			cout << elems[i] << " ";
		}
	}
	else {
		for (int i = maxSize - 1; i >= tailtop; i--) {
			cout << elems[i] << " ";
		}
	}
}


int main() {
	ShareStack<int> test(15);
	for (int i = 0; i < 5; i++) {
		test.Push(0, i * 10);
	}
	for (int i = 14; i >= 10; i--) {
		test.Push(1, 16);
	}
	test.Show(0);
	cout << endl;
	test.Show(1);
	int e = 1;
	test.Pop(0, e);
	cout << e << endl;

	return 0;
}
