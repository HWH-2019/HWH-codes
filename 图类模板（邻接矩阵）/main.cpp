#include<iostream>
using namespace std;

template<class T>
class AdjMatrixUndirGraph {
protected:
	int vexNum, vexMaxNum, arcNum;	//顶点数目、允许的顶点最大数目、边数
	int** arcs;						//存放边信息的邻接矩阵
	T* vertexes;					//存放顶点信息的数组
	mutable bool* tag;				//标志数组
public:
	AdjMatrixUndirGraph(T es[], int vertexNum, int vertexMaxNum=100);	//构造函数1
	AdjMatrixUndirGraph(int vertexMaxNum = 100);						//构造函数2
	void AddEdge(int start, int end);		//添加边
	void AddVex(const T &d);				//添加顶点
	void DeleteArc(int start, int end);     //删除边
	void DeleteVex(const T& d);				//删除顶点
	int GetVexNum() const;					//获取顶点个数
	int GetArcNum() const;					//获取边的个数
	int FirstAdjVex(int v) const;			//返回顶点v的第一个邻接顶点
	int NextAdjVex(int v1, int v2) const;	//返回顶点v1相对于v2的下一个邻接点
	bool GetTag(int v)const;				//获取顶点v的标志
	void SetTag(int v, bool val)const;		//设置顶点v的标志为val
	void ShowArcs();
};

//构造函数1
template<class T>
AdjMatrixUndirGraph<T>::AdjMatrixUndirGraph(T es[], int vertexNum, int vertexMaxNum) {
	if (vertexMaxNum < 0)
		throw("允许的最大的顶点数目不能为负！");
	if (vertexMaxNum < vertexNum)
		throw("顶点数目不能大于允许的顶点最大数目！");
	vexMaxNum = vertexMaxNum;
	vexNum = vertexNum;
	arcNum = 0;
	vertexes = new T[vexMaxNum];
	tag = new bool[vexMaxNum];
	arcs = new int* [vexMaxNum];
	for (int i = 0; i < vexMaxNum; i++) {
		arcs[i] = new int[vexMaxNum];
	}
	for (int i = 0; i < vexNum; i++) {
		vertexes[i] = es[i];
		tag[i] = false;
		for (int j = 0; j < vexNum; j++) {
			arcs[i][j] = 0;
		}
	}


}

//构造函数2
template<class T>
AdjMatrixUndirGraph<T>::AdjMatrixUndirGraph(int vertexMaxNum) {
	if (vertexMaxNum < 0)
		throw("允许的最大的顶点数目不能为负！");
	vexMaxNum = vertexMaxNum;
	vexNum = arcNum = 0;
	vertexes = new T[vexMaxNum];			//生成顶点信息数组
	tag = new bool[vexMaxNum];				//生成标志数组
	arcs = new int* [vexMaxNum];			//生成邻接矩阵
	for (int i = 0; i < vexMaxNum; i++) {
		arcs[i] = new int[vexMaxNum];
	}
}

//添加边
template<class T>
void AdjMatrixUndirGraph<T>::AddEdge(int start, int end) {
	arcs[start][end] = 1;
	arcNum++;
}

//添加顶点
template<class T>
void AdjMatrixUndirGraph<T>::AddVex(const T& d) {
	if (vexNum + 1 > vexMaxNum) {
		throw("图的顶点数已经达到允许的最大值");
	}
	else {
		vertexes[vexNum] = d;
		for (int v = 0; v <= vexNum; v++) {
			arcs[vexNum][v] = 0;
			arcs[v][vexNum] = 0;
		}
		vexNum++;
	}
}

//删除边
template<class T>
void AdjMatrixUndirGraph<T>::DeleteArc(int start, int end) {
	if (start < 0 || end < 0 || start >= vexNum || end >= vexNum) {
		throw("顶点位置错误");
	}
	else {
		arcs = [start][end];
		arcNum--;
	}
}

//删除顶点
template<class T>
void AdjMatrixUndirGraph<T>::DeleteVex(const T& d) {
	for (int v = 0; v < vexNum; v++) {
		if (vertexes[v] == ·d) {

		}
	}
}

//获取顶点个数
template<class T>
int AdjMatrixUndirGraph<T>::GetVexNum() const {
	return vexNum;
}

//获取边的个数
template<class T>
int AdjMatrixUndirGraph<T>::GetArcNum() const {
	return arcNum;
}

//返回顶点v的第一个邻接顶点
template<class T>
int AdjMatrixUndirGraph<T>::FirstAdjVex(int v) const {
	if (v < 0 && v >= vexNum) {
		throw("不存在此顶点");
	}
	else {
		for (int i = 0; i < vexNum; i++) {
			if (arcs[v][i] != 0) {
				return i;
			}
		}
		return -1;	//未找到邻接节点
	}
}

//返回顶点v1相对于v2的下一个邻接点
template<class T>
int AdjMatrixUndirGraph<T>::NextAdjVex(int v1, int v2) const {
	if (v1 < 0 || v2 < 0 || v1 >= vexNum || v2 >= vexNum) {
		throw("顶点位置错误");
	}
	else {
		for (int i = v2+1; i < vexNum; i++) {
			if (arcs[v1][i] != 0) {
				return i;
			}
		}
		return -1;	//未找到邻接节点
	}
}

//获取顶点v的标志
template<class T>
bool AdjMatrixUndirGraph<T>::GetTag(int v)const {
	if (v < 0 || v >= vexNum) {
		throw("不存在此顶点");
	}
	else {
		return tag[v];
	}
}

//设置顶点v的标志为val
template<class T>
void AdjMatrixUndirGraph<T>::SetTag(int v, bool val)const {
	if (v < 0 || v >= vexNum) {
		throw("不存在此节点");
	}
	else {
		tag[v] = val;
	}
}

//显示邻接矩阵
template<class T>
void AdjMatrixUndirGraph<T>::ShowArcs() {
	for (int i = 0; i < vexNum; i++) {
		for (int j = 0; j < vexNum; j++) {
			cout << arcs[i][j] << " ";
		}
		cout << endl;
	}
}


int main() {
	int arr[4] = { 1,2,3,4 };
	AdjMatrixUndirGraph<int> *graph = new AdjMatrixUndirGraph<int>(arr,4,5);
	for (int i = 0; i < 2; i++) {
		graph->AddEdge(i, i + 2);
	}
	graph->AddEdge(1, 1);
	graph->AddEdge(2, 0);
	graph->ShowArcs();
	cout << graph->GetVexNum() << endl;
	cout << graph->GetArcNum() << endl;
	cout << graph->FirstAdjVex(1) << endl;
	cout << graph->NextAdjVex(1, 1) << endl;
	graph->AddVex(5);
	graph->ShowArcs();
	return 0;
}
