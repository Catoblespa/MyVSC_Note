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
copy 알고리즘은 지정한 구간을 복사하는데 주로 일부 요소들을 다른 컨테이너로 복사하고 싶을 때 사용한다. 
같은 타입의 컨테이너 전체를 완전히 복사하려면 copy 함수를 쓸 필요없이 컨테이너의 = 연산자로 대입해 버리면 된다. 
복사 방향에 따라 다음 두 개의 함수가 정의되어 있다.

		//OutIt copy(InIt first, InIt last, OutIt result);				//OutIt 출력 반복자
		//BiIt copy_backward(BiIt first, BiIt last, BiIt result);		//BiIt  양방향 반복자

copy 함수는 first~last 사이의 모든 요소를 result반복자 위치 이후에 복사한다. 
복사 목적지의 시작 위치는 result 반복자 하나로만 지정되며 길이는 원본과 같다고 가정하므로 
result이후 last - first만큼의 기억 장소가 미리 확보되어 있어야 한다.

 반복자는 같은 컨테이너의 다른 부분일 수도 있지만 다른 컨테이너의 반복자 구간끼리도 물론 복사할 수 있다.
*/

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}


int main()
{
	
	char src[] = "1234567890";
	char dest[] = "abcdefghij";

	copy(&src[3], &src[7], &dest[5]);		//	//두 개의 문자열끼리 복사한다.
	puts(dest);	//abcde4567j
	//copy 함수는 이름이 의미하듯이 복사를 할 뿐이지 원본의 요소를 목적지에 삽입하는 것이 아니다.
	//따라서 result 반복자 이후부터 원본의 길이만큼 미리 확보되어 있지 않으면 결과는 예상할 수 없다. 
	//위 예제의 복사 목적지를 dest[9]로 변경하면 배열 뒤쪽을 덮어쓰므로 아마도 다운될 것이다. 
	//이럴 때 삽입 반복자를 사용하면 복사와 동시에 요소를 삽입할 수 있다.



	list<char> li;									//li 리스트는 빈 상태로 생성되었다.
	copy(&src[3], &src[7], back_inserter(li));		//back_inserter 반복자가 대입 동작을 push_back 삽입 동작으로 재정의하므로 
	dump("list", li);								//복사되는 족족 리스트의 크기가 늘어난다. 
	//list        ==> 4 5 6 7

	//만약 copy(&src[3], &src[7], li.begin()); 으로 복사를 수행하면 
	//컴파일은 잘 되겠지만 허가되지 않은 영역에 쓰기 동작을 수행하므로 당장 다운되어 버릴 것이다.
	//일반 알고리즘은 컨테이너를 변경할 수 없지만 삽입 반복자를 쓰는 경우에는 요소를 추가로 삽입하는 것이 가능하다.
	//삽입 반복자는 자신이 적용할 컨테이너에 대한 정보를 전달받으며 어떤 식으로 삽입해야 한다는 것을 알기 때문이다.




	//같은 컨테이너끼리도 복사할 수 있는데 이때는 복사 방향에 신경을 써야 한다. 
	//copy는 first에서부터 시작해서 last로 이동하면서 한 요소씩 순서대로 복사하는데 
	//원본과 목적 구간이 겹쳐 있으면 원본이 앞쪽 복사에 의해 읽기도 전에 파괴되는 문제가 있다. 
	//그래서 역방향으로 진행하면서 복사하는 copy_backward 함수가 따로 마련되어 있는 것이다. 리스트로 이 문제를 테스트해 보자.
	cout << "===============copy_backward===============" << endl;
	list<int> li2, li3;
	list<int>::iterator first, last, result, it;

	for (int i = 0; i < 10; i++) li2.push_back(i);

	li3 = li2;

	dump("복사전", li2);
	first = find(li2.begin(), li2.end(), 2);		//li2에서 2요소의 위치 저장
	last = find(li2.begin(), li2.end(), 7);			//li2에서 7요소의 위치 저장
	result = find(li2.begin(), li2.end(), 3);		//복사 시작 목적지
	copy(first, last, result);
	dump("copy", li2);

	first = find(li3.begin(), li3.end(), 2);
	last = find(li3.begin(), li3.end(), 7);
	result = find(li3.begin(), li3.end(), 8);		//복자 끝 다음점
	copy_backward(first, last, result);
	dump("back", li3);
	//0 ~ 9까지의 정수를 리스트에 넣어 놓고 2 ~ 6까지의 요소를 3번 위치, 
	//즉 한칸 오른쪽으로 복사하되 한 번은 copy를 한 번은 copy_backward를 사용했다.
	//역방향으로 복사할 때는 제대로 복사되었는데 순방향으로 복사할 때는 뭔가 잘못된 복사를 하고 있다. 
	//왜 그런지 복사 순서를 잘 생각해 보자.
	// 0 1 2 3 4 5 6 7 8 9	//li 
	// 0 1 2 2 2 2 2 2 8 9	// copy		
	// 0 1 2 2 3 4 5 6 8 9  // copy_backward

	//copy는 [2]의 위치부터 [7]위치까지  [3]위치에 복사를 실행한다.
	// [3]위치에 2가 복사되고, copy는 [3]를 참조해서 [4]에 복사를 하므로, [4]에도 똑같은 값인 2가 들어간다.(이미 [3]이 2로 복사 됬으므로.)
	// 그러므로 마지막 복사 위치인 [7]까지 모두 같은 2가 복사 되는것이다.
	//copy_backward는 뒤에서 부터 복사를 실시하는데,
	//복사할 2 3 4 5 6 값중 마지막에 복사되야할 6이 [7]자리에, 5가 [6]자리에 들어가는 식으로 하나씩 복사되므로 원래 의도가 정확히 표현된다.
	//이처럼 같은 컨테이너에서의 복사를 시행할경울 copy_backward를 사용해야 안전하다.
	// 그러므로 copy_backward함수는 반복자가 반대 방향으로 움직여야 하므로 양방향 반복자여야 한다.
	
	//또한 result가 복사 목적지의 시작점이 아니라 끝다음점이어야 한다는 점도 다르다. 
	//구간을 한칸 오른쪽으로 이동할 때 순방향은 2 ~ 6을 3의 자리로 이동하라는 식으로 인수를 전달하지만 
	//역방향으로 이동할 때는 2 ~ 6을 8 앞쪽으로 이동하라는 식으로 인수를 전달해야 한다.

	cout << "========copy를 vector에서 할 경우 ============" << endl;
	vector<int> vi, vi2;
	for (int i = 0; i < 10; i++) vi.push_back(i);
	vi2 = vi;

	dump("복사전", vi);

	copy(vi.begin() + 2, vi.begin() + 7, vi.begin() + 3);
	dump("copy   ", vi);

	copy_backward(vi2.begin() + 2, vi2.begin() + 7, vi2.begin() + 8);
	dump("copy_bw", vi2);
	//똑같은 소스를 작성했는데 벡터의 경우는 복사 방향에 상관없이 잘 동작한다. 
	//똑같은 소스를 데크에 대해 작성해 보면 데크는 리스트와 마찬가지로 방향이 잘못되면 원본이 파괴된다.

	/*
	유독 벡터에 대해서만 복사 방향에 상관없이 잘 복사되는데 이는 구현 방식과 관련이 있다.
	벡터는 요소들이 인접해 있는 구조를 가지고 있으므로 좀 더 빠른 복사를 위해 memmove 함수 또는 그에 준하는 메모리 복사 함수를 사용한다.
	이 함수는 CPU의 메모리 이동 코드를 호출하는데 CPU가 복사 방향에 따라 순서를 적절하게 조정하기 때문에 겹치더라도 잘 동작하는 것이다.

	그렇다면 리스트의 경우는 이런 방향 자동 판단을 왜 할 수 없을까? 
	리스트의 노드는 메모리의 도처에 흩어져 있어 반복자만으로는 앞뒤 순서를 판단할 수 없으며 그래서 사용자가 수동으로 복사 방향을 선택해야 한다. 

	대부분의 컴파일러에서 벡터는 복사 방향에 상관없도록 구현되어 있지만 
	STL 스팩에 그렇게 구현해야 한다고 되어 있지는 않으므로 가급적이면 방향에 맞는 함수를 선택해서 사용하는 것이 바람직하다.
	*/

	//다음은 아주 기본적인 함수에 대해 알아보자. 
	//다음 함수는 이름만 봐도 뭐하는 함수인지 알 수 있으므로 굳이 두 개의 값을 교환한다고 설명하지 않아도 될 것이다.

	/*	void swap(T& x, T& y);	*/
	//기본 타입은 물론이고 컨테이너에 대해서도 사용할 수 있으며 대입 연산이 느린 경우는 특수화된 함수가 호출된다.
	//부분의 컨테이너 타입에 대해 특수화되어 있어 컨테이너의 구조에 딱 맞는 교환 멤버 함수가 호출된다.
	//두 개의 벡터가 있을 때 swap(v1,v2)는 두 벡터의 내용을 완전히 바꾼다. 
	//리스트나 벡터에 대해서는 링크나 내부 포인터만 조작하는 멤버 함수를 호출하도록 특수화되어 있어 생각보다 훨씬 빠르다


	/*	FwdIt2 swap_ranges(FwdIt1 first1, FwdIt1 last1, FwdIt2 first2);		*/
	//first1~last1사이를 first2구간과 바꾼다고 생각하면 된다. 
	//다른 컨테이너의 반복자 구간끼리도 값을 교환할 수 있되 동일 컨테이너내의 교환인 경우 반복자 구간이 겹쳐서는 안된다.




	return 0;
}
