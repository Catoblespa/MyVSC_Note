#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>

using namespace std;

/*
함수 템플릿은 함수를 만들기 위한 형틀이라고 생각하면 된다. 
비슷한 모양의 함수들을 여러 개 만들어야 한다면 각 함수들을 매번 직접 정의할 필요없이 
함수 템플릿을 한 번만 만들어 놓고 이 템플릿으로부터 일련의 함수들을 찍어낼 수 있다. 
다음 예제는 일정한 타입의 변수 두 개의 값을 교환하는 Swap 함수를 만든다.
*/

/*
void Swap(int& a, int& b)
{
	int t;
	t = a; a = b; b = t;
}



void Swap(double& a, double& b)
{
	double t;
	t = a; a = b; b = t;
}*/

/*
 void *라는 일반적인 포인터 타입을 쓰는 방법도 있다. 
 void *는 임의의 타입을 가리킬 수 있으므로 교환 대상 변수의 번지를 전달하여 메모리 복사하는 방식으로 두 값을 교환할 수 있다.

 void *를 이용한 교환 함수는 나름대로 실용성도 있고 그야말로 임의의 타입을 다룰 수 있다는 점에서 훌륭하다. 
 실제로 이런 함수는 종종 사용되며 템플릿보다 더 우월한 면도 있다. 
 하지만 일일이 &를 붙여 번지를 전달해야 하고 길이까지 가르쳐 주어야 한다는 점에서 불편하기는 마찬가지이다.

void Swap(void *a,void *b,size_t len)
{
	 void *t;
	 t=malloc(len);
	 memcpy(t,a,len);
	 memcpy(a,b,len);
	 memcpy(b,t,len);
	 free(t);
}
*/

//Swap 함수 템플릿을 정의한 후 정수, 실수, 문자열, 구조체 등에 대해 Swap 함수를 호출해 보았다. 
//임의의 타입에 대해 Swap 함수를 사용할 수 있되 단 함수 내에서 지역적으로 선언된 타입은 사용할 수 없다.
// 지역 타입은 함수 내부에서만 쓰는 것이므로 함수간의 통신에는 사용할 수 없기 때문이다.
//그래서 tag_st 구조체를 전역으로 선언했는데 이 구조체 선언문이 main 함수 안에 포함되면 에러로 처리된다.

//함수 템플릿을 정의할 때는 키워드 template 다음에 <> 괄호를 쓰고 괄호안에 템플릿으로 전달될 인수 목록을 나열한다.
//템플릿 인수 목록에는 키워드 typename 다음에 함수의 본체에서 사용할 타입의 이름이 오는데 함수의 형식 인수와 비슷한 기능을 한다고 생각하면 된다.
//이 이름은 명칭 규칙에만 맞으면 마음대로 작성할 수 있으나 일반적으로 T나 Type이라는 짧은 이름을 많이 사용한다.
//이어지는 함수의 본체에서 템플릿 인수를 참조하여 구체적인 코드를 작성한다.

//템플릿이란 컴파일러가 미리 등록된 함수의 형틀을 기억해 두었다가 함수가 호출될 때 실제 함수를 만드는 장치이다. 
template <typename T>

void Swap(T& a, T& b)
{
	T t;
	t = a; a = b; b = t;
}

	
struct tag_st { int i; double d; };

void main()
{

	int a = 3, b = 4;
	double c = 1.2, d = 3.4;
	char e = 'e', f = 'f';
	tag_st g = { 1,2.3 }, h = { 4,5.6 };

	printf("before a=%d, b=%d\n", a, b);
	Swap(a, b);		//int int
	printf("after a=%d, b=%d\n", a, b);
	Swap(c, d);		//double double
	Swap(e, f);		//char char	
	Swap(g, h);		//tag_st  tag_st

}


//
//void main()
//
//{
//
//	int a = 3, b = 4;
//
//	double c = 1.2, d = 3.4;
//
//	Swap(a, b);
//
//	Swap(c, d);
//
//	printf("a=%d,b=%d\n", a, b);
//
//	printf("c=%f,d=%f\n", c, d);
//
//}