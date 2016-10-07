// Interpert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
using namespace std;

// 解释器模式：给定一种语言，定义它的文法的一种表示，并定义一个解释器
// 该解释器使用该表示来解释语言中的句子

// 类似于程序语言或者脚本

// 假设情景是一个脚本控制系统
// wasd上下左右方向，正数数字为移动步数
// 简化一下吧，测试和开发支持wasd字母，移动步数为1-9的正整数


class Fire
{
public:


};

class Action
{
public:
	virtual void Interpret(string &strCmd)
	{
		if (strCmd.length() == 0)
		{
			return;
		}
		else
		{
			string strNum = strCmd.substr(1, 2);
			m_nNum = atoi(strNum.c_str());
			strCmd = strCmd.substr(2);
			Excute();
		}
	}
	virtual void Excute() = 0;
protected:
	int		m_nNum;

};


// W
class Forward : public Action
{
public:
	void Excute()
	{
		for (int i = 0; i < m_nNum; i++)
		{
			printf("前进  ");
		}
	}
};

// A
class Left : public Action
{
public:
	void Excute()
	{
		for (int i = 0; i < m_nNum; i++)
		{
			printf("左移  ");
		}
	}
};

class Right : public Action
{
public:
	void Excute()
	{
		for (int i = 0; i < m_nNum; i++)
		{
			printf("右移  ");
		}
	}
};

// S
class Back : public Action
{
public:
	void Excute()
	{
		for (int i = 0; i < m_nNum; i++)
		{
			printf("后退  ");
		}
	}
};

void Interper(string &str)
{
	string tmpStr = str.substr(0, 1);
	Action	*pAction = NULL;

	char t;
	memcpy(&t, tmpStr.c_str(), 1);
	switch (t)
	{
	case 'W':
		pAction = new Forward();
		break;
	case 'A':
		pAction = new Left();
		break;
	case 'D':
		pAction = new Right();
		break;
	case 'S':
		pAction = new Back();
		break;
	default:
		break;
	}
	if (pAction)
	{
		pAction->Interpret(str);
		delete pAction;
		pAction = NULL;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	string str = "A7S4D4W1A5D5";
	while (str.length() != 0)
	{
		Interper(str);
	}
	printf("\n");

	return 0;
}
