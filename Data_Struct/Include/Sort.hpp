#ifndef _SORT_H
#define _SORT_H

#include "sys_comm.h"
#include "Heap_Array.hpp"
#include "CompleteBinaryTree.hpp"
#define DEFAULT_SIZE 100//default maxsize of DataList
#define THRESH_Q_I 5//threshold of quicksort,when the length is less than threshold,use insertsort instand,the value between 5 to 25 is reasonable.
template<typename T>
class Element
{
	public:
		//we can also define more key or data member,blank for default.
		T key;
		Element<T>& operator=(const Element<T> &x){key = x.key;return *this;}
		bool operator==(const Element<T> &x){return key == x.key;}
		bool operator!=(const Element<T> &x){return key != x.key;}
		bool operator<=(const Element<T> &x){return key <= x.key;}
		bool operator>=(const Element<T> &x){return key >= x.key;}
		bool operator<(const Element<T> &x) {return key < x.key;}
		bool operator>(const Element<T> &x) {return key > x.key;}
};

template<typename T>
class DataList
{
	public:
		DataList(int s = DEFAULT_SIZE):Vector(new Element<T>[s]),maxsize(s),currentsize(0){}
		~DataList(){delete [] Vector;}
		Element<T>& operator[](int i){return Vector[i];}
		void Initial(std::istream &is);
		void Initial(T a[],int n);
		void Insert(const T &vle);
		void Swap(Element<T> &p,Element<T> &q);
		int Length(){return currentsize;}
		bool IsEmpty(){if(!currentsize){std::cout<<"empty.."<<std::endl;return true;}else return false;}
		void Traverse();

		//bubble sort
		void BubbleSort();
		void BubbleSort_I();
		void CocktailSort();
		//insert sort
		void InsertSort();
		void BinaryInsertSort();
		void ShellSort();
		//quick sort
		int Partition(const int left,const int right);
		int Partition(DataList<T> &L,const int left,const int right);//Another method to select base pivot
		void Partition(DataList<T> &,const int left,const int right,int &,int &);//for huge amount of reapting elements.
		void QuickSort();
		void QuickSort2();
		void QuickSort(DataList<T> &L,const int left,const int right);//basical quick sort.
		void Quick_Insert_Mixed_Sort(DataList<T> &L,const int left,const int right);//mixed sort.
		void Quick_Insert_Mixed_Sort_N(DataList<T> &L,const int left,const int right);//drop insert sort
		void HybirdSort(DataList<T> &L,const int left,const int right);//efficient quick sort mixed with insert sort.
		//select sort
		void SelectSort();
		void HeapSort();
		void HeapSort2();
		void TournamentSort();
		//merge sort
		void MergeSort();

	private:
		Element<T> *Vector;
		int maxsize;
		int currentsize;
};

template<typename T>
void DataList<T>::Initial(std::istream &is)
{
	int i = currentsize;
	T vle;
	while(is>>vle)
	{
		Insert(vle);
		i++;
	}
}

template<typename T>		
void DataList<T>::Initial(T a[],int n)
{
	int i = currentsize,j = 0;
	while(j < n)
	{
		Insert(a[j]);
		++i,++j;
	}
}

template<typename T>
void DataList<T>::Insert(const T &vle)
{
	if(currentsize == maxsize)
	{
		maxsize *= 2;
		Element<T> *tmp = new Element<T>[maxsize];
		for(int i = 0;i<currentsize;++i)
			tmp[i] = Vector[i];
		delete [] Vector;
		Vector = tmp;
	}
	Vector[currentsize].key = vle;
	currentsize++;
}

template<typename T>
void DataList<T>::Swap(Element<T> &p,Element<T> &q)
{
	Element<T> tmp = p;
	p = q;
	q = tmp;
}

template<typename T>
void DataList<T>::Traverse()
{
	for(int i = 0;i<currentsize;++i)
		std::cout<<this->operator[](i).key<<" ";
	std::cout<<std::endl;
}

template<typename T>
void DataList<T>::BubbleSort()
{
	int i,j;
	for(i = 1;i < currentsize; ++i)
		for(j = currentsize - 1 ;j >= i; --j)
			if(Vector[j - 1] > Vector[j])
				Swap(Vector[j - 1] , Vector[j]);
}

template<typename T>
void DataList<T>::BubbleSort_I()
{
	int i,j;
	bool exchange = false;
	for(i = 1;i < currentsize; ++i)
	{
		for(j = currentsize - 1;j >= i ;--j)
		{
			if(Vector[j - 1] > Vector[j])
			{
				Swap(Vector[j - 1],Vector[j]);
				exchange = true;
			}
		}
		if(exchange == false)
			return;
	}
}

