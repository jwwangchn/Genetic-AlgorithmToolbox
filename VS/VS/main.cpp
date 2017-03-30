#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

typedef struct
{
	int date;
	int No;
}node;


/*按照降序排列*/
bool operator<(const node &a, const node &b)
{
	return a.date > b.date;
}

double sum(vector<double> RFun, int i, int j)
{
	double result = 0;
	for (int index = i; index <= j; index++)
	{
		result = result + RFun[index];
	}
	return result;
}


//ranking 函数
vector<double> ranking(vector<int> ObjV)
{
	int Nind = ObjV.size();
	//为了排序方便返回索引, 构造一个结构体
	
	vector<node> ObjVSub(Nind);
	for (int i = 0; i < Nind; i++)
	{
		ObjVSub[i].date = ObjV[i];
		ObjVSub[i].No = i;
	}

	vector<double> RFun(Nind);
	vector<int> FitnVIndex;
	
	//计算适应度的中间变量
	for (int i = 0; i < Nind; i++)
	{
		RFun[i] = 2 * (double)(i) / (double)(Nind - 1);
	}
	//降序排列
	sort(ObjVSub.begin(), ObjVSub.end());

	vector<node> ix(Nind);
	for (int i = 0; i < Nind; i++)
	{
		ix[i].date = ObjVSub[i].No;
		ix[i].No = i;
	}
	vector<node> Sorted = ObjVSub;


	//计算不相同元素的索引
	for (int i = 0; i < Nind - 1; i++)
	{
		if (Sorted[i].date != Sorted[i + 1].date)
		{
			FitnVIndex.push_back(i);
		}
	}
	FitnVIndex.push_back(Nind - 1);

	//double sumRFun = 0;
	//for (int i = 0; i <= FitnVIndex[0]; i++)
	//{
	//	sumRFun = sumRFun + RFun[i];
	//}
	vector<double> FitnVSub(Nind);
	//for (int i = 0; i <= FitnVIndex[0]; i++)
	//{
	//	FitnVSub[i] = sumRFun / (double)(FitnVIndex[0] + 1);
	//}

	//int i = FitnVIndex[0] + 1;

	int index = 0;
	int iWhile = 0;
	while (iWhile <= FitnVIndex.size() - 1)
	//for (int j = FitnVIndex[0]; j <= FitnVIndex[FitnVIndex.size() - 1];j++)
	{
		int j = FitnVIndex[iWhile++];
		FitnVSub[j] = sum(RFun, index, j) / (double)(j - index + 1);
		if (index != j)
		{
			for (int i = index; i < j; i++)
			{
				FitnVSub[i] = FitnVSub[j];
			}
		}
		double sumLook = sum(RFun, index, j);
		index = j + 1;
	}
	
	sort(ix.begin(), ix.end());
	vector<double> FitnV(Nind);
	for (int i = 0; i < Nind; i++)
	{
		FitnV[i] = FitnVSub[ix[Nind - i - 1].No];
	}
	return FitnV;
}

vector<vector<int>> select(vector<vector<int>> Chrom, vector<double>, double GGAP)
{
	vector<vector<int>> SelCh;
	return SelCh;
}

vector<vector<int>> recombin(vector<vector<int>> SelCh, double px)
{
	return SelCh;
}

vector<vector<int>> mut(vector<vector<int>> SelCh, double pm)
{
	return SelCh;
}

//pair<vector<vector<int>>,vector<int>> reins(vector<vector<int>> SelCh, double pm)
//{
//	pair<vector<vector<int>>, vector<int>> result;
//
//	return result;
//}


int main()
{
	vector<int> ObjV = {1,1,1,1,2,2,2,2};
	
	//ranking函数测试
	vector<double> FitnV = ranking(ObjV);
	for (int i = 0; i < FitnV.size(); i++)
	{
		cout << FitnV[i] << " ";
	}
	cout << endl;
	return 0;
}