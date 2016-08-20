#include "stdafx.h"  
#include  <windows.h>  


enum EOperator
{
  ADD_OPER,
  SUB_OPER
};

class MathOperator
{
public:
  MathOperator() { ; }
  virtual ~MathOperator() { ; }

  void SetMember(int first, int second)
  {
    m_nFirst = first;
    m_nSecond = second;
  }
  virtual int GetResult() = 0;
protected:
  int m_nFirst;
  int m_nSecond;
};


class AddOperator :public MathOperator
{
public:
  int GetResult()
  {
    return m_nFirst + m_nSecond;
  }
};


class SubOperator :public MathOperator
{
public:
  int GetResult()
  {
    return m_nFirst - m_nSecond;
  }
};

class OperatorFactory
{
public:
  MathOperator *CreateOperator(EOperator eOper)
  {
    MathOperator *pOper = NULL;
    switch (eOper)
    {
    case ADD_OPER:
      pOper = new AddOperator();
      break;
    case SUB_OPER:
      pOper = new SubOperator();
      break;
    }
    return pOper;
  }
};


int _tmain(int argc, _TCHAR* argv[])
{
  OperatorFactory OFactrory;
  MathOperator *pOper = OFactrory.CreateOperator(ADD_OPER);
  pOper->SetMember(2, 3);
  int nResult = pOper->GetResult();
  if (pOper)
  {
    delete pOper;
    pOper = NULL;
  }
  return 0;
}


