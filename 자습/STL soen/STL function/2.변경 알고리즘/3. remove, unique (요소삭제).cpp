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
요소를 제거하는 함수는 조건에 맞는 요소를 찾아 제거하는 시늉을 한다. 
실제로 요소를 제거하지는 못하는데 일반성을 가진 알고리즘이 컨테이너를 조작할 권한이 없기 때문이다. 

자세한 이유는 예제를 보면서 연구해 보자. 
조건에 맞는 요소를 제거하는 remove 함수는 다음 4가지가 준비되어 있다.
		//FwdIt remove(FwdIt first, FwdIt last, const Type& val);
		//FwdIt remove_if(FwdIt first, FwdIt last, UniPred F);
		//OutIt remove_copy(FwdIt first, FwdIt last, OutIt result, const Type& val);
		//OutIt remove_copy_if(FwdIt first, FwdIt last, OutIt result, UniPred F);
remove 함수는 작업 대상이 되는 반복자 구간과 제거할 값을 인수로 전달받아 first ~ last 사이의 값을 제거한다.
 이 함수는 제거 대상을 선택할 때 == 연산자로 val과 일치하는 요소를 선택하는데 비해 
 remove_if는 단항 조건자 F가 true를 리턴하는 요소를 선택한다는 점이 다르다. 나머지 동작은 동일하다.

 remove는 실제로 요소를 제거하지는 않으며 제거 대상이 아닌 요소들을 골라 구간의 앞쪽으로 이동시키고 남은 요소의 시작을 가리키는 반복자를 리턴한다.
  제거 대상이 아닌 요소의 원래 순서는 유지되므로 안정성이 있다.
  요소가 실제로 제거되지 않고 위치만 바뀌므로 remove 호출 후에도 컨테이너의 크기는 변하지 않는다.
  요소를 실제로 제거하려면 컨테이너의 erase 멤버 함수를 호출해야 한다. 
  
  동작 방식이 상당히 복잡한데 예제를 통해 연구해 보자.

