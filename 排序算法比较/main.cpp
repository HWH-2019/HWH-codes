#include<iostream>
#include<iomanip>
#include<algorithm>
#include<Windows.h>
using namespace std;


//冒泡排序
template<typename T>
int* BubbleSort(T nums[], int n) {
	bool finish = false;
	static int count[2] = { 0,0 };		//count[0]记录比较次数，count[1]记录移动次数
	int i = 1;
	while (i<n&&!finish)
	{
		finish = true;
		for (int j = 0; j < n - i; j++) {
			count[0]++;
			if (nums[j] > nums[j + 1]) {
				T temp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = temp;
				finish = false;
				count[1] += 3;
			}
		}
		i++;
	}
	return count;
}

//快速排序(递归)
template<typename T>
int* QuickSort(T nums[], int low,int high) {
	static int count[2] = { 0,0 };		//count[0]记录比较次数，count[1]记录移动次数
	T num = nums[low];
	count[1]++;
	int i = low;
	int j = high;
	while (i < j) {
		count[0]++;
		while (i < j && nums[j] >= num) {
			j--;
			count[0]++;
		}
		if (i < j) {
			nums[i++] = nums[j];
			count[1]++;
		}
		count[0]++;
		while (i < j && nums[i] <= num) {
			i++;
			count[0]++;
		}
		if (i < j) {
			nums[j--] = nums[i];
			count[1]++;
		}
	}
	nums[i] = num;
	count[1]++;
	int* temp = nullptr;
	if (low < i - 1) {
		QuickSort(nums, low, i - 1);
	}
	if (i + 1 < high) {
		QuickSort(nums, i + 1, high);
	}
	return count;
}

//快速排序(封装)
template<typename T>
int* QuickSort(T nums[], int n) {

	return QuickSort(nums, 0, n - 1);

}

//希尔排序
template<typename T>
int* ShellSort(T nums[], int n) {
	int i, j, d = n / 2;
	static int count[2] = { 0,0 };		//count[0]记录比较次数，count[1]记录移动次数
	T num = 0;
	while (d > 0) {
		for (i = d; i < n; i++) {
			num = nums[i];
			j = i - d;
			count[0]++;
			count[1]++;
			while (j >= 0 && num < nums[j]) {
				nums[j + d] = nums[j];
				j -= d;
				count[0]++;
				count[1]++;
				
			}
			nums[j + d] = num;
			count[1]++;
		}
		d = d / 2;
	}
	return count;
}

//向下调整
template<typename T>
int* FilterDown(T nums[], int low, int high) {
	int f = low;
	int i = 2 * low + 1;
	static int count[2] = { 0,0 };	//count[0]记录比较次数，count[1]记录移动次数
	T num = nums[low];
	count[1]++;
	while (i <= high) {
		count[0]++;
		if (i < high && nums[i] < nums[i + 1]) {
			i++;
			count[0]++;
		}
		count[0]++;
		if (num < nums[i]) {
			count[1]++;
			nums[f] = nums[i];
			f = i;
			i = 2 * f + 1;
		}
		else
			break;
	}
	nums[f] = num;
	count[1]++;
	return count;
}

//堆排序
template<typename T>
int* HeapSort(T nums[], int n) {
	int i = 0;
	static int count[2] = { 0,0 };	//count[0]记录比较次数，count[1]记录移动次数
	int* temp = nullptr;
	for (i = (n - 2) / 2; i >= 0; --i) {
		temp = FilterDown(nums, i, n - 1);
	}
	for (i = n - 1; i > 0; --i) {
		int p = nums[0];
		nums[0] = nums[i];
		nums[i] = p;
		count[1] += 3;
		temp = FilterDown(nums, 0, i - 1);
	}
	if (temp != nullptr) {
		count[0] = temp[0];
		count[1] = temp[1];
	}
	return count;
}

//显示关键字比较次数和移动次数
template<typename T>
void Display(int* count) {
	cout << "关键字比较次数：" << count[0] << endl;
	cout << "关键词移动次数：" << count[1] << endl;
}

