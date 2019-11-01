#include <iostream>
#include <string.h>

using namespace std;


/*
  클래스는 string 헤더 파일에 정의되어 있으며 std 네임 스페이스에 포함되어 있다.

 string은 템플릿 기반의 클래스이므로 핵심 코드들은 거의 대부분 헤더 파일에 작성되어 있으며 이 헤더를 열어 보면 소스를 직접 볼 수 있다.
 헤더 파일에는 다음과 같은 basic_string이라는 클래스 템플릿을 정의하는데 선언문은 다음과 같다.



template<class _Elem, class _Traits = char_traits<_Elem>, class _Ax = allocator<_Elem> >

class basic_string { 멤버 목록 };

 _Ax 인수는 문자열 관리를 위한 메모리를 어떻게 할당하고 해제할 것인가를 지정하는 할당기이다.
		=디폴트인 allocator<_Elem>은 C++의 할당 연산자인 new, delete를 사용하는데 원한다면 다른 것으로 바꿀 수 있다

실제 프로그래밍에서는 첫 번째 인수로 문자의 타입만 밝히는 정도면 충분하다.
현재 문자를 표현하기 위해 사용할 수 있는 타입은 char, wchar_t 두 가지가 있는데
이 두 가지에 대해서는 다음과 같은 특수화 버전이 미리 선언되어 있다.

typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;


tring은 ANSI 문자열이며 wstring은 유니코드 문자열을 표현한다.
 두 클래스 모두 첫 번째 인수만 지정했으므로 디폴트에 의해 널 종료 문자열이며 new, delete로 메모리를 관리한다.

*/


/*
string 클래스는 모두 여섯 개의 생성자를 정의하고 있는데 원형은 다음 도표와 같다.
템플릿 함수들은 원형이 다소 복잡하므로  헤더 파일에 있는 선언문을 조금 편집하여 읽기 쉽게 정리했다

string 클래스의 생성자

원형													설명

string()											디폴트 생성자. 빈 문자열을 만든다.

string(const char *s)								널 종료 문자열로부터 생성하는 변환 생성자

string(const string &str, int pos=0, int num=npos)	복사 생성자

string(size_t n, char c)							c를 n개 가득 채움

string(const char *s, size_t n)						널 종료 문자열로부터 생성하되 n길이 확보

template<It> string(It begin, It end)				begin~end사이의 문자로 구성된 문자열 생성
*/

