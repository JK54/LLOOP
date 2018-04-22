#ifndef _SORT_H
#define _SORT_H

#include "sys_comm.h"

#define DEFAULT_SIZE 100//default maxsize of DataList
#define THRESH_Q_I 5//threshold of quicksort,when the length is less than threshold,use insertsort instand,the value between 5 to 25 is reasonable.
template<typename T>
class Element
{
	public:
		T key;
		//we can also define more key or data member,blank for default.
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
		//insert sort
		void InsertSort();
		void BinaryInsertSort();
		void ShellSort();
		//quick sort
		int Partition(const int left,const int right);
		int Partition(DataList<T> &L,const int left,const int right);//Another method to select base pivot
		void QuickSort(DataList<T> &L,const int left,const int right);//basical quick sort.
		void Quick_Insert_Mixed_Sort(DataList<T> &L,const int left,const int right);//mixed sort.
		
		void Quick_Insert_Mixed_Sort_N(DataList<T> &L,const int left,const int right);//drop insert sort
		void HybirdSort(DataList<T> &L,const int left,const int right);//efficient insert and quick sort.

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
		std::cout<<"list full..."<<std::endl;
		return;
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
		for(j = currentsize - 1;j >= i; --j)
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
	Element<T> pivot = Vector[left];
	for(int i = left + 1;i < right; ++i)
	{
		if(Vector[i] < pivot)//pivotpos will be blocked in front of the element which is bigger than it,and exchange the smaller element and the bigger element.when the loop ended,exchanged the first pos and the pivotpos.
		{
			pivotpos++;
			if(pivotpos != i)
				Swap(Vector[pivotpos],Vector[i]);
		}
	}
   /*  Vector[left] = Vector[pivotpos]; */
	/* Vector[pivotpos] = pivot; */
	Swap(Vector[left],Vector[pivotpos]);
	return pivotpos;
}

template<typename T>
int DataList<T>::Partition(DataList<T> &L,const int left,const int right)
{
	int mid = (left	+ right)/2;
	Element<T> pivot;
	//rearrange the smallest element to the left,median to the right,largest to the middle
	int k = left;
	if(L[mid] <L[k])
		k = mid;
	if(L[right] <L[k])
		k = right;
	if(k != left)
		Swap(L[k],L[left]);
	if(L[mid] < L[right])
		Swap(L[mid],L[right]);
	pivot = L[right];

}
template <typename T>
void DataList<T>::QuickSort(DataList &L,const int left,const int right)
{
	if(left < right)
	{
		// int pivotpos = Partition(left,right);
		int pivotpos = Partition(L,left,right);//use median3.
		QuickSort(L,left,pivotpos - 1);
		QuickSort(L,pivotpos + 1,right);
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
		int pivotpos = Partition(left,right);
		QuickSort(L,left,pivotpos - 1);
		QuickSort(L,pivotpos + 1,right);
	}
}

template <typename T>
void DataList<T>::Quick_Insert_Mixed_Sort_N(DataList &L,const int left,const int right)
{
	if(right - left <= THRESH_Q_I)
		return;
	else
	{
		int pivotpos = Partition(left,right);
		QuickSort(L,left,pivotpos - 1);
		QuickSort(L,pivotpos + 1,right);
	}
}

template<typename T>
void DataList<T>::HybirdSort(DataList<T> &L,const int left,const int right)
{
	Quick_Insert_Mixed_Sort_N(L,left,right);
	InsertSort();
}


#endif
