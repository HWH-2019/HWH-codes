#include<iostream>
#include<stack>
#include<queue>
using namespace std;

const int DEFAULT_SIZE = 100;
const int DEFAULT_INFINITY = 2147483647;

template<class WeightType>
struct AdjListNetWorkArc {
	int adjVex;										//弧头顶点序号
	WeightType weight;
	AdjListNetWorkArc<WeightType>* nextarc;
	AdjListNetWorkArc();
	AdjListNetWorkArc(int v, WeightType w, AdjListNetWorkArc<WeightType>* next = nullptr);
};

template<class WeightType>
AdjListNetWorkArc<WeightType>::AdjListNetWorkArc() {
	adjVex = -1;
}

template<class WeightType>
AdjListNetWorkArc<WeightType>::AdjListNetWorkArc(int v, WeightType w, AdjListNetWorkArc<WeightType>* next) {
	adjVex = v;
	weight = w;
	nextarc = next;
}

template<class ElemType,class WeightType>
struct AdjListNetWorkVex {
	ElemType data;
	AdjListNetWorkArc<WeightType>* firstarc;
	AdjListNetWorkVex();
	AdjListNetWorkVex(ElemType val, AdjListNetWorkArc<WeightType>* first=nullptr);

};

template<class ElemType,class WeightType>
AdjListNetWorkVex<ElemType, WeightType>::AdjListNetWorkVex() {
	firstarc = nullptr;
}

template<class ElemType,class WeightType>
AdjListNetWorkVex<ElemType, WeightType>::AdjListNetWorkVex(ElemType val, AdjListNetWorkArc<WeightType>* first) {
	data = val;
	firstarc = first;
}

template<class ElemType,class WeightType>
class AdjListNetWork {
protected:
	int vexNum,vexMaxNum,arcNum;					//顶点数目，允许的顶点最大个数和弧数
	AdjListNetWorkVex<ElemType, WeightType>* vexTable;	//顶点表
	mutable bool* tag;									//标志数组
	WeightType infinity;							//无穷大的值
public:
	AdjListNetWork(int vertexMaxNum=DEFAULT_SIZE,WeightType infinit=(WeightType)DEFAULT_INFINITY);
	AdjListNetWork(ElemType es[],int vertexNum, int vertexMaxNum=DEFAULT_SIZE,WeightType infinit=(WeightType)DEFAULT_INFINITY );
	~AdjListNetWork();
	int GetOrder(const ElemType& d)const;			//获取顶点的序号
	ElemType GetElem(int v)const;			//求顶点的元素值
	void SetElem(int v, const ElemType& d);			//修改顶点的元素值
	void InsertArc(int v1, int v2, WeightType w=1);	//插入从v1到v2权为w的弧
	void SetWeight(int v1, int v2, WeightType w);	//设置从v1到v2的弧的权值
	int GetVexNum()const;							//获取顶点个数
	int GetArcNum()const;							//获取弧数个数
	bool GetTag(int v)const;						//获取顶点v的标志
	void SetTag(int v, bool t)const;				//修改顶点v的标志为tag
	int FirstAdjVex(int v)const;					//求有向网中顶点v的第一个邻接点
	int NextAdjVex(int v1, int v2)const;			//求顶点v1相对于v2的下一个邻接点
	void Show() const;								//显示有向网邻接表
};

//构造函数
template<class ElemType,class WeightType>
AdjListNetWork<ElemType, WeightType>::AdjListNetWork(int vertexMaxNum, WeightType infinit) {
	if (vertexMaxNum < 0) {
		throw("允许的最大顶点个数不能为负！");
	}
	vexNum = 0;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;
	vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
	tag = new bool[vexMaxNum];
	infinity = infinit;
}

template<class ElemType,class WeightType>
AdjListNetWork<ElemType, WeightType>::AdjListNetWork(ElemType es[], int vertexNum, int vertexMaxNum, WeightType infinit) {
	if (vertexMaxNum < 0) {
		throw("允许的最大顶点个数不能为负！");
	}
	if (vertexMaxNum < vertexNum) {
		throw("顶点数目不能大于允许的最大顶点个数！");
	}
	vexNum = vertexNum;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;
	tag = new bool[vexMaxNum];
	vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
	for (int i = 0; i < vexNum; i++) {
		tag[i] = false;
		vexTable[i].data = es[i];
		vexTable[i].firstarc = nullptr;
	}
	infinity = infinit;
}

//析构函数
template<class ElemType, class WeightType>
AdjListNetWork<ElemType, WeightType>::~AdjListNetWork() {
	for (int i = 0; i < vexNum; i++) {
		
		AdjListNetWorkArc<WeightType>* p;
		while (vexTable[i].firstarc!=nullptr) {
			p = vexTable[i].firstarc;
			vexTable[i].firstarc = p->nextarc;
			delete p;
		}
		delete vexTable[i].firstarc;
	}
	delete[] vexTable;
	delete[] tag;
}

