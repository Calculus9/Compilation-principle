# Compilation-principle
## 实验1——词法分析
## 修改记录
- 添加了hash函数
```cpp
unsigned long long getHash(string &s)
{
    unsigned long long hashsum = 0;
    for (int i = 0; i < (int)s.size(); i++)
        hashsum = (hashsum * base + s[i] - 'a' + 1);
    return hashsum;
}

void insert(unsigned long long x)
{
    int p = x % mod;
    while (isKeyword[p] != -1)
    {
        p = (p + 1) % mod;
    }
    isKeyword[p] = x;
}

bool find(unsigned long long x)
{
    int p = x % mod;
    while (isKeyword[p] != -1)
    {
        if (isKeyword[p] == x)
        {
            return true;
        }
        p = (p + 1) % mod;
    }
    return false;
}
```
- 添加了定义一维数组，且可以重复定义

```cpp
//<declaration_stat>::=int ID;  -> ID{,ID}; -> ID([NUM]|空){,ID([NUM]|空)};
int declaration_stat()
{
	int es = 0;
	FIN;
	if (strcmp(token, "ID"))
		return (es = 3); //不是标识符
	
	FIN;
	if(strcmp(token, "[") == 0) {
		FIN;
		if(strcmp(token, "NUM")) return (es = 8);
		FIN;
		if(strcmp(token, "]")) return (es = 9);
		FIN;
	}

	while(strcmp(token, ",") == 0) {
		FIN;
		if (strcmp(token, "ID"))
			return (es = 3); //不是标识符
		FIN;
		if(strcmp(token, "[") == 0) {
			FIN;
			if(strcmp(token, "NUM")) return (es = 8);
			FIN;
			if(strcmp(token, "]")) return (es = 9);
			FIN;
		}
	}
	if (strcmp(token, ";"))
		return (es = 4);
	FIN;
	return (es);
}
```
- 添加了do-while语句
```cpp
int do_while_stat()
{
	int es = 0;
	FIN;
	es = statement();
	if (es)
		return es;
	FIN;
	if (strcmp(token, "while") == 0) // while部分处理
	{
		FIN;
		es = expression();
		if (es > 0)
			return es;
		if (strcmp(token, ";"))
		{
			return (es = 4);
		}
		FIN;
	}
	return es;
}
```
- 支持mod运算

```cpp
//< term >::=<factor>{(%|*|/)< factor >}
int term()
{
	int es = 0;
	es = factor();
	if (es > 0)
		return (es);
	while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0 || strcmp(token, "%") == 0)
	{
		FIN;
		es = factor();
		if (es > 0)
			return (es);
	}
	return (es);
}
```



## 测试
### incf1——测试标识符的越界
教材中长度大于 39 的标识符会报错，最好能实现自动截断。
```
{
int a;
a=7;
int maxlengthmaxlengthmaxlengthmaxlengthmaxlength;
maxlengthmaxlengthmaxlengthmaxlengthmaxlength=a*3;
write maxlengthmaxlengthmaxlengthmaxlengthmaxlength;
}
```
### incf2——测试无词法错
```
{
int a;
a=-123;
if if(a>5) a=a+10;
else a=a-10;
write a;
}
```
### incf3——测试非法符号
```
{
int temp;
temp=(261+@)*5)/16;
write #temp;
}
```
### incf4——测试注释
```
{
int i,sum;
sum=1;
i=1;
do
{
sum=sum*i;
i=i+1;
}while(i<=10)
/* sum=1*2*3*...*10
write sum;
}
```
### incf5——测试write字符串
```
{
int a;
int 5b;
for(i=1;i<a;i=i+1) 5b=5b+i;
write "input error!";
}
```
### incf6——测试read字符串
```
{
int 2a;
int a2;
read n;
n = 345;
}
```
### incf7——测试第一个数字为0的情况
```
{
int n;
n = 012345;
}
```
### incf8——测试数字后为字符
```
{
int 123;
int A$@;
int 2a;
int a2;
}
```
### incf9——测试双分界符！=
```
{
int abc;
read n;
n = 5;
for (i=1;i<=n; i= i+1)
{ 
abc=abc+i; }if(i!=n) n = n+i;
}
```
### incf10——测试do while
```
{
int i,sum;
sum=1;
i=1;
do
{
sum=sum*i;
i=i+1;
}while(i<=10)
}
```