*/

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{

	int ari[] = { 3,1,4,1,5,9,2,6,5 };
	vector<int> vi(&ari[0], &ari[sizeof(ari) / sizeof(ari[0])]);
	//vector<int>::iterator it;
	
	dump("원본", vi);								//원본 == > 3 1 4 1 5 9 2 6 5
	auto it = remove(vi.begin(), vi.end(), 1);
	dump("remove", vi);								//remove == > 3 4 5 9 2 6 5 6 5
	vi.erase(it, vi.end());
	dump("erase", vi);								//erase == > 3 4 5 9 2 6 5

	//remove는 구간의 처음부터 순회하면서 제거 대상이 아닌 요소를 앞쪽으로 차례대로 복사한다. 
	//선두값인 3은 제거 대상인 1이 아니므로 그대로 남는다. 다음값 1은 제거 대상이므로 복사되지 않는다. 
	//그 다음값 4는 3다음으로 복사되며 그 다음 1은 복사되지 않는다. 이후 5, 9, 2, 6, 5는 모두 1이 아니므로 차례대로 앞쪽으로 이동된다.

	//여기까지 작업하면 뒤에 두 칸이 남는데 이 위치를 가리키는 반복자가 remove의 결과로 리턴된다. 
	//뒤에 남은 6과 5는 이미 앞쪽으로 이동되었으므로 지금 현재로서는 쓰레기값인 셈이며 삭제된 1이 여기에 와 있다고 보면 된다.

	//그러나 remove는 굳이 1을 뒤쪽으로 복사하지는 않는데 왜냐하면 이 값은 잠시 후면 진짜 삭제되기 때문이다. 
	//remove가 이렇게 삭제할 값과 남을 값을 좌우로 분할해 놓으면 나머지 작업은 erase 멤버 함수가 처리하는데 
	//remove가 리턴한 반복자부터 끝까지를 삭제하면 된다.

	/*
	그렇다면 remove는 왜 이렇게 복잡한 과정을 거쳐서 요소를 삭제하도록 되어 있을까 ? 
	그냥 1을 삭제해 버리고 1이 아닌 것들만 남겨둔다면 굳이 erase를 호출할 필요가 없지 않은가 ? 
	이렇게 되어 있는 이유는 어떤 장점이 있어서 그런 것이 아니라 일반성을 가진 알고리즘이 할 수 있는 동작이 제한되어 있기 때문이다.
	remove는 지금 자신이 검색하고 있는 컨테이너가 벡터라는 것을 모르며 따라서 실제로 요소를 삭제하기 위해 어떻게 컨테이너를 조작해야 하는지도 알지 못한다.

	만약 remove가 조작 대상이 벡터라는 것을 알 수 있다면 1이 발견될 때마다 이 요소를 삭제하고 뒤쪽 요소를 앞으로 이동시키면 될 것이다. 
	반면 조작 대상이 리스트라는 것을 알 수 있다면 1을 제거하고 양쪽의 링크를 연결하면 된다. 
	하지만 remove는 조작 대상 컨테이너가 어떤 구조를 가지는지도 모르고 어떻게 조작하는지도 알 수 없으며 
	오로지 반복자로 값을 읽고 쓰고 교환하는 것만 가능하다. 
	그러니 remove가 해 줄 수 있는 일은 고작 삭제 대상 요소와 그렇지 않은 요소를 구분해 놓고 그 경계의 반복자를 리턴하는 것 뿐이다.

	실제 삭제는 해당 컨테이너의 erase 멤버 함수가 처리해야 한다.
	 반면 멤버 함수는 컨테이너별로 고유하며 컨테이너의 구조를 알고 있으므로 지정한 요소를 삭제할 수 있다. 
	 리스트의 remove 멤버 함수는 멤버이므로 검색과 동시에 삭제가 가능하다.
	*/

	cout << "====================remove_copy=======================" << endl;
	// 불편하기는 하지만 이런 불편함의 대가로 일반성이 얻어진다. 
	//만약 삭제 대상을 선정하고 실제로 삭제하는 것이 번거롭다면 새로운 컨테이너를 생성하는 remove_copy 함수를 사용한다.

	int ari2[] = { 3,1,4,1,5,9,2,6,5 };
	vector<int> vi2(&ari2[0], &ari2[sizeof(ari2) / sizeof(ari2[0])]);
	vector<int> vi3;

	remove_copy(vi2.begin(), vi2.end(), back_inserter(vi3), 1);

	dump("vi2", vi2);				//vi2          ==> 3 1 4 1 5 9 2 6 5
	dump("vi3", vi3);				//vi3         ==> 3 4 5 9 2 6 5


	//remove_copy는 제거 대상을 제외한 요소들을 새로운 반복자 구간에 대입한다. 
	//_copy가 뒤에 붙은 함수는 항상 작업 결과를 다른 구간으로 복사하는 함수이다.
	// 이 함수와 삽입 반복자를 사용하면 빈 벡터에 원하는 요소만 모을 수 있다.
	// remove는 컨테이너를 조작하지는 못하지만 읽을 수는 있으므로 조건에 맞는 새로운 컨테이너를 만들 수는 있다

	//대입이나 copy 함수로 일단 똑같은 컨테이너를 만든 후 remove로 특정 요소를 제거한 후 erase로 짤라내면 결국 vi2에는 1이 아닌 요소만 남는다. 
	//그러나 보다시피 이 방법은 대입이라는 비싼 연산을 거쳐야 하므로 느리다.
	//복사 함수는 새로운 컨테이너를 만들면서 제거를 겸할 수 있어 복사 후 제거보다 훨씬 더 빠르다. 
	//이런 이유로 STL은 알고리즘을 적용하면서 그 결과를 다른 컨테이너에 작성하는 _copy 류의 함수를 제공하는 것이다. 

	//다음 함수도 일종의 제거 함수인데 동작하는 방식은 remove와 유사하다.

		/*	FwdIt unique(FwdIt first, FwdIt last[, BinPred F]);
			OutIt unique(FwdIt first, FwdIt last, OutIt result[, BinPred F]);	*/
	//unique 함수는 반복자 구간에서 연속된 중복 요소를 제거한다. 
	//이때 중복되었다는 조건의 디폴트는 == 이지만 이항 조건자 F로 사용자가 중복 조건을 지정할 수도 있다. 
	// remove와 마찬가지로 실제로 요소를 삭제하지는 않으며 중복되지 않은 요소들만 앞쪽으로 이동시킨다.

	char str[] = "abcccddefggghi";
	char* p;
	puts(str);
	p = unique(&str[0], &str[strlen(str)]);
	*p = 0;
	puts(str);

	//문자 배열에 중복된 알파벳을 여러 개 써 놓고 unique로 중복을 제거해 보았다. 그리고 리턴된 반복자 위치에 0을 대입하여 남은 요소를 잘라낸다.
			//abcccddefggghi
			//abcdefghi
	// 알파벳 문자들은 하나씩만 남고 나머지는 모두 제거된다. 
	//주의할 것은 unique는 구간내의 중복된 것을 모두 제거하는 것이 아니라 인접된 중복 요소만 제거한다는 것이다.
	//멀리 떨어져있는 중복값은 제거되지 않는다. 

	//만약 중복된 모든 요소를 완전히 제거하고 싶다면 정렬을 먼저 한 후 unique를 적용해야 한다. 
	//unique_copy는 중복되지 않은 요소를 다른 컨테이너로 복사한다.

	return 0;
}
