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
반복자 구간에서 지정한 값과 일치하는 요소의 개수를 센다. 값을 취하는 버전과 조건자를 취하는 버전이 각각 따로 정의되어 있다.

	//size_t count(InIt first, InIt last, const T& val);
	//size_t count_if(InIt first, InIt last, UniPred F);
리턴값은 조건을 만족하는 요소의 개수이며 일치하는 요소가 없으면 0이 리턴된다. 다음 예제는 노래 가사 문자열에서 a문자의 출현 회수를 센다.
*/

const int NUM = 2000;
const int RANGE = 10;


int main()
{
	cout << "==================count==================" << endl;
	const char* str = "Oh baby baby,How was I supposed to know "
		"That something wasn't right here";
	size_t num;
	num = count(&str[0], &str[strlen(str) + 1], 'a');

	printf("이 문장에는 a가 %d개 있습니다.\n", num);
	//count는 반복자 구간을 차례대로 순회하면서 매 요소가 val과 같은지 == 연산으로 비교하여 일치하는 요소가 발견될 때마다 
	//회수를 1 증가시키고 순회를 마칠 때 조사한 회수를 리턴한다. 

	cout << "==================count_if 1==================" << endl;
	//count_if는 단항 조건자 객체가 일치 조건을 판단하므로 좀 더 다양한 조건을 점검할 수 있다.
	num = count_if(&str[0], &str[strlen(str) + 1], bind2nd(greater<char>(), 't'));
										//greater : 첫번째 인자가 두번째 인자보다 크면 true 반환 (bool)
	printf("이 문장에는 t보다 더 큰 문자가 %d개 있습니다.\n", num);
	//이항 조건자인 greater의 두 번째 인수를 bind2nd 어댑터로 't'로 고정하여 't'보다 큰 문자의 개수를 세어 보았다. 결과는 7이다.




	cout << "==================count_if 2==================" << endl;
	//전역 선언
	//const int NUM = 2000;
	//const int RANGE = 10;
	vector<int> num2(NUM);
	vector<int>::iterator it;

	randomize();
											//vector가 갖는 int의 요소값을 변경하기 위해서는 i를 레퍼런스로 접근한다 . call by reference
	for_each(num2.begin(), num2.end(), [](int &i) {
		i = random(RANGE);
		});

	for (int i = 0; i < RANGE; i++) {
		printf("%02d의 출현 회수 : %d\n", i, count(num2.begin(), num2.end(), i));

	}
	//NUM 크기의 벡터를 선언하고 for_each문으로 벡터의 각 요소에 RANGE 미만의 난수를 생성하여 채워 넣었다. 
	//for_each가 레퍼런스를 전달받으면 요소값을 변경할 수도 있다. 벡터를 초기화한 후 난수들이 몇 개씩 생성되었는지 count 함수로 세어 보았다. 
	return 0;
}
