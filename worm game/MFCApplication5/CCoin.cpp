#include "pch.h"
#include "CCoin.h"

CCoin::CCoin()
{
	head = NULL;
	tail = NULL;
}
CCoin::~CCoin()
{
}


void CCoin::CreatItem()
{
	// TODO: 여기에 구현 코드 추가.
	SCoin* newnode = (SCoin*)malloc(sizeof(SCoin));

	CPoint P;
	P.x = rand() % 4740 + 120;
	P.y = rand() % 4740 + 120;
	newnode->P = P;
	SetType(&(newnode->Type));
	newnode->Duration = DURATION_TIME;
	if (head == NULL)
	{
		newnode->prelink = NULL;
		newnode->link = NULL;
		head = tail = newnode;
	}
	else
	{
		SCoin* p = tail;
		newnode->prelink = p;
		newnode->link = NULL;
		p->link = newnode;
		tail = newnode;
	}
}


void CCoin::SetType(int* type)
{
	// TODO: 여기에 구현 코드 추가.
	int per = rand() % 1000;
	if (per >= 200)
		*type = N_PLUS;
	else if (per >= 100)
		*type = N_MINUS;
	else if (per >= 70)
		*type = N_INVISIBLE;
	else if (per >= 0)
		*type = N_MAGNET;
}


void CCoin::DeleteItem(SCoin* p)
{
	// TODO: 여기에 구현 코드 추가.
	if (p->prelink != NULL)
	{
		if (p->link == NULL)
		{
			tail = p->prelink;
			tail->link = NULL;
		}
		else
		{
			p->link->prelink = p->prelink;
			p->prelink->link = p->link;
		}
	}
	else if (p->prelink == NULL)
	{
		if (p->link == NULL)
		{
			head = NULL;
			tail = NULL;
		}
		else
		{
			head = p->link;
			head->prelink = NULL;
		}
	}
	free(p);
}
