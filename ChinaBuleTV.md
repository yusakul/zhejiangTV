# ChinaBuleTV

### 拼接m3u8请求URL

m3u8请求URL组成为：http://源.l.cztv.com/channels/lantian/频道ID/清晰度.m3u8?k=秘钥&t=时间戳

（http://tx.l.cztv.com/channels/lantian/channel01/720p.m3u8?k=2a60a74ad7d65f1e2947e69f4d33ca4f&t=1549943353）

> 获取m3u8请求URL函数
>
> void getRequestUrl(char* strTime, char* strUrl);
>
> strTime：时间戳
>
> strUrl：缓存，保存生成的Url

- 源
  - 腾讯：tx
  - 云帆：yf
  - 阿里：ali
- 频道ID
  - 浙江卫视：channel01
- 清晰度
  - 360p
  - 540p
  - 720p
- KEY
  - 计算："cztv/lantian/"+频道ID+时间戳 组成的字符串MD5值
- 时间戳
  - 当前时间或者自定义时间

### 建立连接获取m3u8文件

> 发送请求，需要的库libcurl.lib
>
> bool AccessWeb( char* strUrl, char* content);
>
> szUrl：请求链接
>
> content：返回内容
>
> 返回值：返回内容不为空则返回true

### 解密m3u8

> 解密并保存m3u8文件到当前目录："result.m3u8"
>
> bool decrypt(DWORD* pStream, char* strPath);
>
> content：待解密数据
>
> strPath：文件路径
>
> 返回值：解密完成则返回true

### 解析m3u8

> 读取已解密的m3u8，获取.ts文件请求
>
> char* getTS(char * strUrl, char* strPath, vector<char*> &VectorTS)
>
> strUrl：m3u8请求Url
>
> strPath：文件路径
>
> VectorTS：vector向量，存储TS链接