//获取顶点的序号
template<class ElemType, class WeightType>
int AdjListNetWork<ElemType, WeightType>::GetOrder(const ElemType& d)const {
	for (int i = 0; i < vexNum; i++) {
		if (vexTable[i].data == d) {
			return i;
		}
	}
	return -1;
}

//求顶点的元素值
template<class ElemType, class WeightType>
ElemType AdjListNetWork<ElemType, WeightType>::GetElem(int v)const {
	if (v < 0 || v >= vexNum) {
		throw("顶点错误不在范围内");
	}
	return vexTable[v].data;
}

//修改顶点的元素值
template<class ElemType, class WeightType>
void AdjListNetWork<ElemType, WeightType>::SetElem(int v, const ElemType& d) {
	if (v < 0 || v >= vexNum) {
		throw("顶点错误不在范围内");
	}
	if (d == infinity) {
		throw("顶点的值不能为无穷！");
	}
	vexTable[v] = d;
}

//插入从v1到v2权为w的弧
template<class ElemType,class WeightType>
void AdjListNetWork<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType w) {
	if (v1 < 0 || v2 < 0 || v1 >= vexNum || v2 >= vexNum || v1 == v2) {
		throw("顶点错误不在范围内！");
	}
	if (w == infinity) {
		throw("权值不能为无穷！");
	}
	AdjListNetWorkArc<WeightType>* p = vexTable[v1].firstarc;
	vexTable[v1].firstarc = new AdjListNetWorkArc<WeightType>(v2, w, p);
	arcNum++;
}

//设置从v1到v2的弧的权值
template<class ElemType,class WeightType>
void AdjListNetWork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w) {
	if (v1<0 || v2<0 || v1>=vexNum || v2>=vexNum||v1==v2) {
		throw("顶点错误不在范围内！");
	}
	if (w == infinity) {
		throw("权值不能为无穷!");
	}
	AdjListNetWorkArc<WeightType>* p = vexTable[v1].firstarc;
	for (; p->adjVex != v2 && p != nullptr;) {
		p = p->nextarc;
	}
	if (p != nullptr) {
		p->weight = w;
	}
	else {
		throw("不存在v1到v2的弧");
	}
}

//获取顶点个数
template<class ElemType,class WeightType>
int AdjListNetWork<ElemType, WeightType>::GetVexNum()const {
	return vexNum;
}

//获取弧数个数
template<class ElemType, class WeightType>
int AdjListNetWork<ElemType, WeightType>::GetArcNum()const {
	return arcNum;
}

//获取顶点v的标志
template<class ElemType, class WeightType>
bool AdjListNetWork<ElemType, WeightType>::GetTag(int v)const {
	return tag[v];
}

//修改顶点v的标志为tag
template<class ElemType, class WeightType>
void AdjListNetWork<ElemType, WeightType>::SetTag(int v, bool t)const {
	tag[v] = t;
}

//求有向网中顶点v的第一个邻接点
template<class ElemType, class WeightType>
int AdjListNetWork<ElemType, WeightType>::FirstAdjVex(int v)const {
	if (v < 0 || v >= vexNum) {
		throw("顶点错误不在范围内");
	}
	if (vexTable[v].firstarc == nullptr) {
		return -1;
	}
	else {
		return vexTable[v].firstarc->adjVex;
	}
}

//求顶点v1相对于v2的下一个邻接点
template<class ElemType, class WeightType>
int AdjListNetWork<ElemType, WeightType>::NextAdjVex(int v1, int v2)const {
	if (v1 < 0 || v2 < 0 || v1 >= vexNum || v2 >= vexNum||v1==v2) {
		throw("顶点错误不在范围内！");
	}
	AdjListNetWorkArc<WeightType>* p = vexTable[v1].firstarc;
	while (p != nullptr && p->adjVex != v2) {
		p = p->nextarc;
	}
	if (p == nullptr||p->nextarc==nullptr) {
		return -1;
	}
	else {
		return p->nextarc->adjVex;
	}
}


//显示有向网邻接表
template<class ElemType,class WeightType>
void AdjListNetWork<ElemType, WeightType>::Show()const {
	for (int i = 0; i < vexNum; i++) {
		for (AdjListNetWorkArc<WeightType>* p = vexTable[i].firstarc; p != nullptr; p = p->nextarc) {
			cout << p->weight << " ";
		}
		cout << endl;
	}
}

//深度优先搜索函数
template<class ElemType,class WeightType>
void DFS(const AdjListNetWork<ElemType, WeightType>& g, int v, void (*visit)(const ElemType&)) {
	if (v < 0 || v >= g.GetVexNum()) {
		throw("顶点错误不在范围内");
	}
	g.SetTag(v, true);
	visit(g.GetElem(v));
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w)) {
		if (g.GetTag(w) == false) {
			DFS(g, w, visit);
		}
	}
}

