#include <iostream>


using namespace std;


//#1 사용자 정의 자료형
//typedef : 기존의 자료형을 사용자가 새로운 이름으로 정의하는 자료형.

/*typedef int MY_INTEGER;*/
// 미리 이렇게 typedef를 써서 변수를 사용하면, 나중에 타입을 쉽게 교체 할 수 있다.
//MY_INTEGER를 short으로 바꾸려면 typedef만 쓰면 된다!

//#2 상황에 따른 타입 정의가 가능하다.
//만약 32비트 환경이라면 int형, 그외에서는 long long 타입으로 사용하라.
#ifdef _WIN32
typedef int MY_INT;
#else
typedef long long MY_INT;
#endif


//#3 공용체 Union
union uniBox
{
	int		a;
	short	b;
};

struct tagBox
{
	int		a;
	short	b;
};


union uniMatrix
{
	struct					//가독성을 높이기 위해
	{
		float _l1, _l2, _l3;
		float _l4, _l5, _l6;
		float _l7, _l8, _l9;
	};
	float m[3][3];			//접근을 용이하게 만들어 주기 위해 
	//m[0][0]에 접근하면 _l1이 접근 된다는 뜻이다.
};


int main()
{
	uniBox uBox;
	//공용체 vs 구조체
	//공용체는 구조체와 달리 모든 맴버가 하나의 메모리를 공유한다.
	//맴버중 가장 큰 메모리를 공유한다.
	cout << "공용체 :" << sizeof(uniBox) << endl;		//4
	cout << "구조체 :" << sizeof(tagBox) << endl;		//8

	cout << "&(uBox.a) :" << &(uBox.a) << endl;	//같은주소
	cout << "&(uBox.b) :" << &(uBox.b) << endl;	//같은주소
	uBox.a = 10;
	uBox.b = 20;
	cout << "uBox.a :" << (uBox.a) << endl;	//b가 a의 같은 주소를 공뮤하는데, b를 20으로 수정했으므로 a도 20이된다.
	cout << "uBox.b :" << (uBox.b) << endl;	//

	uniMatrix uMat;
	uMat.m[0][0] = 1.1f;


	cout << "uMat.m[0][0] :"	<< uMat.m[0][0] << endl;	//
	cout << "uMat._l1     :"	<< uMat._l1 << endl;




	return 0;
}