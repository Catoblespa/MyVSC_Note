// ConsoleApplication2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <memory>



/* 셀룰러 오토마톤*/

#define MapH 200
#define MapW 450

#define GROUND 10
#define SURFACE 15		//표면 SURFACE
#define CRUST_H 40		//지각
#define Hell_MIN_H 180	//헬
#define Hell_MAX_H 190	//헬
#define CORE_H 195
#define AUTOMATA 3


#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

template <typename T1, int row, int col>
void PrintArray(T1(&result)[row][col])
{
	system("cls");
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (result[i][j] == 1)			//일반지형
				cout << "@";
			else if (result[i][j] == 2)		//정글지형
				cout << ".";
			else if (result[i][j] == 3)		//지옥지형
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;

	}
	Sleep(2000);
}


template <typename T1, int row, int col>
void InsertArray(T1(&r1)[row][col], T1(&r2)[row][col])
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			r1[i][j] = r2[i][j];
		}
	}
}

template <typename T1, int row, int col>
void CellAutomata(T1(&cell)[row][col], T1(&temp)[row][col])
{
	for (size_t i = 0; i < AUTOMATA; i++)
	{
		int Rcount = 0;
		int Jcount = 0;
		int Hcount = 0;
		for (size_t i = 1; i < MapH - 1; i++)
		{
			for (size_t j = 1; j < MapW - 1; j++)
			{
				{
					Rcount = 0;
					Jcount = 0;
					Hcount = 0;
					if (cell[i][j + 1] == 1)
						Rcount++;
					if (cell[i - 1][j + 1] == 1)
						Rcount++;
					if (cell[i + 1][j + 1] == 1)
						Rcount++;
					if (cell[i][j - 1] == 1)
						Rcount++;
					if (cell[i + 1][j - 1] == 1)
						Rcount++;
					if (cell[i - 1][j - 1] == 1)
						Rcount++;
					if (cell[i + 1][j] == 1)
						Rcount++;
					if (cell[i - 1][j] == 1)
						Rcount++;

					if (cell[i][j + 1] == 2)
						Jcount++;
					if (cell[i - 1][j + 1] == 2)
						Jcount++;
					if (cell[i + 1][j + 1] == 2)
						Jcount++;
					if (cell[i][j - 1] == 2)
						Jcount++;
					if (cell[i + 1][j - 1] == 2)
						Jcount++;
					if (cell[i - 1][j - 1] == 2)
						Jcount++;
					if (cell[i + 1][j] == 2)
						Jcount++;
					if (cell[i - 1][j] == 2)
						Jcount++;

					if (cell[i][j + 1] == 3)
						Hcount++;
					if (cell[i - 1][j + 1] == 3)
						Hcount++;
					if (cell[i + 1][j + 1] == 3)
						Hcount++;
					if (cell[i][j - 1] == 3)
						Hcount++;
					if (cell[i + 1][j - 1] == 3)
						Hcount++;
					if (cell[i - 1][j - 1] == 3)
						Hcount++;
					if (cell[i + 1][j] == 3)
						Hcount++;
					if (cell[i - 1][j] == 3)
						Hcount++;
				}
				//if (count > 4)
				//	temp[i][j] = 1;
				//else if (count <4)
				//	temp[i][j] = 0;
				//else
				//{
				//	temp[i][j] = random(2);
				//}
				if (Hcount + Jcount + Rcount > 4)
				{
					if (Hcount >= Rcount && Hcount >= Jcount)
					{
						temp[i][j] = 3;
					}
					else if (Jcount >= Rcount && Jcount >= Hcount)
					{
						temp[i][j] = 2;
					}
					else
						temp[i][j] = 1;
				}
				else if (Hcount + Jcount + Rcount < 4)
					temp[i][j] = 0;
				else
					temp[i][j] = temp[i][j - 1];
			}
		}
		//Sleep(2000);
		InsertArray(cell, temp);
	}
}