//显示排序结果函数
template<typename T>
void show(T nums[],int n) {
	for (int i = 1; i <= n; i++) {
		cout<< left << setw(5) << nums[i - 1];
		if (i % 20 == 0) {
			cout << endl;
		}
	}
}

//显示比较结果函数
template<typename T>
void Print(int* result[],int n) {
	int *arr=new int[n];
	//cout << "+============================================================================+" << endl;
	cout << "+" << setw(77) << setfill('=')  << "+" << endl;
	cout << "|" <<right<< setw(48)<<setfill(' ') << "四种排序方法比较表" <<setw(29)<< "|" << endl;
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < n; i++) {
			arr[i] = result[i][j];
		}
		cout << "+----------------+--------------+--------------+--------------+--------------+" << endl;
		if (j == 0) {
			cout << "|  比较次数排序  |";
		}
		else {
			cout << "|  交换次数排序  |";
		}

		sort(arr, arr+n);
		for (int i = 0; i < n; i++) {
			if (arr[i]== result[0][j])
			{
				cout << right << setw(10) << "冒泡排序";
			}
			else if (arr[i] == result[1][j])
			{
				cout << right << setw(10) << "快速排序";
			}
			else if (arr[i] == result[2][j])
			{
				cout << right << setw(10) << "希尔排序";
			}
			else if (arr[i] == result[3][j])
			{
				cout << right << setw(10) << "堆排序";
			}
			cout << right << setw(5) << "|";
		}
		cout << endl;
		cout << "+----------------+--------------+--------------+--------------+--------------+" << endl;
		if (j == 0) {
			cout << "| 关键字比较次数 |";
		}
		else {
			cout << "| 关键字交换次数 |";
		}
		for (int i = 0; i < n; i++) {
			cout << setw(10) << arr[i];
			cout << setw(5) << "|";
		}
		cout << endl;
	}
	cout << "+----------------+--------------+--------------+--------------+--------------+" << endl;
}

int main() {
	int N = 1500;
	int* nums = new int[N];
	int* nums1 = new int[N];
	int* nums2 = new int[N];
	int* nums3 = new int[N];
	int* result[4];
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期   
	 
	srand((unsigned int)time(nullptr));
	for (int t = 0; t < 3; t++) {
		for (int i = 0; i < N; i++) {
			nums1[i] = nums2[i] = nums3[i] = nums[i] = rand() % 3000;
		}
		cout<< "====================================第"<<t+1<<"组数据=================================" << endl;

		cout << endl << "=====================================冒泡排序=================================" << endl;
		QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数  
		result[0] = BubbleSort<int>(nums, N);
		QueryPerformanceCounter(&nEndTime);
		cout << "排序花费的时间：" << (double)(nEndTime.QuadPart - m_nBeginTime.QuadPart) / m_nFreq.QuadPart << endl;
		Display<int>(result[0]);

		cout << endl << "=====================================快速排序=================================" << endl;
		QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数  
		result[1] = QuickSort<int>(nums1, N);
		QueryPerformanceCounter(&nEndTime);
		cout << "排序花费的时间：" << (double)(nEndTime.QuadPart - m_nBeginTime.QuadPart) / m_nFreq.QuadPart << endl;
		Display<int>(result[1]);

		cout << endl << "=====================================希尔排序=================================" << endl;
		QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数  
		result[2] = ShellSort<int>(nums2, N);
		QueryPerformanceCounter(&nEndTime);
		cout << "排序花费的时间：" << (double)(nEndTime.QuadPart - m_nBeginTime.QuadPart) / m_nFreq.QuadPart << endl;
		Display<int>(result[2]);

		cout << endl << "======================================堆排序==================================" << endl;
		QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数  
		result[3] = HeapSort<int>(nums3, N);
		QueryPerformanceCounter(&nEndTime);
		cout << "排序花费的时间：" << (double)(nEndTime.QuadPart - m_nBeginTime.QuadPart) / m_nFreq.QuadPart << endl;
		Display<int>(result[3]);

		cout << endl;

		Print<int>(result, 4);
		cout << endl;
	}
	return 0;
}