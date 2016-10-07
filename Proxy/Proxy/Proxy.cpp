#include "stdafx.h"  
#include <windows.h>  
#include <iostream>  
using namespace std;

//大话设计模式中的例子  
//A君让代理人B君给C小姐送礼物  

class IGiveGift
{
public:
	IGiveGift(){ ; }
	virtual ~IGiveGift(){ ; }

	virtual void GiveGift() = 0;
};

class PersonA : public IGiveGift
{
public:
	PersonA(const std::string & strGirlName)
	{
		m_strGirlName = strGirlName;
	}
	void GiveGift()
	{
		std::cout << m_strGirlName.c_str() << "," << "送你的礼物！" << endl;
	}
private:
	std::string m_strGirlName;

};

class ProxyB : public IGiveGift
{
public:
	void SetClientPerson(PersonA *pA)
	{
		m_pPersonA = pA;
	}
	void GiveGift()
	{
		m_pPersonA->GiveGift();
	}
private:
	PersonA *m_pPersonA;
};

int _tmain(int argc, _TCHAR* argv[])
{
	//A君出现了，怀着对心上人的思念  
	PersonA *pA = new PersonA("C小姐");
	//A君不好意思送礼物，于是找到了代理B君  
	ProxyB *pB = new ProxyB();
	pB->SetClientPerson(pA);
	//B君送礼来了  
	pB->GiveGift();

	//落幕  
	if (pA)
	{
		delete pA;
		pA = NULL;
	}
	if (pB)
	{
		delete pB;
		pB = NULL;
	}
	return 0;
}
