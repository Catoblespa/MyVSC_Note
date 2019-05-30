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
equal 함수는 두 개의 반복자 구간을 비교하여 두 구간이 완전히 일치하는지 아닌지를 검사한다.

	//  bool equal(InIt1 first1, InIt1 last1, InIt2 first2 [, BinPred F]);		//BinPred타입이므로 bool리턴, 2개의 인자를 갖는 함수객체 사용

first1 ~ last1 사이의 구간과 first2 이후의 구간에 있는 요소들을 일대일로 비교해 보고 
모든 요소가 일치하면 true를 리턴하고 하나라도 틀리면 false를 리턴한다.

두 번째 구간은 시작 위치를 지정하는 반복자만 전달되고 끝 반복자는 전달되지 않는데 두 번째 구간도 첫 번째 구간과 길이가 같다고 가정한다. 
구간끼리 비교할 때는 어차피 같은 크기의 구간을 비교하는 경우가 압도적으로 많으므로 이 가정에는 별 무리가 없다.

 개의 똑같은 구간을 전달받는 함수들은 보통 두 번째 구간의 길이를 전달받는 인수가 따로 없고 첫 번째 구간의 길이를 사용한다. 
 두 반복자 구간은 반드시 같은 컨테이너에 소속될 필요는 없으며 컨테이너의 타입이 달라도 상관없다. 
 즉, 벡터와 리스트끼리도 비교 가능하다는 얘기인데 함수 원형에 보다시피 InIt1, Init2 등으로 반복자 타입이 다를 수 있다는 것이 표기되어 있다

 반복자 구간의 대응되는 요소끼리 비교할 때 디폴트로 == 연산자를 사용하도록 되어 있어 동일성 비교를 수행하는데 특별한 비교 방식을 사용하고 싶다면 이항 조건자 F를 제공한다.
  객체의 일부 멤버만 비교할 수도 있고 어느 정도의 오차를 무시할 수도 있다.



*/



int main()
{

	cout << "============================equal 함수================================" << endl;
	int ari[] = { 8,9,0,6,2,9,9 };
	vector<int> vi(&ari[0], &ari[7]);

	if (equal(&ari[0], &ari[7], vi.begin()))		//완전히 똑같은걸 비교하니 당연이 동일하다 나온다.
		puts("두 구간은 동일하다");					//백터를 초기화 한후 ari를 변경하면 틀리다고 나온다.
	else 
		puts("두 구간은 틀리다.");



	double af1[] = { 45.34, 77.84, 96.22, 91.04, 85.24 };
	double af2[] = { 45.99, 77.25, 96.86, 91.23, 86.13 };


	if (equal(&af1[0], &af1[4], &af2[0], [](int a, int b) -> bool{	//double타입을 비교할때 정수부만 비교하도록 비교 방법을 람다 함수로 지정했다
		return (int)a == (int)b;									//비교함수에 따라 어느정도 오차를 발생시킬 수도 있다.
		}))															//비교 구간을 0~4로 지정하므로 equal이 true를 반환한다.
	{																// 0~5으로 했다면 false를 반환 했을 것이다.
		puts("지정 구간의 정수부가 모두 같다.");
	}
	else 
		puts("지정 구간의 정수부 중 일부가 일치하지 않는다.");


	cout << "============================mismatch 함수================================" << endl;
	//mismatch 함수는 equal의 반대 함수인데 두 반복자 구간 중 최초로 틀린 부분이 어디인가를 찾는다. 
	//equal은 같다, 다르다만 조사하는데 비해 이 함수는 틀리다면 어디쯤이 틀린지도 조사한다.
		/*pair<InIt1, InIt2> mismatch(InIt1 first1, InIt1 last1, InIt2 first2 [,BinPred F]);*/
	//리턴값은 두 구간이 최초로 달라진 지점의 반복자 쌍을 pair 객체로 묶어서 리턴한다. 
	//이 구조체의 first, last를 점검해 보면 어디가 최초로 다른 지점인지를 알 수 있다. 
	//모든 구간이 일치한다면 last1과 first2+(last1-first1)의 쌍이 리턴되는데 f
	//irst2+(last1-first1)이라는 수식이 복잡해 보이지만 말로 간단히 설명하면 두 번째 구간의 끝다음이다. 
	//
	// 다음 두 문장이 똑같은 점검을 한다는 것은 쉽게 이해가 될 것이다.

			//equal(&ari[0], &ari[7], vi.begin()) == true				//모든게 일치하면 true 를 반환
			//mismatch(&ari[0], &ari[7], vi.begin()).first == ari[7]    //모든게 일치한다면 last값을 반환한다.
	//모든 요소가 일치한다는 얘기나 최초로 틀린 요소가 구간 바깥의 끝다음이라는 것은 같은 뜻이다.


	int ari2[] = { 8,9,0,6,2,9,9 };
	vector<int> vi2(&ari2[0], &ari2[7]);

	vi2[3] = 7;	// 원래 vi2 는 6값이였다.

	//pair<int*, vector<int>::iterator> p;   //mismatch함수는 최초로 틀려지는 지점의 반복자들이 pair로 묶여 리턴되며 
											 //이 반복자를 읽으면 어디가 어떻게 틀린지를 알 수 있다.
	auto p = mismatch(&ari2[0], &ari2[7], vi2.begin());

	if (p.first != &ari2[7]) {
		printf("%d번째 자리(%d,%d)부터 다르다.\n",
			p.first - ari2, *(p.first), *(p.second));
	}
	else {
		puts("두 컨테이너가 일치한다.");
	}
	


	cout << "============================mismatch 함수2================================" << endl;
	//다음 예제는 mismatch 함수를 사용하여 정답과 학생이 작성한 답안지의 각 요소를 비교하여 오답들을 검색한다.

	int answer[] = { 1,1,4,3,2,4,3,2,3,4,1,2,4,4,3,2,1,3,2,4 };
	int paper[] = { 1,1,4,3,3,4,3,1,3,4,1,2,4,4,3,4,1,3,2,2 };
	pair<int*, int*> p2;
	int i;
	for (i = 0;;) {
		p2 = mismatch(&answer[i], &answer[20], &paper[i]);

		if (p2.first == &answer[20]) break;		// p2.second == &paper[20]와 같은 결과.

		printf("%d번 틀림, 정답=%d, 니가 쓴 답=%d\n",
			p2.first - answer + 1, *(p2.first), *(p2.second));
		i = p2.first - answer + 1;								//i의 값을 mismatch함수가 리턴한 위치의 +1로 바꿔서 반복
	}
	
	
	return 0;
}
