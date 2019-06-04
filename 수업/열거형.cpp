#include <iostream>

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;


enum MONSTER_STATE{ ATTACK , DEFENCE , MOVE};

int main()
{

	//열거체 변수
	MONSTER_STATE iState = ATTACK;//열거체 변수는 열거체의{}안에 있는 값만 가질수 있다.
	int a = ATTACK; //가능! ATTACK은 정수현태의 상수이므로 int에 대입가능
	//MONSTER_STATE iState =2 // Error  2는 int형이므로 MONSTER_STATE를 담을 수 없다.
	//

	switch (iState)	//열거체 변수는 정수로 인식한다.
	{
	case ATTACK:			//열거형에 나열된 값들은 상수로 인식한다.
		cout << "공격 패턴" << endl;
		break;
	case DEFENCE:
		cout << "방어 패턴" << endl;
		break;
	case MOVE:
		cout << "이동 패턴" << endl;
		break;
	}



	return 0;
}