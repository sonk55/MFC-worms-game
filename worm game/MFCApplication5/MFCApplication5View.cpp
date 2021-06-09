
// MFCApplication5View.cpp: CMFCApplication5View 클래스의 구현
//
#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication5.h"
#endif

#include "MFCApplication5Doc.h"
#include "MFCApplication5View.h"
#include <string>
#include <string.h>

#include "CWorm.h"
//#include "memdc-redsusia.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication5View

IMPLEMENT_DYNCREATE(CMFCApplication5View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication5View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMFCApplication5View 생성/소멸

CMFCApplication5View::CMFCApplication5View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	srand(time(NULL));
	mag.Load(L"1.png");
	coin1.Load(L"coin1.png");
	coin2.Load(L"coin2.png");
	coin3.Load(L"coin3.png");
	invisible.Load(L"투명.png");
	dirt.Load(L"2.png");
	bitmap.LoadBitmap(IDB_BITMAP2);
	wall.LoadBitmapW(IDB_BITMAP3);
	wall.GetBitmap(&wallinfo);
	bitmap.GetBitmap(&bmpinfo);
	hp = 200;
}

CMFCApplication5View::~CMFCApplication5View()
{
}

BOOL CMFCApplication5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication5View 그리기

void CMFCApplication5View::OnDraw(CDC* pDC)
{
	CMFCApplication5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CRect rect;
	GetClientRect(&rect);

	if (grade == OPENING)
	{
		CDC MemDC; //메모리에 DC를 만든다.
		MemDC.CreateCompatibleDC(pDC);
		//화면DC와 호환성을 갖는 메모리 DC 만들기
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP1);
		//리소스에서 비트맵을 읽어 들여 DC에 선택
		BITMAP bmpinfo;
		bitmap.GetBitmap(&bmpinfo);
		//비트맵은 높이와 크기가 모두 다르기에 GetBitmap()로 비트맵

		CBitmap* pOldBitmap = (CBitmap*)MemDC.SelectObject(&bitmap);

		pDC->StretchBlt(0, 0, rect.Width(), rect.Height(),
			// 비트맵을 화면에 출력한다.
			&MemDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight,
			SRCCOPY);

		MemDC.SelectObject(pOldBitmap); //DC 복원
		bitmap.DeleteObject();

		pDC->Rectangle(rect.Width() * 3.5 / 10, rect.Height() * 8.4 / 10, rect.Width() * 6.5 / 10, rect.Height() * 8.4 / 10 + 60);
		CFont myFont;
		myFont.CreateFont(40, //가로세로크기
			0, 0, 0, //기울어짐 각도
			FW_DONTCARE, //폰트의 굵기
			FALSE, //이탤릭플러그
			FALSE, //언더라인플러그
			FALSE, //STRIKEOUT 플러그
			DEFAULT_CHARSET, //CHAR SET
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH,
			_T("굴림체"));
		pDC->SelectObject(&myFont);
		pDC->TextOutW(rect.Width() * 3.5 / 10 + 10, rect.Height() * 8.4 / 10 + 10, _T("Name : "));
		pDC->TextOutW(rect.Width() * 3.5 / 10 + 140, rect.Height() * 8.4 / 10 + 10, name);
	}

	else if (grade == PLAY)
	{
		CDC MemDC;
		CBitmap* pOldBitmap;
		CBitmap bmp;

		MemDC.CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		pOldBitmap = (CBitmap*)MemDC.SelectObject(&bmp);
		MemDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);
		DrawImage(&MemDC);
		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
		MemDC.SelectObject(pOldBitmap);
		MemDC.DeleteDC();
		if (GameOver == TRUE)
		{
			grade = ENDING;
		}
	}

	else if (grade == ENDING)	//엔딩화면
	{
		CDC MemDC; //메모리에 DC를 만든다.
		MemDC.CreateCompatibleDC(pDC);
		//화면DC와 호환성을 갖는 메모리 DC 만들기
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP4);
		//리소스에서 비트맵을 읽어 들여 DC에 선택
		BITMAP bmpinfo;
		bitmap.GetBitmap(&bmpinfo);
		//비트맵은 높이와 크기가 모두 다르기에 GetBitmap()로 비트맵

		CBitmap* pOldBitmap = (CBitmap*)MemDC.SelectObject(&bitmap);

		pDC->StretchBlt(0, 0, rect.Width(), rect.Height(),
			// 비트맵을 화면에 출력한다.
			&MemDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight,
			SRCCOPY);

		MemDC.SelectObject(pOldBitmap); //DC 복원
		bitmap.DeleteObject();
		KillTimer(MOVE);
		KillTimer(CREATECOIN);
	}

	else if (grade == RANKING) //랭킹 화명(파일 입출력)
	{
		FILE* ranking;
		char line[MAX_LEN];
		char* result = NULL;
		string arr_name[11];
		int arr_score[11];
		if (fopen_s(&ranking, "Ranking.txt", "r+") == 0)
		{
			for (int i = 0; i < 10; i++)
			{
				result = fgets(line, MAX_LEN, ranking);
				if (result == NULL)
				{
					arr_name[i] = { "NULL" };
					arr_score[i] = 0;
				}
				else
				{
					arr_name[i] = strtok(result, "=");
					arr_score[i] = atoi(strtok(NULL, "="));
				}
			}
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				arr_name[i] = { "NULL" };
				arr_score[i] = 0;
			}
		}
		fclose(ranking);

		CDC MemDC;
		MemDC.CreateCompatibleDC(pDC);
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP1);
		BITMAP bmpinfo;
		bitmap.GetBitmap(&bmpinfo);
		CBitmap* pOldBitmap = (CBitmap*)MemDC.SelectObject(&bitmap);
		pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
		MemDC.SelectObject(pOldBitmap); //DC 복원
		bitmap.DeleteObject();

		pDC->SelectStockObject(WHITE_PEN);
		pDC->SelectStockObject(BLACK_BRUSH);
		CPoint center(rect.Width() / 2, rect.Height() / 2);
		pDC->Rectangle(center.x - rect.Width() / 7, center.y - rect.Height() * 2 / 5, center.x + rect.Width() / 7, center.y + rect.Height() * 2 / 5);
		CRect rect_rank(center.x - rect.Width() / 7, center.y - rect.Height() * 2 / 5, center.x + rect.Width() / 7, center.y + rect.Height() * 2 / 5);
		CFont myFont;
		myFont.CreateFont(rect_rank.Height() / 8, //가로세로크기
			rect_rank.Height() / 16, 0, 0, //기울어짐 각도
			FW_HEAVY, //폰트의 굵기
			FALSE, //이탤릭플러그
			FALSE, //언더라인플러그
			FALSE, //STRIKEOUT 플러그
			DEFAULT_CHARSET, //CHAR SET
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH,
			_T("굴림체"));
		pDC->SelectObject(&myFont);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(_T("Ranking"), CRect(center.x - rect.Width() / 7, center.y - rect.Height() * 2 / 5 + 10, center.x + rect.Width() / 7, center.y - rect.Height() * 2 / 5 + 10 + rect_rank.Height() / 8), DT_TOP | DT_CENTER);

		CRect rect_rank2(rect_rank.left, center.y - rect.Height() * 2 / 5 + 10 + rect_rank.Height() / 8, rect_rank.right, center.y + rect.Height() * 2 / 5);
		CFont myFont2;
		int height = rect_rank2.Height() / 10;
		myFont2.CreateFont(height - 10, //가로세로크기
			(height - 10) / 2, 0, 0, //기울어짐 각도
			FW_HEAVY, //폰트의 굵기
			FALSE, //이탤릭플러그
			FALSE, //언더라인플러그
			FALSE, //STRIKEOUT 플러그
			DEFAULT_CHARSET, //CHAR SET
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH,
			_T("굴림체"));
		pDC->SelectObject(&myFont2);
		for (int i = 0; i < 10; i++)
		{
			CString str;
			str.Format(_T("%2d. "), i + 1);
			str += arr_name[i].c_str();
			pDC->DrawText(str, CRect(rect_rank2.left, rect_rank2.top, rect_rank2.right, rect_rank2.bottom), DT_TOP | DT_LEFT);
			str.Format(_T("%d"), arr_score[i]);
			pDC->DrawText(str, CRect(rect_rank2.left, rect_rank2.top, rect_rank2.right, rect_rank2.bottom), DT_TOP | DT_RIGHT);
			rect_rank2.top += height;
		}
	}
}


