#include <iostream>
#include <vector>
using namespace std;



/*
const를 붙여 선언하면 컴파일러가 사용상의 에러를 잡아내는 데 도움을 준다.
const는 어떤 유효범위에 있는 객체에도 붙을 수 있으며, 함수 매개변수 및 반환 타입에도 붙을 수 있으며,
맴버 함수에도 붙을 수 있다

컴파일 쪽에서 보면 비트수준 상수성을 지켜야 하지만,
우리는 개념적인(논리적인) 상수성을 사용해서 프로그래밍 해야한다.

상수 맴버 및 비상수 맴버 함수가 기능적으로 서로 똑같게 구현되어 있을 경우에는 
코드 중복을 피하는 것이 좋은데, 이때 비상수 버전이 상수 버전을 호출하도록 만들어라!
*/

class TextBlock
{
	char* text;

public:
	const char& operator[] (size_t position) const
	{
		/*~ 경계검사
			~접근 데이터 로깅 ~
			~자료 무결성 검증 등등 ~
		*/
		return text[position];
	}

	char& operator[] (size_t position)
	{
		return const_cast<char&>
			(
				// 이무슨 해괴망측한 코드란말이냐!
				static_cast<const TextBlock>(*this)[position]
			);
	}
};


int main()
{
	return 0;
}
