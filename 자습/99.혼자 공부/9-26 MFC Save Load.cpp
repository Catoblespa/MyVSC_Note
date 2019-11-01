/*
void CMapTool::OnBnClickedSave()
{
	UpdateData(TRUE);

	//파일 여리 혹은 저장에 관한 대화상자 MFC클래스
	CFileDialog Dlg(
		FALSE,				//TRUE 불러오기 // FALSE 저장하기.
		L".dat",			//기본확장자
		L"제목 음슴.dat",	//디폴트 파일 이름.
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,					//OFN_OVERWRITEPROMPT 덮어쓰기일 경우 경고메시지 띄우기, OFN_HIDEREADONLY 읽기 전용 체크 박스 숨김
		L"DataFiles(*.dat)|*.dat|TextFiles(*.txt) |*.txt||",	//필터 //(*.dat)출력문구 |*.dat 실제 필터링되는 확장자. || 다음 필터 구분
																//DataFiles(*.dat)|*.dat    |	TextFiles(*.txt) |*.txt		|| 로 구분된거당
		this);				//부모 전달


	TCHAR szCurrentPath[MAX_STR] = L"";

	//현재 작업 경로를 얻어오는 함수.  //vs로 켜면 Tool프로젝트 경로가 나오고 , exe파일로 하면 exe경로로 가져온다.
	::GetCurrentDirectory(MAX_STR, szCurrentPath);

	//현재 경로에서 파일명을 제거하는 함수.   제거할 파일명이 없으면 말단 폴더명을 제거한다.
	::PathRemoveFileSpec(szCurrentPath);


	lstrcat(szCurrentPath, L"\\MapData");	//문자열 이어붙히기.

	::AfxMessageBox(szCurrentPath);

	//ofn : 오픈    , lpstrInitialDir 현재 대화상자에서 보여질 초기경로 설정.      절대 경로로 넘겨줘야 한다.
	//Dlg.m_ofn.lpstrInitialDir = L"C:\\Users\\a4ka2\Desktop\\수업프로젝트\\5개월차\\Framework99C\\Data";
	Dlg.m_ofn.lpstrInitialDir = szCurrentPath;


	//Dlg.Create() :로도 만들 수 있다 (모달리스 형식)	// Dlg 창이 떠도 다른 창을 컨트롤 할 수 있다. 
	//Dlg.DoModal : 모달 형식		// Dlg 창이 뜨면 Dlg창만 컨트롤 가능하다.

	if (IDOK == Dlg.DoModal())		//IDOK : OK 버튼 눌렀읅경우  IDCANCEL : 취소버튼 
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);


		if (INVALID_HANDLE_VALUE == hFile)
			return;


		CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		NULL_CHECK(pFrameWnd);

		CToolView* pToolView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
		NULL_CHECK(pToolView);

		BYTE iDrawID;

		DWORD dwBytes = 0;
		for (auto& Tile : pToolView->m_pTerrain->m_vecTile)
		{
			WriteFile(hFile, &Tile->byDrawID, sizeof(BYTE), &dwBytes, nullptr);
		}
		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}


void CMapTool::OnBnClickedLoad()
{
	UpdateData(TRUE);

	//파일 여리 혹은 저장에 관한 대화상자 MFC클래스
	CFileDialog Dlg(
		TRUE,				//TRUE 불러오기 // FALSE 저장하기.
		L".dat",			//기본확장자
		L"제목 음슴.dat",	//디폴트 파일 이름.
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,					//OFN_OVERWRITEPROMPT 덮어쓰기일 경우 경고메시지 띄우기, OFN_HIDEREADONLY 읽기 전용 체크 박스 숨김
		L"DataFiles(*.dat)|*.dat|TextFiles(*.txt) |*.txt||",	//필터 //(*.dat)출력문구 |*.dat 실제 필터링되는 확장자. || 다음 필터 구분
																//DataFiles(*.dat)|*.dat    |	TextFiles(*.txt) |*.txt		|| 로 구분된거당
		this);				//부모 전달


	TCHAR szCurrentPath[MAX_STR] = L"";

	//현재 작업 경로를 얻어오는 함수.  //vs로 켜면 Tool프로젝트 경로가 나오고 , exe파일로 하면 exe경로로 가져온다.
	::GetCurrentDirectory(MAX_STR, szCurrentPath);

	//현재 경로에서 파일명을 제거하는 함수.   제거할 파일명이 없으면 말단 폴더명을 제거한다.
	::PathRemoveFileSpec(szCurrentPath);


	lstrcat(szCurrentPath, L"\\MapData");	//문자열 이어붙히기.

	//::AfxMessageBox(szCurrentPath);

	//ofn : 오픈    , lpstrInitialDir 현재 대화상자에서 보여질 초기경로 설정.      절대 경로로 넘겨줘야 한다.
	//Dlg.m_ofn.lpstrInitialDir = L"C:\\Users\\a4ka2\Desktop\\수업프로젝트\\5개월차\\Framework99C\\Data";
	Dlg.m_ofn.lpstrInitialDir = szCurrentPath;


	//Dlg.Create() :로도 만들 수 있다 (모달리스 형식)	// Dlg 창이 떠도 다른 창을 컨트롤 할 수 있다. 
	//Dlg.DoModal : 모달 형식		// Dlg 창이 뜨면 Dlg창만 컨트롤 가능하다.

	if (IDOK == Dlg.DoModal())		//IDOK : OK 버튼 눌렀읅경우  IDCANCEL : 취소버튼 
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, 0,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);


		if (INVALID_HANDLE_VALUE == hFile)
			return;


		BYTE iDraw = 0;


		CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		NULL_CHECK(pFrameWnd);

		CToolView* pToolView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
		NULL_CHECK(pToolView);



		DWORD dwBytes = 0;
		int count = 0;
		while (true)
		{

			ReadFile(hFile, &iDraw, sizeof(BYTE), &dwBytes, nullptr);
			if (0 == dwBytes)
				break;


			pToolView->m_pTerrain->m_vecTile[count]->byDrawID = iDraw;
			count++;
		}
		count = 0;
		CloseHandle(hFile);
		pToolView->Invalidate(FALSE);
	}

	UpdateData(FALSE);
}
*/