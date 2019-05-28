#include <iostream>
#include <time.h>
#include <string>
#include <vector>		//STL Vector
#include <list>			//STL List
#include <map>			//STL Map
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	
#include <iterator>		//여러 종류의 반복자의 정의 담음.

using namespace std;

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}
/*
리스트는 임의 접근 반복자를 제공하지 않으므로 정렬 속도가 대단히 느린 편이다. 
그래서 sort 알고리즘 함수를 사용하지 못하며 대신 sort 멤버 함수를 사용해야 한다. 
sort 알고리즘은 임의 접근을 활용하는 퀵 소트로 구현되어 있는데 비해 리스트의 sort 멤버 함수는 리스트에 좀 더 특화된 알고리즘으로 작성되어 있다.
두 개의 원형이 제공된다.
		//void sort();
		//void sort(BinPred op);

인수를 받지 않는 sort 멤버 함수는 < 연산자로 노드를 비교하여 정렬하며 조건자를 받아들이는 sort 멤버 함수는 조건자의 비교 결과대로 정렬한다. 


다음 멤버 함수는 연속된 중복 요소를 제거하는데 같은 이름의 전역 함수도 있지만 멤버 함수는 리스트의 링크 구조를 활용하도록 구현되어 있다.
		//void unique();
		//void unique(UniPred op);
*/

int main()
{

	const char str[] = "stllistcontainer";
	list<char> li(&str[0], &str[sizeof(str) - 1]);

	dump("원본", li);
	li.sort();						//list는 전역 sort를 사용할 수 없기 때문에 맴버sort함수를 사용해야합니다.

	dump("sort후", li);
	li.unique();
	dump("unique후", li);			// 연속으로 중복되는 리스트의 요소를 제거하고, 한개만남십니다 l l l -> l
	return 0;
}
