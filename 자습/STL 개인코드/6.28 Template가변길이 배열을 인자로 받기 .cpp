#include <iostream>
#include <typeinfo>
using namespace std;


/*
	템플릿을 활용해서 배열길이를 알수없는 걸 인자로 받기!!
*/

int GetArraySize(int(&r)[5])
{
	return sizeof(r);
}


//T& r 에 2차원 배열이 들어올경우
template <typename T>
int GetArraySize(T& r)
{
	// 범위 기반 for문을 이용한 2차원 배열 다루기!! 우오앜ㅋㅋㅋㅋㅋ 개쩐다 ㅋㅋㅋ ㅅㅂ ㅋㅋ 시발 !! ㅠㅠㅋ튜큐ㅜ히.ㅏㅜ루ㅏㅢ
	for (auto& Array : r) // 범위기반 for문.
	{
		for (auto& element : Array)
		{
			cout << element;
		}
		cout << endl;
	}
	return sizeof(r);
}




// 템플릿을 이용한 길이를 알수 없는 1차원 배열 받기	// 위의 방법으로 해도 받을수 있음 rfor만 한번만 돌리면됨.
template <typename T1 , int size>
int GetArraySize(T1(&r)[size])
{
	for (int i = 0; i < size; i++)
	{
		cout << r[i] << endl;
	}
	return sizeof(r);
}


//템플릿을 이용한 2차원 배열 받기 두번째 방법	//왠만하면 T1(&r)[size]와 T1(&r)[row][col]로 나누어서 씁시다.. 맨위에건 1차,2차 다들어가버림
template <typename T1, int row , int col>
int GetArraySize(T1(&r)[row][col])
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << r[i][j];
		}
		cout << endl;
	}

	return sizeof(r);
}

int main()
{
	int iArr[10][10]= {0};
	int iArraySize = GetArraySize(iArr);
	cout << iArraySize << "bytes" << endl;

	cout << "--------------------" << endl;

	int iArr2[10] = { 10 };
	int iArraySize2 = GetArraySize(iArr2);



	return 0;
}
