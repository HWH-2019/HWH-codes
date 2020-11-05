#include<iostream>
using namespace std;

template<class T>
struct Node {
	T data;
	Node<T>* prior;
	Node<T>* next;
	Node();
	Node(const T& d, Node<T>* p,Node<T>* n);
};

template<class T>
Node<T>::Node() {
	prior = nullptr;
	next = nullptr;
}

template<class T>
Node<T>::Node(const T& d, Node<T>* p, Node<T>* n) {
	data = d;
	prior = p;
	next = n;
}

template<class T>
class DLinkList {
private:
	Node<T>* head;
	int length;
public:
	DLinkList();
	bool Insert(int n, const T& d);
	bool Del(int n);
	bool DelElem(const T& d);
	bool Change(int n, const T& d);
	bool ChangeElem(const T& old, const T& d);
	void Traverse(void (*visit)(const T& d));
	void Show();
};

template<class T>
DLinkList<T>::DLinkList() {
	head = new Node<T>;
	length = 0;
}

template<class T>
bool DLinkList<T>::Insert(int n, const T& d) {	
	if (n<1 || n>length + 1) {
		return false;
	}
	else {
		Node<T>* p = head;
		for (int i = 1; i < n; i++) {
			p = p->next;
		}
		Node<T>* q = new Node<T>(d, p, p->next);
		if(p->next!=nullptr) p->next->prior = q;
		p->next = q;
		
		length++;
		return true;
	}
}

template<class T>
bool DLinkList<T>::Del(int n) {
	if (n<1 || n>length) {
		return false;
	}
	else {
		Node<T>* p = head->next;
		for (int i = 1; i < n; i++) {
			p = p->next;
		}
		p->prior->next = p->next;
		if (p->next!=nullptr) p->next->prior = p->prior;
		length--;
		delete p;
		return true;
	}
}

template<class T>
bool DLinkList<T>::DelElem(const T& d) {
	Node<T>* p = head->next;
	while (p != nullptr && p->data != d) {
		p = p->next;
	}
	if (p == nullptr) {
		cout << "表中没有此元素";
		return false;
	}
	else {
		p->prior->next = p->next;
		if(p->next!=nullptr) p->next->prior = p->prior;
		length--;
		delete p;
		return true;
	}
	

}

template<class T>
bool DLinkList<T>::Change(int n, const T& d) {
	if (n<1 || n>length) {
		return false;
	}
	else {
		Node<T>* p = head->next;
		for (int i = 1; i < n; i++) {
			p = p->next;
		}
		p->data = d;
		return true;
	}
}

template<class T>
bool DLinkList<T>::ChangeElem(const T& old, const T& d) {
	Node<T>* p = head->next;
	while (p != nullptr && p->data != old) {
		p = p->next;
	}
	if (p == nullptr) {
		cout << "表中没有此元素";
		return false;
	}
	else {
		p->data = d;
		return true;
	}
}

template<class T>
void DLinkList<T>::Traverse(void (*visit)(const T& d)) {
	Node<T>* p = head->next;
	while (p != nullptr) {
		(*visit)(p->data);
		p = p->next;
	}
}

template<class T>
void DLinkList<T>::Show() {
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

int main() {
	DLinkList<int> Dlink;
	for (int i = 0; i < 10; i++) {
		Dlink.Insert(i + 1, i * 10);
	}
	Dlink.Insert(3, 100);
	Dlink.Show();
	cout << endl;
	//Dlink.Del(3);
	Dlink.DelElem(100);
	Dlink.Show();
	cout << endl;
	//Dlink.Change(3, 100);
	Dlink.ChangeElem(20, 100);
	Dlink.Show();
	cout << endl;
	Dlink.Traverse(show);
	return 0;
}