int main()
{
	string s1("test");								//s1 = test
	string s2(s1);									//s2 = test
	string s3;										//s3 =
	string s4(32, 'S');								//s4 = SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
	string s5("very nice day", 8);					//s5 = very nic
	const char* str = "abcdefghijklmnopqrstuvwxyz";	//
	string s6(str + 5, str + 10);					//s6 = fghij


	cout << "s1=" << s1 << endl;
	cout << "s2=" << s2 << endl;
	cout << "s3=" << s3 << endl;
	cout << "s4=" << s4 << endl;
	cout << "s5=" << s5 << endl;
	cout << "s6=" << s6 << endl;


	cout << endl;
	cout << endl;

	string s("C++ string");

	cout << s << " 문자열의 길이 = " << s.size() << endl;				// 널 종료 문자는 빼고 문자의 개수가 리턴된다.	length는 표준 이전
	cout << s << " 문자열의 길이 = " << s.length() << endl;			//											size는 STL이 표준
	cout << s << " 문자열의 할당 크기 = " << s.capacity() << endl;	//capacity함수는 객체가 할당한 메모리의 양을 조사 (널 포함)  즉, size값보다 항상큼
	cout << s << " 문자열의 최대 길이 = " << s.max_size() << endl;	//max_size 함수는 문자열 객체가 가질 수 있는 최대 길이
																	// 32비트 시스템에서 이 값은 unsigned의 최대값보다 1 작은 값

	s.resize(6);		//resize 함수는 문자열의 길이를 인수로 전달된 개수로 강제 조정한다. 
						//만약 n이 현재 크기보다 더 작으면 뒤쪽 문자열은 잘라 버리며 더 크면 NULL 문자로 채우되 두 번째 인수로 채울 문자를 지정할 수 있다. 
	cout << s << " 길이 = " << s.size() << ",할당 크기 = " << s.capacity() << endl;
	cout << s << endl;

	s.reserve(100);		//reserve 함수는 메모리의 여유분을 지정한 크기만큼 미리 확보한다.
	cout << s << " 길이 = " << s.size() << ",할당 크기 = " << s.capacity() << endl;
	cout << s << endl;


	/*
		void clear( );					//clear 함수는 문자열을 모두 지우는데 "" 빈 문자열을 대입하는 것과 효과가 같다.
		bool empty( ) const;			//empty 함수는 이 객체가 빈 문자열인지 조사하는데 "" 문자열 상수와 비교하는 것과 같으며
										//문자열의 길이가 0이면 true를 리턴한다.

	*/

	cout << endl;
	cout << endl;
	string Cs("char array");


	cout << " Cs.data()  :" << Cs.data() << endl;
	//data 함수는 string 객체의 네이티브 데이터 번지를 그대로 리턴하므로 널 종료 문자가 아닐 수도 있다
	cout << " Cs.c_str() :" << Cs.c_str() << endl;
	//c_str은 항상 널 종료 문자열이다. 
	//basic_string템플릿의 두 번째 인수 _Traits가 지정하는 문자열 관리 방식에 따라 문자열의 형태가 결정되므로 내부적인 형태가 항상 널 종료 문자열이라고 할 수 없다.



	char str2[128];
	strcpy_s(str2, Cs.c_str());
	printf("str2 = %s\n", str2);

	//문자열의 개별 문자들을 액세스하고 싶을 때는 [ ] 연산자 또는 at 멤버 함수를 사용한다. 
	//둘 다 첨자 번호를 인수로 전달받아 첨자 위치의 문자를 읽는다.
	//이 함수들은 상수 버전과 비상수 버전이 각각 준비되어 있다.
		//char& operator[](size_type _Off)
		//char& at(size_type _Off);
		//const char& operator[](size_type _Off) const
		//const char& at(size_type _Off) const;
	//[ ] 연산자와 at 함수는 기능이 거의 동일한데 인수로 주어진 첨자의 문자를 읽되 레퍼런스가 리턴되므로 좌변에 사용하여 값을 변경하는 것도 가능하다.
	cout << endl;
	cout << endl;

	string str3("korea");
	size_t len;

	len = str3.size();
	for (int i = 0; i < len; i++) 
		cout << str3[i];

	cout << endl;
	str3[0] = 'c';

	for (int i = 0; i < len; i++)
		cout << str3.at(i);

	cout << endl;
	cout << endl;
	//string 객체에 다른 문자열이나 문자를 대입할 때는 = 연산자를 사용한다.
		//string& operator=(char ch);
		//string& operator=(const char* str);
		//string& operator=(const string & other);

	//단일 문자, 문자열 상수 또는 다른 string 객체를 대입할 수 있는데 상식적으로 문자열에 대입할만한 모든 것들을 다 대입할 수 있다고 보면 된다.
		//string& operator+=(char ch);
		//string& operator+=(const char* str);
		//string& operator+=(const string & other);

	//str객체의 off 위치에서 count개수만큼만 대입하거나 연결한다. = 연산자가 표준 strcpy 함수라면 assign은 strncpy 함수에 해당한다
		//string& assign(const string & _str, size_t off, size_t count);
		//string& append(const string & _str, size_t off, size_t count);

	//다음 두 함수는 문자 배열에 문자열을 복사하거나 string 객체끼리 교환한다.

		//copy 함수는 _Ptr 문자 배열에 객체의 _Off 위치에 있는 문자들을 _Count 개수만큼 복사한다.
		//size_type copy(value_type* _Ptr, size_type _Count, size_type _Off = 0) const;	

		//wap함수는 이름 그대로 두 문자열의 내용을 교환하는데 이때 두 객체의 메모리는 자동으로 관리된다.
		//void swap(basic_string& _Str);

	//문자열의 일부를 삭제하는 함수이다.
	//	string& erase(size_t pos = 0, size_t count = npos);

	//문자열 중간에 다른 문자 또는 문자열을 삽입하는 insert 함수
	//insert


	//string 비교
		//int compare(const string& str) const;														//두 문자열 객체 전체를 비교
		//int compare(size_t pos, size_t num, const string& str) const;								//호출 객체의 일부를 str 전체와 비교
		//int compare(size_t pos, size_t num, const string& str, size_t off, size_t count) const;	//호출 객체 일부와 str의 일부

	//string 객체에서 부분 문자열이나 특정 문자가 어디에 있는지를 찾는 검색 함수
		//size_t find(char ch, size_t off = 0) const;
		//size_t find(const char* ptr, size_t off = 0) const;
		//size_t find(const char* ptr, size_t off = 0, size_t count) const;
		//size_t find(const string& str, size_t off = 0) const;

	cout << endl;	
	cout << endl;	
	string str4("string class find function");
	string str5("func");

	cout << "i:" << str4.find('i') << "번째" << endl;
	cout << "i:" << str4.find('i', 10) << "번째" << endl;
	cout << "ass:" << str4.find("ass") << "번째" << endl;
	cout << "finding의 앞 4:" << str4.find("finding", 0, 4) << "번째" << endl;
	cout << "kiss:" << str4.find("kiss") << "번째" << endl;
	cout << str5 << ':' << str4.find(str5) << "번째" << endl;


	return 0;
}