//深度优先遍历函数
template<class ElemType,class WeightType>
void DFSTraverse(const AdjListNetWork<ElemType, WeightType>& g, void (*visit)(const ElemType&)) {
	for (int i = 0; i < g.GetVexNum(); i++) {
		g.SetTag(i, false);
	}
	for (int i = 0; i < g.GetVexNum(); i++) {
		if (g.GetTag(i) == false) {
			DFS(g, i, visit);
		}
	}
}

//输出值
template<class ElemType>
void show(const ElemType& d) {
	cout << d;
}

//深度优先搜索函数(重载)
template<class ElemType, class WeightType>
bool DFS(const AdjListNetWork<ElemType, WeightType>& g, int v1, int v2) {
	g.SetTag(v1, true);
	if (v1 == v2) {
		return true;
	}
	bool result=false;
	int w = g.FirstAdjVex(v1);
	for (; w != -1; w = g.NextAdjVex(v1, w)) {
		if (g.GetTag(w) == false) {
			if (DFS(g, w, v2)) {
				result = true;
			}
		}
	}
	return result;
}

//深度优先搜索判断v1到v2是否有路径
template<class ElemType,class WeightType>
bool DFSFindPath(const AdjListNetWork<ElemType, WeightType>& g,int v1,int v2) {
	if (v1 < 0 || v2 < 0 || v1 >= g.GetVexNum() || v2 >= g.GetVexNum() || v1 == v2) {
		throw("顶点错误不在范围内！");
	}
	for (int i = 0; i < g.GetVexNum(); i++) {
		g.SetTag(i, false);
	}
	return DFS(g, v1, v2);
}

//深度优先遍历函数(非递归)
template<class ElemType,class WeightType>
void DFST(const AdjListNetWork<ElemType, WeightType>& g, void (*visit)(const ElemType&)) {
	for (int i = 0; i < g.GetVexNum(); i++) {
		g.SetTag(i, false);
	}
	stack<int> s;
	for (int i = 0; i < g.GetVexNum(); i++) {
		if (g.GetTag(i) == false) {
			s.push(i);
			visit(g.GetElem(i));
			int temp = i;
			for (int w = g.FirstAdjVex(temp);w!=-1;) {
				if (g.GetTag(w) == false) {
					s.push(w);
					g.SetTag(w, true);
					visit(g.GetElem(w));
				}
				w = g.NextAdjVex(temp, w);
				if(w==-1) break;
				if (g.FirstAdjVex(w) == -1&&!s.empty()) {
					s.pop();
					temp = s.top();
					w = g.FirstAdjVex(temp);
				}
				if(g.FirstAdjVex(w)!=-1&&!s.empty()){
					temp = w;
					w = g.FirstAdjVex(temp);
				}
				
			}
		}
	}
	
}

//广度优先搜索函数
template<class ElemType,class WeightType>
void BFS(const AdjListNetWork<ElemType, WeightType>& g, int v, void (*visit)(const ElemType&)) {
	if (v < 0 || v >= g.GetVexNum()) {
		throw("顶点错误不在范围内");
	}
	queue<int> q;
	g.SetTag(v, true);
	visit(g.GetElem(v));
	q.push(v);
	for (; !q.empty();) {
		int u=q.front();
		q.pop();
		for (int w = g.FirstAdjVex(u); w != -1; w = g.NextAdjVex(u, w)) {
			if (g.GetTag(w) == false) {
				q.push(w);
				g.SetTag(w, true);
				visit(g.GetElem(w));
			}
		}
	}
}

//广度优先遍历函数
template<class ElemType,class WeightType>
void BFSTraverse(const AdjListNetWork<ElemType, WeightType>& g, void (*visit)(const ElemType&)) {
	for (int i = 0; i < g.GetVexNum(); i++) {
		g.SetTag(i, false);
	}
	for (int i = 0; i < g.GetVexNum(); i++) {
		if (g.GetTag(i) == false) {
			BFS(g, i, visit);
		}
	}
}

int main() {
	int arr[5] = { 1,2,3,4 };
	AdjListNetWork<int,int> test(arr,4,6);
	test.InsertArc(0, 1);
	test.InsertArc(0, 2);
	test.InsertArc(2, 3);
	test.InsertArc(3, 0);
	//test.InsertArc(1, 3);
	cout << "显示邻接表" << endl;
	test.Show();
	cout <<"顶点序号为0的第一个结点 "<< test.FirstAdjVex(0) << endl;
	cout <<"顶点0相对于2的下一个邻接点 "<< test.NextAdjVex(0, 2) << endl;
	cout << test.GetOrder(2) << endl;
	if (DFSFindPath(test, 0, 3)) {
		cout << "有路径"<<endl;
	}
	else {
		cout << "无路径"<<endl;
	}
	cout << "深度优先遍历";
	DFSTraverse(test, show);
	cout << endl << "深度优先遍历(非递归)：";
	DFST(test, show);
	cout << endl << "广度优先遍历：";
	BFSTraverse(test, show);
	return 0;
}