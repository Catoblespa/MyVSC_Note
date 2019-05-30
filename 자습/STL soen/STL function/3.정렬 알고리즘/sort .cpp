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

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;

/*
정렬은 검색과 함께 가장 자주 사용되는 알고리즘이다. 
STL은 정렬을 하는 알고리즘과 정렬된 컨테이너에 대해 동작하는 알고리즘 다수 개를 제공한다. 

다음은 컨테이너를 정렬하는 4개의 알고리즘인데 정렬 범위와 안정성 여부가 각각 다르다.
		//void sort (RanIt first, RanIt last [, BinPred F]);
		//void stable_sort (RanIt first, RanIt last [, BinPred F]);
		//void partial_sort (RanIt first, RanIt SortEnd, RanIt last [, BinPred F]);
		//void nth_element(RanIt first, RanIt Nth, RanIt last [, BinPred F]);

모든 정렬 함수들은 바른 정렬을 위해 임의 접근 반복자를 요구하므로 임의 접근이 가능한 컨테이너에 대해서만 사용할 수 있다.
주로 벡터에 대해 정렬을 수행하며 C의 단순 배열에 대해서도 정렬을 수행할 수 있다.
네 함수 모두 정렬 대상을 지정하는 first ~ last 반복자 구간을 인수로 취하며 마지막 인수로 정렬의 기준으로 사용될 이항 조건자를 전달할 수 있다.
		*별도의 조건자가 지정되지 않을 경우 < 연산자로 요소의 대소를 비교한다.

sort 함수가 가장 기본적인 정렬 함수이며 first ~ last 구간을 조건자의 비교 결과대로 정렬한다.

stable_sort는 같은 값의 상대적인 순서가 정렬 후에도 유지되는 안정적인 정렬을 수행하는데 정렬 속도는 안정성이 없는 sort보다 조금 더 느리다.

partial_sort는 두 번째 인수로 지정한 SortEnd 부분 직전까지만 정렬하고 나머지 뒷부분은 정렬되지 않은 채로 내버려 둔다.
	최상위 n 번까지만 골라내고 싶을 때 이 함수를 사용하며 안정성은 없다. 

nth_element는 두 번째 인수로 지정한 nth에 n번째 값을 놓고 그 왼쪽에 n보다 작은 값을, 오른쪽에 n 이상의 값으로 구간을 분할한다. 
n의 위치만 정확하며 나머지 좌우 구간의 정렬 상태는 보증되지 않는다.
	특정값을 기준으로 미만 그룹, 이상 그룹을 분류할 때 유용하다. 
	

별도의 조건자를 지정하지 않으면 미만 비교 조건자인 less가 사용된다.
	다음 예제로 4가지 함수를 모두 테스트해 보자.
*/


template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{
	int ari[] = { 49,26,19,77,34,52,84,34,92,69 };


	vector<int> vi(&ari[0], &ari[10]);
	dump("원본", vi);

	sort(vi.begin(), vi.end());
	dump("sort", vi);

	vector<int> vi2(&ari[0], &ari[10]);
	stable_sort(vi2.begin(), vi2.end());
	dump("stable_sort", vi2);

	vector<int> vi3(&ari[0], &ari[10]);
	partial_sort(vi3.begin(), vi3.begin() + 5, vi3.end());
	dump("partial_sort", vi3);

	vector<int> vi4(&ari[0], &ari[10]);
	nth_element(vi4.begin(), vi4.begin() + 5, vi4.end());
	// , vi4.begin() + 5 기준으로 작은 요소는 왼쪽에, 큰 요소는 오른쪽에 정렬한다.
	dump("nth_element", vi4);
	/*
		원본        ==> 49 26 19 77 34 52 84 34 92 69
		sort        ==> 19 26 34 34 49 52 69 77 84 92
		stable_sort ==> 19 26 34 34 49 52 69 77 84 92
		partial_sort==> 19 26 34 34 49 77 84 52 92 69
		nth_element ==> 19 26 34 34 49 52 69 77 84 92

		 stable_sort도 sort와 같은 결과를 보이는데 안정성이 있다는 점이 다르다. 
		 예제의 벡터에는 34가 두 개 있는데 이 두 34가 원래의 위치를 유지하는가 아닌가가 다르다. 
		 정수같은 단순 타입은 어차피 값으로만 구분되므로 원래의 순서가 별 의미가 없지만 객체끼리 비교할 때는 이런 안정성이 중요할 수도 있다.

		 partial_sort는 지정한 요소까지만 정렬하고 나머지 뒤쪽은 정렬하지 않는다. 
		 예제에서는 5번째 요소까지만 정렬했는데 결국 상위 0 ~ 4까지 다섯 개의 요소만 정렬된다. 
		 상위 다섯 개인 49까지 정확하게 정렬되었고 뒷부분은 이보다 큰 값들만 남는데 남은 값들의 순서는 전혀 보장되지 않는다.

		 nth_element는 지정한 요소 위치에만 정확한 값을 배치하고 나머지는 이 요소를 기준으로 좌우로 구간을 분할한다.
			특정 위치를 기준으로 그룹을 분류하고 싶을 때 이 함수를 사용하는데 
			예를 들어 30만명의 학생 중 상위 30%는 차후 더 난이도가 높은 시험을 보도록 하고 하위 70%는 원래 난이도와 같은 시험을 보도록 할 때 이 함수가 유용하다. 
			특정 학생이 몇 등인가는 중요하지 않고 30%에 들었는지 그렇지 못한지만 관심사이므로 30% 위치를 기준으로 좌우로 구간만 나누면 된다.
	*/
	return 0;
}
