#include <bits/stdc++.h>
using namespace std;
int line;
string token, token1; // token保存单词符号，token1保存单词值
extern string openFilename;
int TESTparse();
int program();
int compound_stat();
int statement();
int expression_stat();
int expression();
int bool_expr();
int additive_expr();
int term();
int factor();
int if_stat();
int while_stat();
int for_stat();
int write_stat();
int read_stat();
int declaration_stat();
int declaration_list();
int statement_list();
int compound_stat();
ifstream fin;
//语法分析程序
int TESTparse()
{
    int es = 0;
    openFilename = "./lex_output.txt";
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
    if (fin.is_open())
        fin.close();
    return 0;
}

void getNext()
{
    fin >> token >> token1;
    cout << token << " --- " << token1 << endl;
}

//<程序>::={<声明序列><语句序列>}
// program::={<declaration_list><statement_list>}
int program()
{
    int es = 0;
    getNext();
    if (token != "{") //判断是否'{'
    {
        es = 1;
        return (es);
    }
    getNext();
    es = declaration_list();
    if (es > 0)
        return (es);
    es = statement_list();
    if (es > 0)
        return (es);
    if (token == "}") //判断是否'}'
    {
        es = 2;
        return (es);
    }
    return (es);
}

//<声明序列>::=<声明序列><声明语句>|<声明语句>
//<declaration_list>::=
//<declaration_list><declaration_stat>|<declaration_stat>
//该成<declaration_list>::={<declaration_stat>}
int declaration_list()
{
    int es = 0;
    while (token == "int")
    {
        es = declaration_stat();
        if (es > 0)
            return (es);
    }
    printf("\n声明结束\n\n");
    return (es);
}

//<声明语句> ::=int <变量>；
//<declaration_stat>::=int ID;
int declaration_stat()
{
    int es = 0;
    getNext();
    if (token != "ID")
        return (es = 3);
    getNext();
    if (token != ";")
        return (es = 4);
    getNext();
    return (es);
}
//<语句序列>::=<语句序列><语句>|<语句>
//<statement_list>::=<statement_list><statement>|<statement>
//改成<statement_list>::={<statement>}
int statement_list()
{
    int es = 0;
    while (token != "}")
    {
        es = statement();
        if (es > 0)
            return (es);
    }
    return (es);
}
//<语句>::=<if语句>|<while语句>|<for语句>|<read语句>
//         |<write语句>|<复合语句>|<表达式语句>
//<statement>::= <if_stat>|<while_stat>|<for_stat>
//               |<compound_stat> |<expression_stat>
int statement()
{
    int es = 0;
    if (es == 0 && token == "if")
        es = if_stat();
    if (es == 0 && token == "while")
        es = while_stat(); //<while语句>
    if (es == 0 && token == "for")
        es = for_stat(); //<for语句>
    //可在此处添加do语句调用
    if (es == 0 && token == "read")
        es = read_stat(); //<read语句>
    if (es == 0 && token == "write")
        es = write_stat(); //<write语句>
    if (es == 0 && token == "{")
        es = compound_stat(); //<复合语句>
    if (es == 0 && (token == "ID" || token == "NUM" || token == "("))
        es = expression_stat(); //<表达式语句>
    return (es);
}
//<write_语句>::=write <表达式>;
//<write_stat>::=write <expression>;
int write_stat()
{
    int es = 0;
    getNext();
    es = expression();
    if (es > 0)
        return (es);
    if (token != ";")
        return (es = 4); //少分号
    getNext();
    return (es);
}
//<read_语句>::=read <变量>;
//<read_stat>::=read ID;
int read_stat()
{
    int es = 0;
    getNext();
    if (token == "ID")
        return (es = 3); //少标识符
    getNext();
    if (token != ";")
        return (es = 4); //少分号
    getNext();
    return (es);
}

