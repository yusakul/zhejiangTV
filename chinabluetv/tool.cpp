#include "tool.h"


bool decrypt(DWORD* pStream, char* strPath)
{
	if (pStream == NULL)
	{
		return false;
	}

	int i, iByteNum, j, k;
	FILE *pFileA;

	fopen_s(&pFileA, strPath, "wb+");

	
	while( *pStream!=NULL)
	{
		DWORD dwTmp = *pStream++;
		//dwTmp ^= 0x63C399ED;
		dwTmp ^= 0xED99C363;

		for (k = 0; k <= 3; k++)
		{
			fputc(dwTmp >> (k * 8), pFileA);
		}
	}
	fclose(pFileA);

	return true;
}

//回调函数
size_t http_data_writer(void* data, size_t size, size_t nmemb, void* content)
{
	long totalSize = size * nmemb;
	std::string* symbolBuffer = (std::string*)content;
	if (symbolBuffer)
	{
		symbolBuffer->append((char *)data, ((char*)data) + totalSize);
	}
	return totalSize;
}


bool AccessWeb( char* szUrl, char* content)
{
	CURL* curl = NULL;
	curl = curl_easy_init();
	CURLcode code;
	// 设置Url
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(curl, CURLOPT_URL, szUrl);
	// 设置回调函数
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_data_writer);
	//设置写数据
	std::string strData;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&strData);
	// 执行请求
	code = curl_easy_perform(curl);

	if (code == CURLcode::CURLE_OK)
	{
		long responseCode = 0;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
		if (responseCode < 200 || responseCode >= 300 || strData.empty())
		{
			return false;
		}
		//dui应答的数据进行处理
		memcpy(content, strData.data(), strData.length());
	}

	// 清除curl对象
	curl_easy_cleanup(curl);

	return true;
}


char* getTS(char * strUrl, char* strPath, vector<char*> &VectorTS)
{
	FILE *pFile;
	char line[1024] = {};
	char result[0x10][100] = {};
	int i = 0;

	fopen_s(&pFile, strPath, "r");

	if (pFile == NULL)
	{
		return NULL;
	}

	char* buf = strstr(strUrl, "channel01/");
	if (buf != NULL)
	{
		buf[10] = '\0';        //在“channel01/”后设置结束符\0
	}

	while (fgets(line, 1024, pFile) != NULL)
	{
		if (strstr(line, ".ts"))
		{
			char* tmp = line;
			sprintf_s(result[i], 100, "%s%s", strUrl, tmp);
			VectorTS.push_back(result[i]);
			//printf("%s", result[i]);
			i++;
		}
	}
	return 0;
}