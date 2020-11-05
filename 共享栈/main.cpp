#include<iostream>
using namespace std;
#define DEFAULT_SIZE 100
#define SUCCESS 1
#define FAILED 0
typedef int Status;
template<class ElemType>
class SeqQueue {
    protected:
    	int front, length;// 队头指针 ，队列长度
        int maxSize; // 队列容量 
        ElemType* elems; // 元素存储空间
public:
       SeqQueue(int size = DEFAULT_SIZE);
       virtual ~SeqQueue();
       bool IsEmpty() const;
       void Clear();
       Status DelQueue(ElemType& e);
       Status EnQueue(const ElemType e);
										
       void Show() {
          for (int i = front; i < front + length; i++) {
                                                            						cout << elems[i % maxSize] << " ";
          }
		}
	void YangHuiTriangle(int N);
};

template<class ElemType>
SeqQueue<ElemType>::SeqQueue(int size) {
	elems = new ElemType[size];
	maxSize = size;
	front = 0;
	length = 0;
}

template<class ElemType>
SeqQueue<ElemType>::~SeqQueue() {

}

template<class ElemType>
bool SeqQueue<ElemType>::IsEmpty() const {
	if (length == 0) {
		return true;
	}
	else {
		return false;
	}
}

template<class ElemType>
void SeqQueue<ElemType>::Clear() {
	front = length = 0;
}

template<class ElemType>
Status SeqQueue<ElemType>::DelQueue(ElemType& e) {
	if (length == 0) {
		return FAILED;
	}
	else {
		e = elems[front];
		front = (front + 1) % maxSize;
		length--;
		return SUCCESS;
	}
}

template<class ElemType>
Status SeqQueue<ElemType>::EnQueue(const ElemType e) {
	if (length == maxSize) {
		return FAILED;
	}
	else {
		elems[(front + length) % maxSize] = e;
		length++;
		return SUCCESS;
	}
}



template<class ElemType>
void SeqQueue<ElemType>::YangHuiTriangle(int N){

	EnQueue(1);
	EnQueue(1);
	int temp1=0;
	int temp2=0;
	for(int i=1;i<N;i++){
		DelQueue(temp1);
		cout<<temp1<<" ";
		EnQueue(1);
		int k=front;
		for(int j=k;j<=k+i-2;j++){
			DelQueue(temp2);
			cout<<temp2<<" ";
			EnQueue(temp1+temp2);
			temp1=temp2;
		}
		if(i!=1) EnQueue(1);
		cout<<endl;
	}
		
}


int main() {
	SeqQueue<int> queue;
	queue.YangHuiTriangle(18);                                                     
	system("pause");
   return 0;
}
