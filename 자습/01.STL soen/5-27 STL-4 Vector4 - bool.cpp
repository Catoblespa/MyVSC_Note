#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>		
#include <iterator>		//여러 종류의 반복자의 정의 담음.

using namespace std;


/*
bool vector

벡터는 임의 타입의 요소를 저장할 수 있으므로 bool 타입의 진위형 값도 저장할 수 있다. 
그런데 bool은 크기가 1바이트이지만 true 또는 false를 기억하는데는 단지 1비트만 사용되므로 7비트가 낭비되는 문제가 있다. 
100개의 진위값이 필요하다면 100/8 = 13바이트 정도면 충분한데 bool형 요소 100의 크기 총합은 100바이트나 차지하므로 대략 8배 정도의 공간 낭비가 있는 셈이다.

그래서 벡터는 bool형에 대해서 특수화되어 있으며 하나의 값을 저장하는데 비트 하나만 사용한다. 
마치 C 구조체의 비트필드와 유사하다. 

vector<bool>은 진위형의 요소들을 1비트에 하나씩 압축하여 저장하는 별도의 독립 클래스이다. 
8개의 진위형을 저장할 때 bool형의 단순 배열에 비해 vector<bool>의 크기가 훨씬 더 작다.

bool 배열은 8바이트를 차지하고 vector<bool>은 불과 1바이트밖에 차지하지 않아 7바이트를 아낄 수 있다. 
vector<BOOL>도 가능한데 BOOL은 정수와 크기가 같으므로 무려 32배나 더 크다. 
물론 요즘같이 메모리가 풍분한 상황에서 7바이트 정도야 아껴 봤자겠지만 대규모의 로그 정보를 관리할 때는 이 차이가 아주 심각해질 수도 있다.


*/


int main()
{


	vector<bool> vb(32);					//크기 32의 bool 벡터 vb를 선언했다
											//32의 크기지만 실제 정보 저장을 위해 사용하는 메모리는 불과 4바이트 정도밖에 되지 않을 것이다.
	cout << vb[10] << endl;					// 특수화된 클래스이기는 하지만 사용하는 방법은 일반 벡터와 별로 틀리지 않으며 배열과도 유사하다.
	vb[10] = true;							//특정 위치의 값을 액세스할 때는 [ ] 연산자로 읽기만 하면 된다.
	cout << vb[10] << endl;

	vector<bool>::reference r = vb[10];		//vector<bool>에 포함된 reference 타입은 벡터내의 한 요소, 그러니까 한 비트를 표현하는 클래스이다
	cout << r << endl;
	r.flip();								//이 외에 비트를 뒤집는 flip, bool형으로 변환하는 캐스트 연산자, 비트를 반전하는 ~ 연산자, 대입 연산자 등이 정의되어 있다. 
	cout << r << endl;
	vector<bool>::iterator it;

	//반복자로 전체를 순회하면서 출력해 보았다. 
	for (it = vb.begin(); it != vb.end(); it++) 
	{
		cout << *it;
	}


	//vector<bool>은 표준에 포함되어 있기는 하지만 몇 가지 점에서 문제가 있고 컴파일러마다 지원 범위가 달라 가급적이면 사용을 자재하는 것이 좋다.

	return 0;
}
