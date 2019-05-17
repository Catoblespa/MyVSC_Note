#include <iostream>
#include <string.h>
using namespace std;


class Cairplan
{
private:
	string m_cName;
	int m_ispeed;
public:
	//const char* Name
	//디폴트 생성자
	Cairplan()	
	{
		m_cName = "";
		m_ispeed = NULL;
	}

	//맴버 초기화 생성자.
	Cairplan(const string  Name,int ispeed=10)
	{
		m_cName = Name;
		m_ispeed = ispeed;
	}

	//복사 생성자.
	// 만들어 두지 않으면 디폴트 복사 생성자가 생기지만, 깊은 복사는 생기지 않는다.
	Cairplan(const Cairplan &Other)		// 항상 래퍼런스로 래퍼런스(&)로 받아와야만 한다.
	{
		m_cName = Other.m_cName;
		m_ispeed = Other.m_ispeed;
	}

	int getSpeed()
	{
		return m_ispeed;
	}
	void ViewPlan()
	{
		cout << "이름   : " << m_cName << endl;
		cout << "스피드 : " << m_ispeed << endl;
	}
};


int main()
{
	Cairplan Air1("1호기", 10);
	Cairplan Air2("2호기", 20);
	Cairplan TempAir(Air1);

	//정상적으로 TempAir에 Air1이 복사생성된다.
	TempAir.ViewPlan();

	return 0;
}
//===========================================================================================================================
//===========================================================================================================================

