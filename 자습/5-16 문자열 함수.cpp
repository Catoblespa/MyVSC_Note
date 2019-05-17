#include <iostream>
#include <string.h>			//문자열에 대한 함수를 사용하기 위해 추가
using namespace std;



/*

char str1[16];
char str2[16];  일때

str1="Korea";                   // 문자열 상수를 대입할 수 없음
str1=str2;                      // 배열끼리도 대입할 수 없음
str3=str1+str2;					// +연산자로 문자열을 연결할 수 없음
if (str1 == str2)				// ==연산자로 문자열끼리 비교할 수 없음*/
int main()
{
	char str1[30] = "Hello World";
	char str2[30] = "안녕하세요?!";
	char strTemp[30];

	
	//erron_t strcpy_s ( char * dest, size_t size, const char * source )
	//dest : 문자열을 복사할 버퍼		size dest : 버퍼의 크기  source : 복사할 원본 문자열.
	strcpy_s(strTemp, sizeof(strTemp), str1);
	cout << "strcpy_s(strTemp, sizeof(strTemp), str1) 결과 : " << strTemp << endl;		//"Hello World" 출력.
	//puts(strTemp); //를 사용해서 출력 할수도 있음.

	//=========================================================================================================
	//strncpy_s(char * dest, const char * source, size_t count);
	//source를 dest로 복사하되, count 만큼 복사한다. // 복사하고 남은 나머지공간은 NULL로 체워진다.
	strncpy_s(strTemp, str2,6);		
	puts(strTemp);
	

	//strlen(strTemp) : 문자열의 길이를 반환한다.
	cout << strlen(strTemp) << endl;

	//=========================================================================================================
	//char* strcat(char* dest, const char* src);
	//char* strncat(char* dest, const char* src, size_t count);
	//문자열을 합치는 함수이다. strncat은 src의 count 길이만큼 합친다.

	strcat_s(strTemp, "살법!");
	cout << strTemp << endl;



	//=========================================================================================================
	//int strcmp(const char* s1, const char* s2);
	//int strncmp(const char* s1, const char* s2, size_t count);
	//  "ABC"와 "ABC"는 같다.비교 결과는 0이다.
	//	"ABC"는 "ABD"보다 작다.비교 결과는 음수이다.
	//	"ABC"는 "ABB"보다 크다.비교 결과는 양수이다.

	if (!strcmp(str1, str2))
	{
		cout << "서로 다른 문자입니다!" << endl;
	}


	//char* strchr(const char* string, int c);					//strchr 함수는 문자열중에 c라는 문자가 있는지를 찾아 그 포인터(주소값)를 리턴한다. 
																// 만약 c가 존제 하지 않을 경우 NULL을 리턴한다.
	//char* strrchr(const char* string, int c);					//strchr은 str[0]부터 검색하고 , strrchr은 배열의 끝부터 검색한다.
																//strchr을 이용하여 특정 문자의 갯수를 구할 수 있다.
	//char* strstr(const char* string, const char* strSearch);  //strstr은 string에서 strSearch와 일치하는 '문자열의 시작 주소' 을 찾는다.
	//char* strpbrk(const char* string, const char* strCharSet);//이 함수는 첫 번째 인수로 주어진 문자열에서 두 번째 인수로 주어진 
																//문자열에 속해 있는 문자 중 가장 먼저 발견된 문자를 찾아 그 번지를 리턴한다. 
	//char* strtok_s(char* strToken, const char* strDelimit);
	//strtok 함수는 문자열을 토큰으로 잘라낸다.예를 들어 "서울/대전/대구/부산" 문자열을
	//"/" 구분자로 자르면 서울, 대전, 대구, 부산 4개의 문자열로 분할할 수 있다.
	//첫 번째 인수로 잘라낼 문자열을 주며 두 번째 인수로 구분자를 구성하는 문자열을 준다.
	//구분자는 한 문자열에 여러 개를 지정할 수 있는데 / 와 :그리고, 가 토큰 구분자라면 "/:,"를 준다

	char str3[50] = "123_456\t789 abc";

	char* token[4], * context;
	token[0] = strtok_s(str3, "_", &context);
	token[1] = strtok_s(NULL, "\t", &context);
	token[2] = strtok_s(NULL, " ", &context);
	token[3] = strtok_s(NULL, " ", &context);
	for (auto& i : token)
	{
		int b = 0;
			
		cout << "token[" << b << "] : " << i << " " << endl;
		b++;
	}

	return 0;
}