#include <iostream>
#include <string>

using namespace std;



int main()
{

	//##1 string class	
	string str1 = "Hello";		//인자있는 생성자 호출
	string str2 = str1;			//복사생성자 호출
	string str3;				//디폴트 생성자 호출
	string str4 = "World";
	str3 = str2;				//대입연산자 호출
	str4 = "World!!!!!!";		//대입연산자 호출

	//string 객체와 문자열 간 덧셈 및 축약 연산가능
	str1 = str1 + str4;			
	str1 += str4;
	cout << str1 << endl;

	if (str1 == str4)		//객체간 비교 가능
		cout << "str1과 str4는 같습니다" << endl;
	else
		cout << "str1과 str4는 다릅니다." << endl;


	if (str1 == "Hello")	//객체와 문자열 간 비교
		cout << "str1과 Hello는 같습니다" << endl;
	else
		cout << "str1과 Hello는 다릅니다." << endl;


    string str = "Hello";
    // char * ptr = str;           //불가능
    const char * ptr = str.c_str();     //가능
    cout << ptr <<endl;

	return 0;
}