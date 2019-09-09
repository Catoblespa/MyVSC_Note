

bool CDeviceManager::Display()
{
	//
	// draw the scene:
	//
	m_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFF4682B4, 1.0f, 0);
	m_pDevice->BeginScene();		//장면 시작

    /*//스트림소스 지정 스트림소스를 버텍스 버퍼와 연결하여 버퍼의 기하정보를 렌더링 파이프라인에 보낼 수 있도록 한다 .
    HRESU1T IDirect3DDevice9::SetStreamSource(
    UINT StreamNumber,						//버텍스 버퍼를 연결할 스트림 소스를 지정한다 이 책에서는 중 스트림을 이용하지 않으므로 항상 스트림 을 이용할 것이다
    IDirect3DVertexBuffer9* pStreamData ,	//스트림과 연결하고자 하는 버텍스 버퍼로의 포인터
    UINT OffsetInBytes,						//렌더링 파이프라인으로 공급될 버텍스 데이터의 시작을 지정하는 스트림의 시작 오프셋
    UINT Stride								//스트림에 연결하고자 하는 버텍스 버퍼가 갖는 각 요소의 바이트 수
    )*/
	m_pDevice->SetStreamSource(0, vb, 0, sizeof(Vertex));
	m_pDevice->SetIndices(ib);		//	인덱스 버퍼 포인터의 복사본을 전달한다. 
	m_pDevice->SetFVF(Vertex::FVF);	//버텍스 포맷을 지정한다 이후의 드로잉 호출에서 이용될 버텍스 포뱃을 지정하는 단계이다. 

    /*
    HRESULT IDirect3DDevice9: : DrawPrimitive (
    D3DPRIMITIVETYPE PrimitiveType ,	그리고자 하는 기본형 타입
    예를 들어， 삼각형 이외에도 포인트나 선을 그릴 수 있다.
    여기에서 그리고자 하는 것은 삼각형이므로 D3DPT_TRIANGLELIST를 지정한다
    UINT StartVertex,					버텍스 읽기를 시작할 버텍스 스트림 요소로의 인덱스
    이 인자는 버텍스 버퍼 내의 데이터를 일부만 그릴 수 있도록 하는 유연성을 제공한다

    UINT PrimitiveCount					그리고자 하는 기본형의 수
    )


    HRESULT IDirect3DDevice9::DrawIndexedPrimitive(
    D3DPRIMITIVETYPE Type ,
    INT BaseVertexIndex,				//이번에 호출에 이용될 인텍스에 더해질 기반 번호를 지정한다
    UINT MinIndex,						//참조할 최소 인텍스 값
    UINT NumVertices,					//이번 호출에 참조될 버텍스의 수
    UINT StartIndex,					//인덱스 버퍼 내에서 읽기를 시작할 요소로의 인텍스
    UINT PrimitiveCount					//그리고자 하는 기본형의 수
    )
    */
    // Draw cube.
    //m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);	// 인덱스 정보를 이용하지 않는 기본형을 그리는 데 이용된다.


	m_pDevice->SetMaterial(&RED_MTRL);
	ppBoxMesh->DrawSubset(0);
	//auto v= Vector2(5, 5);
	//ppLine->Draw(&v,10,BLUE);

	m_pDevice->EndScene();		//장면 끝
	m_pDevice->Present(0, 0, 0, 0);
	return true;
}