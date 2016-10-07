// Visitor.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"



// 访问者模式(vistor), 表示一个作用于某对象结构中的各元素的操作，
// 它使你可以在不改变各元素类的前提下定义作用于这些元素的操作

// 假设一个绘制软件，只能够绘制线面两种类型的图形
// 但是每个图形都有多种风格（有纹理，无纹理，三维模式，等等等等）



// 绘制方式

// 绘制方式，（风格）可以无限添加，从DrawAction中派生即可
// 每个派生类中都会重载对【线】和【面】的绘制
// 其特点是，绘制风格通过指针传递给绘制对象类，绘制对象类会根据自己的指针
// 调用绘制风格的两个绘制对象函数的一种，然后由绘制风格派生类来实现绘制方式


class DrawAction
{
public:
	virtual void DrawLine() = 0;
	virtual void DrawPolygon() = 0;
};

class DrawWithTexture : public DrawAction
{
public:
	void DrawLine()			{ printf("绘制无纹理的线\n"); }
	void DrawPolygon()		{ printf("绘制无纹理的多边形\n"); }
};

class DrawWithOutTexture : public DrawAction
{
public:
	void DrawLine()			{ printf("绘制有纹理的线\n"); }
	void DrawPolygon()		{ printf("绘制有纹理的多边形\n"); }

};

class DrawIn3DModel : public DrawAction
{
public:
	void DrawLine()			{ printf("绘制3D模式下的线\n"); }
	void DrawPolygon()		{ printf("绘制3D模式下的多边形\n"); }
};


class Element
{
public:
	virtual void Draw(DrawAction *visitor) = 0;
};


class Line : public Element
{
public:
	void Draw(DrawAction *visitor)
	{
		visitor->DrawLine();
	}
};


class Polygon : public Element
{
public:
	void Draw(DrawAction *visitor)
	{
		visitor->DrawPolygon();
	}
};



// 一般的做法是，将绘制对象封装，抽象类Element中只有一个Draw纯虚函数，以及一个SetDrawStyle(...)
// 函数，通过SetStyle将风格设置进来，然后在派生类的Draw函数中用switch case绘制
// （ps.我们现在的系统就是这样写的，还好吧，比较直观，还能保存绘制风格呢）

// 但是vistor这是一种双选择模式
// 绘制的时候需要知道绘制对象的种类，和绘制风格的种类
// 传给绘制对象的不是状态的枚举，而是一个类指针
// 因为传递的是类指针，所以可进行动态绑定，通过风格类指针来调用绘制函数

int _tmain(int argc, _TCHAR* argv[])
{
	Element *pLine = new Line;
	Element *pPoly = new Polygon;

	DrawAction *pHTex = new DrawWithTexture;
	DrawAction *p3DM = new DrawIn3DModel;


	// 析构部分  略
	pLine->Draw(pHTex);
	pPoly->Draw(p3DM);

	return 0;
}
