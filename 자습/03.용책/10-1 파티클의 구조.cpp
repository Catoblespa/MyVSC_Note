
/*	
						[포인트 스프라이트의 구조체]


파티클은 매우 작은 물체이며 일반적으로 하나의 포인트로 모델링된다. 
즉， 파티클을 보여주는 데 있어 포인트 기본형이 (D3DPRIMITIVETYPE 의 D3DPT POINTLIST) 가장 훌륭한 후보가 된다
 하지만， 포인트 기본형은 단일 픽셀로 래스터라이즈되며， 
 이와 같은 특성은 다양한 크기의 파티클을 이용하거나 텍스처를 입힌 파티클이 구현해야 하는 동의 상황에 심각한 제한으로 작용한다. 

struct Particle
{
	Vector3 _position;
	D3DCOLOR	_color;
	float _size;
	static const DWORD FVF;
};
const DWORD Particle::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE;




						[포인트 스프라이트 렌더 상태]

 포인트 스프라이트의 동작들은 거의 대부분 렌더 상태에 의해 제어된다 포인트트 스프라이트와 관련된 렌더 상태를 차례로 살펴보기로 하자.

- D3DRS_POINTSPRITEENABLE (부울 값 , 디폴트 : FALSE)
	 True값 : 현재 지정된 전체 텍스처를 포인트 스프라이트의 텍스처 매핑에 이용할 것을 의미한다.
	 FALSE값 : 포인트 스프라이트의 텍스처 좌표로 (버텍스 구조체 내에 텍스처 좌표를 가진 경우)
	 		지정한 픽셀을 이용해 포인트 스프라이트의 텍스처를 입혀야 하도록 지정한다.

	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true); 
	

- D3DRS_POINTSCALEENABLE (부울 값 , 디폴트 : FALSE)
	True : 포인트 크기를 뷰 스페이스 단위로 해석하도록 지정한다.
		뷰스페이스 단위는 간단히 카메라 공간 내의 3D포인트를 나타내며,
		포인트 스프라이트의 크기는 카메라와의 거리에 따라 적절하게 조정된다.
		즉, 카메라와 멀리 떨어진 파티클은 가까운 파티클에 비해 작게 나타난다.

	FALSE :  포인트 크기를 스크린 스페이스 단위로 해석하도록 지정한다.
		스크린 스페이스 단위는 화면 상의 픽셀 단위이다.
		즉 , false를 지정하고 포인트 스프라이트의 크기로 3을 이용하면 3x3픽셀 크기의 포인트 스프라이트가 그려진다.

	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true) ; 


- D3DRS_POINTSIZE 
	포인트 스프라이트의 크기를 지정한다. 이 값은 D3DS_POINTSCALEENABLE 상태 값에 따라서
	뷰 스페이스 내의 크기나 스크린 스페이스 내의 크기로 해석된다.
	다음의 코드는 포인트 크기를 2.5단위로 지정한다.

	m_pDevice->SetRenderState( D3DRS_POINTSIZE, d3d::FtoDw(2.5f)); 

		주의[!] :d3d::FtoDw 함수는 용책에서의  d3dUtility.h/cpp에 추가한 것으로 , float값을 DWORD값으로 변환 시켜주는 함수.
				SetRenderState함수는 float이 아닌 DWORD값을 필요로 하기 때문임.

DWORD d3d::FtoDw(float f)
{
	return *((DWORD*)&f);
}

- D3DRS_POINTSIZE_MIN 
	포인트 스프라이트의 지정할 수 있는  최소 크기를 지정한다.
	다음은 최소 크기에 0.2를 저지정하는 예를 보여준다.
		device->SetRenderState(D3DRS_POINTSIZE_MIN , d3d::FtoDw(0.2f)) ; 

- D3DRS_POINTSIZE_MAX - 
 	포인트 스프라이트의 지정할 수 있는 최대 크기를 지정한다 
	 다음은 최대 크기에 5.0을 지정하는 예를 보여준다，

		device->SetRenderState(D3DRS_POINTSIZE_MAX , d3d::FtoDw(5.0f)}; 


-  D3DRS_POINTSCALE_A, D3DRS_POINTSCALE_ B, D3DRS_POINTSCALE_C
	이 세개의 상수는 거리에 따라 포인트 스프라이트의 크기가 변하는 방법을 제어한다.
	여기서 말하는 거리란, 카메라와 포인트 스프라이트 간의 거리이다.


	다음은 Direct3D가 거리와 세가지 상수를 이용해 포인트 스프라이트의 최종 크기를 계산하는데 이용되는 식이다.
	FinalSize = ViewportHeight * Size * sqrt(1/A+ B(D) + C(D^2));

	FinalSize :  거리 계산을 마치고 얻은 포인트 스프라이트의 최종 크기
	ViewportHeight : 뷰포트의 높이
	Size : D3DRS_POINTSIZE : 렌더 상태에 지정된 값.

	A,B,C : 순서대로 D3DRS_POINTSCALE_A, D3DRS_POINTSCALE_ B, D3DRS_POINTSCALE_C
			렌더 상태에 지정된 값.
		
	D :  뷰 스페이스 내의 포인트 스프라이트와 카메라 위치와의 거리.
		카메라는 뷰 스페이스의 원점에 위치하므로 뷰 스페이스 내의 (x,y,z)에 포인트 스프라이특 ㅏ위치한다고 할때
		이값은 D = sqrt(x^2 + y^2 + z^2)이 된다.


	다음 코드는 스프라이트가 작아지도록 포인트 스프라이트 거리 상수 값을 지정한다.

	device->SetRenderState(D3DRS POINTSCALE A, d3d::FtoDw(0.0f));
	device->SetRenderState(D3DRS POINTSCALE B, d3d::FtoDw(0.0f));
	device->SetRenderState(D3DRS POINTSCALE C, d3d::FtoDw(1.0f)) ; 





						[파티클과 파티클의 속성들]
실제로 파티클은 위치와 컬러 이외의 상당히 많은 다양한 속성들로 이루어져 있다.
를 들어 파티클은 특정 한 속도를 가질 수 있다. 하지만 이들 부가적인 속성들은
파티클을 렌더링하는 데 필수적인 것은 아니다.

 따라서 우리는 파티클을 렌더링하는
데 필요한 데이터와 파티클 속성을 별도의 구조체 내에 보관하게 되는데， 파티클을
만들고 파괴하고 갱신할 때는 바로 이러한 속성을 이용해 작업하는 것이며，

이를 렌더링할 준비가 완료되면 Particle 구조제로 위치와 속성을 복사해 이용하는 것이다，

파티클의 속성은 우리가 모텔링하려는 파티클 시스댐의 종류에 따라서 달라진다. 
하지만 약간의 일반화를 거치면 몇 가지 공통적인 속성을 가려낼 수 있다. 

다음 구조체 예제는 몇 가지의 공통적인 파티클 속성을 포함하고 있다.
대부분의 시스템에서 이들 속성을 모두 이용하지는 않으며,
일부 시스템에서는 여기에 포함되지 않은 부가적인 속성을 필요로 한다.

struct Attribute
{
	D3DXVECTOR3 _position;			//월드 스페이스 내의 파티클 위치
	D3DXVECTOR3 velocity;			//파티클의 속도, 보통은 초당 이동 단위로 기록
	D3DXVECTOR3 acceleration;		//파티클의 가속,  보통은 초당 이동 단위로 기록
	float lifeTime;					//파티클이 소멸할 때까지 유지되는 시간.
	float age ;						//파티클의 현재 나이
	D3DXCOLOR color;				//파티클의 컬러
	D3DXCOLOR colorFade;			//파티클의 컬러가 시간의 흐름에 따라 퇴색하는 방법
	bool isAlive; 					//파트클이 생존한경우 True, 소멸할경우 false
}



*/
