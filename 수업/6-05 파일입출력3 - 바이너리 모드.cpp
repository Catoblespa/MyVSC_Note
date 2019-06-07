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



typedef struct MY_POINT {
	int x;
	int y;
};


int main()
{

	//#1 바이너리 모드 파일 입출력.
	//배열과 구조체와 같이 연속된 메모리 공간을 갖는 바이너리 데이터라면
	//한번에 입출력 할 수 있다!!
	int iArray[5] = { 10,20,30,40,50 };


	FILE* fp = nullptr;
	errno_t err = fopen_s(&fp, "../Data/test3.text", "wb");

	if (0 == err)
	{
		//바이너리 전용 Write 함수
		//내가 저장,출력하고 싶은 메모리의 첫 주소를 첫번째 인자로 주면 된다.
		//fwrite(메모리 첫주소, 원소 크기, 요소 갯수, 출력 스트림);
		fwrite(iArray, sizeof(int), 5, fp);
		//fwrite(iArray, sizeof(iArray), 1, fp);			위와 같은 결과이다.
		cout << "fp2 fwrite 개방 성공" << endl;
		fclose(fp);
	}
	else
		cout << "개방 실패" << endl;

	cout << "============================" << endl;


	//#2 바이너리 모드 파일 입력
	int iArray2[5] = {};


	FILE* fp2 = nullptr;
	errno_t err2 = fopen_s(&fp2, "../Data/test3.text", "rb");
	if (0 == err2)
	{
		fread(iArray2, sizeof(int), 5, fp2);
		cout << "fp2 fread 개방 성공" << endl;

		for (int i = 0; i < 5; i++)
		{
			cout << iArray2[i] << endl;
		}
		fclose(fp2);
	}
	else
		cout << "개방 실패" << endl;

	cout << "============================" << endl;

	MY_POINT tPosistion = { 100,200 };
	FILE* fp3 = nullptr;
	errno_t err3 = fopen_s(&fp3, "../Data/test4.text", "wb");
	if (0 == err3)
	{
		fwrite(&tPosistion, sizeof(MY_POINT), 1, fp3);
		cout << "fp3 fwrite 개방 성공" << endl;

		fclose(fp3);
	}
	else
		cout << "개방 실패" << endl;

	cout << "============================" << endl;



	FILE* fp4 = nullptr;
	errno_t err4 = fopen_s(&fp4, "../Data/test3.text", "rb");
	if (0 == err4)
	{
		fread(&tPosistion, sizeof(MY_POINT), 1, fp4);
		cout << "fp4 fread 개방 성공" << endl;

		cout << tPosistion.x << "," << tPosistion.y << endl;
		fclose(fp4);
	}
	else
		cout << "개방 실패" << endl;


	return 0;
}