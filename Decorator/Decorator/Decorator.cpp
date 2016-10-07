#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;

#define DELETE_OBJECT(p)		{ if (p) delete p;	p = NULL; }
#define DELETE_ARRAY(p)			{ if (p) delete []p; p = NULL;}

//假设情景
//1.打印论文正文
void Demand1();
//2.新需求，打印正文之前还要打印页眉
void Demand2();
//3.新需求，打印正文之后还要打印页脚，之前要打印页眉
void Demadn3();
//通过三个需求来看装饰模式


class Component
{
public:
	virtual void Print() = 0;
protected:
private:
};

class SpecialComponent : public Component
{
public:
	void Print()
	{
		printf("Mission begin\n");
	}

protected:
private:
};

class Decorator : public Component
{
public:
	void SetComponent(Component *pComponent)
	{
		m_pComponent = pComponent;
	}
	void Print()
	{
		m_pComponent->Print();
	}

protected:
	Component *m_pComponent;
};


class PrintBody : public Decorator
{
public:
	void Print()
	{
		m_pComponent->Print();
		printf("Print body\n");
	}


protected:
private:
};

class PrintHead : public Decorator
{
public:
	void Print()
	{
		m_pComponent->Print();
		printf("Print Head\n");
		SelfBehavior();
	}
	void SelfBehavior()
	{
		printf("Author is tanben\n");
	}
protected:
private:
};

class PrintEnd : public Decorator
{
public:
	void Print()
	{
		m_pComponent->Print();
		printf("Print End\n");
		NewAddedBehavior();
	}
	void NewAddedBehavior()
	{
		printf("Day: 2012/11/28\n");
	}
protected:
private:
};


//有时候为了让业务逻辑更加清晰，
//可以将某些固定顺序的操作设计为一个类
class Demand1Factory
{
public:
	Component * CreateComponet()
	{
		m_pDemand1 = new SpecialComponent();
		m_pBody = new PrintBody();
		m_pBody->SetComponent(m_pDemand1);
		return m_pBody;
	}
	void Release()
	{
		DELETE_OBJECT(m_pDemand1);
		DELETE_OBJECT(m_pBody);
	}
protected:
	SpecialComponent *m_pDemand1;
	PrintBody		 *m_pBody;
};







int _tmain(int argc, _TCHAR* argv[])
{

	Demand1();
	Demand2();
	Demadn3();

	return 0;
}



void Demand1()
{
	Demand1Factory d1Factory;
	Component *pDemand = d1Factory.CreateComponet();
	pDemand->Print();
	d1Factory.Release();
}

void Demand2()
{
	SpecialComponent *pSC = new SpecialComponent();
	PrintBody *pBody = new PrintBody();
	PrintHead *pHead = new PrintHead();
	pHead->SetComponent(pSC);
	pBody->SetComponent(pHead);
	pBody->Print();
	DELETE_OBJECT(pSC);
	DELETE_OBJECT(pBody);
	DELETE_OBJECT(pHead);
}

void Demadn3()
{
	SpecialComponent *pSC = new SpecialComponent;
	PrintBody *pBody = new PrintBody();
	PrintHead *pHead = new PrintHead();
	PrintEnd  *pEnd = new PrintEnd();
	pHead->SetComponent(pSC);
	pBody->SetComponent(pHead);
	pEnd->SetComponent(pBody);
	pEnd->Print();
	DELETE_OBJECT(pSC);
	DELETE_OBJECT(pBody);
	DELETE_OBJECT(pHead);
	DELETE_OBJECT(pEnd);
}


