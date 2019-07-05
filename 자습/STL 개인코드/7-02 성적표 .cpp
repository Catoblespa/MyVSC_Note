#include <iostream>
#include <vector>
#include <functional>
#include <iterator>		//여러 종류의 반복자의 정의 담음.
#include <algorithm>	//STL 알고리즘 헤더
#include <crtdbg.h>
#include <list>


using namespace std;


class Student
{
	struct Info
	{
		string name;
		int kor;
		int math;
		int eng;

		int sum;
		float avg;
		Info()
			:kor(0), math(0), eng(0), sum(0), avg(0)
		{};
		Info(string _name, int _kor, int _math, int _eng)
			:name(_name), kor(_kor), math(_math), eng(_eng), sum(_kor + _math + _eng), avg((_kor + _math + _eng) / 3.f)
		{
		}

		void SettingGrade()
		{
			sum = kor + math + eng;
			avg = sum / 3.f;
		}
	};
private:
	Info info;
public:
	Student() = default;
	Student(string _name, int _kor, int _math, int _eng) : info(_name, _kor, _math, _eng) {	}
	~Student() {}

	void PrintGrade()
	{
		cout << "이름 : " << info.name << endl;
		cout << "국어 : " << info.kor << endl;
		cout << "영어 : " << info.eng << endl;
		cout << "수학 : " << info.math << endl;
		cout << "총점 : " << info.sum << endl;
		cout << "평균 : " << info.avg << endl;
	}
	void PrintName()
	{
		cout << info.name << endl;
	}

	void setGrade()
	{
		cout << "이름 : ";
		cin >> info.name;
		cout << "국어 : ";
		cin >> info.kor;
		cout << "영어 : ";
		cin >> info.eng;
		cout << "수학 : ";
		cin >> info.math;
		info.SettingGrade();
	}

	Info& GetInfo()
	{
		return info;
	}

	bool operator==(const Student& str)
	{
		if (str.info.avg == str.info.avg)
			return true;
		else
			return false;
	}

	bool operator<(const Student & stu)
	{
		return info.avg < stu.info.avg;
	}
};


class teacher
{
private:

	list<Student*> stu;
	//Student* stu;
	//int size;
public:

	teacher()
	{
	}
	~teacher()
	{
		while (true)
		{
			if (stu.back() != nullptr)
				delete stu.back();

			stu.pop_back();
			if (stu.empty())
				break;
		}
	}


	int getSize()
	{
		return stu.size();
	}
	void SetSize(int _size)
	{
		stu.resize(_size);
	}

	void AddStudent()
	{
		stu.push_back(new Student);
		stu.back()->setGrade();
		this->SortStuforGade();
		SortStuforGade();
	}


	void AddStudent(string name, int  _kor, int _eng, int _math)
	{
		stu.push_back(new Student(name, _kor, _eng, _math));
		this->SortStuforGade();
		SortStuforGade();
		//stu.back()->setGrade();
	}

	void PrintStudents()
	{
		for (auto& st : stu)
		{
			st->PrintGrade();
			cout << "======================" << endl;
		}
	}

	void DelStudent()
	{
		int i = 0;
		for (auto& st : stu)
		{
			i++;
			cout << i;
			st->PrintName();
		}
		cout << "삭제할 학생의 번호를 입력 : ";
		int select = 0;
		cin >> select;
		for (size_t i = 0; i < select-1; i++)
		{
			stu.begin()++;
		}
		Student* temp = *(stu.begin());
		stu.erase(stu.begin());

		if (temp != nullptr)
			delete temp;
	}

	void findStudent()
	{
		string tname;
		cout << "찾으시는 학생의 이름을 입력 :";
		cin >> tname;

		for (auto& i : stu)
		{
			if (i->GetInfo().name == tname)
			{
				i->PrintGrade();
				cout << "======================" << endl;
				return;
			}
		}

		cout << "해당 학생의 정보를 찾지 못했습니다." << endl;
	}

	void SortStuforGade()
	{
		stu.sort();
		//sort(stu.begin(), stu.end());
	}

	//void Swap(vector<Student*>::iterator A, vector<Student*>::iterator B)
	//{
	//	auto Temp = *A;
	//	*A = *B;
	//	*B = Temp;
	//}
};


void Menu();

int MenuSelector();
int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//	_CrtSetBreakAlloc(250);      //누수 라인 중단점
	_CrtDumpMemoryLeaks();			//메모리 누수 출력 (디버그 모드)

	teacher * tc = new teacher;

	tc->AddStudent("김석현", 10, 20, 30);
	tc->AddStudent("정석현", 10, 20, 30);
	tc->AddStudent("이석현", 40, 30, 10);

	int selector = 0;
	while (true)
	{
		Menu();
		selector = MenuSelector();
		system("cls");
		switch (selector)
		{
		case 1:
			tc->AddStudent();
			break;
		case 2:
			tc->DelStudent();
			break;
		case 3:
			tc->PrintStudents();
			break;
		case 4:
			tc->findStudent();
			break;
		case 5:
			cout << "종료합니다. " << endl;
			delete tc;
			return 0;
			break;
		default:
			cout << "잘못된 선택입니다. 다시 선택해주세요" << endl;
			break;
		}
	}


	return 0;
}

void Menu()
{
	cout << " 학교 입니다 " << endl;
	cout << "==================" << endl;
	cout << "1. 학생 추가 하기  " << endl;
	cout << "2. 학생 삭제 하기  " << endl;
	cout << "3. 학생 모두 출력  " << endl;
	cout << "4. 학생 검색 하기  " << endl;
	cout << "5. 종료하기" << endl;
	cout << "==================" << endl;
}
int MenuSelector()
{
	int select = 0;
	cout << "선택할 매뉴 : ";
	cin >> select;
	return select;
}
