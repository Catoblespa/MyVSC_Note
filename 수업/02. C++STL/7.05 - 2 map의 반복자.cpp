// ConsoleApplication2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


//map에서 find_if을 쓸때 functor 를 사용해서 검색할수 있당.
class CCompare
{
	const char * m_pString;
public:
	CCompare(const char * pString) : m_pString(pString) {}

	bool operator()(map<const char *, int >::value_type MyPair)
	{
		if (!strcmp(m_pString, MyPair.first))
			return true;

		return false;
	}

};
int main()
{
	//// #1. map 반복자
	//// 양방향 반복자를 제공한다.
	//map<int, int> Mymap;
	//// 정렬 순서 1,  2,  3
	//Mymap.insert(map<int, int>::value_type(1, 100));
	//Mymap.insert(map<int, int>::value_type(2, 200));
	//Mymap.insert(map<int, int>::value_type(3, 300));
	//map<int, int>::iterator iter_begin = Mymap.begin();
	//map<int, int>::iterator iter_end = Mymap.end();
	////순방향 순회
	//++iter_begin;
	//++iter_begin;
	////map의 반봅자에는 -> 연산자 오버로딩
	//cout << iter_begin->first << "," << iter_begin->second << endl;
	//cout << "----------------------------------------------------" << endl;
	//--iter_begin;
	//cout << iter_begin->first << "," << iter_begin->second << endl;
	//cout << "----------------------------------------------------" << endl;


	// ##2. find 함수
	//map<int, int> Mymap;
	//Mymap.insert(make_pair(1, 100));
	//Mymap.insert(make_pair(3, 300));
	//Mymap.insert(make_pair(2, 200));

	////find 맴버 함수   
	////find(key)
	////key에 해당하는 반복자를 리턴		
	////[]연산자와 같은 이진탐색을 실행하지만,  해당 key값이 없을경우 end()를 반환한다.
	//map<int,int>::iterator iter_find = Mymap.find(2);
	//if (iter_find == Mymap.end())
	//{
	//	cout << "탐색 실패" << endl;
	//	return;
	//}
	//cout << iter_find->first << "," << iter_find->second << endl;
	//cout << "---------------------------------------------" << endl;

	//// ## 3.find_if 함수 <algorithm> 에서 제공
	//map <const char*, int > Mymap;		//주의 ! const char * 이므로 문자열 상수의 주소값이 key값으로 전달된다!
	//Mymap.insert(make_pair("BBB", 200));
	//Mymap.insert(make_pair("AAA", 100));
	//Mymap.insert(make_pair("CCC", 300));
	//
	//
	////이게 되는 이유는 같은 문자열의 주소는 Data영역에 할당되고 , 같은 주소를 갖기 때문이다.
	////만약 문자열 상수의 경우가 아니였다면 , 주소값으로 찾게 되므로 find에 실패할것이다.
	//map<const char*, int >::iterator iter_find = Mymap.find("AAA"); //단순 이진탐색 , 주소값 비교
	//																//앵간하면 키값에 포인터형 넣지 말자 string을 쓰던가.
	//if (Mymap.end() == iter_find)
	//{
	//	cout << "탐색 실패" << endl;
	//	return 0;
	//}
	//cout << iter_find->first << "," << iter_find->second << endl;
	//cout << "---------------------------------------------" << endl;
	////find_if(begin , end 단항조건자)
	////단항 조건자가 반환하는 true에 해당하는 반복자를 리턴
	////주의!!! find_if는 순차탐색 알고리즘이다!
	//const char *szBuffer = "BBB";
	//map<const char*, int >::iterator iter_find2 = 
	//	find_if(Mymap.begin(), Mymap.end(), CCompare(szBuffer));
	//cout << iter_find2->first << "," << iter_find2->second << endl;
	//cout << "---------------------------------------------" << endl;

	return 0;
}
