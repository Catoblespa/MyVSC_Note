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

/*


힙(heap)이라는 말은 흔히 기억 장소의 자유 영역을 의미하는데 
자료 구조에서 말하는 힙은 이런 메모리 영역을 뜻하는 것이 아니라 다음과 같은 조건을 만족하는 자료 구조를 의미한다.

① 첫 번째 요소가 구간에서 가장 크다.
② 푸시, 팝 연산이 로그 시간내로 수행될 수 있다.

단지, 첫 번째 요소가 제일 크기만을 요구하므로 나머지 뒷부분은 크기순으로 정렬되지 않아도 상관없다.
 요구 사항이 많지 않기 때문에 삽입, 삭제 연산도 훨씬 더 빠르다.
   함수들은 우선 순위 큐 구현에 흔히 사용되는데 
  사실 STL의 prority_queue 어댑터가 이런 자료 구조를 잘 제공하므로  함수들을 직접 사용할 일은 거의 없다. 


다음 4개의 함수가 을 제공한다.

		//void make_heap(RanIt first, RanIt last [,BinPred F]);
		//void sort_heap(RanIt first, RanIt last [,BinPred F]);
		//void push_heap(RanIt first, RanIt last [,BinPred F]);
		//void pop_heap(RanIt first, RanIt last [,BinPred F]);

모두 원형이 동일한데 적용할 구간을 인수로 전달받고 원할 경우 조건자를 지정할 수 있다. 디폴트 조건자는 less이다.
 make_heap 함수는 first ~ last 구간을 힙으로 만드는데 구간내에서 제일 큰 값을 선두로 이동시키기만 하면 된다.
		내림차순으로 정렬하는 것이 아니라 첫 요소만 앞쪽으로 이동시키므로 정렬보다는 훨씬 더 속도가 빠르다.


sort_heap은 힙 구간을 오름차순으로 정렬하는데 일반적인 정렬 함수보다는 훨씬 더 빠르다.

push_heap 함수는 first ~ last 구간을 힙으로 만드는데 이때 first ~ last-1까지는 이미 힙이어야 한다.
		즉, first ~ last-1 범위의 요소 중에는 first가 제일 커야 한다. 
		 push_heap 함수는 원래의 힙보다 하나 더 확장된 범위인 first ~ last를 힙으로 만드는데 
		 이는 곧 last를 포함하여 제일 큰 값을 앞으로 보내는 것이다. 
		 그래서 통상 push_heap 이전에 push_back이 먼저 호출된다.

pop_heap은 first에 있는 제일 큰 요소를 제일 뒤로 보내고 나머지 first ~ last-1 구간을 다시 힙으로 만든다.
		즉, 제일 큰 값은 끝으로 추방시키고 남은 요소들 중 제일 큰 값을 다시 선두로 보내는 것이다.


*/

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{
	int ar[] = { 5,3,2,9,6 };

	vector<int> vi(&ar[0], &ar[5]);
	dump("원본", vi);

	make_heap(vi.begin(), vi.end());
	dump("make_heap", vi);

	vi.push_back(10);

	push_heap(vi.begin(), vi.end());
	dump("push_heap", vi);

	pop_heap(vi.begin(), vi.end());
	dump("pop_heap", vi);

	vi.pop_back();

	sort_heap(vi.begin(), vi.end());
	dump("sort_heap", vi);

	return 0;
}

/*
정수 다섯 개가 저장된 벡터를 힙으로 만들고 새 요소를 하나 넣고 또 빼 보기도 했다. 그리고 마지막으로 힙을 정렬하면서 각 단계의 벡터를 출력해 보았다.
		//원본        ==> 5 3 2 9 6
		//make_heap   ==> 9 6 2 3 5
		//push_heap   ==> 10 6 9 3 5 2
		//pop_heap    ==> 9 6 2 3 5 10
		//sort_heap   ==> 2 3 5 6 9

make_heap에 의해 vi 벡터는 힙이 되는데 다섯 개의 정수 중 가장 큰 값이 제일 선두로 이동했다. 나머지 요소는 굳이 정렬될 필요없다.	

 새 요소를 힙에 추가하기 위해 push_back으로 10을 벡터에 추가하고 push_heap으로 이 요소를 힙에 추가했다.
	10을 추가하기 전에 0~5구간이 힙이었는데 push_heap은 새로 추가된 10까지 고려하여 이 벡터를 다시 힙으로 만든다.
	 경우 10이 가장 크므로 선두로 이동해야 힙이 된다. 만약 8을 추가했다면 8이 굳이 선두로 이동하지 않아도 될 것이다.

pop_heap은 힙에서 제일 큰 값, 즉 첫 번째 요소를 제일 마지막 요소와 교환하고 제일 끝을 제외한 나머지 구간을 힙으로 만든다.
	10이 밀려나고 남은 요소들 중 제일 큰 값이 처음으로 오게 될 것이다.
	pop_back은 first ~ last-1만 구간으로 만들 뿐이므로 이 백터의 전 구간이 힙이 되려면 밀려난 10을 pop_back 등의 함수로 삭제해야 한다.

sort_heap은 힙을 오름차순으로 정렬한다.



은 우선 순위 큐같은 자료 구조를 구현하기 위한 연산이다
이런 자료 구조를 구현하기 위해서는 제일 큰 값 하나만 빼 내기 쉬운 위치에 있고 새로운 값이 추가 되거나 제일 큰 값이 빠져 나갈 때 제일 큰 값을 미리 찾아 놓기만 하면 된다.
이 정도 요구 사항을 충족하기 위해서는 굳이 그 비싼 정렬을 매번 할 필요가 없으며 몇 번의 교환만 수행하면 된다.
사실 은 최종 사용자들이 쓸만한 연산은 아니며 실용성도 낮다.



//게임 만들때 장비를 최강장비로 자동 셋팅할때 좋을듯 ?? 쯔꾸르에 있는 기능!! 언젠가 한번은 쓸거 같다.
//는 걍 우선순위 큐 쓰면 될거 같긴한데, 원래 자료형이 우선순위 큐가 아니였을때, 그때만 사용하면 될거같다.
*/
