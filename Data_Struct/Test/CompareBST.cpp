#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "../Include/AVLTree.hpp"
#include "../Include/RBTree.hpp"
#include "../Include/BSTree.hpp"
#include "../Include/Avl.cpp"
#define CW 100
#define TYPE unsigned int

AVLTree<TYPE> avl_h;
AVLtree avl_l;
RBTree<TYPE> rbtree_h;
BSTree<TYPE> bstree_h;
set<TYPE> set0;
struct timeval s0,s1,s2;
double t1,t2,t3,t4;
double t[CW][3];
double total = 0,in = 0,s = 0,r = 0;
vector<TYPE> a;

template<typename T>
void test_singel(bool ordered,int boundary,T jojo,int &count)
{
	std::ios::sync_with_stdio(false);
	std::random_device rd;
	std::mt19937 mt(rd());
	gettimeofday(&s0,NULL);
	if(!ordered)
	{
		for(int i = 0;i < boundary;i++)
			a[i] = mt();
		gettimeofday(&s2,NULL);
		t4 = (1000.0*static_cast<double>(s2.tv_sec - s0.tv_sec) + static_cast<double>(s2.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
		for(int i = 0;i < boundary;i++)
			jojo.insert(a[i]);
	}
	else
		for(int i = 0;i < boundary;i++)
			jojo.insert(i);
	//if the type is not set
	count += jojo.size();
	gettimeofday(&s1,NULL);
	if(ordered)
		t1 = (1000.0*static_cast<double>(s1.tv_sec - s0.tv_sec) + static_cast<double>(s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
	else
		t1 = (1000.0*static_cast<double>(s1.tv_sec - s2.tv_sec) + static_cast<double>(s1.tv_usec - s2.tv_usec)/1000.0) / 1000.0;
	if(!ordered)
		for(int i = boundary - 1;i >= 0;i--)
			jojo.find(a[i]);
	else
		for(int i = boundary - 1;i >= 0;i--)
			jojo.find(i);
	gettimeofday(&s0,NULL);
	t2 = (1000.0*static_cast<double>(s0.tv_sec - s1.tv_sec) + static_cast<double>(s0.tv_usec - s1.tv_usec)/1000.0) / 1000.0;
	if(!ordered)
		for(int i = 0;i < boundary;i++)
			jojo.erase(a[i]);
	else
		for(int i = boundary - 1;i >= 0;i--)
			jojo.erase(i);
	gettimeofday(&s1,NULL);
	t3 = (1000.0*static_cast<double>(s1.tv_sec - s0.tv_sec) + static_cast<double>(s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
}

double add_row(double data[][3],int row)
{
	double result = 0;
	for(int i = 0;i < 3;i++)
		result += data[row][i];
	return result;
}

double add_col(double data[][3],int col,int n)
{
	double result = 0;
	for(int i = 0;i < n;i++)
		result += data[i][col];
	return result;
}

template<typename K>
void test(void f(bool,int,K,int &),K jojo,int x,bool ordered)
{
	int count;
	std::ios::sync_with_stdio(false);
	std::string tile,file1,file2;
	tile = typeid(jojo).name();
	file1 = "/home/jk54/Code/Data_Struct/Test/Statistics/" + tile + "_raw";
	file2 = "/home/jk54/Code/Data_Struct/Test/Statistics/" + tile + "_avg";
#ifdef DDO3
	file1 += "_o3.log";
	file2 += "_o3.log";
	std::ofstream sta(file1,std::ios::app);
	std::ofstream stb(file2,std::ios::app);
#else
	file1 += "_o1.log";
	file2 += "_o1.log";
	std::ofstream sta(file1,std::ios::app);
	std::ofstream stb(file2,std::ios::app);
#endif
	std::ios::sync_with_stdio(false);
	count = 0;
	for(int i = 0;i < CW;i++)
	{
		f(ordered,x,jojo,count);
		t[i][0] = t1;
		t[i][1] = t2;
		t[i][2] = t3;
	}
			sta<<"-----------------------------------------------------------------------------------------------------"<<std::endl;
				stb<<"----------------------------------------------------------------------------------------------------"<<std::endl;
	if(ordered == false)
	{
		sta<<"Generate rand time : "<<t4<<" s";
		stb<<"Generate rand time : "<<t4<<" s";
	}
	sta<<"\n\t\t\t\t\t\t\t\t\t\t"<<tile;
	stb<<"\n\t\t\t\t\t\t\t\t\t\t"<<tile;
	if(ordered == false)
	{
		sta<<"(DisOrdered)"<<std::endl;
		stb<<"(DisOrdered)"<<std::endl;
	}
	else
	{
		sta<<"(Ordered)"<<std::endl;
		stb<<"(Ordered)"<<std::endl;
	}
	sta<<" wanted   nodes : "<<x<<std::endl;
	sta<<" inserted nodes : "<<static_cast<int>(count/CW)<<std::endl;
	sta<<"\t\t"<<"Insert time(s)"<<"\t\t"<<"Search time(s)"<<"\t\t"<<"Remove time(s)"<<"\t\t"<<"Total  time(s)"<<std::endl;
	stb<<" wanted   nodes : "<<x<<std::endl;
	stb<<" inserted nodes : "<<static_cast<int>(count/CW)<<std::endl;
	stb<<"\t\t"<<"Insert time(s)"<<"\t\t"<<"Search time(s)"<<"\t\t"<<"Remove time(s)"<<"\t\t"<<"Total  time(s)"<<std::endl;
	for(int i = 0;i < CW;i++)
		sta<<std::fixed<<std::setprecision(6)<<" "<<i <<"\t\t"<<t[i][0]<<"\t\t\t"<<t[i][1]<<"\t\t\t"<<t[i][2]<<"\t\t\t"<<add_row(t,i)<<std::endl;
	sta<<std::endl;
	in = add_col(t,0,CW);
	s = add_col(t,1,CW);
	r = add_col(t,2,CW);
	total = in + s + r;
	sta<<std::fixed<<std::setprecision(6)<<" Total "<<"\t"<<in<<"\t\t\t"<<s<<"\t\t\t"<<r<<"\t\t\t"<<total<<std::endl;
	sta<<std::fixed<<std::setprecision(6)<<" Avg "<<"\t"<<static_cast<double>(in/CW)<<"\t\t\t"<<static_cast<double>(s/CW)<<"\t\t\t"<<static_cast<double>(r/CW)<<"\t\t\t"<<static_cast<double>(total/CW)<<"\t\t\t"<<"\n\n"<<std::endl;
	stb<<std::fixed<<std::setprecision(6)<<" Avg "<<"\t"<<static_cast<double>(in/CW)<<"\t\t\t"<<static_cast<double>(s/CW)<<"\t\t\t"<<static_cast<double>(r/CW)<<"\t\t\t"<<static_cast<double>(total/CW)<<"\t\t\t"<<"\n\n"<<std::endl;
	sta.close();
	stb.close();
}

int main()
{
	int num[] = {1000,10000,50000,100000,500000,1000000,10000000};
	int size = sizeof(num)/sizeof(num[0]);
	a.reserve(num[size - 1]);
	for(int i = 0; i < size;i++)
	{
#ifdef AVL_H
		test(test_singel,avl_h,num[i],false);
		test(test_singel,avl_h,num[i],true);
#elif  AVL_L
		test(test_singel,avl_l,num[i],false);
		test(test_singel,avl_l,num[i],true);
#elif  RBT
		test(test_singel,rbtree_h,num[i],false);
		test(test_singel,rbtree_h,num[i],true);
#elif  BST
		test(test_singel,bstree_h,num[i],false);
		test(test_singel,bstree_h,num[i],true);
#elif  SET
		test(test_singel,set0,num[i],false);
		test(test_singel,set0,num[i],true);
#endif
	}
	return 0;
}
