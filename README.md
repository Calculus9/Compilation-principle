# Compilation-principle
## 实验1——词法分析
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
### incf8——测试数字后读取字符
```cpp
{
int 123;
int A$@;
int 2a;
int a2;
read n;
n = 012345;
}
```
