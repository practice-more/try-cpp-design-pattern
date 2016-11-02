// FactoryMethod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class Operation
{
public:
  virtual int go(int a, int b) = 0;
};

class IFactory
{
public:
  virtual Operation* create_operation() = 0;
};

class Add_operation : public Operation
{
public:
  int go(int a, int b) override
  {
    return a + b;
  }
};

class Sub_operation: public Operation
{
public:
  int go(int a, int b) override
  {
    return a - b;
  }
};

class Add_operation_factory : public IFactory
{
public:
  Operation* create_operation()
  {
    return new Add_operation();
  }
};

class Sub_operation_factory : public IFactory
{
public:
  Operation* create_operation()
  {
    return new Sub_operation();
  }
};



int main()
{
  IFactory * p_factory = new Add_operation_factory();
  Operation * p_operation = p_factory->create_operation();
  int result = p_operation->go(10, 5);
  return 0;
}

