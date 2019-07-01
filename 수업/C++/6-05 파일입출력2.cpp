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
	cout << endl;
	cout << "=======================SEEK======================" << endl;
	//#1 파일 지시자
	//FILE 구조체 내부에는 파일 지시자가 존재한다
	//파일 지시자의 역할은 파일의 내용을 읽거나 출력할 때 어디서 부터 시작할 것인지 현재 위치를 가리키고 있다.
	//파일 입출력 할 때마다 파일 지시자의 위치는 '항상' 양의 방향으로움직이며 갱신.
	FILE* fp = nullptr;
	errno_t err = fopen_s(&fp,/*상대경로*/"Data/test.txt", "rt");
	
	//			"Data/test.txt" "rt"
	//			1	2	3	4	5	6	7	8	9	EOF
	//			^
	//파일지시자가 여기부터 가르킴
	//int ch = fgetc(fp); 를 한번 시행하면 파일지시자는 2를 가르킨다.
	//ch = fgetc(fp); 다시 실행하면 파일지시자는 3을 가르키게 된다.
	//이렇게 쭉 읽다가 EOF을 읽어오게 되면 파일이 끝났다는 것을 알게된다.

	int ch = fgetc(fp); //1을 읽어옴
	ch = fgetc(fp);		//2를 읽어옴


	//#2 fseek 함수
	//파일 지시자의 위치를 제어하는 함수

	if (0 == err)
	{
		//SEEK_SET : 처음위치부터.  3 : "1 !Byte" 씩 !세칸 이동해라.
		fseek(fp, 3, SEEK_SET);		//출력은 4   = 1 -> 2 -> 3 -> 4 3번이동
		int ch = fgetc(fp);			
		putchar(ch);			//4를 출력하고나서 지시자는 5를 가르키고있다.
		cout << endl;
		cout << "------------------" << endl;
		
		//SEEK_CUR:현재 위치부터 ,0칸 이동해라.
		fseek(fp, 0, SEEK_CUR);
		ch = fgetc(fp);
		putchar(ch);			//5를 출력하고 6을 가르킨다.
		cout << endl;
		cout << "------------------" << endl;

		//SEEK_END : EOF자리부터
		fseek(fp, -3, SEEK_END);
		ch = fgetc(fp);
		putchar(ch);			//7를 출력하고 8을 가르킨다.

		cout << endl;
		cout << "------------------" << endl;

		//SEEK_END : EOF자리부터
		fseek(fp, 0, SEEK_CUR);
		ch = fgetc(fp);
		putchar(ch);			//8를 출력하고 9을 가르킨다.

		fclose(fp);
	}

	cout << endl;
	cout << "===================ftell함수======================" << endl;
	
	
	//#3 ftell함수.
	//현재 파일 지시자의 위치를 알려주는 함수.
	//파일 지시자 위치는 0번 인덱스 부터 시작.
	FILE* fp2 = nullptr;
	errno_t err2 = fopen_s(&fp2,/*상대경로*/"Data/test.txt", "rt");

	if (0 == err)
	{
		long index = ftell(fp);
		cout << "현재 지시자 위치 :" << index << endl;
		cout << endl;
		cout << "------------------" << endl;

		int ch = fgetc(fp2);
		putchar(ch);			//4를 출력하고나서 지시자는 5를 가르키고있다.
		cout << endl;
		cout << "------------------" << endl;

		index = ftell(fp);
		cout << "현재 지시자 위치 :" << index << endl;
		cout << endl;
		cout << "------------------" << endl;
		fclose(fp);
	}


	cout << endl;
	cout << "===================feof함수======================" << endl;
	//#4. feof함수.

	FILE* fp3 = nullptr;
	errno_t err3 = fopen_s(&fp2,/*상대경로*/"Data/test.txt", "rt");

	if (0 == err3)
	{
		int ch = 0;
		while (true)
		{
			ch = fgetc(fp);

			if (feof(fp)) // 현재 파일지시자가 eof에 도달했는지 체크하는 함수
				break;

			putchar(ch);
		}

		fclose(fp);
	}

	return 0;
}