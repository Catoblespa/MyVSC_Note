/*
                [브릿지 패턴 (가교 패턴)]
    추상층과 구현층을 분리시키고 이 둘의 결합을 동적으로 해결하는 패턴!
    추상층 (interface)   구현층 (Implementor)


                [브릿지 패턴을 사용하는 이유]

CUnit 이라는 클래스가 존재 할때
자식 클래스인 '보병' 클래스와 '기마병' 클래스가 있다고 하자.

만약 활들고 싸우는 병사를 만들려고 하는데 , 이 클래스가 보병일 수도있고 기마병일 수도있을때가 있을 수 있다.
그렇게 된다면 활을 들고 싸우는 보병클래스가 보병 또는 기마병을 상속 받는데 ,
이럴 경우 다중상속의 문제가 발생한다.


다중 상속의 문제를 해결하기 위해 우리는 클래스를 따로 설계하는 방법을 선택 할 수 있다.
2019-10-02-15-29-55.png
                        CUnit
        보병                        기마병
        활을쏘는 보병          활을쏘는 기마병
    
그러나 다시 창을 들고있는 유닛의 클래스를 설계하려고 하면.. 계속 클래스가 점점 늘어나게 된다!
하지만 이럴경우 클래스가 늘어나게 되며 관리(확장설계)하기 불편해진다.
여러한 것을 추상층이 정적이라고 한다.

이를 브릿지 패턴으로 해결해보록 하자.
*/
//브릿지 패턴을 사용하지 않은 일반적인 상속
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// #include <iostream>
// using namespace std;
// class CUnit
// {
// public:
// 	virtual void Update() = 0;
// };
// class CSoldier :public CUnit
// {
// public:
// 	virtual void Update()
// 	{
// 		cout << "보병입니다" << endl;
// 		cout << "------------------------" << endl;
// 	}

// };


// class CHorseRider :public CUnit
// {
// public:
// 	virtual void Update()
// 	{
// 		cout << "기마병입니다" << endl;
// 		cout << "------------------------" << endl;
// 	}
// };

// //CSwordMan은 구현부터  CSoldier이 되기 때문에 나중에 CHorseRider 로 바꿀 수없는 문제가 있다.
// class CSwordMan1 : public CSoldier			
// {
// public:
// 	virtual void Update()
// 	{
// 		cout << "검을 들고 싸우는" << endl;
// 		CSoldier::Update();
// 	}
// };
// //라이더로 스워드맨을 만드려면... 클래스가 늘어나게 된다!!		즉 개발은 느려질 수 밖에 없다.
// class CSwordMan2 : public CHorseRider			
// {
// public:
// 	virtual void Update()
// 	{
// 		cout << "검을 들고 싸우는" << endl;
// 		CHorseRider::Update();
// 	}

// };
////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <Windows.h>


using namespace std;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                //브릿지 패턴 적용
//구현층

class CImplementor
{
public:
	virtual void Update() = 0;

};


class CAttackArrow : public CImplementor
{
public:
	virtual void Update() override
	{
		cout << "활들고 싸우는" << endl;
	}

};
class CAttackSpear : public CImplementor
{
public:
	virtual void Update() override
	{
		cout << "창들고 싸우는" << endl;
	}

};

//추상층
class CUnit
{
public:
	CUnit(CImplementor * pImp)
		:m_pImp(pImp){}
	virtual ~CUnit()
	{
		delete m_pImp;
		m_pImp = nullptr;
	}

public:
	virtual void Update() = 0;

protected:
	CImplementor * m_pImp;

};




class CSolider : public CUnit
{

public:
	CSolider(CImplementor * pImp)
		:CUnit(pImp) {}

public:

	virtual void Update()
	{
		m_pImp->Update();
		cout << "보병입니다" << endl;
		cout << "============" << endl;
	}
};



class CHorseRider : public CUnit
{

public:
	CHorseRider(CImplementor * pImp)
		:CUnit(pImp) {}

public:

	virtual void Update()
	{
		m_pImp->Update();
		cout << "기마병입니다" << endl;
		cout << "============" << endl;
	}
};

int main()
{


	CUnit* pUnit1 = new CSolider(new CAttackArrow);
	pUnit1->Update();
	CUnit* pUnit2 = new CHorseRider(new CAttackArrow);
	pUnit2->Update();

	CUnit* pUnit3 = new CSolider(new CAttackSpear);
	pUnit3->Update();
	CUnit* pUnit4 = new CHorseRider(new CAttackSpear);
	pUnit4->Update();



	Sleep(10000);
	return 0; 
}
/*

추상층과 구현층을 서로 분리시켜 이 둘의 결합을 동적으로 처리하자.
따라서 확장설계가 아주 유연해진다.
*/