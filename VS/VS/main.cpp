#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <time.h>
using namespace std;

typedef struct
{
	double date;
	int No;
}node;


/*���ս�������*/
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

//TODO:����ɣ��Ѳ���
//ranking ����
vector<double> ranking(vector<int> ObjV)
{
	int Nind = ObjV.size();
	//Ϊ�����򷽱㷵������, ����һ���ṹ��
	
	vector<node> ObjVSub(Nind);
	for (int i = 0; i < Nind; i++)
	{
		ObjVSub[i].date = ObjV[i];
		ObjVSub[i].No = i;
	}

	vector<double> RFun(Nind);
	vector<int> FitnVIndex;
	
	//������Ӧ�ȵ��м����
	for (int i = 0; i < Nind; i++)
	{
		RFun[i] = 2 * (double)(i) / (double)(Nind - 1);
	}
	//��������
	sort(ObjVSub.begin(), ObjVSub.end());

	vector<node> ix(Nind);
	for (int i = 0; i < Nind; i++)
	{
		ix[i].date = ObjVSub[i].No;
		ix[i].No = i;
	}
	vector<node> Sorted = ObjVSub;


	//���㲻��ͬԪ�ص�����
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




//select����
vector<double> cumsum(vector<double> FitnV)
{
	for (int i = 1; i < FitnV.size(); i++)
	{
		FitnV[i] = FitnV[i - 1] + FitnV[i];
	}
	return FitnV;
}

//����ת��
vector<vector<double>> transpose(vector<vector<double>> Matrix)
{
	vector<vector<double>> MatrixRes(Matrix[0].size(), vector<double>(Matrix.size()));
	for (int i = 0; i < Matrix.size(); i++)
	{
		for (int j = 0; j < Matrix[0].size(); j++)
		{
			MatrixRes[j][i] = Matrix[i][j];
		}
	}
	return MatrixRes;
}


vector<int> sus(vector<double> FitnV, int NSel)
{
	int Nind = FitnV.size();
	vector<double> cumfit = cumsum(FitnV);
	vector<double> trials(Nind);
	for (int i = 0; i < Nind; i++)
	{
		trials[i] = cumfit[i] / (double)NSel * ((double)rand() / RAND_MAX + i);
	}
	vector<vector<double>> Mf, Mt;
	for (int i = 0; i < Nind; i++)
	{
		Mf.push_back(cumfit);
		Mt.push_back(trials);
	}
	Mf = transpose(Mf);


	vector<vector<bool>> MtandMf1(Nind,vector<bool>(Nind));
	vector<vector<bool>> MtandMf2(Nind, vector<bool>(Nind));
	vector<vector<int>> MfFind(Nind, vector<int>(Nind));
	vector<vector<bool>> ans(Nind, vector<bool>(Nind));
	vector<int> NewChrIx;
	for (int i = 0; i < Nind; i++)
	{
		for (int j = 0; j < Nind; j++)
		{
			if (Mt[i][j] < Mf[i][j])
			{
				MtandMf1[i][j] = true;
			}
			else
			{
				MtandMf1[i][j] = false;
			}
			if (i == 0)
			{
				MfFind[i][j] = 0;
			}
			else
			{
				MfFind[i][j] = Mf[i-1][j];
			}

			if (MfFind[i][j] <= Mt[i][j])
			{
				MtandMf2[i][j] = true;
			}
			else
			{
				MtandMf2[i][j] = false;
			}

			if (MtandMf1[i][j] && MtandMf2[i][j])
			{
				ans[i][j] = true;
			}
			else
			{
				ans[i][j] = false;
			}

			if (ans[i][j] == true)
			{
				NewChrIx.push_back(i);
			}
		}
	}
	vector<node> sortRand(NSel);
	for (int i = 0; i < NSel; i++)
	{
		sortRand[i].date = (double)rand() / RAND_MAX;
		sortRand[i].No = i;
	}
	sort(sortRand.begin(), sortRand.end());
	vector<int> NewChrIxRes(NSel);
	for (int i = 0; i < NewChrIx.size(); i++)
	{
		NewChrIxRes[i] = NewChrIx[sortRand[NSel - i - 1].No];
	}
	return NewChrIxRes;
}

vector<vector<int>> select(vector<vector<int>> Chrom, vector<double> FitnV)
{
	int Nind = Chrom.size();
	int Length = Chrom[0].size();
	int GGAP = 1;
	int NSel = Nind;
	vector<vector<int>> SelCh(Nind,vector<int>(Length));
	vector<int> ChrIx = sus(FitnV, NSel);
	for (int i = 0; i < Nind; i++)
	{
		for (int j = 0; j < Length; j++)
		{
			SelCh[i][j] = Chrom[ChrIx[i]][j];
		}
	}
	return SelCh;
}

//���溯��
vector<vector<int>> xovmp(vector<vector<int>> OldChrom, double Px, int Npt, int Rs)
{
	int Nind = OldChrom.size();
	int Lind = OldChrom[0].size();
	int Xops = Nind / 2;
	vector<int> DoCross(Xops);
	for (int i = 0; i < Xops; i++)
	{
		if ((double)rand() / RAND_MAX < Px)
		{
			DoCross[i] = 1;
		}
		else
		{
			DoCross[i] = 0;
		}
		
	}
	vector<int> odd;
	vector<int> even;
	int i = 0;
	while (i < Nind-1)
	{
		odd.push_back(i);
		even.push_back(i + 1);
		i = i + 2;
	}
	vector<vector<double>> Mask(odd.size(), vector<double>(Lind, 1));
	for (int i = 0; i < Mask.size(); i++)
	{
		Mask[i] = cumsum(Mask[i]);
	}
	vector<vector<double>> xsites(Mask.size(),vector<double>(2));
	for (int i = 0; i < Mask.size(); i++)
	{
		xsites[i][0] = Mask[i][Lind - 1];
	}
	for (int i = 0; i < Mask.size(); i++)
	{
		xsites[i][0] + ((int)(Mask[i][Nind] + 1)*DoCross[i] - 1) % (Mask[i][Nind - 1]) + 1;
	}
	return SelCh;
}

vector<vector<int>> xovsp(vector<vector<int>> OldChrom, double XOVR)
{
	return xovmp(OldChrom, XOVR, 1, 0);
}

vector<vector<int>> recombin(vector<vector<int>> Chrom, double px)
{
	int Nind = Chrom.size();
	Chrom = xovsp(Chrom, px);
	return Chrom;
}

vector<vector<int>> mut(vector<vector<int>> SelCh, double pm)
{
	return SelCh;
}

pair<vector<vector<int>>,vector<int>> reins(vector<vector<int>> SelCh, double pm)
{
	pair<vector<vector<int>>, vector<int>> result;

	return result;
}


int main()
{
	srand(time(NULL));
	vector<vector<int>> Chrom = { { 0, 1, 1, 0, 0 }, { 1, 0, 0, 1, 0 }, { 1, 1, 0, 0, 1 }, { 1, 0, 0, 0, 1 } };
	vector<int> ObjV = {1,2,3,4};
	double px = 0.1;
	double pm = 0.1;

	//ranking��������
	vector<double> FitnV = ranking(ObjV);
	cout << "ranking" << endl;
	for (int i = 0; i < FitnV.size(); i++)
	{
		cout << FitnV[i] << " ";
	}
	cout << endl << endl;
	cout << "select" << endl;
	vector<vector<int>> SelCh = select(Chrom, FitnV);
	for (int i = 0; i < SelCh.size(); i++)
	{
		for (int j = 0; j < SelCh[0].size(); j++)
		{
			cout << SelCh[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "recombin" << endl;
	SelCh = recombin(SelCh, px);
	/*vector<vector<int>> reverseMatrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	vector<vector<int>> reverseMatrixRes(reverseMatrix[0].size(), vector<int>(reverseMatrix.size()));
	for (int i = 0; i < reverseMatrix.size(); i++)
	{
		for (int j = 0; j < reverseMatrix[0].size(); j++)
		{
			reverseMatrixRes[j][i] = reverseMatrix[i][j];
		}
	}
	*/
	

	//FitnV = cumsum(FitnV);
	//for (int i = 0; i < FitnV.size(); i++)
	//{
	//	cout << FitnV[i] << " ";
	//}
	//cout << endl << endl;

	return 0;
}