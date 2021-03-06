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
- 添加了do-while的属性文法

```cpp
// <do-while_stat>→ do ’{‘<statement>’}’while (<expr >) ;
// <do-while_stat>→ do@SETlabel↓label1 
// ’{‘<statement>’}’while (<expr >)@BRF↑label2@BR↑label1@SETlabel↓label2;
// 	 其中动作符号的含义如下
//   @BRF↑label2 ：输出 BRF label2, 
//   @BR↑label1：输出 BR label1, 
//   @SETlabel↓label1：设置标号label1 
//   @SETlabel↓label2：设置标号label2

int do_while_stat()
{
	int es = 0,label1,label2;
	label1=labelp++;//用label1记住无条件时要转向的标号
	fprintf(fout,"LABEL%d:\n",label1);
	FIN;
	es = statement();
	if (es) return es;
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
	label2=labelp++;//用label2记住要转向的标号
	fprintf(fout,"        BRF LABEL%d\n",label2);//输出假转移指令
	fprintf(fout,"        BR LABEL%d\n",label1);//输出无条件转移指令
	fprintf(fout,"LABEL%d:\n",label2);
	return es;
}
```
- 修改了数组定义属性文法

```cpp
//<declaration_stat>↓vartablep,datap,codep ->int ID↑n↑c@name-def↓n,t,c;
//<declaration_stat>::=int ID;  -> ID{,ID}; -> ID([NUM]|空){,ID([NUM]|空)};
int declaration_stat()
{
	int es = 0,cnt = 1;
	do {
		FIN;
		if (strcmp(token, "ID"))
			return (es = 3); //不是标识符
		char name[40];
		strcpy(name,token1);
		FIN;
		if(strcmp(token, "[") == 0) {
			FIN;
			if(strcmp(token, "NUM")) return (es = 8);
			cnt = atoi(token1);
			FIN;
			if(strcmp(token, "]")) return (es = 9);
			FIN;
		}
		es=name_def(name,cnt);//插入符号表
		if (es>0) return(es);
	}while(strcmp(token, ",") == 0);

	if (strcmp(token, ";"))
		return (es = 4);
	FIN;
	return (es);
}
```
- 变量重复定义错误
```cpp
for(i=vartablep-1;i!=0;i--)//查符号表
```
- 模拟机MOD运算
```cpp
// MOD
if (strcmp(code[i],"MOD")==0) 
{
	stack[stacktop-2]=stack[stacktop-2]%stack[stacktop-1];
	stacktop--;

}
```

- 支持嵌套定义
```cpp
if (es==0 && strcmp(token,"int")==0) es=declaration_list();//<int语句>
```
- 修改compound_stat和program使得while，for,if之后能继续识别
```cpp
int compound_stat(){   //复合语句函数
	int es=0;
	FIN;
	es=statement_list();
	if(strcmp(token,"}"))//判断是否'}'
	{
		es=2;
		return(es);
	}
	FIN;
	return(es);
}
```

- 修复STI指令
```cpp
	fprintf(fout,"        IN   \n");//输入指令
	fprintf(fout,"        STI   %d\n",address);//指令
	// fprintf(fout,"        POP\n");
```

- 修改IN的问题,注释i++
```cpp
//IN 从标准输入设备（键盘）读入一个整型数据，并入栈。
if (strcmp(code[i],"IN")==0)
{
	// i++;
	printf("请输入数据: ");
	scanf("%d",&stack[stacktop]);
	stacktop++;
}
```

- 修改了模拟机的data的类型

```cpp
int es=0,i,k=0,codecount,stack[1000],stacktop=0,data[1000];
```

- 修改了数组的赋值操作

```cpp
else if(strcmp(token2,"[")==0) 
{
	FIN;
	if(strcmp(token, "NUM")) return (es = 8);
	cnt = atoi(token1);
	FIN;
	if(strcmp(token, "]")) return (es = 9);
	fileadd=ftell(fp);   //@ASSIGN记住当前文件位置
	fscanf(fp,"%s %s %d\n", &token2,&token3,&line1);
	printf("%s %s %d\n",token2,token3,line1);
	if (strcmp(token2,"=")==0)  //'='
	{
		int address;
		es=lookup(name,&address);
		if (es>0) return(es);
		FIN;
		es=bool_expr();
		if (es>0) return(es);
		fprintf(fout,"        STO %d\n",address-cnt);
	}else
	{
		fseek(fp,fileadd,0); //若非'='则文件指针回到'='前的标识符
		printf("%s %s\n",token,token1);
		es=bool_expr();
		if (es>0) return(es);
	}
} 
```

- 修改输出数组
```cpp
else if(strcmp(token,"]")==0) {
	int address;
	es=lookup(expression_name,&address);//查符号表，获取变量地址
	if (es>0) return(es);//变量没声明
	fprintf(fout,"        LOAD %d\n",address-expression_cnt);
	FIN;
	return(es);
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