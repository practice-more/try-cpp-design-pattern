// Mediator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <memory>

class Colleague;
class Translater;
class English_colleague;
class Chinese_colleague;

class Mediator
{
public:
  Mediator(){ ; }
  virtual void send(const std::string & msg, Colleague* _p_colleague) = 0;
};

class Colleague
{
public:
  Colleague(Mediator* _p_mediator)
    : p_mediator(_p_mediator)
  {

  }

  bool b_speak_eng;
protected:
  Mediator* p_mediator;
};

class English_colleague : public Colleague
{
public:

  English_colleague(Translater * _p_mediator)
    :Colleague((Mediator*)_p_mediator)
  {

    b_speak_eng = true;
  }

  void send(const std::string & msg) 
  {
    p_mediator->send(msg, this);
  }

  void notify(const std::string & msg)
  {
    printf(msg.c_str());
  }

};

class Chinese_colleague : public Colleague
{
public:

  Chinese_colleague(Mediator * _p_mediator)
    :Colleague(_p_mediator)
  {

    b_speak_eng=false;
  }

  void send(const std::string & msg) 
  {
    p_mediator->send(msg, this);
  }

  void notify(const std::string & msg)
  {
    printf(msg.c_str());
  }
};


class Translater : Mediator
{
public:

  void set_eng_colleagure(English_colleague* p)
  {
    p_eng = p;
  }

  void set_chn_colleagure(Chinese_colleague* p)
  {
    p_chn = p;
  }

  void send(const std::string & msg, Colleague* _p_colleague) override
  {
    // as our mediator can't speak Chinese and English...
    if (_p_colleague->b_speak_eng)
    {
      const std::string str = "您好，我也听不懂他在说什么。";
      p_chn->notify(str);
    }
    else
    {
      const std::string str = "Hi, I don't know what did he speak either!";
      p_eng->notify(str);
    }
  }




protected:
  English_colleague * p_eng;
  Chinese_colleague * p_chn;
};

int _tmain(int argc, _TCHAR* argv[])
{

  Translater * p = new Translater();
  English_colleague * p_eng = new English_colleague(p);
  Chinese_colleague * p_chn = new Chinese_colleague((Mediator*)p);
  p_eng->send("Hello");
  p_chn->send("您好");
	return 0;
}

