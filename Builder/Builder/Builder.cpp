// 建造者模式（Builder），将一个复杂对象的构造与它的表示分离，
// 使得同样的构建过程可以创建不同的表示


// 大概就是把一个整体结构的几个可能变化的部分拆为独立的函数
// 然后再派生类重载实现的方式

// 主要应对与整体中变化的部件，
// 而不是流程状态，要不然可以用状态模式，
// 请求处理的流程可以用职责链模式

// 这次状态不好，就偷懒，直接用《大话设计模式》Java代码，翻译为C++了


// 情景，画人物
// 人物包括 头 手 脚 肚子
// 人物有两种 胖子和瘦子
// 胖瘦的区别主要在于肚子不同。

#include "stdafx.h"
#include <Windows.h>
#include <iostream>

using namespace std;


class PersonBuilder
{
public:
	PersonBuilder(const string & strGrap, const string & strPen)
	{
		m_strGraphics = strGrap;
		m_strPen = strPen;
	}
	virtual ~PersonBuilder()
	{

	}
	virtual void BuildHead() = 0;
	virtual void BuildBody() = 0;
	virtual void BuildLeg() = 0;

protected:
	string	m_strGraphics;
	string  m_strPen;

private:
};

class PersonThinBuilder : public PersonBuilder
{
public:
	PersonThinBuilder(const string & strGrap, const string & strPen)
		: PersonBuilder(strGrap, strPen)
	{

	}
	void BuildHead()
	{
		cout << "With " << m_strPen.c_str() << endl;
		printf("Draw normal head\n");
		cout << "On" << m_strGraphics.c_str() << endl;

	}
	void BuildBody()
	{
		cout << "With " << m_strPen.c_str() << endl;
		printf("Draw thin body\n");
		cout << "On" << m_strGraphics.c_str() << endl;

	}
	void BuildLeg()
	{
		cout << "With " << m_strPen.c_str() << endl;
		printf("Draw normal leg\n");
		cout << "On" << m_strGraphics.c_str() << endl;

	}

protected:
private:
};


class PersonFatBuilder : public PersonBuilder
{
public:
	PersonFatBuilder(const string & strGrap, const string & strPen)
		: PersonBuilder(strGrap, strPen)
	{

	}
	void BuildHead()
	{
		cout << "With " << m_strPen.c_str() << endl;
		printf("Draw normal head\n");
		cout << "On" << m_strGraphics.c_str() << endl;
	}
	void BuildBody()
	{
		cout << "With " << m_strPen.c_str() << endl;
		printf("Draw Fat body\n");
		cout << "On" << m_strGraphics.c_str() << endl;
	}
	void BuildLeg()
	{
		cout << "With " << m_strPen.c_str() << endl;
		printf("Draw normal leg\n");
		cout << "On" << m_strGraphics.c_str() << endl;
	}

protected:
private:
};


class PersonDirector
{
public:

	void SetPersonBuilder(PersonBuilder * pb)
	{
		m_pPbuilder = pb;
	}

	void CreatePerson()
	{
		m_pPbuilder->BuildHead();
		m_pPbuilder->BuildBody();
		m_pPbuilder->BuildLeg();
	}
protected:
private:
	PersonBuilder * m_pPbuilder;

};

int _tmain(int argc, _TCHAR* argv[])
{
	PersonBuilder *pThinBuilder = new PersonThinBuilder("Screen", "YellowPen");
	PersonBuilder *pFatBuilder = new PersonFatBuilder("Screen", "WhitePen");
	PersonDirector pd;
	pd.SetPersonBuilder(pThinBuilder);
	pd.CreatePerson();
	pd.SetPersonBuilder(pFatBuilder);
	pd.CreatePerson();

	if (pThinBuilder)
	{
		delete pThinBuilder;
		pThinBuilder = NULL;
	}
	if (pFatBuilder)
	{
		delete pFatBuilder;
		pFatBuilder = NULL;
	}
	return 0;
}


//输出结果
//With YellowPen
//Draw normal head
//OnScreen
//With YellowPen
//Draw thin body
//OnScreen
//With YellowPen
//Draw normal leg
//OnScreen
//With WhitePen
//Draw normal head
//OnScreen
//With WhitePen
//Draw Fat body
//OnScreen
//With WhitePen
//Draw normal leg
//OnScreen
//请按任意键继续. . .