#include <iostream>

using namespace std;

//#1 구조체 (structure)
// 자료의 집합을 정의한 자료형(사용자 정의 자료형)
//

struct tagGrade
{
	char szName[32];
	int iKorean;
	int iEnglish;
	int iMath;
	int iTotal;
	int fAverage;
};

struct tagMyVector
{
	int x;
	int y;
	int z;
};

struct tagPoint {
	int x, y;
};

void Swap(tagPoint* tp)
{
	int temp = tp->x;
	tp->x = tp->y;
	tp->y = temp;
}

int main()
{
	//구조체 변수 선언과 초기화
	//tagGrade tGrade2 = { "홍길동", 10,20,30,40,50.f };
	//tagGrade tGrade = {};	//모든 맴버 0 초기화.
	//tagGrade tGrade3 = { "홍길동", 10,20,30 }; //나머지 0초기화.


	//구조체 맴버 접근
	//tagGrade tGrade2 = { "홍길동", 10,20,30,40,50.f };
	//cout << tGrade2.szName << endl;
	//cout << tGrade2.iKorean << endl;
	//cout << tGrade2.iEnglish << endl;
	//cout << tGrade2.iMath << endl;
	//cout << tGrade2.iTotal << endl;
	//cout << tGrade2.fAverage << endl;

	////tGrade는 엄연한 tagGrade타입이지, tagGrade* 타입이 아니므로 배열이름과는 다른 성격이다.
//	tagGrade tGrade4 = {};
//	cout << tGrade4 << endl;	//Error
//	cout << &tGrade4 << endl;			//단, 구조체 변수의 주소는 곧 첫 맴버의 주소와 같다
//	cout << &tGrade4.szName << endl;	// 즉 , 구조체 변수의 주소는 현재 구조체의 시작 주소이다.

	tagMyVector tVector = {10,20,30};
	tagMyVector* ptr = &tVector;

	(*ptr).x = 11;
	(*ptr).x = 22;
	(*ptr).x = 33;

	ptr->x = 100;
	ptr->y = 200;
	ptr->z = 300;


	tagPoint tPos = { 100,200 };
	Swap(&tPos);
	//구조체의 크기
	// 맴버(기본자료형 ) 중 가장 큰메모리를 기준으로 잡아 나간다.
	// 32비트 환경에서는 4바이트씩 끊어서 처리, 64비트 환경에서는 8바이트씩 끊어서 처리.

	cout << tPos.x << "," << tPos.y << endl;
}