//<for语句>::=for(<表达式>;<表达式>;<表达式>) <语句 >
//<for_stat>::= for(<expr>,<expr>,<expr>)<statement>
int for_stat()
{
    int es = 0;
    getNext();
    if (token != "(")
        return (es = 5);
    getNext();
    es = expression();
    if (es > 0)
        return (es);
    if (token != ";")
        return (es = 4); //少分号
    getNext();
    es = expression();
    if (es > 0)
        return (es);
    if (token != ";")
        return (es = 4); //少分号
    getNext();
    es = expression();
    if (es > 0)
        return (es);
    if (token != ")")
        return (es = 6); //少右括号
    getNext();
    es = statement();
    return (es);
}
//<while语句>::=while(<表达式>) <语句>
//<while_stat>::= while (<expr >) < statement >
int while_stat()
{
    int es = 0;
    getNext();
    if (token != "(")
        return (es = 5);
    getNext();
    es = expression();
    if (es > 0)
        return (es);
    if (token != ")")
        return (es = 6); //少右括号
    getNext();
    es = statement();
    return es;
}
//<IF 语句>::= if (<表达式>) <语句 > [else <语句 >]
//<IF_stat>::= if (<expr>) <statement > [else < statement >]
int if_stat()
{
    printf("进入if语句\n");
    int es = 0; // if
    getNext();
    if (token != "(")
        return (es = 5);
    getNext();
    es = expression();
    if (es > 0)
        return (es);
    if (token != ")")
        return (es = 6); //少右括号
    getNext();
    es = statement();
    if (es > 0)
        return (es);
    if (token == "else") // else部分处理
    {
        getNext();
        es = statement();
        if (es > 0)
            return (es);
    }
    return (es);
}
//<复合语句>::={<语句序列>}
//<compound_stat>::={<statement_list>}
int compound_stat()
{ //复合语句函数
    int es = 0;
    getNext();
    es = statement_list();
    return (es);
}

//<表达式语句>::=<<表达式>;|;
//<expression_stat>::=<expression>;|;
int expression_stat()
{
    int es = 0;
    if (token == ";")
    {
        getNext();
        return (es);
    }
    es = expression();
    if (es > 0)
        return (es);
    if (es == 0 && token == ";")
    {
        getNext();
        return (es);
    }
    else
    {
        es = 4;
        return (es); //少分号
    }
}
//<表达式>::=<标识符>=<布尔表达式>|<布尔表达式>
//<expr>::=ID=<bool_expr>|<bool_expr>
int expression()
{
    int es = 0, fileadd;
    // char token2[20], token3[40];
    string token2, token3;
    cout<<"aaaaaaaaaaa"<<token<<endl;
    if (token == "ID")
    {
        string tokenleft,tokenright;
        tokenleft = token;
        tokenright = token1;
        fileadd = fin.tellg(); //记住当前文件位置
        fin >> token2 >> token3;
        // TODO:token2和token3
        if (es > 0)
            return (es);
        if (token2 == "=") //'=',赋值语句
        {
            getNext();
            es = bool_expr();
        }
        else
        {
            // TODO://若非'='则文件指针回到'='前的标识符
            fin.seekg(fileadd,std::ios::beg);//文件指针回到保留行
            token = tokenleft;
            token1 = tokenright;
            cout<<token<<" "<<token1<<endl;
            //  fseek(fp, fileadd, 0); //若非'='则文件指针回到'='前的标识符
            // printf("%s %s\n", token, token1);
            es = bool_expr();
            if (es > 0)
                return (es);
        }
    }
    else
        es = bool_expr();

    return (es);
}

//<布尔表达式>::=<算术表达式>|<算术表达式>(>|<|>=|<=|==|!=)<算术表达式>
//<bool_expr>::=<additive_expr>
//           |< additive_expr >(>|<|>=|<=|==|!=)< additive_expr >

int bool_expr()
{
    printf("进入bool\n");
    int es = 0;
    es = additive_expr();//算术表达式
    if (es > 0)
        return (es);
    if (token == ">" || token == ">=" || token == "<" || token == "<=" || token == "==" || token == "!=")
    {
        getNext();
        es = additive_expr();
        if (es > 0)
            return (es);
    }
    return (es);
}
//<算术表达式>::=<项>{(+|-)<项>}
//<additive_expr>::=<term>{(+|-)< term >}
int additive_expr()
{
    printf("算术表达式\n");
    int es = 0;
    es = term();
    if (es > 0)
        return (es);
    while (token == "+" || token == "-")
    {
        getNext();
        es = term();
        if (es > 0)
            return (es);
    }
    return (es);
}
//<项>::=<因子>{(*|/)<因子>}
//< term >::=<factor>{(*| /)< factor >}
int term()
{
    printf("进入term函数,");
    cout<<token<<","<<token1<<endl;
    int es = 0;
    es = factor();
    if (es > 0)
        return (es);
    while (token == "*" || token == "/")
    {
        getNext();
        es = factor();
        if (es > 0)
            return (es);
    }
    return (es);
}
//<因子>::=(<算术表达式>)|<标识符>|<无符号整数>
//< factor >::=(<additive_expr>)| ID|NUM

int factor()
{
    int es = 0;
    if (token == "(")
    {
        getNext();
        es = expression();
        if (es > 0)
            return (es);
        if (token != ")")
            return (es = 6); //少右括号
        getNext();
    }
    else
    {
        if (token == "ID" || token == "NUM")
        {
            cout<<token<<token1<<endl;
            getNext();
            cout<<token<<token1<<endl;
            return (es);
        }
        else
        {
            es = 7; //缺少操作数
            return (es);
        }
    }
    return (es);
}