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
STL의 주요 알고리즘들은 전역 함수로 제공되며 임의의 컨테이너에 대해 똑같은 방법으로 적용할 수 있다.
그래서 STL을 일반적이라고 한다.

이때 각 알고리즘과 컨테이너를 결합하기 위한 접착제로 반복자가 사용되며 상이한 컨테이너 구조에도 알고리즘이 잘 실행될 수 있도록 완충 역할을 하기도 한다.
컨테이너가 제공하는 반복자와 알고리즘이 요구하는 반복자가 다를 경우 효율상의 문제로 가끔 결합하지 못하는 조합도 있다.

대부분의 알고리즘 함수들은 algorithm 헤더 파일에 원형이 선언되어 있으므로 이 헤더를 반드시 인클루드해야 한다.

알고리즘은 기능에 따라 읽기, 변경, 정렬, 수치 4가지로 크게 분류되는데 이름으로부터 대충의 기능을 유추할 수 있다.
기능별 분류외에 컨테이너를 직접 변경하는 것과 복사본을 생성하는 것으로 분류하기도 하고
 함수 객체를 취하는 버전과 그렇지 않은 버전으로 분류하기도 한다.



*/
int main()
{

	string names[] = { "김정수","구홍녀","문병대","김영주","임재임","박미영","박윤자","김정수" };
	vector<string> as(&names[0], &names[8]);

	vector<string>::iterator it;


	/*InIt find(InIt first, InIt last, const T& val);*/
	cout << "========가장 앞에 있는 요소 find===========" << endl;
	it = find(as.begin(), as.end(), "안순자");

	if (it == as.end())
		cout << "없다" << endl;
	else
		cout << "있다" << endl;
	// find는 구간을 순차 검색하며 요소를 비교할 때는 요소 타입의 == 연산자로 비교한다. 
	//따라서 검색을 위한 특별한 조건은 필요없지만 컨테이너에 요소가 많으면 검색 속도는 느려진다.
	//find는 최초로 조건을 만족하는 요소 하나만 검색하는데 만약 구간내에 일치하는 모든 요소를 검색하고 싶다면 다음과 같이 루프를 돌리면 된다.
	cout << "========find로 모두 찾기===========" << endl;
	for (it = as.begin();; it++) {
		it = find(it, as.end(), "김정수");
		if (it == as.end()) break;
		cout << *it << "이(가) 있다." << endl;
	}
	cout << "========rfor로 찾기 ===========" << endl;
	for (auto& i : as)
	{
		if (i == "김정수")
			cout << i << "이(가) 있다." << endl;
	}


	/*InIt find_if(InIt first, InIt last, UniPred F);*/
	//이 외에 마지막 인수로 조건자를 취하는 find_if 함수도 있는데 
	//이 함수를 사용하면 완전히 일치하는 요소뿐만 아니라 원하는 조건을 만족하는 요소를 검색할 수 있다.
	//find는 요소를 비교할 때 == 연산자를 사용하지만 find_if는 사용자가 지정한 단항 함수 객체 F로 비교한다. 
	//구간내의 매 요소에 대해 F 함수를 호출하여 true가 리턴되는 요소를 검색하는데 
	//F가 어떤 식으로 비교를 수행하는가에 따라 다양한 방식으로 요소값을 점검할 수 있다.
	for (it = as.begin();; it++) {
		it = find_if(it, as.end(), [](string who) ->bool {		//람다식으로 함수객체를 대체하여 생성.
			return who.find("영") != string::npos;				//string who를 인자로 받고 who.find 로 who안의 "영"이 포함되는지 찾는다.
			});													//who.find는 find에 실패할 경우 who::npos를 반환한다.
		if (it == as.end()) break;
		cout << *it << "이(가) 있다." << endl;
	}



	//다음 함수는 반복자 구간에서 인접한 두 요소가 같은 값을 가지는 위치를 검색한다.
	/*FwdIt adjacent_find(FwdIt first, FwdIt last[, BinPred F]);
			template<class ForwardIterator>
			ForwardIterator adjacent_find(
				ForwardIterator _First,
				ForwardIterator _Last
			);

			template<class ForwardIterator, class BinaryPredicate>
			ForwardIterator adjacent_find(
				ForwardIterator _First,
				ForwardIterator _Last,
				BinaryPredicate _Comp
			);*/
			//조건자를 취하는 버전과 그렇지 않은 버전이 중복 정의되어 있어 조건자는 생략 가능한데 이런 인수에 대해서는 [ ] 괄호로 생략 가능함을 표기하기로 한다. 
			//함수 객체는 포인터의 NULL처럼 지정되지 않았다는 특이값이 존재하지 않으므로 디폴트 인수 기능을 사용할 수 없어 두 원형으로 따로 정의할 수밖에 없다. 
			//이후의 원활한 학습을 위해 표기법에 대해 부연 설명을 했다.

			//조건자가 없는 함수는 인접한 두 요소를 == 연산자로 비교하므로 두 요소가 같은 위치를 찾는다. 
			//adjacent_find는 구간을 순회하면서 앞뒤의 요소값이 같은 위치를 찾아 앞쪽 반복자의 위치를 리턴한다.
			//접한 두 요소가 같은 것이 없으면 last가 리턴된다.


	cout << "========adjacent_find ===========" << endl;
	int ari[] = { 1,9,3,6,7,5,5,8,1,4 };
	vector<int> vi(&ari[0], &ari[9]);

	vector<int>::iterator it2;

	it2 = adjacent_find(vi.begin(), vi.end());				//조건자가 없을 경우 인접한 두 요소의 비교는 '=='를 사용한다.
	if (it2 != vi.end()) {
		cout << "두 요소가 인접한 값은 " << *it2 << "입니다." << endl;
	}

	// adjacent_find의 조건자 함수객체의 타입은 BinPred 이므로. bool형 이항 함수객체이여야 한다.
	it2 = adjacent_find(vi.begin(), vi.end(), [](int a, int b) -> bool {return a % b == 0; });		//조건자 계산을 넣을 수 있다. 
	if (it2 != vi.end()) {					//앞요소a가 뒷요소 b로 나누어 떨어지는지 계산하여 그럴경우 1을 반환하여 find를 멈춘다.
		cout << "최초로 발견된 약수 관계는" << *it2 << "," << *(it2 + 1) << "입니다." << endl;
	}



	cout << "========adjacent_find 2===========" << endl;
	//문장을 쳐 넣다 보면 실수로 공백을 두 번 입력하는 경우도 있는데 인접한 두 문자가 공백이면 그 위치를 출력하도록 했다. 
	//find에 비해 인접한 두 요소의 값을 한꺼번에 검사해 볼 수 있다는 점이 다르다.
	const char* str = "기다림은  만남을 목적으로 하지 않아도  좋다.";
	const char* p, * pend = &str[strlen(str)];
	for (p = str;; p++) {

		p = adjacent_find(p, pend, [](char a, char b)->bool {
			return (a == ' ' && b == ' ');
			});
		if (p == pend) break;
		cout << p - str << "위치에 이중 공백이 있습니다." << endl;

	}

	//다음 함수는 첫 번째 반복자 구간에서 두 번째 반복자 구간 중 하나가 최초로 발견되는 지점을 찾는다.
	//각 구간은 물론 순방향 반복자를 지원하는 임의의 컨테이너를 지시할 수 있으므로 벡터에서 리스트의 한 요소를 검색하거나 반대로도 검색할 수 있다.
	/*FwdIt1 find_first_of(FwdIt1 first1, FwdIt1 last1, FwdIt2 first2, FwdIt2 last2[, BinPred F]);*/

	//이 함수는 첫 구간의 모든 요소와 두 번째 구간의 모든 요소에 대해 이중 루프를 돌며 두 값이 조건을 만족하는지 검사한다.
	//디폴트 조건은 == 이지만 마지막 인수로 이항 조건자를 지정하면 원하는 조건을 지정할 수 있다.

	int ar1[] = { 3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3 };		// 배열도 염연히 컨테이너. 포인터를 선언하여 이터레이터처럼 사용 가능!

	int ar2[] = { 2,4,6,8,0 };

	int* p2 = find_first_of(&ar1[0], &ar1[25], &ar2[0], &ar2[4]);
	if (p2 != &ar1[25]) {
		printf("최초의 짝수는 %d번째의 %d입니다.\n", p2 - ar1, *p2);
	}
	//두 개의 정수 배열을 선언하고 ar1에서 ar2에 있는 값 중 하나가 발견되는 최초의 지점을 찾는다.
	// 예제에서 ar2에 모든 짝수를 나열해 두었으므로 ar1의 최초로 짝수인 수가 검색될 것이다.
	//여러 개의 조건 중 하나라도 만족하는 요소를 검색하고 싶을 때 이 함수를 사용한다.

	return 0;
}
