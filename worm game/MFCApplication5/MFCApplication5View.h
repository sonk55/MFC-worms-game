
// MFCApplication5View.h: CMFCApplication5View 클래스의 인터페이스
//

#pragma once
#include "CWorm.h"
#include "CCoin.h"
#include <atlimage.h>
class CMFCApplication5View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication5View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication5View)

// 특성입니다.
public:
	CMFCApplication5Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCApplication5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	CPoint P;
	CDC* main;
	CWorm worm;
	int LastDirection=0;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int grade=0;
	CString name;
	CCoin coin;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void DrawImage(CDC* pDC);
	CImage mag;
	CBitmap bitmap;
	BITMAP bmpinfo;
	CImage dirt;
	CImage coin1;
	CImage coin2;
	CImage coin3;
	CBitmap wall;
	BITMAP wallinfo;
	BOOL GameOver = FALSE;
	CImage invisible;
	BOOL B_Invisible = FALSE;
	BOOL B_Magnet = FALSE;
	int score=0;
	void ResetGame();
	int hp;
};

#ifndef _DEBUG  // MFCApplication5View.cpp의 디버그 버전
inline CMFCApplication5Doc* CMFCApplication5View::GetDocument() const
   { return reinterpret_cast<CMFCApplication5Doc*>(m_pDocument); }
#endif

