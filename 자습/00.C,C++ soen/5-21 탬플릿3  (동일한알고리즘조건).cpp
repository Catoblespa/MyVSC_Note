#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>

using namespace std;

//세 함수 템플릿들을 보면 값을 비교, 연산하고 선택하는 알고리즘이 타입과 상관없이 항상 동일하다는 것을 알 수 있다. 
//달라질 수 있는 것은 오로지 타입뿐이므로 이런 함수들이 템플릿으로 통합될 수 있는 것이다.
template <typename T>
T Max(T a, T b)
{
	return (a > b) ? a : b;

}

template <typename T>
T Add(T a, T b)
{
	return a + b;
}

template <typename T>
T Abs(T a, T b)
{
	return (a > 0) ? a : -a;
}

template <typename T>
void Swap(T& a, T& b)
{
	T t;
	t = a; a = b; b = t;
}

template <typename T>
void SwapArray(T* a, T* b, int num)
{
	void* t;

	t = malloc(num * sizeof(T));
	memcpy(t, a, num * sizeof(T));
	memcpy(a, b, num * sizeof(T));
	memcpy(b, t, num * sizeof(T));
	free(t);
}

int main()
{

	int a = 1, b = 2;
	double c = 3.4, d = 5.6;
	printf("더 큰 정수 = %d\n", Max(a, b));
	printf("더 큰 실수 = %f\n", Max(c, d));
	//만약 알고리즘이 동일하지 않다면, 즉 함수의 본체가 완전히 달라야 한다면 이 함수들은 같은 템플릿으로 통합될 수 없다.
// 예를 들어 두 값을 교환하는 Swap 함수 템플릿의 경우 임의의 타입에 대해 잘 동작하지만 배열에 대해서는 동작하지 않는다. 
//만약 다음과 같이 배열을 가리키는 포인터를 두 개 선언하고 이 포인터를 Swap 함수로 전달했다고 해 보자.

	int arA[3] = { 1,2,3 }, arB[] = { 4,5,6 };
	int* pa = arA, * pb = arB;
	//Swap(pa, pb);
	// Swap(arA, arB);


	//Swap(pa, pb)는 일단 정상적으로 동작하는 것처럼 보인다. 
	//그러나 이는 배열을 가리키는 포인터만 교환한 것이지 배열 자체가 교환된 것은 아니다. 
	//Swap(arA, arB); 호출로 배열 자체를 교환하려고 시도하면 포인터 상수인 배열명을 변경할 수 없다는 에러로 처리된다. 
	//두 배열의 타입과 크기가 일치하더라도 배열을 교환하는 알고리즘은 단순 타입이나 구조체를 교환하는 것과는 다르다. 
	//배열끼리는 대입되지 않으므로 배열의 요소들을 일대일로 교환해야 하며 배열의 크기가 가변적이므로 길이에 대한 별도의 정보를 더 전달해야 한다.


	char chC[] = "문자열", chD[] = "string";

	SwapArray(arA, arB, sizeof(arA) / sizeof(arA[0]));
	printf("before chC=%s,chD=%s\n", chC, chD);

	SwapArray(chC, chD, sizeof(chC) / sizeof(chC[0]));
	printf("after chC=%s,chD=%s\n", chC, chD);

	//앞에서 만들었던 SwapVoid와 상당히 유사한데 메모리의 길이를 인수로 전달받는 것이 아니라 요소의 개수를 전달받는다는 점이 다르다.
	//main에서 크기 3의 정수형 배열과 크기 7의 문자형 배열에 대해 교환을 했으므로 SwapArray는 두 가지 버전으로 구체화될 것이다.실행 결과는 다음과 같다.

	/*
	before c = 문자열, d = string
	after c = string, d = 문자열
	*/

	//보다시피 배열을 교환하는 알고리즘은 단순 타입을 교환하는 알고리즘과 완전히 틀리고 필요한 인수 목록도 다르기 때문에 
	//하나의 함수 템플릿으로 통합될 수 없으며 따로 템플릿을 구성해야 한다. 
	
	//이 예제에서는 배열을 교환하는 함수 템플릿에 SwapArray라는 이름을 사용했는데 
	//인수 목록이 달라 오버로딩이 가능하므로 Swap이라는 이름을 같이 써도 상관없다. 즉 템플릿끼리도 오버로딩은 가능하다.


	return 0;	
}
