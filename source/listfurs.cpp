#include "listfurs.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define NO_OF_COLOR 6

using namespace std;

listfurs *_listfurs              = NULL;
bool      listfurs::puredelete   = false;
unsigned int listfurs::listCount = 0;

listfurs* getfur(unsigned int a)
{
  listfurs *op = _listfurs;

  while (a != op->m_gridval) op = op->p;
  return op;
}

listfurs::listfurs(COORD a, unsigned short value, int pt = 0)
{
  srand(time(0));

  if (!pt) f = new furs(a, (rand() % NO_OF_COLOR) + 1);
  else
  {
    f = new furs(a, pt);
  }

  Setgridval(value);

  if (!_listfurs) p = NULL;
  else p = _listfurs;
  _listfurs = this;
  listCount++;
}

listfurs* getbefore(listfurs *o)
{
  listfurs *op = _listfurs;

  while (o != (op->p)) op = op->p;

  // op->p = o->p;
  return op;
}

// void listfurs::printfurs()
// {
//   listfurs *s = _listfurs;

//   do
//   { cout << "\n " << s->Getgridval() << " " << s;
//     cout << " " << s->p;
//     s = s->getp(); } while (s != NULL);
// }

listfurs::~listfurs()
{
  if (puredelete) {
    delete f;
    m_gridval = -1;
    p         = NULL;
  }
  else {
    listfurs *tp;
    delete f;

    if (this != _listfurs) {
      tp    = getbefore(this);
      tp->p = p;
      p     = NULL;
    }
    else {
      _listfurs = _listfurs->p; p = NULL;
    }
    m_gridval = -1;
  }
  listCount--;
}

void deleteall()
{
  listfurs::puredelete = true;
  listfurs *in, *pt = _listfurs;

  while (pt != NULL)
  { in = pt; pt = pt->p; delete in; }
  _listfurs            = NULL;
  listfurs::puredelete = false;
}
