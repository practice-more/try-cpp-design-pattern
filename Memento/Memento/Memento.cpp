// Memento.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// 备忘录模式(Memento): 再不跑坏封装性的前提下
// 捕获一个对象的内部状态， 并在对象之外保存这个状态
// 这样以后就可将该对象恢复到原先保存的状态


// 情景假设，存储于恢复游戏中人物的状态

// 模拟的人物状态的结构体
struct SRoleState
{
	int nlevle;
	int nHp;
	int nMp;
};

// 人物状态的存档
class Memento
{
public:
	void GetInfo(SRoleState &sState) const
	{
		sState = m_sRolestate;
	}
	void SetInfo(const SRoleState& sState)
	{
		m_sRolestate = sState;
	}
private:
	SRoleState	m_sRolestate;
};

// 人物角色
class Role
{
public:
	void SaveState(Memento &memo)
	{
		memo.SetInfo(m_sRoleState);

	}
	void LoadState(const Memento &memo)
	{
		memo.GetInfo(m_sRoleState);
	}

	void SetRoleState_fortest(int lvl, int hp, int mp)
	{
		m_sRoleState.nlevle = lvl;
		m_sRoleState.nHp = hp;
		m_sRoleState.nMp = mp;
	}

	void ShowInfor()
	{
		printf("The lvl of hero is %d\nHp:%d\nMp:%d\n",
			m_sRoleState.nlevle,
			m_sRoleState.nHp,
			m_sRoleState.nMp);
	}
protected:
	SRoleState m_sRoleState;
};

class MementoMgr
{
public:
	void SetMemnto(const Memento& mem)
	{
		m_memento = mem;
	}
	Memento GetMemnto()
	{
		return m_memento;
	}
protected:
	Memento		m_memento;
private:
};

int _tmain(int argc, _TCHAR* argv[])
{
	MementoMgr mgr;
	Role hero;


	// 英雄的初始属性
	hero.SetRoleState_fortest(0, 100, 100);
	hero.ShowInfor();
	Memento memStart;
	hero.SaveState(memStart);
	mgr.SetMemnto(memStart);

	// 后来英雄的属性
	hero.SetRoleState_fortest(10, 500, 300);
	hero.ShowInfor();

	// 回档
	hero.LoadState(mgr.GetMemnto());
	hero.ShowInfor();
	return 0;
}

// 输出结果：
//The lvl of hero is 0
//Hp:100
//Mp:100
//The lvl of hero is 10
//Hp:500
//Mp:300
//The lvl of hero is 0
//Hp:100
//Mp:100