// CMFCApplication5View 인쇄

BOOL CMFCApplication5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCApplication5View 진단

#ifdef _DEBUG
void CMFCApplication5View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication5Doc* CMFCApplication5View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication5Doc)));
	return (CMFCApplication5Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication5View 메시지 처리기


void CMFCApplication5View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	if (grade == OPENING)
	{
		if (nChar == VK_RETURN)
		{
			if (name.IsEmpty() == TRUE)
			{
				name.AppendFormat(_T("NULL"));
			}
			grade = PLAY;
			SetTimer(MOVE, 16, NULL);
			SetTimer(CREATECOIN, 300, NULL);
			SetTimer(REDUCE_HP, 300, NULL);
			Invalidate();
		}
		if (nChar == VK_BACK)
		{
			name.Delete(name.GetLength() - 1, 1);
			Invalidate(FALSE);
		}
	}

	else if (grade == PLAY)
	{
		//worm.ClearWorm(&dc);
		switch (nChar)
		{
		case VK_UP:
			if (LastDirection != DOWN)
				LastDirection = UP;
			break;
		case VK_LEFT:
			if (LastDirection != RIGHT)
				LastDirection = LEFT;
			break;
		case VK_RIGHT:
			if (LastDirection != LEFT)
				LastDirection = RIGHT;
			break;
		case VK_DOWN:
			if (LastDirection != UP)
				LastDirection = DOWN;
			break;
		}
		worm.MoveWorm(LastDirection);
		Invalidate(FALSE);
	}
	else if (grade == ENDING)
	{
		if (nChar == VK_RETURN)
		{
			grade = RANKING;
			FILE* ranking;
			char line[MAX_LEN];
			char* result = NULL;
			string arr_name[11];
			int arr_score[11];
			if (fopen_s(&ranking, "Ranking.txt", "r+") == 0)
			{
				for (int i = 0; i < 10; i++)
				{
					result = fgets(line, MAX_LEN, ranking);
					if (result == NULL)
					{
						arr_name[i] = { "NULL" };
						arr_score[i] = 0;
					}
					else
					{
						arr_name[i] = strtok(result, "=");
						arr_score[i] = atoi(strtok(NULL, "="));
					}
				}
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					arr_name[i] = { "NULL" };
					arr_score[i] = 0;
				}
			}
			fclose(ranking);
			for (int i = 0; i < 10; i++)
			{
				if (arr_score[i] < score)
				{
					int temp;
					string str_temp;
					for (int j = i; j < 11; j++)
					{
						if (j == i)
						{
							temp = arr_score[i];
							str_temp = arr_name[i];
							arr_score[i] = score;
							CT2CA pszConvertedAnsiString(name);
							arr_name[i] = pszConvertedAnsiString;
						}
						else
						{
							int a = arr_score[j];
							string b = arr_name[j];
							arr_score[j] = temp;
							arr_name[j] = str_temp;
							temp = a;
							str_temp = b;
						}
					}
					break;
				}
			}
			if (fopen_s(&ranking, "Ranking.txt", "w") == 0)
			{
				for (int i = 0; i < 10; i++)
				{
					char result[100];
					sprintf(result, "%s=%d\n", arr_name[i].c_str(), arr_score[i]);
					fputs(result, ranking);
				}
				fclose(ranking);
			}
			Invalidate();
		}
	}
	else if (grade == RANKING)
	{
		if (nChar == VK_RETURN)
		{
			grade = OPENING;
			ResetGame();
			Invalidate();
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFCApplication5View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (grade == OPENING)
	{
		if (nChar >= 32) { // 제어 문자를 제외시킨다.
			name.AppendChar(nChar);

			Invalidate(FALSE);
		}
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CMFCApplication5View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nIDEvent == CREATECOIN)
	{
		SCoin* p = coin.head;
		while (p != NULL)
		{
			p->Duration -= 300;
			p = p->link;
		}
		if (coin.head != NULL)
		{
			if (coin.head->Duration <= 0)
			{
				p = coin.head;
				coin.head = coin.head->link;
				coin.head->prelink = NULL;
				free(p);
			}
		}
		coin.CreatItem();
	}
	if (nIDEvent == REDUCE_HP)
	{
		hp -= 1;
	}
	if (nIDEvent == MOVE)
	{
		worm.MoveWorm(LastDirection);
		SCoin* p = coin.head;
		while (p != NULL)
		{
			if (((worm.head->P.x - p->P.x) * (worm.head->P.x - p->P.x)) + ((worm.head->P.y - p->P.y) * (worm.head->P.y - p->P.y)) < 4 * radius * radius)
			{
				switch (p->Type)
				{
				case N_PLUS:
					worm.PlusBody(LastDirection);
					score += 100;
					hp += 5;
					break;
				case N_MINUS:
					score -= 200;
					hp -= 10;
					if (worm.tail->prelink != NULL)
						worm.MinusBody();
					else
						GameOver = TRUE;
					break;
				case N_INVISIBLE:
					B_Invisible = TRUE;
					SetTimer(INVISIBLE, 5000, NULL);
					break;
				case N_MAGNET:
					B_Magnet = TRUE;
					SetTimer(MAGNET, 5000, NULL);
					break;
				}
				//Delete Item
				coin.DeleteItem(p);
				break;
			}
			p = p->link;
		}
		p = coin.head;
		if (B_Magnet == TRUE)
		{
			while (p != NULL)
			{
				if (((worm.head->P.x - p->P.x) * (worm.head->P.x - p->P.x)) + ((worm.head->P.y - p->P.y) * (worm.head->P.y - p->P.y)) < 4 * 400 * radius)
				{
					if ((worm.head->P.x - p->P.x) * (worm.head->P.x - p->P.x) < 225)
					{
						p->P.x += (worm.head->P.x - p->P.x);
					}
					else if ((worm.head->P.x - p->P.x) * (worm.head->P.x - p->P.x) > 225)
					{
						if (worm.head->P.x - p->P.x > 0)
						{
							p->P.x += 20;
						}
						else if (worm.head->P.x - p->P.x < 0)
						{
							p->P.x -= 20;
						}
					}
					if ((worm.head->P.y - p->P.y) * (worm.head->P.y - p->P.y) < 225)
					{
						p->P.y += (worm.head->P.y - p->P.y);
					}
					else if ((worm.head->P.y - p->P.y) * (worm.head->P.y - p->P.y) > 225)
					{
						if (worm.head->P.y - p->P.y > 0)
						{
							p->P.y += 20;
						}
						else if (worm.head->P.y - p->P.y < 0)
						{
							p->P.y -= 20;
						}
					}
				}
				p = p->link;
			}
		}
		Invalidate(FALSE);
	}
	if (nIDEvent == INVISIBLE)
	{
		KillTimer(INVISIBLE);
		B_Invisible = FALSE;
	}
	if (nIDEvent == MAGNET)
	{
		KillTimer(MAGNET);
		B_Magnet = FALSE;
	}
	CView::OnTimer(nIDEvent);
}


BOOL CMFCApplication5View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}


