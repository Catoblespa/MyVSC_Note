#include <iostream>
using namespace std;


/*
	#define을 쓰려거든 const, enume, inline을 사용하자.

	#define을 상수로 교체하려는 경우 두가지만 조심하자
		-첫째, 상수 포인터를 정의 하는 경우에 포인터는 꼭 const로 선언해주어야 하고,
		포인터로 가리키는 대상까지 const로 선언해야한다.
			const char * const authorName = "Scott Meyers";
			문자열을 상수로 정의 하려면 가급적 string을 사용하는게 좋다
			const string autorName("Sott Meyers");

		-두번째 클래스 맴버로 상수를 정의하는 경우 그 상수를 클래스로 한정하고자 할때는
		상수 맴버로 만들어야하는데, 그 상수의 사본이 여러개 생기지 않게 하기 위해서는
		static 맴버로 만들어야한다

		class GamePlayer
		{
		private:
			static const int NumTurns = 5;		//상수 선언
			int scores[NumTurns];				//상수를 사용하는 부분
		};

		단, 위의 코드에서 static const int NumTurns = 5;는 정의가 아닌 선언이라는 것에 주의 해야한다
		C++에서 정적 맴버로 만들어지는 정수류(각종 정수 타입, char, bool) 타입의 클래스 내부상수는 예외이다
			//int는 정수타입이므로 저렇게 선언하여 사용 가능하다.
			*/

			
//실수일경우 아래와 같이 사용해야한다
class CostEstimeate
{
private:
	static const double FudgeFactor;			//선언부는 클래스 안에
	/*...*/
};

const double CostEstimeate::FudgeFactor = 1.35;	//정의 부는 정의구현 cpp에!
/*
		앵간하면 이정도로 대부분 되지만, 한가지 예외가 있다.
		바로 클래스를 컴파이라흔ㄴ 도중에 클래스 상수의 값이 필요할 때이다.
		예를들어
		GamePlayer클래스 처럼 배열인 scores맴버를 선언할때가 대표적이다.
*/


/*
컴파일러는 클래스를 컴파일하면서 외부에 정의가 구현 되어 있는 수를 알수가 없으므로
애러가 나게되는데, 이때 사용하기 편리한것이 나열자 둔갑술(enum hack)이라는 것이다.
*/
class GamePlayer2
{
private:
	enum { Numturns = 5 };		//나열자 둔갑술 : Numturns를
								//5에 대한 기호식 이름으로 만든다
	int score[Numturns];			//해결
};


/*
나열자 둔갑술을 알아야하는 첫번째 이유
	나열자 둔갑술은 동작방식이 const보다 #define에 가깝다
	const는 주소값을 저장하는것은 합당한 방법이지만
	#define은 그렇게 사용해서는 안되기 때문이다.
	우리가 선언한 const 상수를 가지고 다른 사람이 주소를 얻어낸다던가 그런길은 피하고 싶을거다.


나열자 둔갑술을 알아야하는 두뻔째 이유
	현업에서 상당히 많이 쓰는 문법이며, 템플릿 메타프로그래밍의 핵심 기법이기도 하다
*/


/*
매크로를 사용할때 인자를 일일히 괄호로 싸줘야한다는건 익히 알려진 사실이다.
그러나 그걸로 안전한 것일까 ?   매크로는 때때로 괴현상을 불러올때도 있다
아래코드를 보자 */

#define CALL_WITH_MAX(a,b) ((a)> (b) ? (a) : (b))

template <typename T>
inline void callWithMax(const T& a, const T& b)
{
	f(a > b ? a : b);
}
//이함수는

int main()
{
	int a = 5, b = 0;
	CALL_WITH_MAX(++a, b);				//a가 두번 증가한다
	CALL_WITH_MAX(++a, b+10);			//a가 한번 증가한다.

	cout << a << endl;
	cout << b << endl;
	
	//이를 해결하기 위한 inline


	return 0;
}


/*
이것만은 잊지말자!
 

	*단수 상수를 쓸 때는 #define보다는 const객체 혹은 enum을 우선 생각하자
	*함수처럼 쓰이는 매크로를 만드려면 #define보다 인라인 함수를 우선생각하자.
 
 */