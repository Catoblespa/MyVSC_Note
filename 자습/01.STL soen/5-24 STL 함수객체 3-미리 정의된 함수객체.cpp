#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>		//미리 정의된 함수 객체를 사용하기 위한 !헤더.
					
using namespace std;

/*
함수 객체는 통상 () 연산자 하나만 정의하고 그나마도 동작이 간단해 길이가 아주 짧다. 
이런 짧은 클래스도 직접 선언해서 쓰자면 번거로운데 그래서 STL은 자주 사용할만한 연산에 대해 미리 함수 객체를 정의하고 있다.

대표적으로 가장 간단한 함수 객체인 plus를 보자. 더할 피연산자의 타입 T를 인수로 받아들이는 클래스 템플릿이다.

		//struct plus : public binary_function<T, T, T> {
		//	 T operator()(const T& x, const T& y) const { return (x+y); }
		//};
 
 T 가 int라면 결국 a, b를 받아 a+b를 리턴하는 동작을 하는 함수 객체이다.
 간단한 사용예를 보자.

*/



/*
함수 객체		연산

minus			두 인수의 차를 계산한다.

multiplies		두 인수의 곱을 계산한다.

divides			두 인수를 나눈 후 몫을 리턴한다.

modulus			두 인수를 나눈 후 나머지를 리턴한다.

negate			인수 하나를 전달받아 부호를 반대로 만든다.

equal_to		두 인수가 같은지 비교하여 결과를 bool타입으로 리턴한다.

not_equal_to	두 인수가 다른지 비교한다.

greater			첫 번째 인수가 두 번째 인수보다 큰지 조사한다.

less			첫 번째 인수가 두 번째 인수보다 작은지 조사한다.

greater_equal	첫 번째 인수가 두 번째 인수보다 크거나 같은지 조사한다.

less_equal		첫 번째 인수가 두 번째 인수보다 작거나 같은지 조사한다.

logical_and		두 인수의 논리곱(&&) 결과를 리턴한다.

logical_or		두 인수의 논리합(||) 결과를 리턴한다.

logical_not		인수 하나를 전달받아 논리부정(!)을 리턴한다.

헤더 파일을 굳이 열어 보지 않더라도 함수 객체의 이름으로부터 어떤 연산을 하는지 쉽게 유추된다.
이 함수 객체들을 사용하면 알고리즘들의 동작에 여러 가지 다양한 변화를 줄 수 있다.
그 예로 정렬 방식에 변화를 가해 보자.
sort 함수는 요소의 < 연산자로 대소를 비교하므로 기본적으로 올림차순으로 정렬하는데
함수 객체를 취하는 다음 버전을 사용하면 정렬 순서를 원하는대로 지정할 수 있다.

		//void sort(RanIt first, RanIt last, BinPred F);
마지막 인수 F는 비교할 두 요소를 전달받아 비교 결과를 리턴하는데 함수 객체의 조건을 만족하면 true를 리턴한다. 
bool형을 리턴하므로 F는 조건자 함수 객체이다. 다음 예제는 문자열을 정렬하는데 일반 sort 함수와 함수 객체 버전으로 각각 정렬한다.

*/

int main()
{
	//!ex1
	int a = 1, b = 2;
	int c = plus<int>()(a, b);		//임시객체를 통해서 plus의 생성자를 불러와 a,b를 넣고 return a+b;
	cout << c << endl;

	//!ex2
	string names[] = { "STL","MFC","owl","html","pascal","Ada",
	 "Delphi","C/C++","Python","basic" };

	vector<string> vs(&names[0], &names[10]);
	vector<string>::iterator it;

	sort(vs.begin(),vs.end());
	cout << "sort(vs.begin(),vs.end());" << endl;
	
	for (it = vs.begin(); it != vs.end(); it++) {
		cout << *it << endl;
	}
	sort(vs.begin(), vs.end(), greater<string>());		//sort함수의 함수객체를 사용한 버젼. 알고리즘을 바꾼다!!
														//greater			첫 번째 인수가 두 번째 인수보다 큰지 조사한다.
	cout << "================================================" << endl;
	cout << "sort(vs.begin(), vs.end(), greater<string>());" << endl;
	for (it = vs.begin(); it != vs.end(); it++) {
		cout << *it << endl;
	}

	sort(vs.begin(), vs.end(), less<string>());
	cout << "================================================" << endl;
	cout << "sort(vs.begin(), vs.end(), less<string>());" << endl;	//less			첫 번째 인수가 두 번째 인수보다 작은지 조사한다.
	for (it = vs.begin(); it != vs.end(); it++) {
		cout << *it << endl;
	}



}

