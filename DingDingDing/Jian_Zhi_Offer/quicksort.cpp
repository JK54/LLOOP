#include <random>
#include <iostream>

template<typename T>
void swap(T &a,T &b)
{
	T c = a;
	a = b;
	b = c;
}

template<typename T>
void disp(T a[],int n)
{
	for(int i = 0;i < n;i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
}

template<typename T>
int partition(T data[],int left,int right)
{
	T dstone = data[left];
	int pos = left;
	for(int i = left + 1;i <= right;i++)
	{
		if(data[i] < dstone)
			if(++pos != i)
				swap(data[pos],data[i]);
	}
	swap(data[left],data[pos]);
	return pos;
}

template<typename T>
void quicksort(T data[],int left,int right)
{
	if(left < right)
	{
		int pos = partition(data,left,right);
		quicksort(data,left,pos - 1);
		quicksort(data,pos + 1,right);
	}
}

/* int main() */
// {
	// int n;
	// std::cin>>n;
	// int *a = new int[n];
	// std::random_device rd;
	// std::mt19937 mt(rd());
	
	// for(int i = 0;i < n;i++)
		// a[i] = mt();
	// quicksort<int>(a,0,n - 1);
	// disp<int>(a,n);
	// delete [] a;
/* } */
