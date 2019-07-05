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

    
	//##4 중간 삭제

	list<int> myList;
	myList.push_back(10);
	myList.push_back(20);
	myList.push_back(30);
	list<int>::iterator iter_begin = myList.begin();
	list<int>::iterator iter_end = myList.end();

	++iter_begin;
	list<int>::iterator iter_next = myList.erase(iter_begin);

	cout << *iter_next << endl;


	//중간 삭제 이후 삭제된 위치의 반복자는 무효화가 일어나므로
	//다시 초기화하거나 반환으로 다음 위리를 받아주면 된다.
	//list는 중간 삭제 이후에도 end의 무효화는 일어나지 않는다.
	for (iter_begin = myList.begin(); iter_begin != iter_end; ++iter_begin)
		cout << *iter_begin << endl;
	
	return 0;
}

