// 观察者模式定义了一种一对多的依赖，让多个观察者对象同时监听某一个
// 主题对象。这个主题对象在状态发生变化时，会通知所有观察者对象，使
// 他们能够自动更新自己。



// 观察者模式是一个很重要的模式，使用频率是非常高啊

// 当一个对象改变需要同时改变其他对象的时候
// 当具体不知道有多少个对象有待改变的时候。


// 适用的范围
// 在《大话模式》中，众多的观察者对象是上班开小差，看NBA，炒股票的同事
// 主题对象是坐在门口的前台。当老板回到公司的时候，前台会通知所有的“注册”
// 后的同事赶紧干正经事。


// 其实三维浏览中也可以用到
// 将各种行为作为观察者对象，摄像机为主题对象，主题对象通过给观察对象当前的
// 时间来更新各种浏览控制器，浏览控制器再调整摄像机各个参数。



// 情景假设
// 对一飞机飞行进行控制，
// 先飞行小于10秒
// 在旋转小于20秒



#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <vector>

// 毕竟作为示例，还是开发效率重要，
// 所以就用using namespace吧
using namespace std;

//浏览控制器基类
class IControl
{
public:
	virtual bool Update(double dtime) = 0;
	virtual bool Begin(double dtime) = 0;
	virtual bool IsFinish() = 0;

protected:
	double	m_dLastTime;
	bool	m_bFinish;
private:
};

//飞行浏览控制器
class FlyControl : public IControl
{
public:
	bool Begin(double dtime)
	{
		m_bFinish = false;
		m_dLastTime = dtime;
		return true;
	}
	bool Update(double dtime)
	{
		double dDetal = dtime - m_dLastTime;
		if (dDetal > 10)
		{
			cout << "Complete fly!" << endl;
			m_bFinish = true;
			return true;
		}
		cout << "We have fly  " << dDetal << "  meters!" << endl;
	}
	bool IsFinish()
	{
		return m_bFinish;
	}
protected:
private:
};

//转向浏览控制器
class RotateControl : public IControl
{
public:
	bool Begin(double dtime)
	{
		m_bFinish = false;
		m_dLastTime = dtime;
		return true;
	}
	bool Update(double dtime)
	{
		double dDetal = dtime - m_dLastTime;
		if (dDetal > 20)
		{
			cout << "Complete Rotate!" << endl;
			m_bFinish = true;
			return true;
		}
		cout << "We have Rotate  " << dDetal << "  degress" << endl;
	}
	bool IsFinish()
	{
		return m_bFinish;
	}
protected:
private:
};


// 控制器集合
class ControlList
{
public:
	int GetCount()
	{
		return m_CtrlVec.size();
	}
	void SetTime(double dTime)
	{
		m_dLastTime = dTime;
	}
	void Attach(IControl *pCtrl)
	{
		for (int i = 0; i < m_CtrlVec.size(); i++)
		{
			if (pCtrl == m_CtrlVec[i])
			{
				return;
			}
		}
		m_CtrlVec.push_back(pCtrl);
	}
	void Detach(IControl *pCtrl)
	{
		for (int i = 0; i < m_CtrlVec.size(); i++)
		{
			if (pCtrl == m_CtrlVec[i])
			{
				m_CtrlVec.erase(m_CtrlVec.begin() + i);
			}
			return;
		}
	}

	bool UpdateAllCtrls(double dtime)
	{
		double dT = dtime - m_dLastTime;
		if (dT == 0.0)
		{
			return false;
		}

		int nSize = m_CtrlVec.size();
		if (m_CtrlVec.size() != 0)
		{
			IControl* pCtrl = m_CtrlVec.front();
			if (NULL != pCtrl)
			{
				pCtrl->Update(dtime);

				if (pCtrl->IsFinish())
				{
					delete pCtrl;
					pCtrl = NULL;
					m_CtrlVec.erase(m_CtrlVec.begin());

					if (m_CtrlVec.size() != 0)
					{
						pCtrl = m_CtrlVec.front();
						if (NULL != pCtrl)
						{
							pCtrl->Begin(dtime);
						}
					}
				}
			}
		}

		m_dLastTime = dtime;

		return true;
	}

protected:
private:
	std::vector<IControl*>	m_CtrlVec;
	double					m_dLastTime;

};


// 
// Plain
// 飞机类
class Plain : public ControlList
{
public:
protected:
private:
};


int _tmain(int argc, _TCHAR* argv[])
{
	//演示程序，就不用多线程了

	Plain plain;

	//恩，现在时刻是0.0
	double curTime = 0.0;
	plain.SetTime(curTime);
	FlyControl *pFlyCtrl = new FlyControl;
	pFlyCtrl->Begin(curTime);
	plain.Attach(pFlyCtrl);
	//恩，现在时刻是0.1
	curTime = 0.1;
	RotateControl *pRoCtrl = new RotateControl;
	pRoCtrl->Begin(curTime);
	plain.Attach(pRoCtrl);

	while (plain.GetCount())
	{
		Sleep(200);
		// 模拟时间的流逝
		// 7.5倍的速度
		curTime += 1.5;
		plain.UpdateAllCtrls(curTime);
	}

	return 0;
}

// 输出结果
//We have fly  1.6  meters!
//We have fly  3.1  meters!
//We have fly  4.6  meters!
//We have fly  6.1  meters!
//We have fly  7.6  meters!
//We have fly  9.1  meters!
//Complete fly!
//We have Rotate  1.5  degress
//We have Rotate  3  degress
//We have Rotate  4.5  degress
//We have Rotate  6  degress
//We have Rotate  7.5  degress
//We have Rotate  9  degress
//We have Rotate  10.5  degress
//We have Rotate  12  degress
//We have Rotate  13.5  degress
//We have Rotate  15  degress
//We have Rotate  16.5  degress
//We have Rotate  18  degress
//We have Rotate  19.5  degress
//Complete Rotate!
//请按任意键继续. . .