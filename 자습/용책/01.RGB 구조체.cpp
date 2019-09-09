



// D3DCOLOR_ARGB 매크로
D3DCOLOR brightRed = D3DCOLOR_ARGB(255 , 255 , 0 , 0);
D3DCOLOR someColor = D3DCOLOR_ARGB(255 , 144 , 87 , 201); 


// D3DCOLORVALUE 구조체
typedef struct D3DCOLORVALUE {
    float r ; // 적색 성분， 범위 ， 0 . 0- 1. 0
    float g ; // 색 성분 1 범위 ， 0.0-1. 0
    float b ; // 청색 생분 ， 위， 0 . 0- 1. 0
    float a;  // 파 생분l 범위 ， 0 . 0- 1. 0
) D3DCOLORVALUE; 


#define cplusplus;
typedef struct D3DXCOLOR
{
#ifdef cplusplus
public:
    D3DXCOLOR () {}
    D3DXCOLOR{ DWORD argb } ;
    D3DXCOLOR( CONST FLOAT * );
    D3DXCOLOR( CONST D3DXFLOAT16 * ) ;
    D3DXCOLOR( CONST D3DCOLORVALUE& ) ;
    D3DXCOLOR( FLOAT r , FLOAT g , FLOAT b , FLOAT a ) ;


// 형 변환
    operator DWORD () const ;
    operator FLOAT* () ;
    operator CONST FLOAT* () const ;
    operator D3DCOLORVALUE* ();
    operator CONST D3DCOLORVALUE* () const ;
    operator D3DCOLORVALUE& () ;
    operator CONST D3DCOLORVALUE& () const ;

// 할당 연산자
    D3DXCOLOR& operator += ( CONST D3DXCOLOR& ) ;
    D3DXCOLOR& operator ( CONST D3DXCOLOR& ) ;
    D3DXCOLOR& operator *= ( FLOAT ) ;
    D3DXCOLOR& operator /= ( FLOAT ) ;
// 단항 연산자
    D3DXCOLOR operator + () const ;
    D3DXCOLOR operator - () const ;
// 이항 연산자
    D3DXCOLOR operator + ( CONST D3DXCOLOR& ) const ;
    D3DXCOLOR operator - ( CONST D3DXCOLOR& ) const;
    D3DXCOLOR operator * ( FLOAT ) const ;
    D3DXCOLOR operator / ( FLOAT ) const; 

    friend D3DXCOLOR operator * (FLOAT, CONST D3DXCOLOR& ) ;
    BOOL operator ;; ( CONST D3DXCOLOR& ) const ;
    BOOL operator 1 ; ( CONST D3DXCOLOR& ) const ;
#endif // cplusplus
    FLOAT r , g , b , a ;
 } D3DXCOLOR, *LPD3DXCOLOR; 
