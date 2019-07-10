#include <iostream>
#include <time.h>
#include <string>
#include <vector>		//STL Vector
#include <list>			//STL List
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	
#include <iterator>		//여러 종류의 반복자의 정의 담음.
#include <deque>		//STL deque 정의 헤더
#include <set>			//STL 연관컨테이너 set
#include <map>			//STL 연관컨테이너 map
#include <stack>		//STL 컨테이너 어댑터 stack
#include <queue>		////STL 컨테이너 어댑터 queue
#include <array>
#include <numeric>		//수치 관련 알고리즘 . STL이 아닌 C+라이브러리에 포함되어 있다.
#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;

template <typename T>
inline void SAFE_opVECTOR_DELETE_ALL_ELEMENT(vector<T*>& con)
{
	while (true)
	{
		if (con.empty())
			break;
		if (con.back() != nullptr)
			delete con.back();

		con.pop_back();
	}
}

template <typename T>
inline void SAFE_opVECTOR_DELETE_ALL_ELEMENT(vector<T*>* con)
{
	while (true)
	{
		if (con->empty())
			break;

		if (con->back() != nullptr)
			delete con->back();

		con->pop_back();
	}

	if (con != nullptr)
		delete con;
}



template <typename T, typename S>
inline void SAFE_opMAP_DELETE_ALL_ELEMENT(map<S,T*>& con)
{
	while (true)
	{
		if (con.empty())
			break;

		if (con.begin()->second != nullptr)
		{
			delete (con.begin()->second);
			con.erase(con.begin());
		}
	}
}

template <typename T, typename S>
inline void SAFE_opMAP_DELETE_ALL_ELEMENT(map<S, T*>* con)
{
	while (true)
	{
		if (con->empty())
			break;

		if (con->begin()->second != nullptr)
		{
			delete (con->begin()->second);
			con->erase(con->begin());
		}
	}

	if (con != nullptr)
		delete con;

}


template <typename T>
inline void SAFE_opLIST_DELETE_ALL_ELEMENT(list<T> list)
{
	while (true)
	{
		if (list.empty())
			break;


		if (list.back() != nullptr)
			delete list.back();

		list.pop_back();
	}
}


template <typename T, template<typename,typename> typename Container>
void DELETER(Container<T*,allocator<T*>> con) // vector < T> list <T>
{
	for (auto& i : con)
	{
		if (i != nullptr)
			delete i;
	}

	con.clear();

//	cout << "할뚜이따	" << endl;
	cout << typeid(T).name() << endl;
	cout << typeid(con).name() << endl;
}

/*template <typename T, template<typename, typename> typename Container>
void DELETER(Container<T*, allocator<T*>>* con) 
{
	for (auto i : con)
	{
		if (i != nullptr)
			delete i;
	}

	con->clear();
	if (con != nullptr)
		delete con;

}*/

class CTest
{
	
};

class CTest2
{

};


int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1365);      //누수 라인 중단점
	_CrtDumpMemoryLeaks();			//메모리 누수 출력 (디버그 모드)
	vector<CTest*> vec;

	vec.push_back(new CTest());
	vec.push_back(new CTest());
	vec.push_back(new CTest());
	vec.push_back(new CTest());
	//SAFE_opVECTOR_DELETE_ALL_ELEMENT(vec);
	DELETER(vec);

	vector<CTest*>* vec2;

	vec2 = new vector<CTest*>();
	vec2->push_back(new CTest());
	vec2->push_back(new CTest());
	vec2->push_back(new CTest());
	SAFE_opVECTOR_DELETE_ALL_ELEMENT(vec2);

	//DELETER(vec2);

	list<CTest*> list;
	list.push_back(new CTest());
	list.push_back(new CTest());
	list.push_back(new CTest());
	list.push_back(new CTest());
	list.push_back(new CTest());
	SAFE_opLIST_DELETE_ALL_ELEMENT(list);


	map<string, CTest*> MAP;
	MAP.insert(pair<string, CTest*>("1", new CTest()));
	MAP.insert(pair<string, CTest*>("2", new CTest()));
	MAP.insert(pair<string, CTest*>("3", new CTest()));
	MAP.insert(pair<string, CTest*>("4", new CTest()));

//	auto a = MAP.begin()->second;
	SAFE_opMAP_DELETE_ALL_ELEMENT(MAP);



	vector<CTest*> b;

	b.push_back(new CTest);
	b.push_back(new CTest);
	b.push_back(new CTest);
	b.push_back(new CTest);

	DELETER(b);
	
	//list<int> a;

	//list<int> list2;
	//list.push_back(1);
	//SAFE_opLIST_DELETE_ALL_ELEMENT(list);

	//DELETER(list);

	return 0;
}