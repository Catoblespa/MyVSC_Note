#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


using namespace std;



struct even : public unary_function<int, bool> {
	bool operator()(int a) const
	{
		if (a % 2 == 0)
			return true;
		else
			return false;
	}
};

struct odd {
	bool operator()(int a)
	{
		if(a% 2 !=0)
			return true;
		else
			return false;
	}
};



template <typename T, template<typename, typename> typename Container>
void DELETER(Container<T*, allocator<T*>> con) // vector < T> list <T>
{
	for (auto& i : con)
	{
		if (i != nullptr)
			delete i;
	}

	con.clear();

	//	cout << "할뚜이따	" << endl;
	//cout << typeid(T).name() << endl;
	//cout << typeid(con).name() << endl;
}



void MemoryLeakCheck()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1365);      //누수 라인 중단점
	_CrtDumpMemoryLeaks();			//메모리 누수 출력 (디버그 모드)
}


int main()
{
	////##1. count_if	 알고리즘 함수.
	//// 컨테이너가 갖고 있는 원소 중에 조건에 맞는 원소가 몇개 있는지 세어주는 함수.
	//
	//int iArr[5] = { 1,2,3,4,5 };

	////count_if (begin , end , 단항 조건자)
	//int Count = count_if(iArr, iArr + 5, even());
	//cout << "evne : " << Count << endl;
	//Count = count_if(iArr, iArr + 5, not1(even()));
	//cout << "odd : " << Count << endl;



	/*vector<int> vec{ 1,2,3,4,5 };
	int Count = count_if(vec.begin(), vec.end(), even());
	cout << "evne : " << Count << endl;
	Count = count_if(vec.begin(), vec.end(), not1(even()));
	cout << "evne : " << Count << endl;*/



	////##2 for_each(begin , end , 함수객체);
	////세번째 인자로 전달 받은 함수를 반복 호출하고 있는 형태의 알고리즘.
	//vector<int*> vec;

	//vec.push_back(new int);
	//vec.push_back(new int);
	//vec.push_back(new int);
	//vec.push_back(new int);

	//for_each(vec.begin(), vec.end(), [](int *& a)
	//	{
	//		delete a;
	//		a = nullptr;

	//	});
	//	DELETER(vec);



	// ##3 sort
	// 임의접근이 가능한 컨테이너에 대해 sort를 실행한다.
	// sort함수는 이항조건자를 받는다.
	vector<int> vec{ 5,1,4,3,2 };

	// 기본은 less (오름차순) 정렬을 실행한다.
	//	sort(vec.begin(), vec.end());

	// <functional>에서 제공하는 이항 조건자  less<>,
	sort(vec.begin(), vec.end(), less<int>());
	for_each(vec.begin(), vec.end(), [](int & a)
		{
			cout << a << endl;
		}
	);
	sort(vec.begin(), vec.end(), greater<int>());
	for_each(vec.begin(), vec.end(), [](int& a)
		{
			cout << a << endl;
		}
	);



	return 0;
}