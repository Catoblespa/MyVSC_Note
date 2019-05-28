#include <iostream>
#include <time.h>
#include <string>
#include <vector>		//STL Vector
#include <list>			//STL List
#include <map>			//STL Map
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	
#include <iterator>		//여러 종류의 반복자의 정의 담음.
#include <deque>		//STL deque 정의 헤더
#include <set>

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

/*
집합 연산 알고리즘은 합집합, 교집합, 차집합, 포함 여부 등의 집합 관련 연산 기능을 제공한다. 
전역 알고리즘 함수들이라 임의의 컨테이너와 함께 사용할 수 있지만 주로 셋과 함께 사용되므로 여기서 알아보도록 하자. 
다음 다섯 가지의 함수가 제공된다.
		//OutIt set_union(InIt1 first1,InIt1 llast1, InIt2 first2, InIt2 last2, OutIt result);
		//OutIt set_intersection (InIt1 first1,InIt1 llast1, InIt2 first2, InIt2 last2, OutIt result);
		//OutIt set_difference (InIt1 first1,InIt1 llast1, InIt2 first2, InIt2 last2, OutIt result);
		//OutIt set_sysmmetric_difference (InIt1 first1,InIt1 llast1, InIt2 first2, InIt2 last2, OutIt result);
		//bool includes (InIt1 first1,InIt1 llast1, InIt2 first2, InIt2 last2);

대표적으로 합집합을 구하는 set_union 함수에 대해서만 알아보자. 
이 함수는 두 개의 반복자 구간 first1~last1, first2~last2를 인수로 전달받아 두 구간에 속하는 요소들을 중복없이 합쳐서 result 반복자 위치에 대입한다.
원본 반복자 구간은 입력 반복자이므로 꼭 set일 필요는 없지만 효율적인 합집합 연산을 위해 반드시 정렬되어 있어야 한다.
 정렬된 벡터나 리스트의 구간도 원본으로 사용할 수 있다.
구해진 합집합은 result 반복자가 지정하는 위치에 차례대로 대입되는데 이 반복자도 출력 기능만 제공하면 되므로 임의의 컨테이너에 결과를 저장할 수 있다.
이때 결과를 대입받을 컨테이너는 예상되는 합집합을 저장할만한 충분한 공간을 확보하고 있어야 한다.
아니면 삽입 반복자를 사용하여 입력되는데로 컨테이너의 공간을 재할당하도록 할 수 있는데 주로 끝에 삽입하는 back_inserter가 사용된다.

나머지 함수들은 교집합, 차집합, 대칭적 차집합을 작성한다. 
대칭적 차집합이란 한쪽 구간에만 있는 요소로 구성된 집합을 의미한다. 
includes 함수는 두 반복자 구간이 포함관계에 있는지를 조사하여 한 집합이 다른 집합의 부분집합인지를 점검한다. 

모든 집합 함수들은 마지막 인수로 요소의 대소 관계를 비교하는 이항 조건자를 지정할 수 있다


*/


int main()
{

	int i;
	int ar1[] = { 7,0,0,6,2,9,1,9,1,4,9,2,0 };
	int ar2[] = { 9,1,7,6,0,0,4,0,5,1,8 };
	set<int> s1;
	for (i = 0; i < sizeof(ar1) / sizeof(ar1[0]); i++) {
		s1.insert(ar1[i]);
	}

	set<int> s2;
	for (i = 0; i < sizeof(ar2) / sizeof(ar2[0]); i++) {
		s2.insert(ar2[i]);
	}



	vector<int> vu;
	set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(vu));
	dump("합집합", vu);

	vector<int> vi;
	set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(vi));
	dump("교집합", vi);

	vector<int> vd;
	set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(vd));
	dump("차집합", vd);

	vector<int> vd2;
	set_symmetric_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(vd2));
	dump("대칭차", vd2);


	return 0;
}
