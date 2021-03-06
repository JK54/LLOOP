#include <iostream>
#include <cstring>

void draw(int n)
{
	int i,j,count,size,**data;
	count = 1;
	size = n * n;
	//left,right,up,down ,flag of direction
	data = new int *[n];
	for(i = 0;i < n;i++)
	{
		data[i] = new int [n];
		std::memset(data[i],0,sizeof(int) * n);
	}
	i = 0;
	j = -1;	
	while(count <= n * n)
	{
		//another way of judge:axis less than boundary and the front element is unmodified.
   /*      while(count <= n * n && j < n - i - 1) */
		// // while(j + 1 < n && data[i][j + 1] == 0)
			// data[i][++j] = count++;
		// while(count <= n * n && i < j)
			// data[++i][j] = count++;
		// while(count <= n * n && j > n - i - 1)
			// data[i][--j] = count++;
		/* while(count <= n * n && i > j + 1) */
			// data[--i][j] = count++;
		while(j < n - i - 1)
		// while(j + 1 < n && data[i][j + 1] == 0)
			data[i][++j] = count++;
		while(i < j)
			data[++i][j] = count++;
		while(j > n - i - 1)
			data[i][--j] = count++;
		while(i > j + 1)
			data[--i][j] = count++;
	}
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
			std::cout<<data[i][j]<<" ";
		std::cout<<std::endl;
	}
	for(i = 0;i < n;i++)
		delete [] data[i];
	delete [] data;
}

int main()
{
	int n;
	std::cin>>n;
	draw(n);
	return 0;
}
