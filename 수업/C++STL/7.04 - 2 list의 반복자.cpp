// ConsoleApplication2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"



int main()
{
	////##1 list 반복자.
	////방방향 반복자를 제공한다.

	//list<int> myList;
	//myList.push_back(10);
	//myList.push_back(20);
	//myList.push_back(30);
	//myList.push_back(40);
	//myList.push_back(50);
	//list<int>::iterator iter_begin = myList.begin();
	//list<int>::iterator iter_end = myList.end();
	////순방향 조회
	//for (; iter_begin != iter_end; iter_begin++)
	//{
	//	cout << *iter_begin << endl;
	//}
	//cout << "================" << endl;

	////iter_begin = myList.begin();
	////iter_end = myList.end();
	//////역방향 조회(reverse iterator)
	////list<int>::reverse_iterator iter_rbegin = myList.rbegin();
	////list<int>::reverse_iterator iter_rend = myList.rend();
	////for (; iter_rbegin != iter_rend ;iter_rbegin++)
	////{
	////	cout << *iter_rbegin << endl;
	////}
	////cout << "================" << endl;


	////##2 list.reverse() 함수 
	//myList.reverse();		//모든 원소를 뒤집음
	////순방향 조회
	//for (; iter_begin != iter_end; iter_begin++)
	//{
	//	cout << *iter_begin << endl;
	//}
	//cout << "================" << endl;




	//##3. 중간 삽입
	//list<int> myList;
	//myList.push_back(10);
	//myList.push_back(30);
	//myList.push_back(50);
	//list<int>::iterator iter_begin = myList.begin();
	//list<int>::iterator iter_end = myList.end();
	//++iter_begin;
	//myList.insert(iter_begin, 20);

	//++iter_begin;
	//myList.insert(iter_begin, 40);		// list는 중간 삽입 이후에도 end무효화는 일어나지 않는다!

	//for (auto& i : myList)
	//{
	//	cout << i << endl;
	//}

	//cout << "===============" << endl;

    /////////////////////////////////////////////////////////////////
	////##4 중간 삭제
	//list<int> myList;
	//myList.push_back(10);
	//myList.push_back(20);
	//myList.push_back(30);
	//list<int>::iterator iter_begin = myList.begin();
	//list<int>::iterator iter_end = myList.end();

	//++iter_begin;
	//list<int>::iterator iter_next = myList.erase(iter_begin);

	//cout << *iter_next << endl;


	////중간 삭제 이후 삭제된 위치의 반복자는 무효화가 일어나므로
	////다시 초기화하거나 반환으로 다음 위리를 받아주면 된다.
	////list는 중간 삭제 이후에도 end의 무효화는 일어나지 않는다.
	//for (iter_begin = myList.begin(); iter_begin != iter_end; ++iter_begin)
	//	cout << *iter_begin << endl;

	///////////////////////////////////////////////////////////////////
	////#5 sort맴버 함수
	//list<int> lst{ 5,2,4,3,1 };
	//lst.sort();
	////기본 오름차순
	//for (auto& i : lst)
	//{
	//	cout << i << endl;
	//}
	//cout << "====================" << endl;
	//lst.sort(greater<int>()); //조건자를 이용한 내림차순 정렬
	//for (auto& i : lst)
	//{
	//	cout << i << endl;
	//}


/*
	|---------------------------------------------------------------|
	|							vector vs list						|
	|---------------------------------------------------------------|
	|			|		vector			|			list			|
	|---------------------------------------------------------------|
	|메모리방식	|	배열기반(연속된)	|	노드기반 (비연속된)		|
	|---------------------------------------------------------------|
	|반복자		|	임의접근+양방향		|		양방향 반복자		|
	|---------------------------------------------------------------|	
	|장점		|	탐색에 유리함		|	빈번한 삽입 삭제 유리	|
	|---------------------------------------------------------------|
	|단점		|	빈번한 삽입삭제 불리|		탐색에 불리			|
	|---------------------------------------------------------------|
	|sort		|	<algorithm>에서제공	|		맴버함수 제공		|
	|---------------------------------------------------------------|
	|공통		|		표준 시퀀스 컨테이너(선형적 구조)			|
	|---------------------------------------------------------------|







*/





	return 0;
}

