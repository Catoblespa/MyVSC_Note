#include <iostream>
#include <typeinfo>
using namespace std;
/*
	##1. 템플릿 (Template)
	동일한 로딕에 대해여러 자료형을 호환할 수 있게 프로그램을 작성하도록 도와주는 C++문법
*/

/*
	##2. 함수 템플릿
	이런 모양의 함수를 찍어낼거라는 템플릿(툴)임
	템플릿은 선언해놔도 컴파일 해보면 코드가 생성되지않음.
	구체적인 호출 코드가 없으면 함수 코드는 생성되지 않는다.

*/



template <typename T>
T Add( T a, T b)
{
	return a + b;
}


// #4 템플릿 특수화
//템플릿이 여러 자료형을 호환하지만
//특정 자료형에 대해서는 별도의 다른 동작이 필요할때

template <>
char* Add( char* a, char* b)
{
	int iTotal = strlen(a) + strlen(b);

	char* pName = new char[iTotal + 1];

	strcpy_s(pName, iTotal + 1, a);
	strcat_s(pName, iTotal + 1, b);

	return pName;
}


// ## 여러 Typename을 받는 함수 템플릿
template <typename T1, typename T2, typename T3>
void Func(T1 a, T2 b, T3 c)
{

}


int main()
{
	
	//##3. 템플릿 함수
	
	int iResult =Add<int>(10,20);			//이떄 int 타입을 가진 함수코드가 생성된다.(컴파일 시점)
	iResult = Add<int>(20, 40);				//위에서 이미 생성된 <int>코드를 재사용!	

	float fResult = Add<float>(3.14f, 3.f);	//이떄 float 타입을 가진 함수코드가 생성된다.(컴파일 시점)



	//Char*는 +연산이 되지 않는다! 그런데 Template로 이따구로 써두면 ??
	//때론 예외사항이 필요하다
	//char* pTotal = Add<char*>("Hello", "World");

	char* pTotal = Add<char*>(const_cast<char*>("Hello"), const_cast<char*>("World"));


    Func<int,float, double>(10,3.14f,3.142592184);

	return 0;
}