void CMFCApplication5View::DrawImage(CDC* pDC)
{
	// TODO: 여기에 구현 코드 추가.
	CRect rect;
	GetClientRect(&rect);

	//게임 정보 표기
	CFont myFont;
	myFont.CreateFont(30, 15, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("굴림체"));
	pDC->SelectObject(&myFont);
	CRect rect2(rect.left + 10, rect.top + 10, rect.right - 300, rect.bottom - 10);


	//게임 맵 그리기
	CDC MemDC, MemDC2; //메모리에 DC를 만든다.
	MemDC.CreateCompatibleDC(pDC);
	MemDC2.CreateCompatibleDC(pDC);
	(CBitmap*)MemDC2.SelectObject(&wall);
	CBitmap* pOldBitmap = (CBitmap*)MemDC.SelectObject(&bitmap);
	CPoint Start_P(worm.head->P.x - rect.Width() / 2, worm.head->P.y - rect.Height() / 2);
	CPoint Wall_P(0, 0);
	for (int i = 0; i < 50; i++)
	{
		MemDC.StretchBlt(Wall_P.x, Wall_P.y, 100, 100, &MemDC2, 0, 0, 100, 100, SRCCOPY);
		Wall_P.x += 100;
	}
	Wall_P.x = 0;
	for (int i = 0; i < 50; i++)
	{
		MemDC.StretchBlt(Wall_P.x, 4900, 100, 100, &MemDC2, 0, 0, 100, 100, SRCCOPY);
		Wall_P.x += 100;
	}
	Wall_P.x = 0;
	Wall_P.y = 100;
	for (int i = 0; i < 48; i++)
	{
		MemDC.StretchBlt(0, Wall_P.y, 100, 100, &MemDC2, 0, 0, 100, 100, SRCCOPY);
		MemDC.StretchBlt(4900, Wall_P.y, 100, 100, &MemDC2, 0, 0, 100, 100, SRCCOPY);
		Wall_P.y += 100;
	}
	if (Start_P.x < 0)
		Start_P.x = 0;
	if (Start_P.x + rect.Width() > 5000)
		Start_P.x = 5000 - rect.Width();
	if (Start_P.y < 0)
		Start_P.y = 0;
	if (Start_P.y + rect.Height() > 5000)
		Start_P.y = 5000 - rect.Height();
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(),
		&MemDC, Start_P.x, Start_P.y, rect.Width(), rect.Height(),
		SRCCOPY);

	//지렁이 그리기
	if (B_Invisible == FALSE)
	{
		CPen pen;
		pen.CreatePen(PS_SOLID, 3, RGB(220, 141, 131));
		pDC->SelectObject(&pen);
		CBrush brush(RGB(242, 141, 131));
		pDC->SelectObject(&brush);
		SWorm* p1;
		p1 = worm.tail;
		while (p1 != NULL)
		{
			CPoint point;
			point.x = p1->P.x - worm.head->P.x + rect.Width() / 2;
			point.y = p1->P.y - worm.head->P.y + rect.Height() / 2;
			if (worm.head->P.x < rect.Width() / 2)
			{
				point.x -= rect.Width() / 2 - worm.head->P.x;
			}
			else if (worm.head->P.x > 5000 - rect.Width() / 2)
			{
				point.x += worm.head->P.x - 5000 + rect.Width() / 2;
			}
			if (worm.head->P.y < rect.Height() / 2)
			{
				point.y -= rect.Height() / 2 - worm.head->P.y;
			}
			else if (worm.head->P.y > 5000 - rect.Height() / 2)
			{
				point.y += worm.head->P.y - 5000 + rect.Height() / 2;
			}

			pDC->Ellipse(point.x - radius, point.y - radius, point.x + radius, point.y + radius);
			if (p1->prelink == NULL)
			{
				CPoint P_head = point;
				pDC->SelectStockObject(NULL_PEN);
				pDC->SelectStockObject(WHITE_BRUSH);
				switch (LastDirection)
				{
				case UP:
					pDC->Ellipse(P_head.x - 20, P_head.y - 23, P_head.x - 10 + 10, P_head.y + 3);
					pDC->Ellipse(P_head.x, P_head.y - 23, P_head.x + 10 + 10, P_head.y + 3);
					break;
				case DOWN:
					pDC->Ellipse(P_head.x - 20, P_head.y + 23, P_head.x - 10 + 10, P_head.y - 3);
					pDC->Ellipse(P_head.x, P_head.y + 23, P_head.x + 10 + 10, P_head.y - 3);
					break;
				case LEFT:
					pDC->Ellipse(P_head.x - 23, P_head.y - 20, P_head.x + 3, P_head.y);
					pDC->Ellipse(P_head.x - 23, P_head.y, P_head.x + 3, P_head.y + 20);
					break;
				case RIGHT:
					pDC->Ellipse(P_head.x + 23, P_head.y - 20, P_head.x - 3, P_head.y);
					pDC->Ellipse(P_head.x + 23, P_head.y, P_head.x - 3, P_head.y + 20);
					break;
				default:break;
				}
				pDC->SelectStockObject(BLACK_BRUSH);
				switch (LastDirection)
				{
				case UP:
					pDC->Ellipse(P_head.x - 15, P_head.y - 20, P_head.x - 10 + 5, P_head.y-5);
					pDC->Ellipse(P_head.x + 5, P_head.y - 20, P_head.x + 15, P_head.y-5);
					break;
				case DOWN:
					pDC->Ellipse(P_head.x - 15, P_head.y + 20, P_head.x - 10 + 5, P_head.y+5);
					pDC->Ellipse(P_head.x + 5, P_head.y + 20, P_head.x + 10 + 5, P_head.y+5);
					break;
				case LEFT:
					pDC->Ellipse(P_head.x - 20, P_head.y - 15, P_head.x-5, P_head.y - 5);
					pDC->Ellipse(P_head.x - 20, P_head.y + 5, P_head.x-5, P_head.y + 15);
					break;
				case RIGHT:
					pDC->Ellipse(P_head.x + 20, P_head.y - 15, P_head.x+5, P_head.y - 5);
					pDC->Ellipse(P_head.x + 20, P_head.y + 5, P_head.x+5, P_head.y + 15);
					break;
				default:break;
				}
			}
			if (p1->prelink != NULL)
			{
				if (worm.head->P.x == p1->P.x && worm.head->P.y == p1->P.y)
				{
					GameOver = TRUE;
				}
			}
			p1 = p1->prelink;
			if (B_Magnet == TRUE && p1 == NULL)
			{
				CPen redpen;
				redpen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				pDC->SelectObject(&redpen);
				pDC->SelectStockObject(NULL_BRUSH);
				pDC->Ellipse(point.x - 200, point.y - 200, point.x + 200, point.y + 200);
			}
		}
	}


	//아이템그리기
	SCoin* p2;
	p2 = coin.head;
	while (p2 != NULL)
	{
		CPoint point;
		point.x = p2->P.x - worm.head->P.x + rect.Width() / 2;
		point.y = p2->P.y - worm.head->P.y + rect.Height() / 2;
		if (worm.head->P.x < rect.Width() / 2)
		{
			point.x -= rect.Width() / 2 - worm.head->P.x;
		}
		else if (worm.head->P.x > 5000 - rect.Width() / 2)
		{
			point.x += worm.head->P.x - 5000 + rect.Width() / 2;
		}

		if (worm.head->P.y < rect.Height() / 2)
		{
			point.y -= rect.Height() / 2 - worm.head->P.y;
		}
		else if (worm.head->P.y > 5000 - rect.Height() / 2)
		{
			point.y += worm.head->P.y - 5000 + rect.Height() / 2;
		}

		switch (p2->Type)
		{
		case N_PLUS:
			coin1.Draw(*pDC, point.x - radius, point.y - radius);
			break;
		case N_MINUS:
			coin2.Draw(*pDC, point.x - radius, point.y - radius);
			break;
		case N_INVISIBLE:
			invisible.Draw(*pDC, point.x - radius, point.y - radius);
			break;
		case N_MAGNET:
			mag.Draw(*pDC, point.x - radius, point.y - radius);
			break;
		default:break;
		}
		p2 = p2->link;
	}

	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(_T("Name : "), CRect(10, 10, 200, 40), DT_TOP | DT_LEFT);
	pDC->DrawText(name, CRect(120, 10, 350, 40), DT_TOP | DT_LEFT);

	CString str_score;
	str_score.Format(_T("%d"), score);
	pDC->DrawText(_T("SCORE : "), CRect(rect.right - 300, 10, rect.right - 170, 40), DT_TOP | DT_LEFT);
	pDC->DrawText(str_score, CRect(rect.right - 170, 10, 2000, 40), DT_TOP | DT_LEFT);

	pDC->DrawText(_T("HP "), CRect(360, 10, 420, 40), DT_TOP | DT_LEFT);
	CBrush green(RGB(0, 255, 0));
	CBrush orange(RGB(255, 128, 0));
	CBrush red(RGB(255, 0, 0));
	pDC->SelectStockObject(NULL_PEN);
	if (hp > 100)
	{
		pDC->SelectObject(&green);
	}
	else if (hp > 50)
	{
		pDC->SelectObject(&orange);
	}
	else
	{
		pDC->SelectObject(&red);
	}
	int wd = rect.right - 400 - 420;
	pDC->Rectangle(420, 10, 420 + wd * hp / 200, 40);
	//장애물 충돌
	if (worm.head->P.x < 100 || worm.head->P.x>4900 || worm.head->P.y < 100 || worm.head->P.y>4900)
	{
		GameOver = TRUE;
	}
	//체력 고갈
	if (hp <= 0)
	{
		GameOver = TRUE;
	}
}


void CMFCApplication5View::ResetGame()
{
	// TODO: 여기에 구현 코드 추가.
	score = 0;
	GameOver = FALSE;
	void* p = worm.tail;
	void* temp;
	while (p != NULL)
	{
		temp = ((struct SWorm*)p)->prelink;
		free(p);
		p = temp;
	}
	p = coin.head;
	while (p != NULL)
	{
		temp = ((struct SCoin*)p)->link;
		free(p);
		p = temp;
	}
	worm.head = (SWorm*)malloc(sizeof(SWorm));
	worm.tail = (SWorm*)malloc(sizeof(SWorm));
	coin.head = (SCoin*)malloc(sizeof(SCoin));
	coin.tail = (SCoin*)malloc(sizeof(SCoin));
	worm.tail = worm.head;
	coin.tail = coin.head = NULL;
	worm.head->P = { 2500,2500 };
	worm.head->prelink = worm.head->link = NULL;
	name.Empty();
	hp = 200;
}
