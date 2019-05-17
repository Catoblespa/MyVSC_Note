#include <iostream>

using namespace std;

/*
조건부 컴파일 지시자(Conditional Compile Directive)는 지정한 조건의 진위 여부에 따라 코드의 일정 부분을 컴파일할 것인지 아닌지를 지정한다.
전처리문이므로 컴파일되기 전에 조건을 평가하며 코드를 컴파일 대상에 포함시키거나 제외시키는 역할을 한다.
이때 조건의 형태는 여러 가지가 있지만 주로 매크로 상수의 존재 여부나 값에 대한 평가식이 사용된다.
실행중에 결정되는 변수의 값이나 함수 호출은 당연히 조건문이 될 수 없다.

#ifdef 매크로명
코드
#else

#endif

#ifndef
코드
#endif

#ifndef는 #ifdef와 반대의 조건을 점검하는 지시자이다.
#ifdef는 매크로가 정의되어 있을 때만 컴파일하지만 #ifndef는 반대로 매크로가 정의되어 있지 않을 때만 컴파일한다.



#ifdef, #ifndef는 매크로의 존재 여부만으로 컴파일 조건을 판단하며 매크로가 어떤 값으로 정의되어 있는지는 평가하지 않는다.
이에 비해 #if는 매크로의 값을 평가하거나 여러 가지 조건을 결합하여 컴파일 여부를 결정하는 좀 더 복잡한 전처리문이다.
#ifdef보다는 사용법이 조금 까다롭지만 C 언어의 조건문과 유사하므로 쉽게 익힐 수 있다. 기본 형식은 다음과 같다.

#if 조건1
코드1           // 조건1을 만족하면 코드1을 컴파일
#elif 조건2
코드2           // 조건 2가 만족되면 코드2를 컴파일
#else
코드3           // 둘 다 맞지 않으면 코드 3을 컴파일

#endif

ex)
#if (LEVEL == 3)
#if (VER >= 7)
	// 대상은 정수 상수여야 하며 실수나 문자열은 매크로와 비교할 수 없다.
#if (VER == 3.14)          // 에러
#if (NAME == "Kim")          // 에러
#if (LEVEL == BASIC)        // 가능

#if (LEVEL == 8 || defined(PROFESSIONAL))		//#if defined(MACRO) 전처리문은 #ifdef MACRO와 완전히 동일한 문장이다.
												//defined 연산자로 매크로의 존재 여부를 평가할 수 있다.
												//defined 연산자는 전처리문에서만 사용 가능하다.

*/

#if 0
if 0도 주석 대신 흔히 사용되는 구문이다.
아주 긴 소스를 잠시 주석 처리해 놓고 싶을 때는 이 부분을 #if 0 .... #endif로 감싸 버리면 항상 거짓이므로 전처리기에 의해 이 코드는 없는 것으로 취급된다.
주석은 중첩될 수 없어 긴 소스를 주석 처리할 때 불편한 반면 #if 0는 중첩 가능하기 때문에 이런 문제가 없다.

#undef는 #define의 반대되는 동작을 하는 전처리문이다.
#define이 매크로를 정의하는데 비해 #undef는 정의되어 있는 매크로를 삭제한다.
전처리기는 이 명령을 만나면 지정한 매크로의 정의를 취소하고 이후부터 이 명칭에 대해서는 치환을 중지한다.
#undef 다음에 취소하고 싶은 매크로의 이름만 적어주면 된다.

#endif

/*
#define TIME 800
#include <ext1.h>
#undef TIME
#define TIME 1400
#include <ext2.h>
//이렇게 하면 ext1.h를 컴파일할 때 TIME은 800이 되고 ext2.h를 컴파일할 때 TIME은 1400이 된다. 
일정한 범위 내에서만 매크로의 의미를 잠시 바꾸고 싶을 때 매크로 재정의 기법이 가끔 필요하다.
*/

/*

#error 전처리문은 지정한 에러 메시지를 출력하고 전처리 과정에서 컴파일을 중지하도록 한다.
 에러 메시지는 메시지 창에 출력되는데 비주얼 C++의 경우 Output창에 나타난다.
  단독으로 사용되는 경우는 없으며 주로 조건부 컴파일 지시자와 함께 사용되어 컴파일 불가능한 상황임을 개발자에게 알려 주는 역할을 한다.
  다음이 그 예이다.

    
#ifndef UNICODE
#error This program require unicode environment         // UNICODE 환경이 아닐경우 해당 에러메시지창 출력!
#endif

 
*/

int main()
{

#define SIZE 10
	printf("SIZE=%d\n", SIZE);

#undef SIZE
#define SIZE 20
	printf("SIZE=%d\n", SIZE);

	return 0;
}