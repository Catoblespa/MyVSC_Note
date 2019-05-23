#include <iostream>
#include <time.h>
#include <vector>
#include <list>
#include <map>
#include <algorithm> //알고리즘 함수들은 대부분 algorithm 헤더 파일에 정의되어 있으므로 알고리즘 함수 중 하나라도 사용하려면 이 헤더 파일을 포함해야 한다. 
					// 이 헤더 파일에는 STL의 모든 알고리즘이 정의되어있다.
using namespace std;

/*
STL의 알고리즘 함수들은 대부분 특정 컨테이너의 멤버 함수가 아닌 일반 전역 함수로 작성되어 있다
 왜냐하면 반복자에 의해 컨테이너를 다루는 방법이 일반화되어 모든 컨테이너에 대해 적용할 수 있으므로 멤버 함수가 될 필요도 없고 멤버 함수가 되어서도 안된다.
 STL은 일반화된 알고리즘을 제공하므로 캡슐화를 적극적으로 사용하지 않는다.	
 컨테이너 클래스들은 표현하고자 하는 자료 구조를 위한 데이터 멤버와 연산자만을 정의하며 알고리즘 구현은 반복자와 전역 함수에게 맡긴다.

	template<typename InIt, class T>
	InIt find(InIt first, InIt last, const T& val);

	임의의 모든 타입에 대해 동작할 수 있어야 하므로 STL 알고리즘 함수들은 예외없이 템플릿으로 구현되어 있다.
	find는 first ~ last 사이의 반복자 구간에서 T형의 값 val이 있는지 검사한다. 
	발견되면 해당 위치의 반복자가 리턴되며 발견되지 않을 경우 컨테이너 전체를 순회만 하고 종료되므로 구간의 끝인 last가 리턴된다.
	C 함수들은 검색에 실패할 경우 NULL을 리턴하지만 STL은 검색 실패조차도 반복자로 리턴한다.

	반복자만으로 요소를 읽을 수 있고 이 요소를 val과 비교할 수 있으며 비교 범위도 명확하게 전달되었으므로 find가 컨테이너에 대한 정보를 전달받을 필요는 없다.
	컨테이너가 어떤 식의 구조를 가지는지 모르므로 find는 가장 간단하고 어떤 형태의 자료에나 사용할 수 있는 순차 검색 방법을 사용한다. 예제를 작성해 보자.
*/


int main()
{
	int ari[] = { 1,2,3,4,5 };

	cout << "---------------------------------------" << endl;
	vector<int> vi(&ari[0], &ari[5]);
	list<int> li(&ari[0], &ari[5]);


	puts(find(vi.begin(), vi.end(), 4) == vi.end() ? "없다." : "있다.");
	puts(find(li.begin(), li.end(), 8) == li.end() ? "없다." : "있다.");
	puts(find(&ari[0], &ari[5], 3) == &ari[5] ? "없다." : "있다.");
	/*
	find의 정의
	InIt find(InIt first, InIt last, const T& val)
	{
	 for (;first != last; ++first) {
		  if (*first == val) break;
	 }
	 return first;
	}
	//first를 계속 증가시키면서 last에 이를 때까지 순회하며 순회 중에 *연산자로 first의 값을 읽어 val과 같은지를 점검한다.
	//검색되었다면 이 상태에서 루프를 빠져 나와 first를 리턴하며 검색에 실패했다면 first가 last까지 이동한 채로 리턴될 것이다. 
	끝에 도달하거나 검색하는 값을 찾을 때까지 무조건 전진 이동하다가 루프가 끝났을 때의 반복자를 리턴한다
	*/


	//검색 다음으로 많이 사용되는 알고리즘은 자료를 일정한 기준에 따라 재배치하는 정렬이다.

	//		void sort(RanIt first, RanIt last);

	//이 함수는 인수로 주어진 first ~ last 사이의 모든 요소를 정렬한다. 
	//정렬을 하기 위해서는 객체들을 비교해야 하는데 sort 함수는 정렬 중에 < 연산자로 요소의 순위를 판단한다. 
	//따라서 정렬 대상 요소들은 < 연산자를 반드시 정의해야 한다.
	//정수, 실수 등의 기본 타입은 < 연산자로 비교할 수 있으므로 항상 정렬 가능하며 사용자가 정의한 클래스라도 < 연산자가 오버로딩되어 있으면 이 함수로 정렬 가능하다.

	cout << "---------------------------------------" << endl;
	vector<int> vi2(&ari[0], &ari[5]);

	sort(vi2.begin(), vi2.end());						//STL의 소트정렬은 퀵소트 알고리즘을 사용한다. 
	vector<int>::iterator it;
	for (it = vi2.begin(); it != vi2.end(); it++) {
		printf("%d\n", *it);
	}
	//벡터에 다섯 개의 정수를 넣어 두고 sort 함수로 정렬한 후 출력해 보았다. 오름차순으로 정렬되어 출력될 것이다.
	
	
	
	//	void reverse(BiIt first, BiIt last);
	//reverse 함수는 이름대로 지정한 구간의 요소들 순서를 반대로 뒤집는다. 
	//begin과 end를 구간으로 지정하면 컨테이너의 모든 요소들 순서가 반대로 바뀔 것이다. 
	//컨테이너의 일부 구간만 반대로 뒤집을 수도 있다. 다음 예제는 배열의 중간 부분 요소들을 반대의 순서로 뒤집는다.
	int ari2[] = { 1,2,3,4,5,6,7,8,9 };

	int i;

	for (i = 0; i < 9; i++) printf("%d ", ari2[i]); puts("");
	reverse(&ari2[2], &ari2[6]);		//2번째 요소 ~ 5번째 요소까지의 순서가 반대로 뒤집어진다. 즉 ari[2]는 ari[5]와 교환되고 ari[3]은 ari[4]와 교환된다.
	for (i = 0; i < 9; i++) printf("%d ", ari2[i]); puts("");
	/*
	1 2 3 4 5 6 7 8 9
	1 2 6 5 4 3 7 8 9
	*/



	//다음 함수는 컨테이너의 구간내 요소를 무작위로 마구 섞는다.
	//		void random_shuffle(RanIt first, RanIt last);
	//게임을 만들 때 이 함수가 자주 사용되는데 퍼즐이나 카드패를 사용자가 예측하지 못하도록 할 때 무작위 섞기 기능이 사용된다. 예제를 보자.


	vector<int> vi3(20);
	vector<int>::iterator it3;



	for (int i = 0; i < 20; i++) vi3[i] = i;

	srand(time(NULL));

	//random_shuffle(vi3.begin(), vi3.end());

	for (it3 = vi3.begin(); it3 != vi3.end(); it3++)
		cout << *it3 << ' ';

	cout << endl;

	return 0;
}

/*
함수					설명

count				조건에 맞는 요소의 개수를 센다.

for_each			각 요소에 대해 지정한 작업을 한다.

equal				구간이 일치하는지 비교한다.

search				일치하는 부분 구간을 검색한다.

copy				구간끼리 복사한다.

fill				일정한 값으로 지정 구간을 채운다.

reverse				구간의 요소들을 반대로 뒤집는다.

random_shuffle		요소들을 무작위로 섞는다.

swap				컨테이너를 교환한다.

binary_search		이분 검색한다.

merge				구간을 병합하여 새로운 구간으로 복사한다.

accumulate			구간의 값을 모두 합한다.



*/