template<typename T>
void DataList<T>::CocktailSort()
{
	int low = 1,high = currentsize;
	int i,j;
	while(low < high)
	{
		for(i = low;i < high;i++)
		{
			if(Vector[i] < Vector[i - 1])
			{
				Swap(Vector[i],Vector[i - 1]);
				j = i;
			}
		}
		high = j;
		for(i = high;i >= low ;i--)
		{
			if(Vector[i - 1] > Vector[i])
			{
				Swap(Vector[i],Vector[i - 1]);
				j = i;
			}
		}
		low = j;
	}
}
template<typename T>
void DataList<T>::InsertSort()
{
	if(IsEmpty())
		return;
	Element<T> tmp;
	int j;
	for(int i = 1;i < currentsize;++i)
	{
		if(Vector[i - 1]> Vector[i])
		{
			tmp = this->operator[](i);
			j = i;
			while(j >= 1 && tmp < Vector[ j - 1])
			{
				Vector[j] = Vector[j - 1];
				--j;
			}
			Vector[j] = tmp;
		}
	}
}

template<typename T>
void DataList<T>::BinaryInsertSort()
{
	if(IsEmpty())
		return;
	Element<T> tmp;
	int low,high,middle;
	for(int i = 1; i < currentsize; ++i)
	{
		tmp = Vector[i];
		low = 0;
		high = i - 1;
		while(low <= high)
		{
			middle = (low + high)/2;
			if(tmp < Vector[middle])
				high = middle - 1;
			else
				low = middle + 1;
		}
		for(int j = i - 1 ; j >= low; j--)
			Vector[j + 1] = Vector[j];
		Vector[low] = tmp;
	}
}

template<typename T>
void DataList<T>::ShellSort()
{
	int i,j,gap = currentsize;
	Element<T> tmp;
	while(gap > 1)
	{
		gap = gap/3 + 1;
		for(i = gap;i < currentsize; i++)
		{
			if(Vector[i - gap] > Vector[i])
			{
				tmp = Vector[i];
				for(j = i;j >= gap && tmp < Vector[j - gap];j = j - gap)//initialize j = i or j = i - gap.
				{
					Vector[j] = Vector[j - gap];
				}
				Vector[j] = tmp;
			}
		}
	}
}

template<typename T>
int DataList<T>::Partition(const int left,const int right)
{
	int pivotpos = left;
	Element<T> pivot = Vector[left - 1];
	for(int i = left + 1;i <= right; ++i)
	{
		if(Vector[i - 1] < pivot)//pivotpos will be blocked in front of the element which is bigger than it,and exchange the smaller element and the bigger element.when the loop ended,exchanged the base value pos and the pivotpos.
		{
			pivotpos++;
			if(pivotpos != i)
				Swap(Vector[pivotpos - 1],Vector[i - 1]);
		}
	}
	Swap(Vector[left - 1],Vector[pivotpos - 1]);
	return pivotpos;
}

template<typename T>
int DataList<T>::Partition(DataList<T> &L,const int left,const int right)
{
	int i = left - 1,j = right - 1,k;
	int mid = (i + j)/2;
	Element<T> pivot;
	k = (L[i] > L[j])?i:j;
	if(L[mid] < L[k])
		Swap(L[mid],L[k]);//maxheap:mid,i,j
	if(L[i] > L[j])
		Swap(L[i],L[j]);
	pivot = L[j];
	j--;
	while(i < j)
	{
		while(i < j && L[i] < pivot)
			i++;
		while(i < j && L[j] > pivot)
			j--;
		if(i < j)
		{
			Swap(L[i],L[j]);
			i++;
			j--;
		}
	}
	if(L[i] > L[right - 1])
		Swap(L[i],L[right - 1]);
	return i + 1;
}
template<typename T>
void DataList<T>::Partition(DataList<T> &L,const int left,const int right,int &i,int &j)
{
	int p = left - 1,q = right - 1,r;
	int k = (L[left - 1] > L[right - 1]) ? left - 1: right - 1;/*{{{*/
	if(L[(p + q)/2] < L[k] && q - p != 1)
		Swap(L[(p + q)/2],L[k]);
	if(L[right - 1] < L[left - 1] )
		Swap(L[left - 1],L[right - 1]);/*}}}*/
	Element<T> pivot = L[right - 1];
	i = left - 1,j = right - 1;
	q--;
	j--;
	while(p < q)
	{
		while(p < q && L[p] < pivot)
			p++;
		while(p < q && L[q] > pivot)
			q--;
		if(p < q)
		{
			if(L[p] != L[q])
				Swap(L[p],L[q]);
			if(p < q && L[p] == pivot)
			{
				Swap(L[i],L[p]);
				i++;
				p++;
			}
			if(p < q && L[q] == pivot)
			{
				Swap(L[j],L[q]);
				j--;
				q--;
			}	
		}
	}
	r = right - 1;
	if(L[p] > pivot)
	{
		Swap(L[right - 1],L[p]);
		p++;
		q--;
		r--;
	}
	while(r > j)
	{
		//if this if-statement is absent,it will cause infinite loop in such situation:there are two elements in this loop,and right is bigger than left,than r is the right,and swap with the left.
		if(right - left != 1)
			Swap(L[r],L[p]);
		r--;
		p++;
	}
	for(r = left - 1;r < i;r++,q--)
		Swap(L[r],L[q]);
	i = q + 1;
	j = p + 1;
}

