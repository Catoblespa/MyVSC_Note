// ConsoleApplication2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


//#1. STL list
//양방향 연결 리스트 기반이다. (더블 링크드 리스트)
// 표준 시퀀스 컨테이너다.(원소배치가 선형적이다)
// 노드기반 컨테이너이다 (비연속된 메모리를 사용한다)
// 임의접근이 불가하고 오로지 순차접근만 허용한다 => 탐색에 불리하다
//벡터와 달리 한정된 메모리가 아니기에 빈번한 삽입,삭제에 유리하다


int main()
{
	//#2 list 원소 삽입
	//list<int> myList1;
	//list<double> list2;
	//myList1.push_back(30);
	//myList1.push_back(40);
	//myList1.push_back(50);
	//for (auto& element : myList1)
	//	cout << element << endl;
	//cout << "size : " << myList1.size() << endl;
	//cout << "------------------------------" << endl;
	//myList1.push_front(20);
	//myList1.push_front(10);
	//for (auto& element : myList1)
	//	cout << element << endl;
	//cout << "size : " << myList1.size() << endl;



	////#3 list 원소 제거
	//list<int> myList;
	//myList.push_back(10);
	//myList.push_back(20);
	//myList.push_back(30);
	//myList.push_back(40);
	//myList.push_back(50);

	//for (auto& element : myList)
	//	cout << element << endl;
	//cout << "-=-====================" << endl;

	//myList.pop_back();
	//myList.pop_back();
	//for (auto& element : myList)
	//	cout << element << endl;
	//cout << "-=-====================" << endl;

	//myList.pop_front();
	//for (auto& element : myList)
	//	cout << element << endl;
	//cout << "-=-====================" << endl;





//
//	//#4 vector와 동일하게 front , back, clear , swap, size ,empty 등의 함수를 재공해준다.
//	list<int> myList;
//	if (myList.empty())
//		cout << "비어있음" << endl;
//	else
//		cout << "원소 있음" << endl;
//	myList.push_back(10);
//	myList.push_back(20);
//	myList.push_back(30);
//	cout <<"front : "<< myList.front() << endl;			//list의 front 와 back은 사본이 아니라 원본을 반환함
//	cout << "back  : " << myList.back() << endl;
////	cout << myList[2] << endl;	//Error ! 임의 접근 불가.



	list<int> myList;



    return 0;
}

