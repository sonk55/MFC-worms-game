#include "pch.h"
#include "CWorm.h"

CWorm::CWorm()
{
	head = NULL;
	tail = NULL;
	head = (SWorm*)malloc(sizeof(SWorm));
	tail = (SWorm*)malloc(sizeof(SWorm));
	tail = head;
	head->P.x = 2500;
	head->P.y = 2500;
	head->prelink = head->link = NULL;
}
CWorm::~CWorm()
{
}

void CWorm::MoveWorm(int Direction)
{
	// TODO: 여기에 구현 코드 추가.
	SWorm* p = tail;
	while (p != NULL)
	{
		if (p->prelink == NULL)
			break;
		p->P.x = p->prelink->P.x;
		p->P.y = p->prelink->P.y;
		p = p->prelink;
	}
	switch (Direction)
	{
	case UP:
		head->P.y -= MOVERANGE;
		break;
	case DOWN:
		head->P.y += MOVERANGE;
		break;
	case LEFT:
		head->P.x -= MOVERANGE;
		break;
	case RIGHT:
		head->P.x += MOVERANGE;
		break;
	default:
		break;
	}
}


void CWorm::ClearWorm(CClientDC *dc)
{
	// TODO: 여기에 구현 코드 추가.
	SWorm* p = tail;
	dc->SelectStockObject(WHITE_PEN);

	dc->Ellipse(p->P.x, p->P.y, p->P.x + radius, p->P.y + radius);

	if (tail->prelink != NULL)
	{
		dc->Ellipse(p->prelink->P.x, p->prelink->P.y, p->prelink->P.x + radius, p->prelink->P.y + radius);
	}
}


void CWorm::PlusBody(int Direction)
{
	// TODO: 여기에 구현 코드 추가.
	SWorm* newNode,*p;
	newNode = (SWorm*)malloc(sizeof(SWorm));
	CPoint P;
	p = tail;
	if (p->prelink != NULL)
	{
		P.x = p->P.x + (p->P.x - p->prelink->P.x);
		P.y = p->P.y + (p->P.y - p->prelink->P.y);
	}
	else
	{
		switch (Direction)
		{
		case UP:
			P.x = p->P.x;
			P.y = p->P.y + BODYGAP;
			break;
		case DOWN:
			P.x = p->P.x;
			P.y = p->P.y - BODYGAP;
			break;
		case LEFT:
			P.x = p->P.x + BODYGAP;
			P.y = p->P.y;
			break;
		case RIGHT:
			P.x = p->P.x - BODYGAP;
			P.y = p->P.y;
			break;
		}
	}
	newNode->P = P;
	newNode->prelink = p;
	newNode->link = NULL;
	p->link = newNode;
	tail = newNode;
}


void CWorm::MinusBody()
{
	// TODO: 여기에 구현 코드 추가.
	SWorm* pre;
	pre = tail->prelink;
	free(tail);
	tail = pre;
}
