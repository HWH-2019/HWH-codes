#include<iostream>
#include<queue>
#include<stack>
using namespace std;

template<class T>
class BinTreeNode {
public:
	T data;							//数据域
	BinTreeNode<T>* leftChild;		//指针域(左孩子)
	BinTreeNode<T>* rightChild;		//指针域(右孩子)
public:
	BinTreeNode();
	BinTreeNode(const T& d, BinTreeNode<T>* l = nullptr, BinTreeNode<T>* r = nullptr);
};

//构造函数
template<class T>
BinTreeNode<T>::BinTreeNode() {
	leftChild = nullptr;
	rightChild = nullptr;
}

template<class T>
BinTreeNode<T>::BinTreeNode(const T& d, BinTreeNode<T>* l , BinTreeNode<T>* r) {
	data = d;
	leftChild = l;
	rightChild = r;
}

template<class T>
class BinaryTree {
private:
	BinTreeNode<T>* root;
	//辅助函数
	BinTreeNode<T>* CopyTree(BinTreeNode<T>* t);	//复制二叉树
	void PreOrder(BinTreeNode<T>* t, void (*visit)(const T& ));	//先序遍历
	void InOrderN(BinTreeNode<T>* t, void (*visit)(const T& ));	//中序遍历(非递归)
	void InOrder(BinTreeNode<T>* t, void (*visit)(const T&));	//中序遍历
	void PostOrder(BinTreeNode<T>* t, void (*visit)(const T&)); //后序遍历
	int CountNodes(const BinTreeNode<T>* t)const;	//求以t为根的二叉树结点个数
	int CountLeafNodes(const BinTreeNode<T>* t)const;	//求以t为根的二叉树叶子结点个数
	int Height(const BinTreeNode<T>* t)const;	//求以t为根的二叉树的高度
	int Width(BinTreeNode<T>* t)const;	//求以t为根的二叉树的宽度
	bool CompleteBinTree(BinTreeNode<T>* t) const;	//判断是否为完全二叉树
public:
	//成员函数
	BinaryTree();
	BinaryTree(BinTreeNode<T>* r);
	BinaryTree(const T& d);		//构造以d为根的二叉树
	void Create(BinTreeNode<T>*& r);			//创建二叉树
	void PreOrder(void (*visit)(const T& d));	//先序遍历
	void InOrderN(void (*visit)(const T& d));	//中序遍历(非递归)
	void InOrder(void(*visit)(const T& d));		//中序遍历
	void PostOrder(void(*visit)(const T& d));   //后序遍历
	int CountNodes() const; //求结点数
	int CountLeafNodes()const;//求以t为根的二叉树叶子结点个数
	int Height() const;		//求树高
	int Width() const;		//求树宽
	bool CompleteBinTree() const; //判断是否为完全二叉树
};


//辅助函数
template<class T>
BinTreeNode<T>* BinaryTree<T>::CopyTree(BinTreeNode<T>* t) {
	root = t;
}

//先序遍历
template<class T>
void BinaryTree<T>::PreOrder(BinTreeNode<T>* t, void (*visit)(const T& )) {
	if (t != nullptr) {
		(*visit)(t->data);
		PreOrder(t->leftChild,visit);
		PreOrder(t->rightChild, visit);
	}
}

//中序遍历(非递归)
template<class T>
void BinaryTree<T>::InOrderN(BinTreeNode<T>* t, void (*visit)(const T&)) {
	if (t != nullptr) {
		stack<BinTreeNode<T>* > s;		//栈(STL)作为辅助空间
		BinTreeNode<T>* p = t;			//创建p作为辅助指针
		do {
			while (p != nullptr) {		//将树的根和左孩子入栈
				s.push(p);
				p = p->leftChild;
			}
			p = s.top();				//取栈顶元素
			s.pop();					//出栈
			(*visit)(p->data);			//访问栈顶元素的data
			p = p->rightChild;			//将辅助指针指向该栈顶元素右孩子
		} while (p != nullptr||!s.empty());
	}
}

//中序遍历
template<class T>
void BinaryTree<T>::InOrder(BinTreeNode<T>* t, void (*visit)(const T&)) {
	if (t != nullptr) {
		InOrder(t->leftChild, visit);
		(*visit)(t->data);
		InOrder(t->rightChild, visit);
	}
}

//后序遍历
template<class T>
void BinaryTree<T>::PostOrder(BinTreeNode<T>* t, void (*visit)(const T&)) {
	if (t != nullptr) {
		PostOrder(t->leftChild, visit);
		PostOrder(t->rightChild, visit);
		(*visit)(t->data);
	}
}

//求以t为根的二叉树的结点个数
template<class T>
int BinaryTree<T>::CountNodes(const BinTreeNode<T>* t)const {
	int count;
	if (t != nullptr) {
		count = CountNodes(t->leftChild) + CountNodes(t->rightChild) + 1;
	}
	else {
		return 0;
	}
	return count;
}

