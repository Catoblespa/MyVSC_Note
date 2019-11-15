

//TODO :hlsl을 작성하기 위한 파일
//정점의 위치에 행렬을 곱해서 스페이스를 변환시켜주는 작업 (함수 ) ://VS  : Vertex Shader


//float	vTmp1;
//float2	vTmp2;
//float3 vTmp3;
//float4 vTmp4;;
//vector vTmp5//float 4개를 사용하는 데이터 타입.
//(참고로 GPU는 부동소수점 벡터를 처리하는데 최적화된 장치입니다. 
//따라서 쉐이더에서 사용하는 기본적인 데이터형은 정수가 아닌 부동소수점입니다. 
//정수는 오히려 쉐이더의 성능을 저하시키는 요인입니다.)


//float2	vTmp2;
//
//vTmp2.xy = 10.f; // vTmp2안에 있는 x , y값에 10.f를 채운다.
//vTmp2.rg = 10.f; //vTmp2 안에 r , g 값에 10.f을 채운다.
//				//hlsl은 x y z w 와 r g b a 가 똑같이 대응되어 위의 두 문장은 문법적으로 같은 뜻이다.

//일단 우리가 일반적인 폴리곤을 그리기 위한 작업을 만들어보자.
//그럴려면 일단 인자 값으로 내가 그릴려고 하는 정점의 정보를 인자값을 받아와야한다. 

//셰이더에서 MAIN 의 인자를 받아올때 해당 변수가 어떤 값을 받아올건지 이미 정의 해줘야한다.
//만약 정점의 위치를 받아올고면 위치를 받을 것이라고 알려줘야 잘들어간다.
//그것을 '시멘틱' 이라고 한다.
//그러면 쉐이더에 넣어준 정점 정보중 인자에 정확히 맞는 정보만 알아서 들어간다.
//시멘틱을 정해줬는데 Clinet에서 매치되는 정보를 안넘겨줄경우 0이 들어간다!
//! VS_MAIN(float3 vPosition : POSITION , float3 NOrmal : NORMAL , long Color : COLOR)



//! 정점구조체를 받아고 위해 struct를 만들어서 받아 올수도 있다!
struct VS_IN {
	float3 vPosition : POSITION;	//정점의 위치 벡터이므로 Vector3이 대응되는 float3로 선언		컬러값 시멘틱 : POSITION
	int Color : COLOR;				//Color값은 정수형이니까 int형을 사용..   컬러값 시멘틱은  : COLOR
};

struct VS_OUT {
	float4 vPosition : POSITION;	//이녀석은 반드시 float4를 뱉어야한다.
	int Color : COLOR0;				//우리가 여기서 투영행렬을 곱해서 w위치에 viewSpace에서의 z값을 저장해놓기 때문
									//정점 셰이더에서는 뷰포트 변환이전까지만 작업하기 떄문에 반드시 w값을 리턴해줘야한다.
	float4 vWorldPos :COLOR1;		//픽셀 셰이더에서 월드좌표로 이용하기 위해 월드좌표를 저장해서 사용하자!
									//TODO 버텍스 셰이더에서 픽셀셰이더에서 이용할 정보를 뽑아서 버텍스 구조체를 바꿔버리는 역할도 한다

};									

//행렬은 float4x4 으로 선언할 수도 있다.
//client에서 행렬을 받아오기 위한 행렬 전역변수.
//TODO 전역변수들 : 컨스턴트테이블. 이라고 부른다.
//TODO 셰이더에서 선언되는 모든 전역변수는 상수다.
//TODO 즉 선언하고 클라이언트에서 값을 받아오기만 할뿐, 절대 값을 변경할 수 없다!!!!
matrix g_matWorld, g_matView, g_matProj;

//VS_MAIN 은 정점 정보를 인자로 받고 정점정보를 리턴해줘야한다!
VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT  Out =(VS_OUT)0;		//VS_OUT임시구조체를 만들고 이걸 0으로 만들고 Out에 대입해준다..
								//주의 VS_OUT(0) 이건 안된다!!
	//float3 vTmp = (float3)0.f;	//이것도 된다.
	//float3 vTmp = float3(0.f);	//이건 안된다.
	//float 3 vTemp = float(0.f, 0.f, 0.f);//이건 된다 ;


	//여기서 In.vPosition은 버텍스는 Local값이다.
	//DrawPrimitive에서 정점을 하나 던져주면 정점을 하나하나씩 계산한다.
	//정점버퍼에서 그대로 꺼내서 받아온거니까 당연히 Local이죠 ?
	//이제 정점에 월드 행렬을 곱해줘야하는데 
	//이걸 받아오는 방법중 하나는 월드행렬을 셰이더에서 전역변수로 선언하는것이다.
	//전역변수로 선언하면 Client와의 소통이 가능하다.



	vector vPosition;
	//월드 변환
	//float3를 float 4로 변환!  -> 이제 1-4 행렬과 4-4 행렬의 곱을 실시하고 1-4행렬을 리턴한다.
	vPosition = mul(float4(In.vPosition,1.f), g_matWorld);		// mul() 모든 행렬과 행렬의 곱을 수행하는 함수이다. 수리적으로 곱셈이 가능한 행렬 두개가 있을경우 알아서 곱해준다!
	vPosition = mul(vPosition, g_matView);	//위에서 
	vPosition = mul(vPosition, g_matProj); 

	Out.vPosition = vPosition;
	Out.Color = In.Color;

	return Out;
}

