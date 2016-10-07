// 模板方法模式， 定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。
// 模板方法使得子类可以不改变一个算法的结构既可冲定义该算法的某些特定步骤。


// 问1：和泛型编程区别？
// 问2：感觉用策略模式也可以啊？

// 答1：泛型编程改变的是数据类型，模板方法一个改变的是自定义的实现细节。
// 答2：模板方法模式更后一层，为算法的实现细节，而策略模式是针对几种算法。

#include "stdafx.h"


// 函数模板
template<typename T>
int Compare(const T &v1, const T &v2)
{
	if (v1 < v2)
	{
		return -1;
	}
	else if (v1 > v2)
	{
		return 1;
	}
	else
		return 0;
}


// 类模板
template<class Type>
class CCompare
{
public:
	CCompare(const Type & v1, const Type & v2)
	{
		m_tFirst = v1;
		m_tSecond = v2;
	}
	~CCompare(){ ; }

	//template<class Type>
	int Compare()
	{
		if (m_tFirst < m_tSecond)
		{
			return -1;
		}
		else if (m_tFirst > m_tSecond)
		{
			return 1;
		}
		else
			return 0;
	}
private:
	Type  m_tFirst;
	Type  m_tSecond;
};

//模板方法
class Bill
{
public:
	virtual void AddCondition() = 0;
	void Pay()
	{
		AddCondition();
		printf("You need pay $100!\n");
	}
protected:
private:
};

class MaleBill : public Bill
{
public:
	void AddCondition()
	{
		printf("Sir!\n");
	}
protected:
private:
};

class FemaleBill : public Bill
{
public:
	void AddCondition()
	{
		printf("Lady!\n");
	}
protected:
private:
};



// 测试函数
void TestTemplateFunc()
{
	int result;
	result = Compare(2.3, 3.1);
	result = Compare(1, 2);
}

void TestTemplateClass()
{
	int result;
	CCompare<double> cp(2.3, 3.1);
	result = cp.Compare();

	CCompare<int> cp1(1, 2);
	result = cp1.Compare();
}

void TestTemplateMethod()
{
	Bill *pMale = new MaleBill;
	pMale->Pay();
	Bill *pFemale = new FemaleBill;
	pFemale->Pay();

	if (pMale)
	{
		delete pMale;
		pMale = NULL;
	}
	if (pFemale)
	{
		delete pFemale;
		pFemale = NULL;
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	//测试模板函数
	TestTemplateFunc();
	//测试模板类
	TestTemplateClass();
	//测试模板方法
	TestTemplateMethod();

	return 0;
}