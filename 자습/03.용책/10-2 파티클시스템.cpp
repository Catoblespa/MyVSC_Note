/*


		[파티클 시스템의 요소들 ]

파티클 시스템은 파티클들의 모임이며 파티클을 보여주고 관리하는 역할을 담당한다.
파티클 시스템은 파티크르이 크기나 파티클 원천의 위치 ,
파티클에 적용할 텍스처 등 시스템 내의 모든 파티클에 영향을 주는 전역 특성을 관리한다.
기능적 관점에서 보면 파티클 시스템은 파티클 갱신과 디스플레이 소멸, 생성 들을 관장하는 역할을 한다.

다른 전형적 파티클 시스템들은 서로 다른 행동 방식을 가지고 있지만 이를 일반화하여
모든 파티클 시스템이 공유하는 몇가지 기본적인 특성들을 찾아낼 수 있다.
우리는 이들 공통 특성을 PSystem기반 클래스로 추상화 하고 다른 모든 전형적 파티클 시스템의 부모로 이용할 것이다.
pSystem의 구조는 아래와 같다.


class PSystem
{
public :
	PSystem();				//디폴트값을 초기화는 생성자와 장치 인터페이스(버텍스버퍼, 텍스쳐)를 해제하는 디스트럭터
	virtual -PSystem();

	virtual bool init(				
		IDirect3DDevice9* device , 
		char* texFileName) ;
	virtual void reset();
	virtual void resetParticle(Attribute* attribute) =0;
	virtual void addParticle(); 
	virtual void update(float timeDelta) =0;

	virtual void preRender() ;
	virtual void render();
	virtual void postRender() ;

	bool isEmpty();
	bool isDead() ;
protected:
	virtual void removeDeadParticles() ;
protected:
	IDirect3DDevice9* _device;
	D3DXVECTOR3 _origin;						//시스템의 원천.  시스템 내에서 파티클이 시작되는 곳이다.
	d3d::BoundingBox _boundingBox;				//경계 상자(bounding box)는 파티클이 이동할 수 있는 부피를 제한하는데 이용된다.
														//예를 들어 산 정상을 둘러싼 지역에만 눈이 오는 시스템의 예를 생각해 보자.
														//원하는 영역을 경계상자로 정의하면, 이 영역을 벗어난 파티클들은 곳바로 소멸된다.

	float _emitRate ;							//시스템에 새로운 파티클이 추가되는 비율. 보통은 초당 파티클 수로 기록된다.
	float _size ;								//시스템 내 모든 파티클의 크기
	IDirect3DTexture9* _tex ;					
	IDirect3DVertexBuffer9* _vb;
	std::list<Attribute> _particles;			//시스템 내 파티클 속성의 리스트.
													//우리는 파티클을 만들고 제거하고 갱신하는데 이 리스트를 이용한다.
													//파티클을 그릴 준비가 완료되면 리스트 노드의 일부를 버텍스 버퍼로 복사하고 파티클 드로잉 과정을 거친다.
													//이어 다음 단계의 데이터를 복사하고 다시 파티클을 그리며 , 모든 파티클을 그릴 때까지 이 과정을 반복한다.
	int maxParticles;					//주어진 시간동안 시스템이 가질 수 있는 최대 파티클의 수. 
										예를들어 파티클이 파괴되는 속도보다 만들어지는 속도가 빠르다면 엄청나게 많은 수의 파티클이 동시엥 존재 할 수 있다.
										이 맴버는 이 같은 상황을 방지하기위해 사용한다.
	DWORD _vbSize;						//버텍스 버퍼가 보관할 수있는 파티클의 수. 이값은 실제 파티클 시스템 내의 파티클 수와는 독립적이다.
	DWORD _vbOffset;
	DWORD _vbBatchSize ; 
}



virtual bool init(IDirect3DDevice9* device , char* texFileName);
	이 메서드는 포인트 스프라이트를 저장하기 위한 버텍스 버퍼를 만들고
	텍스처를 만드는 등의 Direct3D의 장치 의존적인 초기화 작업을 처리한다.
	버텍스 버퍼 생성에는 앞서 소개한 몇가지 플래그들이 포함되지만 아직까지는 이용되지 않는다.

hr = device->CreateVertexBuffer(
	_vbSize * sizeof(Particle) ,
	D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
	Particle::FVF,
	D3DPOOL_DEFAULT ,
	&_vb,
	0);
	
	[]파티클을 사용하기 위해
	우리는 동적 버텍스 버퍼를 이용할 것임을 기억하자.
	이것은 매 프레임 마다 파티클을 갱신해야 하며 이는 곧 버텍스 버퍼의 메모리에 접근해야 함을 의미하기 때문이다.
	정적 버텍스 버퍼로의 접근 속도는 상당히 느리다는 데 주의하자. 동적 버텍스 버퍼를 이용하는 것은 바로 이 때문이다.

	[]버텍스 버퍼가 포인트 스프라이트를 보관할 것임을 지정하는 D3DUSAGE_POINTS를 이용했다.

	[]버텍스 버퍼 크기가 _vbSize에 의해 미리 정의되며 시스템 내의 파티클 수와는 관련이 없음을 주의하자.
	_vbSize가 시스템 내 파티클의 수와 같은 경우는 거의 없다.
	이는 파티클 시스템의 렌더링이 한번에수행됮지 않고 단계적으로 이루어지기 때문이다.

	[]동적 버텍스 버퍼는 관리 메모리 풀에 보관 할 수 없으므로 일반적인 관리 메모리 풀 대신 디폴트 메모리 풀을 이용했다.



virtual void reset();
	이 메서드는 시스템 내의 모든 파티클 속성을 리셋한다.
	내부적으로 속성 리스트를 순회하면서 resetParticle을 호출한다.


virtual void resetParticle(Attribute* attribute) =0;
	이 메서드는 한 파티클의 속성을 리셋한다.
	파티클의 속성이 리셋되는 방식은 파티클 시스템에 따라 달라진다.
	따라서 하위 클래스에서 메서드를 구현하도록 추상 메서드로 선언하였다.

virtual void addParticle(); 
	시스템에 파티클을 추가한다. 이 메서드는 리스트에 추가하기 전에 파티클을 초기화 하는데 resetParticle 메서드를 이용한다.
	void PSystem::addparticle()
	{
		Attribute attribute;
		resetParticle(&attribute);
		_particle.push_bakc(attribute);
	}

virtual void update(float timeDelta)=0;
	시스템 내의 모든 파티클들을 갱신한다.
	이와 같은 메서드의 구현은 특정 파티클 시스템에 따라 달라지므로,
	하위 클래스에서 메서드를 구현하도록 추상 메서드로 선언하였다.


virtual void render();
	시스템 내의 모든 파티클들을 렌더링 한다.
virtual void preRender() ;
	렌더링에 앞서 지정해야 할 초기 렌더 상태를 지정한다.
	이메서드는 시스템에 따라 달라질 수 있으므로 가상 함수로 선언하였다.
	디폴트 구현은 다음과 같다
	void PSystem::preRender()
	{
		device->SetRenderState(D3DRS_LIGHTING, false);
		device->SetRenderState (D3DRS_POINTSPRITEENABLE, true ) ;
		device->SetRenderState(D3DRS_POINTSCALEENABLE, true ) ;
		device->SetRenderState(D3DRS_POINTSIZE, d3d: : FtoDw(_size)) ; 
		device- >SetRenderState(D3DRS_POINTSIZE MIN , d3d : :FtoDw(0.0f));
		// 거리에 따른 따티 의 크기를 제어한다.
		device->SetRenderState(D3DRS_POINTSCALE A, d3d::FtoDw(0.0f)) ;
		device->SetRenderState(D3DRS_POINTSCALE B, d3d::FtoDw(0.0f));
		device->SetRenderState(D3DRS_POINTSCALE C, d3d::FtoDw(1.0f)) ;
		// 처의 를 이용한 .
		_device->SetTextureStageState(O, D3DTSS_ALPHAARGl , D3DTA_TEXTURE) ;
		_device->SetTextureStageState(O , D3DTSS_ALPHAOP, D3DTOP_SELECTARGl) ;
		device->SetRenderState(D3DRS_ALPHABLENDENABLE , true);
		device->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA) ; 
	}
	알파 블렌딩을 활성화하여 텍스처의 알파 채널이 텍스처의 픽셀 투명도를 결정하도록 했음을 확인하자.
	이를 통해 다양한 효과를 얻을 수 있으며, 가장 대표적인 것이 사각형이아닌 다른 파티클 형태를 구현하는 것이다.


virtual void postRender() ;
	특정 파티클 시스템이 지정했을 수 있는 렌더 상태를 복구하는데 이용된다.
	이 메서드는 시슽메에 따라 다를 수 있으므로 가상 메서드로 선언했다. 
	디폴트 구현은 다음과 같다.
	void PSystem : :postRender()
	{
		device->SetRenderState(D3DRS_LIGHTING, true) ;
		device->SetRenderState(D3DRS_POINTSPRITEENABLE, false) ;
		device->SetRenderState(D3DRS_POINTSCALEENABLE, false) ;
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, false) ;
	}

bool isEmpty();
	현재 시스템에 파티클이 없는 경우 True를 리턴하며, 그렇지 않으면 False를 리턴한다.

bool isDead();
	시스템 내의 파티클이 모두 죽은 경우 True를 리턴하며, 그렇지 않으면 False를 리턴한다.
	모든 파티클이 죽은 상태와 시스템이 빈 상태를 혼동하지 않도록 하자.
	빈 상태는 시스템 내의 파티클이 없는 상태를 의미하며, 죽은 상태는 파티클이 존재하지만 죽은 것으로 표시된 상태를 의미한다.

virtual void removeDeadParticles() ;
	속성리스트 _particle을 검색하여 죽은 파티클을 리스트에서 제거한다.

	void PSystem::removeDeadParticles()
	{
		std::list<Attribute>::iterator i;

		i = _particles.begin() ;

		while( i != -particles.end() )
		{
			if( i - > isAlive == false )
			{
				// erase는 다음 반복자를 리턴하므로
				// 우리가 반복자를 증가시킬 필요가 없다.
				i = _particles . erase( i ) ;
			}
			else
			{
				i++ ; // next in list
			}
		}
	}

	이 메서드는 주로 하위 클래스의 갱신 메서드에서 호출되어
	죽은 파티클을 제거하는데 이용된다.
	하지만 일부 파티클 시스템에서는 죽은 파티클을 제거하기 보다는 재활용하는 것이
	효율 적일 수 있다.
	즉 파티클이 만들어지고 제거될 때 할당과 해제를 반복하는 것이 아니라 간단하게 죽은 파티클을 리셋하여
	새로운 파티클로 이용할 수있다.





*/