// ConsoleApplication2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//


using namespace std;


/*
체력치 계산을 왜 꼭 함수가 해야해 ?
그냥 함수처럼 동작하는 펑터를 쓰면 안되나 ? 라고 반박해지고 싶다.
혹여 반드시 함수여야 한다면 어쟤서 맴버 함수는 안되느냐는 의문도 나오고?

반환값도 그렇다 int로 바꿀 수 있는 임의의 타입이면 충분하겠는데, 왜 꼭 int가 아니면 안될까?

이는 tr1::function 타입의 객체를 서서 기존의 함수 포인터를 대신하게 만드는 순간,
이 모든 것이 시원하게 사라집니다. 

tr1::function 계열의 객체는 함수호출성 개체(함수포인터, 함수객체 혹은 맴버 함수 포인터)를 가질 수 있고,
이들 개체는 주어진 시점에서 예상되는 시그니처와 호환되는 시그니쳐를 갖고 있답니다.
그럼 이번엔 tr1::function을 써서 설계를 바꾸어 보자.
*/

/*

*/

class GameCharacter_v1;

//채력치 계산에 대한 기본 알고리즘을 구현.
int defaultHealthCalc(const GameCharacter_v1& gc);

class GameCharacter_v1
{
public:
	//////typedef int(*HealthCalcFunc)(const GameCharacter_v1&);
	//HealthCalcFunc는 함수호출성 개체로서, GameCharacter와 호환되는
	//어떤 것이든 넘겨받아서 호출될 수 있으며, int 와 호환되는 모든 타입의 객체를 반환합니다.   
	// function의 템플릿 인자는 다음과 같다.
    // <RET (N1, N2, ...)>
    // RET              : 반환 타입
    // N1, N2, ...      : 인자 타입들
	//출처:[TR1] function
	//자세한 내용은 아래를 보시면 나옵니다.
	typedef function을<int(const GameCharacter_v1&)> HealthCalcFunc;

	explicit GameCharacter_v1(HealthCalcFunc hcf = defaultHealthCalc)
		:healthCalcFunc(hcf)
	{}

	int healtValue() const
	{
		return healthCalcFunc(*this);
	}
private:
	HealthCalcFunc healthCalcFunc;
};


int defaultHealthCalc(const GameCharacter_v1 & gc)
{
	return 100;
}

/*
보다시다 시피 HealthCalcFunc는 tr1::function 템플릿을 인스턴스화한 것에 대한
typedef 타입입니다. 다시 말해 이 타입은 일반화된 함수 포인터 타입처럼 동작한다는 뜻이죠
그럼 HealthCalcFunc가 원래 어떤 것을 typedef한것인지 다시 눈크게 뜨고 봅시다.

	//typedef function<int(const GameCharacter_v1&)>

tr1::function을 인스턴스화 하기 위해 매개변수로 쓰인 "대상 시그니처"가 잘 보이라고 강조 표시해두었습니다()
이 대상 시그니처를 그대로 읽으면 const GameCharacter에 대한 참조자를 받고 int를 반환하는 함수입니다.
이렇게 정의된 tr1::fucntion타입(HealthCalcFunc)으로 만들어진 객체는 앞으로
대상 시그니처와 호환되는 함수호출성 개체를 어떤 것도 가질 수 있습니다.

여기서 호환된다는 말은 함수 호출성 개체타입이
const GameCharacter& 이거나
const GameCharacter& 으로 암시적 변환이 가능한 타입이며,
반환 타입도 암시적으로 int로 변환될 수 있다는 뜻입니다.


바로 앞 코드 (함수포인터방식)에서 살펴본 설계와 비교하면,
지금 설계도 사실 크게 다른것은 없습니다.
다른점이 있다면 GameCharacter가 이제는 tr1::function객체 그러니까,
좀더 일반화된 함수 포인터를 물게 된다는 거죠.

변했다고 하기엔 미안한 정도라 정말살짝 바꾼 설계라고 말씀드릴 수 있겠습니다.
하지만 아주 조금 바꾼 덕택에 사용자 쪽에선 체력치 계싼함수를 지정하는데 있어서
머리가 멍해질 정도로 불어난 융통성을 만끽 할 수 있게 되었다는 점은 넘어가면 안되겠죠

*/

short calcHealth(const GameCharacter_v1&);		//채력 계산함수입니다.
												//반한타입이 int가 아닌부분에 주목!

struct HealtCalculator {							//체력치 계산용 
	int operator()(const GameCharacter_v1&) const	//함수 객체를 만들기 위한 클래스.
	{}
};

