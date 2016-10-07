// 本来是要写组合模式的，仓促写个大概吧
// 先写一个三维中的普通的树型裁剪
// 场景中以一棵树来组织
// 树有子节点，每个树节点也有模型节点

// 随便写写的，没有运行，也没有参考，如有不当，请指出

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;

struct Point3d
{
	double x;
	double y;
	double z;
};

class SpatialObject
{
public:
	SpatialObject(){ ; }
	virtual ~SpatialObject()
	{
		;
	}
	virtual void Cull() = 0;
protected:
	virtual bool IsInFrustum(){ return true; }
	Point3d m_Center;
	double	m_dRadius;
};

class SpatialMode : public SpatialObject
{
public:
	~SpatialMode()
	{
		;
	}
	void Draw(){ ; }
	void Cull()
	{
		if (IsInFrustum())
		{
			Draw();
		}
	}
};

class SpatialNode : public SpatialObject
{
public:
	~SpatialNode()
	{
		// 删除节点中的模型
		vector<SpatialMode*>::iterator modeIter = m_SubMode.begin();
		for (; modeIter != m_SubMode.end(); ++modeIter)
		{
			SpatialMode *pMode = static_cast<SpatialMode*>(*modeIter);
			if (pMode)
			{
				delete pMode;
				pMode = NULL;
			}
		}
		m_SubMode.clear();

		// 删除子节点
		vector<SpatialNode*>::iterator nodeIter = m_SubNode.begin();
		for (; nodeIter != m_SubNode.end(); ++nodeIter)
		{
			SpatialNode* pNode = static_cast<SpatialNode*>(*nodeIter);
			if (pNode)
			{
				delete pNode;
				pNode = NULL;
			}
		}
		m_SubNode.clear();
	}
	void Cull()
	{
		vector<SpatialMode*>::iterator modeIter = m_SubMode.begin();
		for (; modeIter != m_SubMode.end(); ++modeIter)
		{
			SpatialMode *pMode = static_cast<SpatialMode*>(*modeIter);
			pMode->Cull();
		}
		vector<SpatialNode*>::iterator nodeIter = m_SubNode.begin();
		for (; nodeIter != m_SubNode.end(); ++nodeIter)
		{
			SpatialNode* pNode = static_cast<SpatialNode*>(*nodeIter);
			pNode->Cull();
		}
	}
	void AddSubNode(SpatialNode*){ ; }
	void AddSubMode(SpatialMode*){ ; }
	void RemoveSubNode(SpatialNode*){ ; }
	void RemoveSubMode(SpatialMode*){ ; }
protected:
	vector<SpatialNode*>		m_SubNode;
	vector<SpatialMode*>		m_SubMode;
};

void ReadFile(IN const wstring& wstrFile, OUT SpatialMode* &pMode)
{
	// 从文件中构建模型
	;
}
void BuildTree(IN const vector<SpatialMode*>&, OUT SpatialNode* pRootNode)
{
	// 根据模型集合构建树
	// 中间会new SpatialNode
	;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int k = 2;
	vector<SpatialMode*> modeVec;
	for (int i = 0; i < k; i++)
	{
		SpatialMode *pMode = new SpatialMode;
		ReadFile(L"filePath i", pMode);
		modeVec.push_back(pMode);
	}
	SpatialObject* pRootNode = new SpatialNode();
	BuildTree(modeVec, dynamic_cast<SpatialNode*>(pRootNode));

	// 假设渲染一千帧吧
	int frame = 0;
	while (frame == 1000)
	{
		pRootNode->Cull();
		frame++;
	}

	// 析构
	// 会调用子类的析构函数层层析构
	if (pRootNode)
	{
		delete pRootNode;
		pRootNode = NULL;
	}
	return 0;
}
