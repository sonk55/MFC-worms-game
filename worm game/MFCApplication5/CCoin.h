#pragma once
struct SCoin
{
	CPoint P;
	int Type;
	int Duration;
	SCoin* link;
	SCoin* prelink;
};
class CCoin
{
public:
	CCoin();
	~CCoin();
	CPoint P;
	SCoin* head;
	SCoin* tail;
	void CreatItem();
	void SetType(int* type);
	void DeleteItem(SCoin* p);
};

