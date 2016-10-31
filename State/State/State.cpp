// State.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>

class Work;
class State;
class Forenoon_state;
class NoonState;


class State
{
public:
  virtual void write_programe(std::shared_ptr<Work> w) = 0;
};

class Forenoon_state : public State
{
public:
  void write_programe(std::shared_ptr<Work> w) override;
};

class Work :public std::enable_shared_from_this<Work>
{
public:

  void set_state(std::shared_ptr<State> _current)
  {
    current = _current;
  }

  Work()
  {
    current = std::make_shared<Forenoon_state>();
  }

  void write_programe()
  {
    current->write_programe(shared_from_this());
  }
  int Hour;

private:
  std::shared_ptr<State> current;
};



class NoonState : public State
{
public: 
  void write_programe(std::shared_ptr<Work> w) override;
};

void Forenoon_state::write_programe(std::shared_ptr<Work> w)
{
  if (w->Hour < 12)
  {
    printf("Now, forenoon.\n");
  }
  else
  {
    w->set_state(std::make_shared<NoonState>());
    w->write_programe();
  }
}

void NoonState::write_programe(std::shared_ptr<Work> w)
{
  printf("Finish forenoon's work, let us have a rest!");
}


int _tmain(int argc, _TCHAR* argv[])
{
  std::shared_ptr<Work> sp_work = std::make_shared<Work>();
  sp_work->Hour = 9;
  sp_work->write_programe();
  sp_work->Hour = 12;
  sp_work->write_programe();
	return 0;
}

