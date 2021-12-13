# Compilation-principle
## 实验1——词法分析
## 测试
### ①incf1——测试标识符的越界
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
### ②incf2——测试无词法错
```
{
int a;
a=-123;
if if(a>5) a=a+10;
else a=a-10;
write a;
}
```
### ③incf3.txt——测试非法符号