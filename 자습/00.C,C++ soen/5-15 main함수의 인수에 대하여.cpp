// 난수 생성시 유용함.

#include <iostream>
#include <time.h>

using namespace std;

//main 의 argc는 운영체제가 main에게 전달한 실제적인 데이터를 가진 인수의 수다.
//argc는 사실상 유효한 데이터를 갖는 인수의 개수를 저장하기 위한 인수로, 카운트 하지 않는다.
//argv[0]는 항상 해당 exe가 실행되는 절대경로를 저장된다.
//argv의 타입이 *argv[] 인 이유는 여러개의 문자열배열이기 때문이다. [0]은 exe의 위치이다
//프로그램으로 전달된 첫 번째 인수는 argv[1]이며 두 번째 인수 이후부터 argv[2], argv[3] 식으로 전달된다.
//boksa file1.txt file2.txt 명령으로 boksa명령을 실행했다면 이때 전달되는 argv 배열은 다음과 같다.
//ene :프로그램으로 전달된 실제 인수값이며 이 값을 읽으면 운영체제로부터 어떤 인수가 전달되었는지 알 수 있다.



int main(int argc, char* argv[], char* env[])
{
	int i;

	printf("전달된 인수의 개수 = %d\n", argc);

	for (i = 0; i < argc; i++)
	{

		cout << i << "번째 인수 =" << argv[i] << endl;

	}
	return 0;
}

