#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>


using namespace std;

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.


int main()
{
	//#1. 파일 입출력 (데이터 불러오기, 저장)
	//콘솔 입출력은 사용시 표준 입출력 스트림을 운영체제가 알아서 할당 및 소멸 해줬었다.
	//파일 입출력은 사용시 입출력 스트림을 운영체제에게 할당 및 소멸을 요청해야한다.

	//#2 파일 출력 (데이터 저장)
	//파일출력 스트림 생성 요청 ("파일 개방"이라고도 한다)
	FILE* fp = nullptr;			//FILE자체가 포인터다. fp는 결론적으로 더블 포인터가 된다.
	//
	//fopen에 &fp로 전달해야한다... 왜 ? 보니까 fopen_s 자체가 fp를 더블포인터로 받는 매개변수이다.
	//errno_t err = fopen_s(&fp,/*절대경로*/"C:/Users/a4ka2/source/repos/자습/자습/Data/test.txt","wt");			
	errno_t err = fopen_s(&fp,/*상대경로*/"Data/test.txt","wt");					//절대경로보단 상대경로를 쓸것. 
	//wt : wirte text (텍스트형식으로 작성)  wb : write birary (바이너리형식으로 작성)	//절대경로는 프로젝트 파일이 이동하면 변경해줘야함..
	//rt :read text ,  w로만 하면 wt / r만하면 rt 기본은 text다.						//상대경로는 프로젝트위치부터 시작함.
	//파일 이름만 줄경우, 프로젝트와 같은 경로안에 있는 파일을 뜻한다.					//비쥬얼 스튜디오에서 실행할경우 프로젝트에서 실행되므로
	//errno_t err : int타입이다. 파일여는데 성공하면 0, 실패하면 0이아닌 값을 반환한다.	//../ 을 쓰면 프로젝트의 상위경로인 sln이 있는 폴더에 저장되고
	//만약 해당 스트림 위치 text.txt가 없을경우 새로 생성하여 저장한다.					//../ 을 빼면 project가 있는 폴더에 저장된다.
																					//만약 exe로 실행하게 되면 
																					//exe가 Debug에 있으므로, ../을 쓸때 project폴더에 저장되고
																					//../을 빼면 exe위치인 Debug폴더에 생성된다
	if (0 == err)
	{
		fputs("Hello World",fp);
		cout << "저장 성공" << endl;


		//스트림 소멸 요청
		fclose(fp);
	}
	else
	{
		cout << "개방 실패" << endl;
	}
	cout << endl;
	//##3 파일 입력 (데이터 불러 오기)
	FILE* pf2 = nullptr;
	errno_t err2 = fopen_s(&fp, "Data/test.txt", "rt");
	if (err ==0)
	{
		char szInput[32] = "";
		fgets(szInput, 32, fp);

		cout << szInput << endl;
		cout << "불러오기 성공! " << endl;
		fclose(fp);

	}
	else
	{
		cout << "불러오기 실패!" << endl;
	}


	//#4. 개방모드
	//w (write) : 출력 (덮어쓰기)		: 기존 파일이 없다면 새로 생성함.
	//a (append) : 출력 (이어쓰기)	: 기존 파일이 없다면 새로 생성함. 있다면 이어씀
	//r (read)  :  입력				: 파일이 없으면 Error

	//t	(text mode)			: 사람이 식별할 수 있는 텍스트 형식으로 파일 입출력
	//b	(binary mode)		: 텍스트로 표현 할 수 없는(동영상, 음원,이미지 등) 형식의 파일 입출력
						//속도측면에서 text보다 바이너리가 빠르다. text는 바이너리->text로 변환해야하기 때문.



	//#5 파일의 끝은 EOF로 검사햐야한다.

	//cout <<"asdasd"<< endl;
	cout << endl; 
	FILE* fp3 = nullptr;
	errno_t err3 = fopen_s(&fp3,/*상대경로*/"Data/test.txt", "rt");
	if (0 == err3)
	{
		int ch = 0;
		while (true)
		{
			ch = fgetc(fp3);
			////\0(널문자)로 검사하면 안됨! 파일 출력할때 널문자는 저장되지 않기 때무니!
			//if ('\0' == ch)			
			//	break;

			if (EOF == ch)
				break;

			putchar(ch);

		}
		cout << "모두 읽기 성공!!" << endl;
		fclose(fp3);
	}
	else
		cout << "개방실패!" << endl;

	return 0;
}