template <typename T1, int row, int col>
void MakeBaseMap(T1(&cell)[row][col], T1(&temp)[row][col])
{
	for (size_t i = 0; i < MapH; i++)
	{
		for (size_t j = 0; j < MapW; j++)
		{
			cell[i][j] = 0;
			temp[i][j] = 0;
		}
	}
	for (size_t i = 0; i < MapH; i++)
	{
		for (size_t j = 0; j < MapW; j++)
		{
			if (i  <Hell_MAX_H && i>Hell_MIN_H)			//지옥 터널 뚫기
				cell[i][j] = 0;
			else if (i < CRUST_H &&  i > SURFACE)		//지각층은 좀더 빽뺵하게 채우기
			{
				if (random(3) > 0)
					cell[i][j] = 1;
				else
					cell[i][j] = 0;

				//여기서는 높은 확률로 돌로 체우도록하자. 현재는 무조건 채워진 상태
			}
			else if (GROUND < i && i < SURFACE)						//표면층은 살짝 울퉁불퉁하게 해보자.
			{
				cell[i][j] = random(2);	//현재는 랜덤으로 되어있지만.. 처음에 1이나왔으면 다음에 1이 나올 확률을 높여서
										//좀 평평하게 만들어야할듯.. 
										//일단 이렇게 처리한후에, 표면을 다듬는 함수를 만들자.
				if (cell[i][j] == 0)
					cell[i][j] = random(2);		//한번더 평탄화
			}
			else if (i < GROUND)
			{
				cell[i][j] = 0;		//좀평평하게 해볼까 ?
			}
			else if (i > CORE_H)		//핵부분은 좀더 빽뺵하게 채우도록하자
			{
				if (random(4) <= 3)
					cell[i][j] = 1;
				else
					cell[i][j] = 0;
			}
			else
				cell[i][j] = random(2);

			//temp[i][j] = 1;
		}
	}
}


template <typename T1, int row, int col>
void AddJungleField(T1(&cell)[row][col])
{
	const size_t jungleScaleH = 40;
	const size_t jungleScaleW = 60;
	size_t junglePosH = random(Hell_MIN_H - jungleScaleH);
	size_t junglePosW = random(MapW - jungleScaleW);

	for (int i = junglePosH; i < junglePosH + jungleScaleH; i++)
	{
		//for (size_t j = junglePosW; j < junglePosW+jungleScaleW; j++)
		//{
		//	if(cell[i][j] == 1)	
		//		cell[i][j] = 2;
		//}
		for (int j = junglePosW - i; j < junglePosW + i; j++)
		{
			if (cell[i][j] == 1)
				cell[i][j] = 2;
		}


	}

	for (int i = junglePosH; i < junglePosH + jungleScaleH; i++)
	{
		for (int j = junglePosW - i - 5; j < junglePosW + i - 5; j++)
		{
			if (cell[i][j] == 1 && random(2))
				cell[i][j] = 2;
		}
	}
	//for (size_t i = junglePosH-5; i < junglePosH + jungleScaleH+5; i++)
	//{
	//	for (size_t j = junglePosW-5; j < junglePosW + jungleScaleW+5; j++)
	//	{
	//		if (cell[i][j] == 1 && random(3) <=1)
	//			cell[i][j] = 2;
	//	}
	//}

	for (size_t i = junglePosH - 10; i < junglePosH + jungleScaleH + 10; i++)
	{
		for (size_t j = junglePosW - i; j < junglePosW + jungleScaleW + i; j++)
		{
			if (cell[i][j] == 1 && random(5) <= 1)
				cell[i][j] = 2;
		}
	}
}

template <typename T1, int row, int col>
void AddHellField(T1(&cell)[row][col])
{
	//const size_t jungleScaleH = 50;
	//const size_t jungleScaleW = 100;
	size_t HellMaxH = MapH;//random(Hell_MIN_H - jungleScaleH);
	size_t HellMinH = Hell_MIN_H - 10;//random(MapW - jungleScaleW);

	for (size_t i = HellMinH; i < HellMaxH; i++)
	{
		for (size_t j = 0; j < MapW; j++)
		{
			if (cell[i][j] == 1)
				cell[i][j] = 3;
		}
	}

	for (size_t i = HellMinH - 10; i < HellMaxH; i++)
	{
		for (size_t j = 0; j < MapW; j++)
		{
			if (cell[i][j] == 1 && random(2) == 1)
				cell[i][j] = 3;
		}
	}
}

int main()
{
	randomize();
	int cell[MapH][MapW];
	int result[MapH][MapW];

	MakeBaseMap(cell, result);
	//PrintArray(cell);
	//AddJungleField(cell);
	AddJungleField(cell);
	AddHellField(cell);
	//PrintArray(cell);
	//PrintArray(cell);
	//PrintArray(cell);
	CellAutomata(cell, result);
	//PrintArray(cell);
	PrintArray(cell);

	return 0;
}
