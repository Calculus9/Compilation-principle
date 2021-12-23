#include <bits/stdc++.h>
using namespace std;

// 保存所有保留字
#define keywordSum 8
#define mod (keywordSum + keywordSum)
string keyword[keywordSum] = {"if", "else", "for", "while", "do", "int", "read", "write"};
bool isKeyword[mod];
int base = 131;

//下面定义纯单分界符，如需要可添加
string singleword = "+-*(){};,:";

//下面定义双分界符的首字符
string doubleword = "><=!";

string openFilename;
const char *outputFilename = "./Lexical_output.txt";

int getHash(string &s)
{
    int hashsum = 0;
    for (int i = 0; i < (int)s.size(); i++)
        hashsum = (hashsum * base % mod + s[i] - 'a' + 1) % mod;
    return hashsum;
}
/**
 * @brief 初始化保留关键字的hash值
 */
void init()
{
    for (int i = 0; i < keywordSum; i++)
    {
        isKeyword[getHash(keyword[i])] = true;
        cout << keyword[i] << " " << getHash(keyword[i]) << endl;
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
    const char *copenFilename = openFilename.c_str(); //可读不可改的常指针

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
        while (ch == '\n')
            fin.get(ch), line++;
        while (ch == ' ' || ch == '\t')
            fin.get(ch);
        if (ch == EOF)
            break;
        token = "";
        if (isalpha(ch)) //如果是字母，则进行标识符处理
        {
            token += ch;
            fin.get(ch); //继续输入字符
            //如果是字母数字则组合标识符；如果不是则标识符组合结束
            while (isalnum(ch))
            {
                token += ch; //组合存放到token中
                fin.get(ch);   //读下一个字符
            }
            //查保留字
            if (!isKeyword[getHash(token)]) //不是保留字，输出标识符
                fout << "ID\t" << token << endl;
            else
                fout << token << "\t" << token << endl;
        }
        else if (isdigit(ch)) //数字处理
        {
            token += ch;
            fin.get(ch);          //读下一个字符
            while (isdigit(ch)) //如果是数字则组合整数；如果不是则整数组合结束
            {
                token += ch; //组合整数保留到token中
                fin.get(ch);   //读下一个字符
            }
            fout << "NUM\t" << token << endl; //输出整数符号
        }
        else if (singleword.find(ch) != string::npos) //单分符处理
        {
            token += ch;
            fin.get(ch);                              //读下一个符号以便识别下一个单词
            fout << token << "\t" << token << endl; //输出单分界符符号
        }
        else if (doubleword.find(ch) != string::npos) //双分界符处理
        {
            token += ch;
            fin.get(ch);     //读下一个字符判断是否为双分界符
            if (ch == '=') //如果是=，组合双分界符
            {
                token += ch;
                fin.get(ch); //读下一个符号以便识别下一个单词
            }
            fout << token << "\t" << token << endl; //输出单或双分界符符号
        }
        else if (ch == '/') //注释处理
        {
            fin.get(ch);     //读下一个字符
            if (ch == '*') //如果是*，则开始处理注释
            {
                char ch1;
                fin.get(ch1); //读下一个字符
                do
                {
                    ch = ch1; //删除注释
                    if (fin.eof())
                    {
                        fout << "ERROR\t"
                             << "注释未完成"
                             << "\t错误: 第" << line << "行" << endl; //输出错误符号
                        return (4);
                    }
                    fin.get(ch1);
                } while ((ch != '*' || ch1 != '/') && ch1 != EOF); //直到遇到注释结束符*/或文件尾
                fin.get(ch);                                         //读下一个符号以便识别下一个单词
            }
            else //不是*则处理单分界符/
            {
                token += ch;
                fout << token << "\t" << token << endl; //输出单分界符/
            }
        }
        else
        { //错误处理
            token += ch;
            fin.get(ch);                                                          //读下一个符号以便识别下一个单词
            es = 3;                                                             //设置错误代码
            fout << "ERROR\t" << token << "\t错误: 第" << line << "行" << endl; //输出错误符号
        }
    }
    fout << "end" << endl;
    fin.close();
    fout.close();
    return (es); //返回主程序
}