#include <iostream>
#include <time.h>
#include <string>
#include <vector>		//STL Vector
#include <list>			//STL List
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	
#include <iterator>		//여러 종류의 반복자의 정의 담음.
#include <deque>		//STL deque 정의 헤더
#include <set>			//STL 연관컨테이너 set
#include <map>			//STL 연관컨테이너 map
#include <stack>		//STL 컨테이너 어댑터 stack
#include <queue>		////STL 컨테이너 어댑터 queue
#include <array>
#include <numeric>		//수치 관련 알고리즘 . STL이 아닌 C+라이브러리에 포함되어 있다.
#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;




int main()
{

	//#1. 입출력 스트림
	//스트림 : 데이터 통신에 필요한 가상의 연결 통로. 단방향 흐름을 갖는다.
	//표준 입력 스트림 : stdin
	//표준 출력 스트림 : stdout
	//입출력 스트림은 os가 알아서 할당 및 소멸 시켜준다.


	//#2 입출력 버퍼
	//데이터 송수신의 효율성 때문에 필요한 임시 공간


	//#3 단일문자 출력 함수
	//putchar , fputc	(f는 file의 약자)
			//putchar('1');			//stdout을 통해 모니터로 문자 출력
			//fputc('2', stdout);		//두번째 인자이 FILE을 주면 해당 파일에 출력한다.
			//						//putch와 달리 스트림을 지정 할 수있다. stdout은 모니터로 전송한다.

	//#4 단일문자 입력 함수
	//getchar , fgetc			//int getchar() : 입력받은 문자를 리턴  (FIFO)
	//함수 호출에 실패하거나 더이상 읽어올 문자가 없다면 EOF(End Of File == -1 )을 반환한다.
	//int ch = getchar();			//stdin(표준입력 스트림)을 통해 키보드로 부터 입력 받음.
			//putchar(ch);
			//ch = getchar();
			//putchar(ch);
			// ch = getchar();
			//putchar(ch);

			//int ch = fgetc(stdin); //스트림 지정 가능. 입력 대상이 키보드가 아닐 수도 있다.
			//fputc(ch, stdout);


	//#5 문자열 출력 함수
	//puts , fputs  (s는 string의 약자)

				//puts("Hello"); //stdout을 통해 문자열을 모니터로 출력  ,자동개행
				//fputs("Hello", stdout); //스트림 지정 가능, 자동 개행 X

	//#6 문자열 임력 함수
	//입력 버퍼로 부터 문자열을 문장 단위(\n)로 읽어오는 함수.
	//gets_s , fgets

	//gets_s(char배열 주소 , 배열크기)				//\n이 입력버퍼에 존재하나 읽어들이지 않고 버림
				//char szName[32] = "";
				//cout << "입력 :" << gets_s(szName, 32);	//stdin을 통해 문자열 입력
				//cout << "출력 :" << puts(szName);	//여기서 개행되는 이유는 puts가 개행하는거임.

	////fgets(char배열 주소, 읽어올 최대 길이, stream)	//이색긴 엔터(\n)도 읽어옴
				//char szName[32] = "";
				//cout << "입력 :" << fgets(szName, 32,stdin);		//size는 szName 끝에 담겨야할 null문자도 고려해야한다. 즉 31바이트까지 입력받을수 있는것.
				//												//스트림 지정 가능
				//cout << "출력 :" << fputs(szName,stdout);		//근데 이번엔 요놈이 개행안시켜쥼



	return 0;
}