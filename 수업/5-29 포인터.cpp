

	//**TIP **
	int iA =10 , iB =20;

	int* ptr = nullptr;

	if (nullptr != ptr)         //포인터 사용할때는 반드시 null 체크를 하도록하자.
		*ptr = 100;

    //포인터가 널 값을 갖고 있을때 참조-수정이 일어나면 , 심각한 에러가 난다. 

	//cosnt와 포인터************************************************************************
	
	const int* ptr1 = &iA;	//이때 const는 ptr1을 상수화 시키는게 아니라, ptr1를 통한 참조로 원본값을 변경 못하게 하는 것이다
	*ptr1 = 200;	//에러	
	ptr1 = &iB;		//가능.
	*ptr1 = 100		//에러

	int * const ptr2 = &iA;	// ptr2을 상수화 하여, ptr2을 값을 변경 불가능하게 한다.

	*ptr2 = 200;    // 가능
	ptr2 = &iB 	    // 에러

	const int * const ptr3 =&iA;
	*ptr3 = 200;	//에러
	ptr3 = &iB;		//에러

	const int iC = 200;
	const int *pt4 = &c;		//가능
	int *ptr5 = 200				//에러


	int iArr[10];
	cout << iArr << endl;   // 배열의 이름은 포인터다. (주소값을 갖는다.)
	iArr = &iA		//에러.  배열의 이름은 상수 포인터다.


//=============================

	int iArr2D[2][3]=
	{
		{10, 20, 30},
		{40,50,60}
	};
	cout << iArr2D<<endl;
	cout << iArr2D+1 <<endl;  	//이중 포인터인 iArr2D의 주소와 iArr2D +1 은 12바이트 움직인 크기로 나타난다.
								//12바이트 움직인 근거는 iArr2D의 열의 길이((intbyte) *3)만큼 움직인 것이다.

	int (*ptr)[3] = iArr2D ;   // 이차원 배열을 포인터로 받기 위해서는 배열의 열의 크기를 알려줘야한다!!!

	cout << ptr[1][2] <<endl;  //60 출력
								//ptr[1][2]해석 : 시작주소로부터 열의 크기만큼 1번 이동하고 , 타입크기만큼 2칸 이동해라.
	cout << *(*(ptr+1)+2) <<endl; // ptr[1][2]와 같은 출력값.
	cout << sizeof(ptr[1]) <<endl; // 12출력 : 1행의 총 크기가 반환
	cout << sizeof(ptr[1][0]) <<endl; // 4출력 : 1행 0번째 값의 크기 반환.


	char szName[5] = {'H','e', 'l', 'l', 'o'};
	cout <<szName<<endl;		// Hello~쓰래기값~
	//cout은 szName의 길이를 알지 못하지 때문에 문자열배열에는 끝을 표시해줘야한다.
	   
	char szName2[6] = {'H','e', 'l', 'l', 'o' , '\0'};
	cout <<szName2<<endl;		// Hello
	//cout은 char*을 만나면 이주소로부터 null문자를 만나기 전까지 출력한다.   null 문자 = '\0'

	char szName3[6] = "Hello";  // 이렇게 초기화 할경우 szName3는 마지막에 자동으로 \0가 삽입된다.
	cout <<szName3<<endl;		// Hello

	const char* zsPName = "Hello";

	cout << zsPName << endl; //Hello
	cout << (int*)zsPName << endl;		//00929B30 같은 주소를 같게 되는데 그 이유는 컴파일러가 상수를 Data영역에 문자배열로 등록되기 때문이다.
	cout << (int*) "Hello" << endl;		//00929B30


	//char* pInput;							//불가능!! 입력받지 않아서 정상적인 메모리를 나타낼수 없음
	//char * pInput == nullptr 	// 같은 이유로 불가능!
	char pInput[6] = "";				//문자열을 입력 받고 싶을땐 이렇게 할것.
	cin >> pInput;
	cout << pInput << endl;









	//#1 문자열 길이 구하는 표준 함수 <string.h> 에서 제공
	//null문자를 제외한 순수 문자열 길이를 구한다.
	// size_t strlen(const *char)

	char szName[6] = "World";
	cout << "길이 : " << strlen(szName) << endl;
	cout << "메모리 크기 : " << sizeof(szName) << endl;

	//strcmp(cosnt char *, size , const char *) 문자열 비교하는 표준함수
	// 같으면 0을 반환 ,다르면 0이 아닌수를 반환.


	//strcpy_s (cosnt char *ch1, int size , const char *ch2) 문자열을  ch2를 ch1으로 복사한다.
	//ch1이 배열의 이름일 경우 size를 안넣어줘도 된다.
	//ch1에 크기는 ch2의 크기만큼 넉넉 해야한다.
	char szName_1[32] = "";
	char szName_2[32] = "Hello";
	strcpy_s(szName_1,sizeof(szName_2), szName_2);
	cout << szName_1 << endl;
	cout << szName_2 << endl;

	char* ptr = szName_1;
//	strcpy(pty, szName_2); 에러!




	//memcpy (dst , src, size)
	//메모리 대 메모리 간의 값 복사 함수
	//src로부터 size만큼 dst에게 복사한다.
	//복사 수행 과정 중에 임시 버퍼를 거치지않는다.


	int iArr_1[5] = {};
	int iArr_2[5] = { 10,20,30,40,50 };

	memcpy(iArr_1, iArr_2, 16);	//40까지 복사됨.

	for (int i = 0; i < 5; i++)
	{
		cout << "iArr_1[" << i << "]:" << iArr_1[i] << endl;
		cout << "iArr_2[" << i << "]:" << iArr_2[i] << endl;
		cout << "=======================================" << endl;
	}


	// memmove 함수
	// memmove (srd로 부터 size만큼 dst에게 복사(이동)한다
	// memcpy와 다르게 버퍼를 거치므로 조금더 느리다.
	// 복사를 수행하는데 메모리가 겹치는 구간이 있다면 memcpy보다 memmove를 써야한다.
	// 만약 겹치는 구간에 memcpy를 사용하면 VS에서는 사용가능하지만, 다른 환경에서는 에러가 난다.
	memmove(iArr_2, iArr_2 + 1, 16);
	for (int i = 0; i < 5; i++)
	{
		cout << "iArr_2[" << i << "]:" << iArr_2[i] << endl;
		cout << "=======================================" << endl;
	}

	return 0;