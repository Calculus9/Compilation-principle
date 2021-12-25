#include <bits/stdc++.h>
using namespace std;

string token, token1; // token保存单词符号，token1保存单词值
extern string openFilename;
int program();
ifstream fin;
//语法分析程序
int TESTparse()
{
    int es = 0;
    const char *copenFilename = openFilename.c_str(); //可读不可改的常指针
    fin.open(copenFilename, ios::in);
    if (!fin)
    {

        cout << "\n打开" << openFilename << "错误!\n"
             << endl;
        es = 10;
    }
    if (es == 0)
        es = program();
    printf("=====语法分析结果!======\n");
    switch (es)
    {
    case 0:
        printf("语法分析成功!\n");
        break;
    case 10:
        cout << "\n打开" << openFilename << "错误!\n"
             << endl;
        break;
    case 1:
        printf("缺少{!\n");
        break;
    case 2:
        printf("缺少}!\n");
        break;
    case 3:
        printf("缺少标识符!\n");
        break;
    case 4:
        printf("少分号!\n");
        break;
    case 5:
        printf("缺少(!\n");
        break;
    case 6:
        printf("缺少)!\n");
        break;
    case 7:
        printf("缺少操作数!\n");
        break;
    }
    if(fin.is_open()) fin.close();
}
//<程序>::={<声明序列><语句序列>}
// program::={<declaration_list><statement_list>}
int program()
{
    int es = 0;
    
}