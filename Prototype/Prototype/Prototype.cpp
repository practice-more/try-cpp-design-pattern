#include "stdafx.h"
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <iostream>




// 原型模式其实就是从一个对象再创建另外一个可定制的对象，而且不需要知道任何创建的细节


// 问1：和deepCopy有什么区别？重载"="或者写一个DeepCopy函数就可以了嘛？
// 问2：貌似没有最大限度的节省内存，要节省内存是不是要用享元模式？
// 问3：C++里面可没有什么MemberwiseClone()



// 假设情景，某游戏，当用户新建角色时，会出现一个基础角色，
// 然后用户再在此基础上对该基础角色进行修改
// （其实应该是根据玩家的性别，身形选择，大致创建一个基础的角色外形，然后由玩家装扮，本处简化）

// char *纯粹是用于深拷贝

#define DELETE_OBJECT(p)	{ if (p) delete p;	p = NULL; }

enum ESex
{
	male,
	famale
};

class IRole
{
public:
	virtual void Setproperty(ESex eSex, int nAge) = 0;
	virtual void SetDescription(char * pDescpt, int nLength) = 0;
	virtual void Show() = 0;
	virtual IRole* Clone() = 0;
	virtual void SetName(const std::string &strName) = 0;

protected:
	std::string m_strName;
	ESex		m_eSex;
	int			m_nAge;
	char*		m_pDescription;
	int			m_nDscriptLength;

};

class BaseRole : public IRole
{
public:
	BaseRole()
		//: m_eSex(male)
		//, m_nAge(25)
		//, m_pDescription(NULL)
	{
		m_eSex = male;
		m_nAge = 25;
		m_pDescription = NULL;
	}
	virtual ~BaseRole()
	{
		DELETE_OBJECT(m_pDescription);
	}

	void SetName(const std::string &strName)
	{
		m_strName = strName;
	}
	void Setproperty(ESex eSex, int nAge)
	{
		m_eSex = eSex;
		m_nAge = nAge;
	}
	void SetDescription(char * pDescpt, int nLength)
	{
		m_nDscriptLength = nLength;
		m_pDescription = new char[nLength + 1];
		memset(m_pDescription, 0, nLength + 1);
		memcpy(m_pDescription, pDescpt, nLength);
	}
	void Show()
	{
		printf("\n\nNow Show A Role Information:\n");
		printf("Name:%s\n", m_strName.c_str());
		if (male == m_eSex)
		{
			printf("Sex: Male\n");
		}
		else
		{
			printf("Sex: FeMale\n");
		}
		printf("Age :%d\n", m_nAge);
		printf(m_pDescription);
		printf("\n");
	}
	IRole* Clone()
	{
		BaseRole * pRole = new BaseRole;
		pRole->m_eSex = m_eSex;
		pRole->m_nAge = m_nAge;
		pRole->m_strName = m_strName;
		pRole->m_nDscriptLength = m_nDscriptLength;
		pRole->m_pDescription = new char[m_nDscriptLength + 1];
		memset(pRole->m_pDescription, 0, m_nDscriptLength + 1);
		memcpy(pRole->m_pDescription, m_pDescription, m_nDscriptLength);
		return pRole;
	}

protected:
private:
};


int _tmain(int argc, _TCHAR* argv[])
{

	//创建描述语句
	char *pChar = "So clever!";
	int nLength = strlen(pChar);

	char *pChar_1 = "A Nice People!";
	int nLength_1 = strlen(pChar_1);

	//创建BaseRole
	BaseRole *pBase = new BaseRole;
	pBase->Setproperty(male, 15);
	pBase->SetDescription(pChar, nLength);
	pBase->SetName("BaseRole");

	//根据BaseRole创建其他
	BaseRole *pTom = (BaseRole*)pBase->Clone();
	pTom->SetDescription(pChar_1, nLength_1);
	pTom->SetName("Tom");

	BaseRole *pLucy = dynamic_cast<BaseRole*>(pBase->Clone());
	pLucy->Setproperty(famale, 18);
	pLucy->SetName("Lucy");

	pBase->Show();
	pTom->Show();
	pLucy->Show();

	DELETE_OBJECT(pBase);
	DELETE_OBJECT(pTom);
	DELETE_OBJECT(pLucy);

	return 0;
}

/*结果
Now Show A Role Information:
Name:BaseRole
Sex: Male
Age :15
So clever!


Now Show A Role Information:
Name:Tom
Sex: Male
Age :15
A Nice People!


Now Show A Role Information:
Name:Lucy
Sex: FeMale
Age :18
So clever!
请按任意键继续. . .
*/