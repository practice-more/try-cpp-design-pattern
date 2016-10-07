#include "stdafx.h"

class CashSuper
{
public:
	virtual double CalcCash() = 0;
	void SetOrginCash(double dOrgCash)
	{
		m_dOrgCash = dOrgCash;
	}
protected:
	double m_dOrgCash;
};

class CashReBate : public CashSuper
{
public:
	double CalcCash()
	{
		return m_dOrgCash * 0.85;
	}
};

class CashReturn : public CashSuper
{
public:
	double CalcCash()
	{
		if (m_dOrgCash > 300)
		{
			return m_dOrgCash - 100;
		}
		else
		{
			return m_dOrgCash;
		}
	}
};

class CashContext
{
public:
	double GetResult(double dMoney)
	{
		m_pCashSuper->SetOrginCash(dMoney);
		return m_pCashSuper->CalcCash();
	}
	void SetCashSuper(CashSuper *pCashSuper)
	{
		m_pCashSuper = pCashSuper;
	}
	/*void ReleaseCashSuper()
	{
	if (m_pCashSuper)
	{
	delete m_pCashSuper;
	m_pCashSuper = NULL;
	}
	}*/
protected:
	CashSuper *m_pCashSuper;

};

int _tmain(int argc, _TCHAR* argv[])
{
	//现在商场进入打折季节，都使用打折suanfa
	CashSuper *pCSuper = new CashReBate;
	CashContext CContext;
	CContext.SetCashSuper(pCSuper);
	//CContext.SetCashSuper(new CashReturn)
	//CContext.ReleaseCashSuper();
	double dPay = CContext.GetResult(100.0f);

	if (pCSuper)
	{
		delete pCSuper;
		pCSuper = NULL;
	}
	return 0;
}
