// ConsoleApplication2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//


/*
NVI 관용구는 public 가상 함수를 대신 할 수 있는 꽤 괜찮은 방법이지만,
클래스 설계의 관점에서 보면 눈속임이나 다름없다.

좀더 극적인 설계를 해본다면 캐릭터의 체력치를 계산하는 작업은
캐릭터 타입과 별개로 놓는 편이 맞을겁니다.
다시 말해 , 체력치 계산이 구태여 어떤 캐릭터의 일부일 필요가 없다는 말이다
한 예시로, 각 캐릭터의 생성자에 채력치 계싼용 함수의 포인터를 넘기게 만들고,
이 함수를 호출해서 실제 계산을 수행하도록 하면 되지 않을까?
*/

/*

*/

class GameCharacter_v1;

//채력치 계산에 대한 기본 알고리즘을 구현.
int defaultHealthCalc(const GameCharacter_v1& gc);

class GameCharacter_v1
{
public:
	typedef int(*HealthCalcFunc)(const GameCharacter_v1&);


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
	이방법은 주변에서 많이들 쓰고 있는 디자인 패턴인 전략(Strategy)패턴의
	단순한 응용 예이다.
	GameCharacter클래스 계통에 가상 함수를 심는 방법과 비교하면,
	꽤 재미있는 융통성을 갖고있습니다.

	같은캐릭터 타입으로부터 만들어진 객체 들도 채력치 계산 함수를 각각 다르게
	가질 수 있습니다. 즉, 이런게 가능하다는 거쥬 ?
*/

class EvilBadGuy : public GameCharacter_v1
{
public:
	explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc)
		: GameCharacter_v1(hcf)
	{}

};
int loseHealtQuickly(const GameCharacter_v1&);	//다른 동작원리로
int loseHealtSlowly(const GameCharacter_v1&);	//구현된 체력치 계산 함수들



int main()
{
	EvilBadGuy ebg1(loseHealtQuickly);
	EvilBadGuy ebg2(loseHealtSlowly);
	/*
		게임이 실행되는 도중 특정캐릭터에 대한 체력치 계싼 함수를 바꿀 수 있습니다.
		예를 들어 GameCharacter클래스에서 setHealthCalculator라는 맴버 함수를
		제공하고 있다면 이를 통해 현재 쓰이는 체력치 계산 함수의 교체가 가능해진다는 것이쥬

	*/
    return 0;
}


/*
하지만 빛이 닿는 곳 뒤에는 언제나 그늘이 있는법.

체력치 계싼함수가 이제 GameCharacter 클래스 계통의 맴버함수가 아니라는 점은,
체력치가 계산 되는 대상 객체의 비공개 데이터는 이함수로 접근 할 수 없는 뜻도 됩니다.
예를 들어 DefaultHealthCalc함수는 EvilBadGuy객체의 public맴버가 아닌 부분은
건드릴 수 없습니다.

뭐 그 캐릭터의 public 인터페이스로 얻은 정보만을 사용해서 캐릭터의 체력치를 계산할수 
있게 되어 있다면 문제가 없지만. 정확한 체력치 계싼을 위해서
public맴버가 아닌정보를 써야할 경우에는 문제가 발생한다.

뭐 friend를 사용하면 가능하긴 하지만. 은닉화는 지키고 싶잖아?

*/