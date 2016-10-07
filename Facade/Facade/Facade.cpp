// 外观模式（Facade），为子系统中的一组接口提供一个一致的界面，此模式
// 定义了一个高程接口，这个接口使得这一子系统更加容易使用。


// 情景假设
// 某一软件，运行时需要连接数据库，获取数据文本，假设为txt文本
// 数据库是Oracle，从数据库中取出的是加密过的文件
// 解密子系统是decryption，解密之后是一个rar，需要解压
// 解压子系统是rar
// 现在创建一个facade掩盖此过程，做到用户给一个输入，就能得到输出。


// 这个例子比较简单，因为就是封装下接口，不需要用到多态之类的
// 所以每个类就只声明一个对象即可

// 最终用户知道的细节越少越好，迪米特法则

#include "stdafx.h"
#include <Windows.h>

//数据库子系统
class OracleDB
{
public:
	bool GetDataFromDB(long id, byte* &pBuf)
	{
		printf("Connect to oracle now!\n");
		printf("Get data from Oracle now!\n");
		return true;
	}
protected:
private:
};

//解密子系统
class Decryption
{
public:
	bool Decrypt(byte* &pBuf)
	{
		byte *pDecryption = NULL;
		pBuf = pDecryption;
		printf("Sucessful Decrypt!\n");
		return true;
	}
protected:
private:
};

//解压缩子系统
class RARSys
{
public:
	bool UnCompress(byte* &pBuf, char* pPath)
	{
		byte* pUncompress = NULL;
		pBuf = pUncompress;
		printf("Sucessful Uncompress!\n");
		if (WriteData(pPath))
		{
			return true;
		}

	}
protected:
private:
	bool WriteData(char* pPath)
	{
		printf("Txt is put in this path:\n");
		printf(pPath);
		printf("\n");
		return true;
	}
};


//外观类
class Facade
{
public:
	bool GetTxt(long id, char *pPath)
	{
		OracleDB	db;
		Decryption	dp;
		RARSys		rs;
		byte *pBuf;
		db.GetDataFromDB(id, pBuf);
		dp.Decrypt(pBuf);
		rs.UnCompress(pBuf, pPath);
		return true;
	}
protected:
private:
};


int _tmain(int argc, _TCHAR* argv[])
{
	Facade fd;
	fd.GetTxt(100, "D:\\temp.txt");
	return 0;
}


//输出结果：
//Connect to oracle now!
//Get data from Oracle now!
//Sucessful Decrypt!
//Sucessful Uncompress!
//Txt is put in this path:
//D:\temp.txt
//请按任意键继续. . .