// Bridge.cpp : Defines the entry point for the console application.
//

// 情景假设
// 一个渲染引擎，支持D3D和OpenGL， 需要提供一系列接口，用于绘制不同物体
// 如茶壶，立方体等

// 最简单的实现是，四个函数，2 * 2，但是当多一种物体，就要多加两个函数，
// 关键是修改的部位比较靠底层。

// 使用桥接模式的话，会更支持扩展

#include "stdafx.h"


class ObjRenderInfo;

class Object
{
public:
	virtual ObjRenderInfo* GetObjInfor() = 0;
};

class Teapot : public Object
{
public:
	ObjRenderInfo* GetObjInfor(){ return NULL; }
};

class Cube : public Object
{
public:
	ObjRenderInfo* GetObjInfor(){ return NULL; }
};

class ObjRender
{
public:
	void SetObj(Object * obj)
	{
		m_object = obj;
	}
	virtual void Render() = 0;
protected:
	Object *m_object;
};

class D3DRender : public ObjRender
{
public:
	void Render()
	{
		if (m_object)
		{
			ObjRenderInfo *pInfo = m_object->GetObjInfor();
			// 使用D3d的函数结合物体本身的渲染信息，如几何体，纹理进行渲染
			D3dRenderFunction(pInfo);
		}
	}
private:
	void D3dRenderFunction(ObjRenderInfo *){ ; }
};

class OpenGLRender : public ObjRender
{
public:
	void Render()
	{
		if (m_object)
		{
			ObjRenderInfo *pInfo = m_object->GetObjInfor();
			// 使用OpenGL的函数结合物体本身的渲染信息，如几何体，纹理进行渲染
			OpenGLRenderFunction(pInfo);
		}
	}
private:
	void OpenGLRenderFunction(ObjRenderInfo *){ ; }
};


// 如果要再绘制茶杯，就添加一个茶杯类就OK了。
int _tmain(int argc, _TCHAR* argv[])
{
	ObjRender *pD3dRender = new D3DRender;
	Object *pObj = new Teapot;
	pD3dRender->SetObj(pObj);
	pD3dRender->Render();
	if (pD3dRender)
	{
		delete pD3dRender;
		pD3dRender = NULL;
	}
	if (pObj)
	{
		delete pObj;
		pObj = NULL;
	}
	return 0;
}
