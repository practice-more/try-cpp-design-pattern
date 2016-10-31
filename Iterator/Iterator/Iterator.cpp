// Iterator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory.h>
#include <vector>


template <class T>
class Iterator
{
public:
  virtual T first() = 0;
  virtual T next() = 0;
  virtual bool is_done() = 0;
  virtual T current_item() = 0;
};


template <class T>
class ConcreteIterator;


template <class T>
class Aggregate
{
public:
  virtual Iterator<T>* create_iterator() = 0;
};

template <class T>
class ConcreteAggregate : public Aggregate<T>
{
public:

  Iterator<T>* create_iterator() override
  {
    return new ConcreteIterator<T>(this);
  }

  int count()
  {
    return item.size();
  }

  T get_object_at(int index)
  {
    return item[index];
  }

  void push_back_object(T obj)
  {
    item.push_back(obj);
  }

private:
  std::vector<T> item;
};


template <class T>
class ConcreteIterator : public Iterator<T>
{
public:
  ConcreteIterator(ConcreteAggregate<T>* _aggregate)
  {
    aggregate = _aggregate;
  }

  T first() override
  {
    return aggregate->get_object_at(0);
  }

  T next() override
  {
    current ++;
    if (current < aggregate->count())
    {
      return aggregate->get_object_at(current);
    }
    return NULL;
  }
  bool is_done() override
  {
    return current >= aggregate->count() ? true : false;
  }

  T current_item() override
  {
    return aggregate->get_object_at(current);
  }

protected:
  ConcreteAggregate<T>* aggregate;
  int current;
};




int _tmain(int argc, _TCHAR* argv[])
{
  int value;
  ConcreteAggregate<int> * ca = new ConcreteAggregate<int>;

  value = 10;
  ca->push_back_object(value);

  value = 20;
  ca->push_back_object(value);

  Iterator<int> *i = new ConcreteIterator<int>(ca);

  int item = i->first();
  while (!i->is_done())
  {
    printf("%d\n", i->current_item());
    i->next();
  }

	return 0;
}

