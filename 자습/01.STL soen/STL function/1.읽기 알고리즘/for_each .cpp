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

for_each 함수는 지정 구간을 반복하면서 지정한 작업을 수행한다.
	//UniOp for_each(InIt first, InIt last, UniOp op);		//UniOp 타입이므로 반환값은 void 인자는 1개를 받는 함수객체를 사용한다.
	first~last 사이의 구간을 순회하면서 op 함수 객체를 호출한다. 리턴값은 함수 객체인데 보통 무시한다
	for_each는 루프를 돌리는 역할밖에 하지 않으므로 구체적인 동작을 하는 함수 객체가 반드시 필요하다.

	op는 순회중의 반복자가 가리키는 요소값 하나를 전달받는 단항 함수 객체이며 
	전달받은 값에 대해 무슨 짓이든지 할 수 있으므로 사실 가장 일반화된 알고리즘이라고 할 수 있다.

	순회하면서 특정 작업을 하고 싶다면 직접 루프를 돌리지 말고 이 함수를 사용하면 된다.

	 for_each는 루프를 알고리즘 안으로 숨기는 역할을 하는데 제어 변수를 선언하고 초기식, 조건식을 지정하는 번거로운 작업을 대신한다고 생각하면 된다.
	 순회중에 요소값을 출력할 수도 있고 검색할 수도 있고 조건을 만족하는 요소의 개수를 조사할 수도 있다.
			find, find_if, count 등등 순회하면서 어떤 일을 하는 대부분의 알고리즘을 이 함수로 구현할 수 있는 셈이다.

	for_each는 분류상 읽기 알고리즘에 속하는데 다른 읽기 알고리즘과는 달리 요소를 변경할 수도 있다.
	순회중에 요소값을 바꾼다거나 요소가 가리키는 대상체를 삭제할 수도 있다.
	 그래서 포인터의 컨테이너에서 요소의 메모리를 정리할 때 흔히 사용된다. 
	 그러나 요소의 내용물만 건드릴 수 있을 뿐 컨테이너 자체를 변경하지는 못하므로 여전히 읽기 알고리즘이다.
*/
int main()
{
	vector<string> vs;
	vs.push_back("로보트 태권 브이");
	vs.push_back("들장미 소녀 캔디");
	vs.push_back("바보 온달과 평강 공주");
	vs.push_back("독수리 오형제");



	for_each(vs.begin(), vs.end(), [](string a) {
		cout << a << endl;
		});

	//문자열들이 저장되어 있는 벡터를 처음부터 끝까지 순회하면서 화면으로 출력해 보았다.
	//for_each의 세 번째 인수인 람다식으로 반복자 구간의 각 요소가 순서대로 전달되며 func는 이 값을 받아 화면으로 출력했다.

	//사실 요소값을 출력하기 위해 꼭 for_each를 사용해야하만 하는 것은 아니다.
	//출력 스트림 반복자와 copy 알고리즘을 사용하면 단 한 줄로 벡터의 모든 요소를 화면으로 출력할 수 있다.
	//for_each는 최고의 일반성을 제공하기는 하지만 for_each로 할 수 있는 작업의 대부분은 이미 더 편리한 알고리즘으로 제공되므로 
	//가급적이면 용도에 맞는 알고리즘을 골라 사용하는 것이 좋다.

	//for_each가 특수화된 다른 알고리즘과 다른 점이라면 일단 순회를 시작하면 멈출 방법이 없다는 것이다.
	// 전체 구간을 한바퀴를 다 돌아야 끝이 나며 모든 요소를 무조건 한 번씩 방문해야 한다. 

	//그래서 for_each로 검색을 구현하는 것은 적당하지 않은데 검색이란 원하는 걸 찾았으면 즉시 중단해야 하기 때문이다. 
	//물론 전부 다 색출하기 작업을 한다면 for_each가 더 어울릴 수도 있다.
	return 0;
}
