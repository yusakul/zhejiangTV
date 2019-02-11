#include <stdio.h>

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

	printf("输入时间戳（输入0则默认为当前时间）: ");
	scanf_s("%s", strTime, 20);

	if (!strcmp(strTime, "0"))
	{
		//时间戳
		time_t myt = time(NULL);  //获取当前时间
		sprintf_s(strTime, "%d", myt);
	}

	getRequestUrl(strTime, url);
	printf("%s\n", url);

	char content[1024] = {};
	AccessWeb(url, content);
	
	decrypt((DWORD*)content);

	char path[111] = "result.m3u8";
	getTS(url, path);

	system("pause");
	return 0;

	//点播
	//http://api.cms.cztv.com/mms/out/video/playJson?id=XXXXXX&domain=www.letv.com&splatid=123&platid=1000&pt=2&at=1
}


//http://ali.l.cztv.com/channels/lantian/channel01/ + .ts
//http://tx.l.cztv.com/channels/lantian/channel01/ + .ts
//http://yf.l.cztv.com/channels/lantian/channel01/ + .ts


