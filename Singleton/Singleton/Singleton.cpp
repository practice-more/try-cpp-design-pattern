// Singleton.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "singleton.h"

void TestFunc1()
{
  TextureMgr  tMgr;
  Texture *pTexStone = g_TextureMgr.GetTexture("stone");
}


int _tmain(int argc, _TCHAR* argv[])
{

  int a = (int)(int*)1;
  int b = (int)(double*)1;

  TestFunc1();

  Texture *pTexStone = g_TextureMgr.GetTexture("stone");
  return 0;
}


