#include<iostream>
using namespace std;

template<typename T>
class Table {
private:
	T* head;
	int length;
	int size;
public:
	Table(int size);
	void add(T value);
	void insert(T value, int pos);
	void del(T value);
	void change(T value, int pos);
	void show();
	int query(T value);
	T operator[](int i);

};

template<typename T>
Table<T>::Table(int size) {
	head = new T[size];
	length = 0;
	this->size = size;
}

template<typename T>
void Table<T>::add(T values) {
	if (length == size) {
		T* temp = new T[size + 1];
		for (int i = 0; i < length; i++) {
			temp[i] = head[i];
		}
		delete[] head;
		head = temp;
		size++;
	}
	int i = length;
	head[i] = values;
	length++;
}

template<typename T>
void Table<T>::insert(T values, int pos) {
	if (pos<1 || pos>length + 1) {
		cout << "元素插入位置有误" << endl;
		return;
	}
	if (length == size) {
		T* temp = new T[size + 1];
		for (int i = 0; i < length; i++) {
			temp[i] = head[i];
		}
		delete[] head;
		head = temp;
		size++;
	}
	for (int i = length - 1; i >= pos - 1; i--) {
		head[i + 1] = head[i];
	}
	head[pos - 1] = values;
	length++;
}

template<typename T>
void Table<T>::del(T values) {
	for (int i = 0; i < length; i++) {
		if (head[i] == values) {
			for (int j = i+1; j < length; j++) {
				head[j - 1] = head[j];
			}
		}
	}
	length--;
}

template<typename T>
void Table<T>::change(T values, int pos) {
	head[pos - 1] = values;
}

template<typename T>
void Table<T>::show() {
	for (int i = 0; i < length;i++) {
		cout << head[i] << " ";
	}
	cout << endl;
}

template<typename T>
int Table<T>::query(T values) {
	for (int i = 0; i < length; i++) {
		if (head[i] == values) {
			return i+1;
		}
	}
	return -1;
}

template<typename T>
T Table<T>::operator[](int i) {
	return head[i];
}

int main() {
	Table<int> t(5);
	for (int i = 0; i < 5; i++) {
		t.add(i * 10);
	}
	t.add(50);
	t.show();
	t.insert(40, 3);
	t.show();
	t.del(40);
	t.show();
	t.change(60, 1);
	t.show();
	cout << t.query(50) << endl;
	
	return 0;
}