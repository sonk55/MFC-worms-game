#pragma once

struct SWorm
{
	CPoint P;
	SWorm *link;
	SWorm *prelink;
};
class CWorm
{
public:
	CWorm();
	~CWorm();
	SWorm* head;
	SWorm* tail;
	void MoveWorm(int Direction);
	void ClearWorm(CClientDC *dc);
	void PlusBody(int Direction);
	void MinusBody();
};