class GameLevel {
public:
	float haelt(const GameCharacter_v1&) const	//체력치 계산에 쓰일 맴버 함수입니다.
	{											//반환 타입이 int가 아닌점에 주목
		return 10.0f;
	}											
};

class EvilBadGuy : public GameCharacter_v1			//이전 코드의 EvilBadGuy와 동일
{
public:
	explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc)
		: GameCharacter_v1(hcf)
	{}

};
int loseHealtQuickly(const GameCharacter_v1&);	//다른 동작원리로
int loseHealtSlowly(const GameCharacter_v1&);	//구현된 체력치 계산 함수들


class EyeCandyCharacter :public GameCharacter_v1
{
public:
	explicit EyeCandyCharacter(HealthCalcFunc hcf = defaultHealthCalc)
		: GameCharacter_v1(hcf)
	{}
};

// bind의 _1, _2, _3, ..._N placeholder를 사용하기 위한 namespace
using namespace std::placeholders;

int main()
{

	EvilBadGuy ebg1(calcHealth);	//체력치 계산을 위한 함수를 사용하는 캐릭터
	EyeCandyCharacter eccl(HealtCalculator());	//체력치 계산을위한 함수객체를 사용하는 캐릭터
	GameLevel currentLevel;

	EvilBadGuy ebg2(bind(&GameLevel::haelt, currentLevel, _1));
 
	EvilBadGuy ebg3([](const GameCharacter_v1&)		//람다도 씹가능..
		{
			return 50;
		});
	return 0;
}


/*
	미친듯한 확장성!
	tr1::function을 사용한것만으로도 대충만들어 넣어도 다된다..
	
	일단 어려운 코드인 ebg2의 정의 문에서 bind문에 대해 설명하도록하자

	위의 정의문이 말하는 ebg2의 체력치를 계산하기 위해 GameLevel클래스의
	healt 맴버 함수를 써야한다는 것입니다. 현재 GameLevel::health함수는
	매개변수 하나(GameCharacter에 대한 참조자)를 받는 것으로 선언 되어 있지만,
	실제로는 두개를 받습니다.

	GameLevel 객체하는를 암시적으로 받아들이니까 말이죠.
	이객체는 this포인터가 가리키는 것입니다. 하지만 GameCharacter 객체에 쓰는 체력치 계산 함수가
	받는 매개변수는 체력치가 계산되는 GameCharacter 개게 그것 하나뿐입니다.


	만일

	ebg2의 체력치 계산에 GameLevel::health함수를 쓰려고 한다면, 어떻게든 "때려맞춰야(adapt)"
	할 것입니다. 매개변수 두개(GameCharacter 및 GameLevel)를 받는 함수를 
	매개변수 한개(GameCharacter)로만 받는 함수로 바궈야 한단 말이죠.

	지금의 예제 코드에서는 ebg2의 체력치 계산에 쓸 GameLevel객체로서 currentLevel이
	사용되도록 "묶어(binding)"준것입니다.

	tr1::bind는 바로 이 묶기 작업을 맡았습니다.

	다시말해 ebg2의 체력치 계싼함수는 항상 currentLevel만을 GameLevel객체로 쓴다고 지정한거죠

	그다지 술렁술렁 설명하기 힘든 세부사항이 많이 남긴 했지만 넘어가려합니다
	"_1"은 ebg2에 대해 currentLevel과 묶인 GameLevel::health함수를 호출할 때 넘기는 
	"첫번째 자리의 매개변수"를 뜻한다는 점도  이런 세부사항중 하나죠.

	아무튼 우리는 함수 포인터 대신에 tr1::function을 사용함으로 써 
	사용자가 게임 캐릭터의 체력치를 계산할때 시그니처가 호환되는 함수호출성개체는
	어떤것도 원하는대로 구사할 수 있도록 융통성을 활짝 열어줬다 이겁니다.
	이거면 충분하죠 ? 인생 뭐 있나요

*/



/*
	*요약*
	- 비가상 인터페이스 관용구 (NVI 관용구)를 사용합니다.
		공개되지 않은 가상함수를 비가상 public맴버 함수로 감싸서 호출하는,
		템플릿 메서드 패턴의 한 형태입니다.
		(여기서 템플릿은 c++의 template와 전혀 연관없음)

	-가상 함수를 함수포인터 데이터 맴버로 대체합니다.
		군더더기 없이 전략패턴의 핵심만을 보여주는 형태입니다.

	-가상 함수를 tr1::function 데이터 맴버로 대체하여 호환되는 시그니처를 가진
		함수호출성 개체를 사용 할 수 있도록 만듭니다.:
			역시 전략 패턴의 한 예시입니다.
*/