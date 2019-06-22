#include <iostream>


using namespace std;



//#1 상속
// 상속은 항상 is -a 관계여야 한다.

class CPerson
{

private:	//private로 정의된 것들은 상속받지 못한다 (자식 클래스에서 접근 불가능 ) :
	char m_szName[32];
	int m_iAge;

protected: //클래스 외부에서 접근할 수 없지만, 상속받은 클래스에서는 접근 할 수 있다.

public :
	CPerson() = default;
	CPerson(const char* pName, int iAge ) : m_iAge(iAge)
	{
		strcpy_s(m_szName, pName);
		cout << "CPerson" << endl;
	}
	~CPerson()
	{
		cout << "CPerson 뒤짐" << endl;
	}

	void WhatYourName()
	{
		cout << m_szName << endl;
	}
	void WhatYourAge()
	{
		cout << m_iAge << endl;
	}

};

class CStudent : public CPerson
{
private:
	char m_szMajor[32];

public:
	CStudent(const char* pName, int iAge, const char* szMajor) : CPerson(pName, iAge)
	{
		strcpy_s(m_szMajor, szMajor);
		cout << "CStudent" << endl;
	}
	~CStudent()
	{
		cout << "CStudent 뒤짐" << endl;

	}
	void WhatYourMajor()
	{
		cout << m_szMajor << endl;
	}
};


class CWorker : public CPerson
{
private:
	char m_szMajor[32];

public:
	CWorker(const char* pName, int iAge, const char* szMajor) : CPerson(pName, iAge)
	{
		strcpy_s(m_szMajor, szMajor);
		cout << "자식" << endl;
	}

	~CWorker()
	{
		cout << "자식 뒤짐" << endl;
	}

	void WhatYourMajor()
	{
		cout << m_szMajor << endl;
	}
};
//자식 객체 생성 과정 : 메모리 할당 -> 부모 생성자 -> 자식 생성자
//자식 객체 소멸 과정 : 메모리 할당 -> 부모 소멸자 -> 자식 소멸자

int main()
{
	CPerson person("John", 32);
	//person.WhatYourAge();
	//person.WhatYourName();

	CStudent student("kim", 20, "GameProgramming");

	//student.WhatYourAge();
	//student.WhatYourMajor();
	//student.WhatYourName();


	return 0;
}