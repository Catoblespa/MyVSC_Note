

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
