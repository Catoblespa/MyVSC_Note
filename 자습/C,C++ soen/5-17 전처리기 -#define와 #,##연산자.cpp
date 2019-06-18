#include <iostream>

#define result(exp) printf(#exp"=%d\n",exp)
// 과 ##은 전처리기의 연산자로서 컴파일러가 #define 전처리 과정에서만 사용하는 특수한 연산자이다.
// # 연산자(stringizing operator)는 #define문의 인수 앞에 사용되며 피연산자를 문자열로 바꾸는 역할을 한다. 
//   피연산자가 실인수로 치환된 후 양쪽에 따옴표를 붙여 치환된 결과 그대로 문자열 상수가 된다.


#define BIN(a) strtol(#a,NULL,2)
//strtorl 은 첫번째 인수를 문자열로 받아, 2진수 상수를 사용하게 해주는 함수이다.
//첫 인수에 "1101" 을 넣어주면 13을 가르키는 값을 반환 해주는 것이다.
//Bin 매크로를 사용하면 문자열을 넣지 않아도 이진수만 넣으면 쉽게 2진수 상수를 사용하게 해준다.


//## 연산자 또한 #연산자와 같이 #define에서만 사용 가능한 연산자이다.
//var 매크로는 두개의 형식 인수를 받아, 두 명칭을 연결하여 하나의 명칭을 반환한다.
#define var(a,b) (a##b)		// (a   ##   b) 로 정의 해도 ##주면의 공백은 모두 사라진다.

//##은 치환전에 두 토큰을 분리하여 각 토큰이 치환될 수 있도록 구분하는 역할을 하며 치환 후에는 주변의 공백과 함께 자폭하여 두 토큰을 하나로 연결한다.
//이 연산자는 주로 일괄적인 타입 정의에 사용된다.
#define defptype(type) typedef type *p##type


//#define의 코드가 두줄 이상일때 \를 쓰면 다음 줄까지 인식 시킨다.
//단 \뒤에는 공백이 남아 있으면 안되니 주의 !
#define SAFE_DELETE(ptr)	\
if(ptr) 					\
{							\
	delete ptr; 			\
	ptr = null;				\
}

#define PI 3.14f
#define SQUARE(X)	(X)*(X)
#define AREA_CIRCLE(R) SQUARE(R) * PI//  쌉가능
using namespace std;

int main()
{

	result(5 * 3);	//변환 순서
					//-> printf(#5*3"=%d",(5*3));
					//-> printf("5*3""=%d",(5*3));		// #5*3 이 "5*3"으로 치환됨
					//-> printf("5*3=%d",(5*3));		// 인접한 문자열을 합침.

	cout << BIN(00010010001101001111000001011100) << endl;
	cout << BIN(1101) << endl;

	int TotalScore;
	var(Total, Score) = 10;
	cout << "TotalScore : " << TotalScore << endl;


	//defptype 매크로는 int, double 등의 타입을 인수로 전달받으며 원래 타입앞에 p를 붙여 포인터 타입을 새로 정의한다.

	defptype(int);		// pint 라는 이름으로 int * 타입을 정의한다.
	defptype(double);	// pdouble 라는 이름으로 double * 타입을 정의한다.
	defptype(char);		// pchar 라는 이름으로 char *타입을 정의 한다.

	pint pi;
	int i = 3;
	pi = &i;
	printf("i = %d\n", *pi);

	return 0;
}