template<typename T>
void DataList<T>::QuickSort()
{
	int *low = new int[currentsize];
	int *high = new int[currentsize];
	int i,j,k;
	int pi,pj;
	Element<T> pivot;
	low[0] = 0;
	high[0] = currentsize - 1;
	while(k != -1)
	{
		i = pi = low[k];
		j = pj = high[k];
		pivot = Vector[pi];
		k--;
		i++;
		while(i <= j)
		{
			while(i < j && Vector[i] < pivot)
				i++;
			while(i < j && Vector[j] > pivot)
				j--;
			if(i < j)
			{
				Swap(Vector[i],Vector[j]);
				i++,j--;
			}
			if(i == j)
			{
				if(Vector[i] < pivot)
					Swap(Vector[i],Vector[pi]);
				break;
			}
		}
		if(pi < pj)
		{
			low[k + 1] = pi;
			high[k + 1] = i - 1;
			low[k + 2] = i + 1;
			high[k + 2] = pj;
			k += 2;
		}
	}
	delete [] low;
	delete [] high;
}

template<typename T>
void DataList<T>::QuickSort2()
{
	int n = 2*currentsize;
	int *queue = new int[n];
	int front = 0,rear = 0;
	int left,right,pivotpos;
	rear = (rear + 1) % n;
	queue[rear] = 1;
	rear = (rear + 1) % n;
	queue[rear] = currentsize;
	while(front != rear)
	{
		front = (front + 1) % n;
		left = queue[front];
		front = (front + 1) % n;
		right = queue[front];
		if(left < right)
		{
			pivotpos = Partition(left,right);
			rear = (rear + 1) % n;
			queue[rear] = left;
			rear = (rear + 1) % n;
			queue[rear] = pivotpos - 1;		
			rear = (rear + 1) % n;
			queue[rear] = pivotpos + 1;
			rear = (rear + 1) % n;
			queue[rear] = right;
		}
	}
}
template <typename T>
void DataList<T>::QuickSort(DataList &L,const int left,const int right)
{
	if(left < right)
	{
		// int pivotpos = Partition(left,right);
		/* int pivotpos = Partition(L,left,right);//use median3. */
		// QuickSort(L,left,pivotpos - 1);
		/* QuickSort(L,pivotpos + 1,right); */
		int i = 0,j = 0;
		Partition(L,left,right,i,j);
		QuickSort(L,left,i);
		QuickSort(L,j ,right);
	}
}

template <typename T>
void DataList<T>::Quick_Insert_Mixed_Sort(DataList &L,const int left,const int right)
{
	if(right - left <= THRESH_Q_I)
	{
		InsertSort();
	}
	else
	{
		int pivotpos = Partition(L,left,right);
		Quick_Insert_Mixed_Sort(L,left,pivotpos - 1);
		Quick_Insert_Mixed_Sort(L,pivotpos + 1,right);
	}
}

template <typename T>
void DataList<T>::Quick_Insert_Mixed_Sort_N(DataList &L,const int left,const int right)
{
	if(right - left <= THRESH_Q_I)
		return;
	else
	{
		int pivotpos = Partition(L,left,right);
		Quick_Insert_Mixed_Sort_N(L,left,pivotpos - 1);
		Quick_Insert_Mixed_Sort_N(L,pivotpos + 1,right);
	}
}

template<typename T>
void DataList<T>::HybirdSort(DataList<T> &L,const int left,const int right)
{
	Quick_Insert_Mixed_Sort_N(L,left,right);
	InsertSort();
}


template<typename T>
void DataList<T>::SelectSort()
{
	for(int i = 0;i < currentsize;i++)
	{
		int k = i;
		for(int j = i + 1;j < currentsize;j++)
			if(Vector[j] < Vector[k])
				k = j;
		Swap(Vector[k],Vector[i]);
	}
}

//the two ideas almost equally.
template<typename T>
void DataList<T>::HeapSort()
{
	MinHeap<Element<T>> h;
	for(int i = 0;i < currentsize;i++)
		h.Insert(Vector[i]);
	for(int i = 0;i < currentsize;i++)
		h.Remove(Vector[i]);
}

template<typename T>
void DataList<T>::HeapSort2()
{
	MaxHeap<Element<T>> h(currentsize);
	int i = currentsize - 1;
	Element<T> tmp;
	for(int i = 0;i < currentsize;i++)
		h.Insert(Vector[i]);
	while(i > 0)
	{
		tmp = h[0];
		h[0] = h[i];
		h[i] = tmp;
		i--;
		h.siftDown(0,i);
	}
	for(int i = 0;i < currentsize;i++)
		Vector[i] = h[i];
   /*  while(i >= 0) */
		/* h.Remove(Vector[i--]); */
}

template<typename T>
void DataList<T>::TournamentSort()
{

}
#endif
