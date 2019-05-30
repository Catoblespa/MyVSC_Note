
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
요소 생성 함수는 새로운 요소를 만들어 지정한 위치에 대입하는 함수들이다.
요소를 만드는 것은 맞지만 컨테이너에 삽입하는 것이 아니라 기존 요소를 파괴하고 대입한다는 점을 주의하도록 하자.



*/

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{
	cout << "==========fill, fill_n===========" << endl;
	//다음 함수는 반복자 구간을 val 값으로 가득 채운다.
	/*		void fill(FwdIt first, FwdIt last, const T& val);
			void fill_n(OutIt first, Size n, const T& val);		*/
	//fill은 반복자 구간을 지정하는데 비해 fill_n은 시작 위치와 개수를 지정한다는 점이 다르다.
	//반복자 구간은 이미 메모리가 확보되어 있어야 한다. 만약 생성된 값을 꼭 삽입하려면 삽입 반복자를 사용해야 하며 이때는 두 번째 원형만 사용할 수 있다.

	int ari[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	vector<int> vi(&ari[0], &ari[16]);
	dump("vi          ", vi);
	fill(vi.begin() + 2, vi.end() - 5, 99);
	dump("fill 99 ->vi ", vi);
	fill_n(vi.begin() + 2, 5, 77); //이렇게 하면 2번째부터 5개의 요소가 99로 바뀐다.
	dump("fill_n 77->vi",vi);
	




	cout << "===============random_shuffle================" << endl;
	// 다음 함수는 반복자 구간의 요소들을 무작위로 마구 섞는다.
			/*	void random_shuffle(RanIt first, RanIt last[, UniOp& op]);	*/			//UniOp이므로 단항, bool이 아닌 리턴값을 가진다.
	//반복자 구간은 물론 유효해야 한다.		
	//이 함수는 난수로 요소를 생성해서 대입하는 것이 아니라 이미 존재하는 값들의 순서를 난수로 변경함으로서 섞는다.
	//세번째 인자는 난수생성기 함수객체 이고, 따로 지정안해줘도 잘 섞이기 때문에 안써도 된다.
	char str[] = "abcdefghijklmnopqrstuvwxyz";
	randomize();

	puts(str);
	random_shuffle(&str[0], &str[strlen(str)]); puts(str);
	random_shuffle(&str[0], &str[strlen(str)]); puts(str);
	random_shuffle(&str[0], &str[strlen(str)]); puts(str);


	cout << "===============generate================" << endl;
	//다음 함수는 반복자 구간에 대해 g 함수를 호출하여 리턴되는 값으로 채운다.
		/*	void generate(FwdIt first, FwdIt last, Gen g);
			void generate_n(OutIt first, Dist n, Gen g);	*/
	//fill 함수와 마찬가지로 반복자 구간을 인수로 전달받을 수도 있고 시작 위치와 개수를 인수로 받을 수도 있다. 
	//g는 인수를 받지 않고 컨테이너 요소 타입을 리턴하는 함수 객체이다. 다음 예제는 피보나치 수열을 만든다.

	vector<int> vi2(10);

	generate(vi2.begin(), vi2.end(), []() -> int 	//피보나치 알고리즘. 앞의 1 1 은 생략.
		{
		static int i1 = 1, i2 = 1;
		int t;
		t = i1 + i2;
		i1 = i2;
		i2 = t;
		return t;
		});

	dump("vi", vi2);

	//피보나치 수열은 이 외에도 다양한 방법으로 만들 수 있다. 
	//생성기 함수 객체는 별도의 인수를 받아들이지 않으므로 매번 다른 값을 만들기 위해서는 함수 자체가 별도의 정보를 저장하고 있어야 한다. 
	//예제의 피보나치 람다함수는 직전의 수 둘을 정적변수에 저장하고 있는데 멀티 스레드 환경에서는 동기화 문제가 발생할 수 있다. 
	//이럴 때는 함수 객체를 만들어야 한다.
	return 0;
}
