// 委托就是i一种引用方法的类型，一旦为委托分配了方法，委托将与
// 该方法具有完全相同的行为，委托方法的使用可以像其他任何方法一样，
// 具有参数和返回值，委托可以看做是对函数的抽象，是函数的“类”，委托
// 的实例代表一个具体的函数

// 委托对象所搭载的所有方法必须具有相同的原型和相识，
// 也就是有相同的参数列表和返回值类型


// C++ 函数指针很神奇，不是吗？

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;

// 对象类，也可以使用类模板来实现
// 实际上，对于void* pArg可以进行进一步的封装
class Object
{
public:
	typedef long (Object::*pFunc)(Object *pObj, void* pArg);
protected:
private:
};


class NameContainer
{
public:
	string strName;
};

// 事件类
class EventHandler
{
public:
	EventHandler(Object *pObject, Object::pFunc pFuncion)
		: m_pObj(pObject)
		, m_pFunc(pFuncion)
	{

	}

	long operator()(Object* pObj, void* pArg)
	{
		return (m_pObj->*m_pFunc)(pObj, pArg);
	}
protected:
	Object			*m_pObj;
	Object::pFunc	m_pFunc;
private:
};

// 事件类的容器
class EventsContainer
{
public:
	// 某些重载就不写了
	EventsContainer& operator +=(const EventHandler& rEvent)
	{
		m_EventsVec.push_back(rEvent);
		return *this;
	}
	long operator()(Object* pObj, void *pArg)
	{
		for (int i = 0; i < m_EventsVec.size(); i++)
		{
			// 暂不对返回值进行判断
			m_EventsVec[i](pObj, pArg);
		}
		return 0;
	}
protected:

private:
	vector<EventHandler>  m_EventsVec;
};



class PersonA : public Object
{
public:
	PersonA(const string &strName)
	{
		m_strName = strName;
	}
	long TellName(Object *pObj, void* pArg)
	{

		// 当然，PersonA是知道这个函数是干什么的，参数是什么
		// 如果不知道的话，利用多态也可以很好解决问题
		// 大不了就是抽象出参数部分处理函数
		string strName = (*((NameContainer*)pArg)).strName;

		cout << "Hello! " << strName.c_str() << ".\nMy name is: " << m_strName.c_str() << endl;
		// 直接cout pArg 就是这个指针的地址了
		return 1;
	}
protected:
private:
	string m_strName;
};

int _tmain(int argc, _TCHAR* argv[])
{
	EventsContainer  tellName;
	PersonA *pA = new PersonA("Joky");
	// Joky不是一个敏锐的人，所以他每次参加聚会前都带着一个提示器
	// 以便于第一时间做自我介绍，尤其是对美女
	// 提示器是[tellName]系统
	//注册事件
	tellName += EventHandler(
		(Object*)pA,						 // 主体 
		(Object::pFunc)&PersonA::TellName);  // 事件

	// 在一次聚会上
	// Joky通过[tellName}系统获得了一个陌生人的名字
	// 陌生人叫[Fuuny]
	NameContainer nc;
	nc.strName = "Fuuny";
	tellName(pA, (void*)&nc);

	if (pA)
	{
		delete pA;
		pA = NULL;
	}

	return 0;
}


// 执行结果
//Hello! Fuuny.
//My name is: Joky
//请按任意键继续. . .