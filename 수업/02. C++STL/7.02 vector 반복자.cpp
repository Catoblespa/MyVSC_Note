#include <iostream>
#include <vector>
using namespace std;

/*
	#1 반복자 (iterator)
	-컨테이너마다 (자료구조마다) 원소를 저장하고 접근하는 방식이 모두 다르다.
	-원소에 접근하기 위한 방법을 통일 시켜놓은 것이 바로 반복자다.
	-컨테이너마다 내부에 반복자 타입이 정의되어 있음.

	반복자의 기본역할
		1. 원소의 위치를 가리킨다. (원소에 접근할 수 있음)
		2. 반복자를 통해서 컨테이너를 순회할 수 있다.

*/
int main()
{
	// ##2.vector의 반복자 선언
	//vector<int> vec;
	//vector<int>::iterator a;



//	//##3 반복자를 통한 vector 원소 접근
//
//	vector <int >vec;
//
//	vec.push_back(10);
//	vec.push_back(20);
//	vec.push_back(30);
//
//
//	//begin() 함수 : 가장 첫번째 원소의 위치를 가리키는 반복자를 리턴
//	vector<int>::iterator iter_begin = vec.begin();
//	
//	//begin 함수는 *역참조 연산자가 오버로딩
//	cout << *iter_begin << endl;
////	cout << iter_begin << endl;		//이터레이터는 포인터가 아니기 때문에 참조연산자를 빼면 주소가 나온다거나 하지 않음!!!!
//
//	//end() 함수 : 가장 마지막 원소 "다음" 위치를 가리키는 반복자를 리턴 
//	vector<int>::iterator iter_end = vec.end();
//
//	// 반복자를 이용한 원소 순화
//
//	for (; iter_begin != iter_end; ++iter_begin)
//	{
//		cout << *iter_begin << endl;
//	}

	///* 비어 있는 컨테이너의 begin과 end는 같은위치다.*/

	//vector<int> vec;

	//if (vec.begin() == vec.end())
	//	cout << "비어 있음" << endl;



	////##5 vector는 임의접근 반복자를 제공한다.
	//vector<int> vec;
	//vec.push_back(10);
	//vec.push_back(20);
	//vec.push_back(30);
	//vector<int>::iterator iter_begin = vec.begin();
	//vector<int>::iterator iter_end = vec.end();
	//cout << "iter_begin[2]   : " << iter_begin[2] << endl;
	//cout << "*(iter_begin+2) : " << *(iter_begin + 2) << endl;		//순방향 임의 접근
	//cout << "iter_end[-2]    : " << iter_end[-2] << endl;			//역방향 임의 접근
	//cout << "*(iter_end-2)   : " << *(iter_end-2) << endl;


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////## 6.vector의 중간 삽입
	//vector<int> vec;
	//vec.push_back(10);
	//vec.push_back(30);
	//// insert( Where, Value); 

	//vector<int>::iterator iter_begin = vec.begin();
	//vector<int>::iterator iter_end = vec.end();


	//vec.insert(vec.begin()+1,20);
	////중간 삽입 이후에 재할당 복사가 발생한다면	 (중간 삽입을 할때 경우!)
	////현재 반복자의 무표화도 같이 진행된다.
	////따라서 반복자를 새로 받아와야한다.	

	////만약 재할당 복사가 발생하지 않았다면 (단순 push_back일 경우가 그렇다) 
	//									//단!!! capacity가 꽉차서 늘어날때 재할당이 발생한다!!!!
	////begin은 그대로 사용 가능하지만 end는 항상 새로 받아와야함.
	//iter_begin = vec.begin();
	//iter_end = vec.end();


	//for (size_t i = 0; i < vec.size(); i++)
	//{
	//	cout << vec[i] << endl;
	//}

	//for (; iter_begin != iter_end;  iter_begin++)
	//{
	//	vec.push_back(10);
	//	iter_end = vec.end();
	//	cout << *iter_begin << endl;
	//}
	/////////////////////////////////////////////////////
	//##6 vector의 중간 삭제

	vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);

	vector<int>::iterator iter_begin = vec.begin();
	vector<int>::iterator iter_end = vec.end();
	//erase(Where);

	auto next = vec.erase(iter_begin + 1);		//erase는 삭제한 원소의 다음위치를 가르킨다!  
												//마지막 원소를 제거하면 end반환!!
	cout << "next 값 : " << *next << endl;
	 

	iter_end = vec.end();			//end의 위치가 바뀌었으므로 갱신해줘야한다.

	for (; iter_begin != iter_end;  iter_begin++)
	{	
		cout << *iter_begin << endl;
	}


	return 0;
}
