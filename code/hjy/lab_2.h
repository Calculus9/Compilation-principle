#include <bits/stdc++.h>
using namespace std;
int line;
string token, token1; // token���浥�ʷ��ţ�token1���浥��ֵ
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
//�﷨��������
int TESTparse()
{
    int es = 0;
    openFilename = "./lex_output.txt";
    const char *copenFilename = openFilename.c_str(); //�ɶ����ɸĵĳ�ָ��
    fin.open(copenFilename, ios::in);
    if (!fin)
    {
        cout << "\n��" << openFilename << "����!\n"
             << endl;
        es = 10;
    }
    if (es == 0)
        es = program();
    printf("=====�﷨�������!======\n");
    switch (es)
    {
    case 0:
        printf("�﷨�����ɹ�!\n");
        break;
    case 10:
        cout << "\n��" << openFilename << "����!\n"
             << endl;
        break;
    case 1:
        printf("ȱ��{!\n");
        break;
    case 2:
        printf("ȱ��}!\n");
        break;
    case 3:
        printf("ȱ�ٱ�ʶ��!\n");
        break;
    case 4:
        printf("�ٷֺ�!\n");
        break;
    case 5:
        printf("ȱ��(!\n");
        break;
    case 6:
        printf("ȱ��)!\n");
        break;
    case 7:
        printf("ȱ�ٲ�����!\n");
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

//<����>::={<��������><�������>}
// program::={<declaration_list><statement_list>}
int program()
{
    int es = 0;
    getNext();
    if (token != "{") //�ж��Ƿ�'{'
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
    if (token == "}") //�ж��Ƿ�'}'
    {
        es = 2;
        return (es);
    }
    return (es);
}

//<��������>::=<��������><�������>|<�������>
//<declaration_list>::=
//<declaration_list><declaration_stat>|<declaration_stat>
//�ó�<declaration_list>::={<declaration_stat>}
int declaration_list()
{
    int es = 0;
    while (token == "int")
    {
        es = declaration_stat();
        if (es > 0)
            return (es);
    }
    printf("\n��������\n\n");
    return (es);
}

//<�������> ::=int <����>��
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
//<�������>::=<�������><���>|<���>
//<statement_list>::=<statement_list><statement>|<statement>
//�ĳ�<statement_list>::={<statement>}
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
//<���>::=<if���>|<while���>|<for���>|<read���>
//         |<write���>|<�������>|<���ʽ���>
//<statement>::= <if_stat>|<while_stat>|<for_stat>
//               |<compound_stat> |<expression_stat>
int statement()
{
    int es = 0;
    if (es == 0 && token == "if")
        es = if_stat();
    if (es == 0 && token == "while")
        es = while_stat(); //<while���>
    if (es == 0 && token == "for")
        es = for_stat(); //<for���>
    //���ڴ˴����do������
    if (es == 0 && token == "read")
        es = read_stat(); //<read���>
    if (es == 0 && token == "write")
        es = write_stat(); //<write���>
    if (es == 0 && token == "{")
        es = compound_stat(); //<�������>
    if (es == 0 && (token == "ID" || token == "NUM" || token == "("))
        es = expression_stat(); //<���ʽ���>
    return (es);
}
//<write_���>::=write <���ʽ>;
//<write_stat>::=write <expression>;
int write_stat()
{
    int es = 0;
    getNext();
    es = expression();
    if (es > 0)
        return (es);
    if (token != ";")
        return (es = 4); //�ٷֺ�
    getNext();
    return (es);
}
//<read_���>::=read <����>;
//<read_stat>::=read ID;
int read_stat()
{
    int es = 0;
    getNext();
    if (token == "ID")
        return (es = 3); //�ٱ�ʶ��
    getNext();
    if (token != ";")
        return (es = 4); //�ٷֺ�
    getNext();
    return (es);
}

//<for���>::=for(<���ʽ>;<���ʽ>;<���ʽ>) <��� >
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
        return (es = 4); //�ٷֺ�
    getNext();
    es = expression();
    if (es > 0)
        return (es);
    if (token != ";")
        return (es = 4); //�ٷֺ�
    getNext();
    es = expression();
    if (es > 0)
        return (es);
    if (token != ")")
        return (es = 6); //��������
    getNext();
    es = statement();
    return (es);
}
//<while���>::=while(<���ʽ>) <���>
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
        return (es = 6); //��������
    getNext();
    es = statement();
    return es;
}
//<IF ���>::= if (<���ʽ>) <��� > [else <��� >]
//<IF_stat>::= if (<expr>) <statement > [else < statement >]
int if_stat()
{
    printf("����if���\n");
    int es = 0; // if
    getNext();
    if (token != "(")
        return (es = 5);
    getNext();
    es = expression();
    if (es > 0)
        return (es);
    if (token != ")")
        return (es = 6); //��������
    getNext();
    es = statement();
    if (es > 0)
        return (es);
    if (token == "else") // else���ִ���
    {
        getNext();
        es = statement();
        if (es > 0)
            return (es);
    }
    return (es);
}
//<�������>::={<�������>}
//<compound_stat>::={<statement_list>}
int compound_stat()
{ //������亯��
    int es = 0;
    getNext();
    es = statement_list();
    return (es);
}

//<���ʽ���>::=<<���ʽ>;|;
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
        return (es); //�ٷֺ�
    }
}
//<���ʽ>::=<��ʶ��>=<�������ʽ>|<�������ʽ>
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
        fileadd = fin.tellg(); //��ס��ǰ�ļ�λ��
        fin >> token2 >> token3;
        // TODO:token2��token3
        if (es > 0)
            return (es);
        if (token2 == "=") //'=',��ֵ���
        {
            getNext();
            es = bool_expr();
        }
        else
        {
            // TODO://����'='���ļ�ָ��ص�'='ǰ�ı�ʶ��
            fin.seekg(fileadd,std::ios::beg);//�ļ�ָ��ص�������
            token = tokenleft;
            token1 = tokenright;
            cout<<token<<" "<<token1<<endl;
            //  fseek(fp, fileadd, 0); //����'='���ļ�ָ��ص�'='ǰ�ı�ʶ��
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

//<�������ʽ>::=<�������ʽ>|<�������ʽ>(>|<|>=|<=|==|!=)<�������ʽ>
//<bool_expr>::=<additive_expr>
//           |< additive_expr >(>|<|>=|<=|==|!=)< additive_expr >

int bool_expr()
{
    printf("����bool\n");
    int es = 0;
    es = additive_expr();//�������ʽ
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
//<�������ʽ>::=<��>{(+|-)<��>}
//<additive_expr>::=<term>{(+|-)< term >}
int additive_expr()
{
    printf("�������ʽ\n");
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
//<��>::=<����>{(*|/)<����>}
//< term >::=<factor>{(*| /)< factor >}
int term()
{
    printf("����term����,");
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
//<����>::=(<�������ʽ>)|<��ʶ��>|<�޷�������>
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
            return (es = 6); //��������
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
            es = 7; //ȱ�ٲ�����
            return (es);
        }
    }
    return (es);
}