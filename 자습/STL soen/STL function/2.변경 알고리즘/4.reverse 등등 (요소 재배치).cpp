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
요소 재배치


요소 재배치 함수들은 구간의 요소들을 특정한 다른 값으로 바꾸거나 요소끼리 교환함으로써 위치를 변경한다. 
다양한 원형이 있지만 일단 기본형의 원형을 보자.
		//void replace (FwdIt first, FwdIt last, const Type& Old, const Type& New);
		//void reverse(BiIt first, BiIt last);
		//void rotate(FwdIt first, FwdIt middle, FwdIt last);

replace 함수는 first ~ last 사이의 Old값을 모조리 뒤져 New로 대체한다. 나머지 값은 물론 그대로 남는다.  알고리즘 함수들 중에 가장 이해하기 쉬운 함수이다.
. 조건자 버전인 replace_if는 특정값이 아닌 특정 조건을 만족하는 값을 다른 값으로 변경할 수 있다. 
복사 버전인 replace_copy도 있고 조건자를 취하는 복사 함수인 replace_copy_if 함수도 제공된다.

reverse는 구간의 모든 요소의 순서를 반대로 뒤집는다.
즉 제일 앞에 있는 요소는 제일 뒤쪽으로 가고 제일 뒤쪽에 있는 요소가 제일 앞쪽으로 온다. 복사 버전인 reverse_copy 함수도 제공된다

rotate 함수는 first ~ last 구간을 middle을 기준으로 회전시킨다. 
구간을 일종의 원형으로 간주하고 한 바퀴 돌리는 것이다. 

	셋 다 개념이 간단하므로 예제를 실행해 보면 쉽게 이해할 수 있을 것이다.


*/

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{

	const char* str = "Notebook Computer";
	vector<char> vc(&str[0], &str[strlen(str)]);

	dump("원본", vc);							//원본 == > N o t e b o o k   C o m p u t e r

	replace(vc.begin(), vc.end(), 'o', 'a');
	dump("replace", vc);						//replace     ==> N a t e b a a k   C a m p u t e r
	//replace 함수로 모든 o를 찾아 a로 변경했다. 

	rotate(vc.begin(), vc.begin() + 2, vc.end());
	dump("rotate", vc);							//rotate      ==> t e b a a k   C a m p u t e r N a
	//rotate 함수는 middle 위치에 있던 요소가 first의 자리로 온다고 생각하면 된다.
	//전 구간을 begin+2를 기준으로 회전시켰으므로 모든 문자가 앞으로 두칸씩 이동하며 제일 앞쪽에 있던 두 문자 N과 a는 제일 뒤쪽으로 이동한다.

	reverse(vc.begin(), vc.end());
	dump("reverse", vc);						//reverse     ==> a N r e t u p m a C   k a a b e t
	//. reverse는 요소의 순서를 반대로 뒤집는다. 다음 함수는 일정한 조건을 기준으로 요소들을 좌우로 재배치한다.


	//다음 함수는 일정한 조건을 기준으로 요소들을 좌우로 재배치한다.
		/*	BiIt partition(BiIt first, BiIt last, UniPred F);
			BiIt stable_partition(BiIt first, BiIt last, UniPred F);	*/
	//단항 조건자 F는 구간내의 요소들을 인수로 전달받아 이 요소가 조건에 맞는지 아닌지를 판별한다
	//partition 함수는 F의 평가 결과에 따라 조건에 맞는 요소는 구간의 앞쪽으로 이동시키고 그렇지 않은 요소는 뒤쪽으로 이동시키며 
	//뒤쪽 그룹의 시작 위치를 리턴한다
	//이 함수를 호출하고 난 후에 왼쪽에는 조건에 맞는 요소, 오른쪽에는 그렇지 않은 요소들이 배치되어 있을 것이다.

	//stable_partition 함수는 재배치후에도 요소들의 원래 순서가 유지되는 안정된 버전이다 
	//같은 그룹에 속하는 값들끼리라도 원래 앞쪽에 있었다면 재배치 후에도 여전히 앞쪽에 배치된다는 뜻이다. 
	//안정성이 있는 대신 속도는 partition보다 느리며 더 많은 메모리를 소모한다. 정수들을 일정한 값 기준으로 재배치해 보자.


	int ari[] = { 3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8 };
	vector<int> vi(&ari[0], &ari[sizeof(ari) / sizeof(ari[0])]);

	dump("원본", vi);					
	partition(vi.begin(), vi.end(), bind2nd(greater<int>(), 5));
	dump("partition", vi);																

	vector<int> ar2(&ari[0], &ari[sizeof(ari) / sizeof(ari[0])]);
	stable_partition(ar2.begin(), ar2.end(), bind2nd(greater<int>(), 5));
	dump("stable", ar2);
	//정수들이 저장되어 있는 벡터를 5를 기준으로 하여 좌우로 재배치했다. 
	//5보다 더 크다는 정도의 조건은 함수 객체를 만들 필요없이 greater 표준 함수 객체와 bind2nd 바인더를 사용하면 쉽게 만들 수 있다.
		//원본			== > 3 1 4 1 5 9 2 6  5 3 5 8 9 7 9 3 2 3 8
		//partition		== > 8 9 7 9 8 9 6 2  5 3 5 5 1 4 1 3 2 3 3
		//stable		== > 9 6 8 9 7 9 8 3 1 4 1 5 2 5 3 5 3 2 3

	//5보다 큰 값들이 왼쪽으로 옮겨졌고 오른쪽에는 그렇지 않은 값들이 배치된다. 
	//5는 5보다 크지 않으므로 이동 대상이 아니다. 
	//안정성이 있는 재배치 함수는 요소의 원래 순서를 그대로 유지하는데 원본에 있는 5보다 큰 값 9, 6, 8, 9가 원본 순서 그대로 재배치되어 있다. 
	
	//반면 안정성이 없는 재배치 함수는 조건을 기준으로 좌우로 옮기기만 할 뿐 순서 유지는 하지 않는다.



	return 0;
}
