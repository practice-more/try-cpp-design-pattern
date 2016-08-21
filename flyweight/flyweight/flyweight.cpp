// Flyweight.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <map>
using namespace  std;

// 享元模式（Flyweight）。运用共享技术有效地支持大量细粒度的对象。


// 假设场景

// 某个三维游戏场景，有一片森林，准备用一棵树，通过摆放位置不同，
// 缩放，角度不同的三棵树摆出一整片森林。

// 时间关系，先不写析构部分了

class Obj
{
public:
  Obj(const string &str)
    : m_strName(str)
  {

  }
  virtual void PrintInfo() { ; }
  virtual std::string GetName() { return m_strName; }
protected:
  string m_strName;
};

// 模型几何信息
class Mesh : public Obj
{
public:
  Mesh(const string &str)
    : Obj(str)
  {

  }
  void PrintInfo() override
  {
    string str = "Mesh information of " + m_strName;
    printf(str.c_str());
  }
};


// 模型姿态信息,其实每个模型都有自己的姿态
// 现在假设只有模型树的姿态是需要自己设置的
class POSInfo
{
public:
  POSInfo(double centerX, double centerY, double centerZ,
    double yaw, double pitch, double roll,
    double xScale, double yScale, double zScale)
    : m_x(centerX)
    , m_y(centerY)
    , m_z(centerZ)
  {
    //.....
  }
  double  m_x;
  double	m_y;
  double	m_z;
};

// 模型树类
class TreeModel
{
public:
  TreeModel(const string & name)
  {
    m_pMesh = new Mesh(name);
  }

  ~TreeModel()
  {
    if (m_pMesh)
    {
      delete m_pMesh;
      m_pMesh = nullptr;
    }
  }

  void Draw(POSInfo *pInfo)
  {
    printf("\n.........\n");
    m_pMesh->PrintInfo();

    if (pInfo)
    {
      printf(" : \nWe will draw it at :\n(x:%lf, y:%lf, z:%lf)", pInfo->m_x, pInfo->m_y, pInfo->m_z);
    }

    printf("\n.........\n");
  }

protected:
  Mesh* m_pMesh;
};

class TreeModelFactory
{
public:
  TreeModelFactory()
  {
    std::vector<std::string> name_array = { "大树", "小树", "小小树" };
    for (std::vector<std::string>::iterator iter = name_array.begin(); iter != name_array.end(); iter++)
    {
      m_TreeModelInstances[*iter] = new TreeModel(*iter);
    }
  }

  TreeModel* GetTreeInstance(std::string name)
  {
    std::map<std::string, TreeModel*>::iterator finder;
    finder = m_TreeModelInstances.find(name);
    if(finder != m_TreeModelInstances.end())
    {
      return finder->second;
    }
    else
    {
      m_TreeModelInstances[name] = new TreeModel(name);
    }
 }
  ~TreeModelFactory()
  {
    // .......
    // delete tree
    // delete mesh
    // delete ro
    // releas map
  }
private:
  std::map<std::string, TreeModel*> m_TreeModelInstances;
};


int _tmain(int argc, _TCHAR* argv[])
{
  TreeModelFactory *pTreeFactory = new TreeModelFactory();

  TreeModel* pT1 = pTreeFactory->GetTreeInstance("大树");
  pT1->Draw(new POSInfo(1, 2, 3, 0, 0, 0, 1, 2, 3));

  TreeModel *pT2 = pTreeFactory->GetTreeInstance("小树");
  pT2->Draw(new POSInfo(6, 2, 3, 7, 0, 0, 1, 2, 3));

  pT2->Draw(new POSInfo(10, 12, 30, 7, 0, 0, 1, 2, 3));
  pT1->Draw(new POSInfo(10, 12, 30, 7, 0, 0, 1, 2, 3));



  // ...
  // ...

  // 这样森林中所有的树只有三种几何体和渲染体，比较节省内存
  // 

  // 当然，如果要给每一个不同的树一个序号或者要保存每一颗树的信息，可以加一个TreeInstance类
  // TreeIns包含序号，位置指针和treeModel的指针即可

  // 如果不需要保存这些信息，那么只需要保存PosInfo列表
  // 需要的时候再进行组合（CreateNewInstacne），然后打印信息

  return 0;
}
