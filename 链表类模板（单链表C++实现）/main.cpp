#include<iostream>
using namespace std;

template<class T>
struct Node {
	T data;
	Node<T>* next;
	Node();
	Node(const T& d, Node<T>* n);
};

template<class T>
Node<T>::Node() {
	next = nullptr;
}

template<class T>
Node<T>::Node(const T& d, Node<T>* n) {
	data = d;
	next = n;
}

template<class T>
class LinkList {
private:
	Node<T>* head;
	int length;
public:
	LinkList();
	bool Insert(int n,const T& d);
	bool Del(int n);
	bool DelElem(const T& d);
	bool Change(int n, const T& d);
	bool ChangeElem(const T& old, const T& d);
	void Traverse(void (*visit)(const T& d));
	void Show();
};

template<class T>
LinkList<T>::LinkList() {
	head = new Node<T>;
	length = 0;
}

template<class T>
bool LinkList<T>::Insert(int n, const T& d) {
	if (n<1||n>length+1) {
		return false;
	}
	else {
		Node<T>* p = head;
		for (int i = 1; i < n; i++) {
			p = p->next;
		}
		Node<T>* q = new Node<T>(d, p->next);
		p->next = q;
		length++;
		return true;
	}
}

template<class T>
void LinkList<T>::Traverse(void (*visit)(const T& d)) {
	Node<T>* p = head->next;
	while (p != nullptr) {
		(*visit)(p->data);
		p = p->next;
	}
}

template<class T>
void LinkList<T>::Show() {
	Node<T>* p = head->next;
	while (p != nullptr) {
		cout << p->data << " ";
		p = p->next;
	}
}


template<typename T>
void show(const T& d) {
	cout << d << " ";
}

template<class T>
bool LinkList<T>::Del(int n) {
	if (n<1 || n>length) {
		return false;
	}
	else {
		Node<T>* p = head,*q;
		for (int i = 1; i < n; i++) {
			p = p->next;
		}
		q = p->next;
		p->next = q->next;
		delete q;
		length--;
		return true;
		
	}
}

template<class T>
bool LinkList<T>::DelElem(const T& d) {
	Node<T>* p = head,*q;
	while (p->next != nullptr && p->next->data != d) {
		p = p->next;
	}
	q = p->next;
	if (q != nullptr) {
		p->next = q->next;
		delete q;
		length--;
		return true;
	}
	else {
		cout << "表中不存在此元素";
		return false;
	}
}

template<class T>
bool LinkList<T>::Change(int n, const T& d) {
	if (n<1 || n>length) {
		return false;
	}
	else {
		Node<T>* p = head;
		for (int i = 0; i < n; i++) {
			p = p->next;
		}
		p->data = d;
		return true;
	}
}

template<class T>
bool LinkList<T>::ChangeElem(const T& old,const T& d) {
	Node<T>* p = head->next;
	while (p != nullptr && p->data != old) {
		p = p->next;
	}
	if (p != nullptr) {
		p->data = d;
		return true;
	}
	else {
		cout << "表中没有此元素";
		return false;
	}
}

int main() {
	LinkList<int> link;
	for (int i = 0; i < 10; i++) {
		link.Insert(i+1,i * 10);
	}
	link.Insert(3, 100);
	link.Show();
	cout << endl;
	//link.Del(3);
	link.DelElem(100);
	link.Show();
	cout << endl;
	//link.Change(3, 100);
	link.ChangeElem(20, 100);
	link.Show();
	cout << endl;
	link.Traverse(show);
	return 0;
}