#include <iostream>
#include <time.h>
#include <string>
#include <vector>		//STL Vector
#include <list>			//STL List
#include <map>			//STL Map
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	
#include <iterator>		//여러 종류의 반복자의 정의 담음.

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.
const unsigned NUM = 100000;


using namespace std;

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{

	randomize();

	vector<int> vi;

	list<int> li;

	int i;      

	clock_t start;



	for (i = 0; i < NUM; i++) {

		vi.push_back(random(100));

		li.push_back(random(100));

	}

	cout << "키를 누르면 벡터를 정렬합니다." << endl;

	getchar();

	start = clock();

	sort(vi.begin(), vi.end());

	cout << "벡터 정렬완료. 소요시간 = " << clock() - start << endl;



	cout << "키를 누르면 리스트를 정렬합니다." << endl;

	getchar();

	start = clock();

	li.sort();

	cout << "리스트 정렬완료. 소요시간 = " << clock() - start << endl;
}

/*
정렬은 비교와 교환이 굉장히 빈번한 알고리즘이므로 조금이라도 속도를 높이려면 임의 접근이 가능해야 한다. 
꼭 필요할 경우는 이 멤버 함수로 리스트를 정렬할 수는 있지만 
//정렬이 필요한 자료를 리스트에 저장하는 것은 애초에 선택이 잘못된 것이다.


*/
