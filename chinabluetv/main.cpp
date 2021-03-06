﻿#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>

#include "tool.h"

using namespace md5;
using namespace std;

void getRequestUrl(char* strTime, char* strUrl)
{
	MD5 md5;

	//源
	const char* source[] = { "tx", "yf", "ali" };
	//mount_name
	char mount_name[] = "lantian";
	//channel
	char channel[] = "channel01";


	//清晰度
	const char* streamtypep[] = { "360p", "540p", "720p" };
	//key
	string str = "cztv/lantian/channel01";
	char strKey[256] = {};
	sprintf(strKey, "%s%s", str.data(), strTime);


	//拼接url
	string url = "http://";
	url += source[0];
	url += ".l.cztv.com/channels/";
	url += mount_name;
	url += "/";
	url += channel;
	url += "/";
	url += streamtypep[2];
	url += ".m3u8";
	url += "?k=";
	url += md5.digestString(strKey);//根据时间戳获取key
	url += "&t=";
	url += strTime;

	memcpy(strUrl, url.data(), url.length());
	return ;
}

int main()
{
	char strTime[20] = {};
	char url[0x100] = {};
	char strPath[MAX_PATH] = "result.m3u8";
	vector<char*> VectorTS;

	printf("输入时间戳（输入0则默认为当前时间）: ");
	scanf_s("%s", strTime, 20);

	if (!strcmp(strTime, "0"))
	{
		//时间戳
		time_t myt = time(NULL);  //获取当前时间
		sprintf_s(strTime, "%d", myt);
	}

	//拼接请求
	getRequestUrl(strTime, url);
	printf("%s\n", url);

	//建立连接请求m3u8
	char content[1024] = {};
	if (!AccessWeb(url, content))
	{
		printf("connect failed...\n");
		return 0;
	}
	
	//解密m3u8
	if (!decrypt((DWORD*)content, strPath))
	{
		printf("decrypt failed...\n");
		return 0;
	}

	//获取Ts链接
	getTS(url, strPath, VectorTS);

	//输出Ts链接
	for (vector<char*>::iterator iter1 = VectorTS.begin(); iter1 != VectorTS.end(); ++iter1) 
	{
		cout << *iter1;
	}

	system("pause");
	return 0;

	//点播
	//http://api.cms.cztv.com/mms/out/video/playJson?id=XXXXXX&domain=www.letv.com&splatid=123&platid=1000&pt=2&at=1
}


