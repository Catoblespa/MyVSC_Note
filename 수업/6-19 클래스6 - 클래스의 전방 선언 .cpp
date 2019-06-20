
/////////////////////////////////////////////////CPlayer.h///////////////////////////////////////////////////////
#pragma once
//#include "CMonster.h"

class CMonster;

class CPlayer
{
private:
	CMonster* mon;
public:
	CPlayer();
	~CPlayer();
	void Func();
};



//////////////////////////////////////////////////CPlayer.cpp////////////////////////////////////////////////////////////
#include "CPlayer.h"

//cpp에 CMonster.h를 인클루드 하면!!! 된다!!!
#include "CMonster.h"


CPlayer::CPlayer()
{
	//메모리의 크기 모르니까 이것도 불가능
	//cpp에서 #include "CMonster.h" 를 해주면 쌉가능!!
	mon = new CMonster;
}

CPlayer::~CPlayer()
{

	delete mon;
}

void CPlayer::Func()
{
	mon->Func(); // 
}






/////////////////////////////////////////////////CMonster.h///////////////////////////////////////////////////////
#pragma once
//#include "CPlayer.h"


class CPlayer; //전방선언

class CMonster
{
private:
	//전방선언 만으로는 해당 클래스의 메모리를 알 수없으므로 포인터로 선언
	CPlayer* player;

public:
	CMonster();
	~CMonster();

	void Func();


};



//////////////////////////////////////////////////CMonster.cpp////////////////////////////////////////////////////////////
#include "CMonster.h"
#include "CPlayer.h"


CMonster::CMonster()
{
	player = new CPlayer;
}


CMonster::~CMonster()
{
	delete player;
}

void CMonster::Func()
{
}





//////////////////////////////////////////////////Main/////////////////////////////////////////////////////////
#include <iostream>

#include "CPlayer.h"
#include "CMonster.h"

using namespace std;

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.
/*
CP.h 에서는 CM.h를 참조하고
CM.h 에서는 CP.h를 참조하면 
상호 참조로 인한 무한루프에 빠지게 된다.

이걸 해결하기 위한 '전방선언'을 사용 할 수있다
그러나 전방선언은 클래스 이름만 알려줄뿐.
해당 클래스의 크기나 함수를 알려주지 않는다.
그러므로 전방선언한 헤더에서는 CPlayer player 처럼 선언 할 수없다.

선언을 하려면 메모리 크기가 명확한 CPlayer *player 로 선언해야한다.

예를들어서 CPlayer.h 에서 CMonster객체를 선언하고 싶으면
CPlayer.h에서 class CMonster으로 전방선언 후,
Cplayer.cpp 에서 CMonster.h 를 인클루드 한다. 이래 되면 CPlayer에서는 CMonster의 크기를 알 수 있다.
CPlayer.h에서 맴버변수 CMonster *CM으로 포인터형으로 선언한 뒤 , 생성자에서 동적할당후 사용하도록 하자.
단, CPlayer.h에서 Monster를 상속받는 행위는 안됨.

*/

int main()
{

}