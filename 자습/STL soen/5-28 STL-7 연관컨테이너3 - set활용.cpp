#include <iostream>
#include <time.h>
#include <string>
#include <vector>		//STL Vector
#include <list>			//STL List
#include <map>			//STL Map
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	
#include <iterator>		//여러 종류의 반복자의 정의 담음.
#include <deque>		//STL deque 정의 헤더
#include <set>


using namespace std;

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{
	set<string> s;
	string name;
	char ch;
	set<string>::iterator it;

	for (;;) 
	{
		cout << "1:삽입, 2:삭제, 3:보기, 4:검색, 5:종료 => ";
		cin >> ch;
		switch (ch) 
		{
		case '1':
			cout << "새 이름을 입력 하시오 : ";
			cin >> name;
			s.insert(name);
			break;
		case '2':
			cout << "삭제할 이름을 입력 하시오 : ";
			cin >> name;
			s.erase(name);
			break;
		case '3':
			for (it = s.begin(); it != s.end(); it++) 
				cout << *it << endl;
			break;
		case '4':
			cout << "검색할 이름을 입력 하시오 : ";
			cin >> name;
			cout << name << "이(가) " << (s.find(name) != s.end() ? "있" : "없")	<< "습니다." << endl;
			break;
		case '5':
			return 1;
		}
	}
	return 0;
}
