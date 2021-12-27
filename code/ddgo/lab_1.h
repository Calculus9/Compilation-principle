#include <bits/stdc++.h>
using namespace std;

// 保存所有保留字
#define keywordSum 8
#define mod (13)
string keyword[keywordSum] = {"if", "else", "for", "while", "do", "int", "read", "write"};
unsigned long long isKeyword[mod];
int base = 131;

//下面定义纯单分界符，添加%
string singleword = "+-*(){};,%[]\"";

//下面定义双分界符的首字符
string doubleword = "><=!";

string openFilename;
const char *outputFilename = "../Lexical_output.txt";

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

/**
 * @brief 初始化保留关键字的hash值
 */
void init()
{
    memset(isKeyword, -1, sizeof(isKeyword));
    for (int i = 0; i < keywordSum; i++)
    {
        insert(getHash(keyword[i]));
    }
}

/**
 * @brief 词法分析函数
 * @return int 返回值
 *      0：词法分析没有发现错误
 *      1、2：输入或输出文件有错误
 *      3：表示有非法符号
 */
int lexicalAnalysis()
{
    // 初始化处理保留字的hash值。
    init();

    string token = "";    // token用于保存识别出的单词
    char ch;              // ch为每次读入的字符
    int line = 1, es = 0; //当前所在行，es错误代码，0表示没有错误。

    cout << "请输入源程序文件名（包括路径）: ";
    cin >> openFilename;
    string c = "../test2/";
    c += openFilename;
    const char *copenFilename = c.c_str(); //可读不可改的常指针

    //判断输入文件名是否正确
    ifstream fin(copenFilename); //输入，从硬盘到内存
    if (!fin)
    {
        cout << "\n打开词法分析输入文件出错!" << endl;
        return (1); //输入文件出错返回错误代码1
    }
    ofstream fout(outputFilename); //输出，从内存到硬盘
    if (!fout)
    {
        cout << "\n创建词法分析输出文件出错!" << endl;
        return (2); //输出文件出错返回错误代码2
    }
    fin.get(ch);
    while (!fin.eof())
    {
        if (fin.eof())
            break;
        while (ch == '\n' || ch == ' ' || ch == '\t')
        {
            if (ch == '\n')
                line++;
            fin.get(ch);
            if (fin.eof())
                break;
        }
        if (fin.eof())
            break;
        token = "";
        if (isalpha(ch)) //如果是字母，则进行标识符处理
        {
            int ok = 0;
            token += ch;
            fin.get(ch); //继续输入字符
            //如果是字母数字则组合标识符；如果不是则标识符组合结束
            while (isalnum(ch))
            {
                if ((int)token.size() < 39)
                    token += ch; //组合存放到token中
                else
                {
                    ok = 1;
                }
                fin.get(ch); //读下一个字符
            }
            if (ok)
                cout << "自动截断" << endl;
            //查保留字
            if (!find(getHash(token))) //不是保留字，输出标识符
                fout << "ID\t" << token << "\t" << line << endl;
            else
                fout << token << "\t" << token << "\t" << line << endl;
        }
        else if (isdigit(ch)) //数字处理
        {
            token += ch;
            fin.get(ch);        //读下一个字符
            while (isdigit(ch)) //如果是数字则组合整数；如果不是则整数组合结束
            {
                token += ch; //组合整数保留到token中
                fin.get(ch); //读下一个字符
            }
            fout << "NUM\t" << token << "\t" << line << endl; //输出整数符号
        }
        else if (singleword.find(ch) != string::npos) //单分符处理
        {
            token += ch;
            fin.get(ch);                                            //读下一个符号以便识别下一个单词
            fout << token << "\t" << token << "\t" << line << endl; //输出单分界符符号
        }
        else if (doubleword.find(ch) != string::npos) //双分界符处理
        {
            token += ch;
            fin.get(ch);   //读下一个字符判断是否为双分界符
            if (ch == '=') //如果是=，组合双分界符
            {
                token += ch;
                fin.get(ch); //读下一个符号以便识别下一个单词
            }
            fout << token << "\t" << token << "\t" << line << endl; //输出单或双分界符符号
        }
        else if (ch == '/') //注释处理
        {
            fin.get(ch);   //读下一个字符
            if (ch == '*') //如果是*，则开始处理注释
            {
                char ch1;
                fin.get(ch1); //读下一个字符
                do
                {
                    ch = ch1; //删除注释
                    if (fin.eof())
                    {
                        cout << "ERROR\t"
                             << "注释未完全"
                             << "\t错误: 第" << line << "行" << endl; //输出错误符号
                        fout << "ERROR\t"
                             << "注释未完全"
                             << "\t错误: 第" << line << "行" << endl; //输出错误符号
                        return (4);
                    }
                    fin.get(ch1);
                } while ((ch != '*' || ch1 != '/') && ch1 != EOF); //直到遇到注释结束符*/或文件尾
                fin.get(ch);                                       //读下一个符号以便识别下一个单词
            }
            else //不是*则处理单分界符/
            {
                token += ch;
                fout << token << "\t" << token << "\t" << line << endl; //输出单分界符/
            }
        }
        else
        { //错误处理
            token += ch;
            fin.get(ch);                                                        //读下一个符号以便识别下一个单词
            es = 3;                                                             //设置错误代码
            fout << "ERROR\t" << token << "\t错误: 第" << line << "行" << endl; //输出错误符号
            cout << "ERROR\t" << token << "\t错误: 第" << line << "行" << endl; //输出错误符号
        }
    }
    fout << "end" << endl;
    fin.close();
    fout.close();
    return (es); //返回主程序
}