//求以t为根的二叉树叶子结点个数
template<class T>
int BinaryTree<T>::CountLeafNodes(const BinTreeNode<T>* t)const {
	if (!t) {
		return 0;
	}
	else if (t->leftChild == nullptr && t->rightChild == nullptr) {
		return 1;
	}
	else {
		return CountLeafNodes(t->leftChild) + CountLeafNodes(t->rightChild);
	}
}


//求以t为根的二叉树的高度
template<class T>
int BinaryTree<T>::Height(const BinTreeNode<T>* t) const {
	int lHeight, rHeight;
	if (t != nullptr) {
		lHeight = Height(t->leftChild);
		rHeight = Height(t->rightChild);
		return ((lHeight > rHeight) ? lHeight : rHeight) + 1;
	}
	else {
		return 0;
	}
}

//求以t为根的二叉树的宽度
template<class T>
int BinaryTree<T>::Width(BinTreeNode<T>* t)const {
	if (t == nullptr) {
		return 0;
	}
	else {
		queue<BinTreeNode<T>* > p;
		BinTreeNode<T>* q;
		int width = 1;
		int temp = 0;	//记录树的每一层的个数
		int tag = 1;	//记录树的每一层的个数(从第二层开始)

		p.push(t);		//将根结点入队
		q = p.front();	//取出队头
		for (int i = 1; i <= tag && q != nullptr; i++) {
			q = p.front();	//取出队头
			p.pop();		//出队
			if (q->leftChild) {
				p.push(q->leftChild);
				temp++;
			}
			if (q->rightChild) {
				p.push(q->rightChild);
				temp++;
			}
			if (i == tag) {
				i = 0;
				tag = temp;
				width = temp > width ? temp : width;
				temp = 0;
			}
		}
		return width;
	}
}

//判断是否为完全二叉树
template<class T>
bool BinaryTree<T>::CompleteBinTree(BinTreeNode<T>* t) const {
	if (t == nullptr) {
		return false;
	}
	else {
		queue<BinTreeNode<T>*> p;
		BinTreeNode<T>* q;
		p.push(t);
		while (!p.empty()) {
			q = p.front();
			p.pop();
			if (q == nullptr) break;
			p.push(q->leftChild);
			p.push(q->rightChild);
		}
		while (!p.empty()) {
			q=p.front();
			if (q) return false;
			p.pop();
		}
		return true;
	}
}


//成员函数
template<class T>
BinaryTree<T>::BinaryTree() {
	Create(root);
}

template<class T>
BinaryTree<T>::BinaryTree(BinTreeNode<T>* r) {
	root = r;
}

template<class T>
BinaryTree<T>::BinaryTree(const T& d) {
	root = new BinTreeNode<T>(d);
}

template<class T>
void BinaryTree<T>::Create(BinTreeNode<T>*& r) {
	char n;
	cin >> n;
	if (n != '#') {
		r = new BinTreeNode<T>(n);
		Create(r->leftChild);
		Create(r->rightChild);
	}
	else {
		r = nullptr;
	}
}

//先序遍历
template<class T>
void BinaryTree<T>::PreOrder(void (*visit)(const T& d)) {
	PreOrder(root, visit);
}

//中序遍历(非递归)
template<class T>
void BinaryTree<T>::InOrderN(void (*visit)(const T& d)) {
	InOrderN(root, visit);
}

//中序遍历
template<class T>
void BinaryTree<T>::InOrder(void (*visit)(const T& d)) {
	InOrder(root, visit);
}

//后序遍历
template<class T>
void BinaryTree<T>::PostOrder(void (*visit)(const T& d)) {
	PostOrder(root, visit);
}

//求树的结点个数
template<class T>
int BinaryTree<T>::CountNodes()const {
	return CountNodes(root);
}

//求树的叶子结点个数
template<class T>
int BinaryTree<T>::CountLeafNodes()const {
	return CountLeafNodes(root);
}

//求树的高度
template<class T>
int BinaryTree<T>::Height()const {
	return Height(root);
}

//求树的宽度
template<class T>
int BinaryTree<T>::Width()const {
	return Width(root);
}

//判断是否是完全二叉树
template<class T>
bool BinaryTree<T>::CompleteBinTree() const {
	return CompleteBinTree(root);
}

template<class T>
void show(const T& d) {
	cout << d << " ";
}

int main() {
	BinaryTree<char> BinTree;
	BinTree.PreOrder(show);
	cout << endl;
	BinTree.InOrderN(show);
	cout << endl;
	BinTree.InOrder(show);
	cout << endl;
	BinTree.PostOrder(show);
	cout << endl;
	cout << "树的结点个数：" << BinTree.CountNodes() << endl;
	cout << "树的叶子结点个数：" << BinTree.CountLeafNodes() << endl;
	cout << "树的高度：" << BinTree.Height() << endl;
	if (BinTree.CompleteBinTree()) {
		cout << "是完全二叉树" << endl;
	}
	else {
		cout << "不是完全二叉树" << endl;
	}
	cout << "树的宽度：" << BinTree.Width() << endl;
	return 0;
}