//여기서 Out값은 투영행렬까지 적용한 값을 뱉어주면된다. 이제 디바이스가 밑의 나머지 처리를 알아서 한다.
// 1.  Out.vPosition.w 로  Out.vPosition.xyzw를 나눈다 (원근투영)
// 2.  뷰 포트 전개
// 3.  레스터 라이즈 (픽섹을 생성)//픽셀을 생성만했지, 픽셀 셰이더를 거치면 변경이 씹가능.

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

//필셀의 색을 결정하는 작업.(함수)		//픽셀 셰이더


//픽셀은 당연히 정점셰이더를 지나서 나온 VS_OUT구조체 정보로 생성된다!!
// 하지만 VS_OUT을 그대로 쓰면 가독성 씹망이니까 PS_IN을 새로 만들어서 사용하자..
// 그러니까 PS_IN은 VS_OUT 구조체와 맴버가 반드시 일치해야한다.
struct PS_IN
{
	float4 vPosition : POSITION;	//주의 VS_OUT데이터를 받아올거니까 이 vPosition은 윈도우 좌표다..
									//사실 VS_OUT에서 버택스의 위치는 이미 정해진거니까 픽셀셰이더에서 건들면 안된다. 상수라고 생각하자.
	int Color		 : COLOR;
	float4 vWorldPos : COLOR1;		
};

struct PS_OUT						//픽셀 셰이더의 아웃은 컬러(RGBA)을 반환한다.
{
	vector color : COLOR;
};


//색깔에 대한 타입은 따로 없으므로 vector를 사용합시다 vector은 float 4개를 갖고있음.
//:COLOR  -이 함수의 반환 값을 백 버퍼의 색상(COLOR)값으로 처리할 것.
vector PS_MAIN(PS_IN In) :COLOR
{
	vector Out = (vector)0.f;		//Out의 모든 요소를 0.f로 초기화.

	//Out = In.Color;		//버텍스 셰이더에서 반환한 Out 즉 PS_IN의 컬러로 그대로 그린다.

	Out.r = 1;
	return Out;
}



//이 셰이더 코드를 사용할때 , 어떤 함수를 호출해서 사용하면 되는지를 명시하는 코드.
//TODO 진입점 함수 지정
technique Defualut_Technique
{
	//pass는 여러개를 선언할수 있다
	//우리는 셰이더를 그린다! 라고 할때  인덱스 값을 넘겨줘야하는데
	//이때 0 은 첫번째 pass , 1은 두번째 패스.. 이렇게 어떤 셰이더를 사용할지 정할수 있다.
	// 즉 셰이더를 캡슐화 할수 있다는것
	pass Default_Rendering	//Index 0
	{									//즉 HLSL에도 버젼이 있다..!
		//VertexShader는 .		vs_3_0 버젼을 사용해서 컴파일 할거다.		만약 호출요청이 오면 VS_MAIN() 을 호출해라.
		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}

	//pass Default_Rendering	//Index 1
	//{									//즉 HLSL에도 버젼이 있다..!
	//									//VertexShader는 .		vs_3_0 버젼을 사용해서 컴파일 할거다.		만약 호출요청이 오면 VS_MAIN() 을 호출해라.
	//	VertexShader = compile vs_3_0 VS_MAIN();
	//	PixelShader = compile ps_3_0 PS_MAIN();
	//}


	//pass Default_Rendering
	//{									//즉 HLSL에도 버젼이 있다..!
	//									//VertexShader는 .		vs_3_0 버젼을 사용해서 컴파일 할거다.		만약 호출요청이 오면 VS_MAIN() 을 호출해라.
	//	VertexShader = compile vs_3_0 VS_MAIN();
	//	PixelShader = compile ps_3_0 PS_MAIN();
	//}


}

// TODO 주의 ! 가능하면 2pass 랜더링 (한 메시를 그릴때 두번의 pass를 지나야 하는 작업)을 절대 하지 말아라.
// 어쩔수 없이 2pass 랜더링을 해야할때 (그림자를 표현하거나) 이외엔 절대 쓰지말것.
