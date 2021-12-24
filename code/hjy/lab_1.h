#include <bits/stdc++.h>
using namespace std;

// �������б�����
#define keywordSum 8
#define mod (13)
string keyword[keywordSum] = {"if", "else", "for", "while", "do", "int", "read", "write"};
unsigned long long isKeyword[mod];
int base = 131;

//���涨�崿���ֽ��������%
string singleword = "+-*(){};,/%\"";

//���涨��˫�ֽ�������ַ�
string doubleword = "><=!";

string openFilename;
const char *outputFilename = "./Lexical_output.txt";

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
 * @brief ��ʼ�������ؼ��ֵ�hashֵ
 */
void init()
{
    memset(isKeyword, -1, sizeof(isKeyword));
    for (int i = 0; i < keywordSum; i++)
    {
        insert(getHash(keyword[i]));
    }
}

int judge_length(string s)
{
    if (s.size() > 39)
        return 1;
    else
        return 0;
}

/**
 * @brief �ʷ���������
 * @return int ����ֵ
 *      0���ʷ�����û�з��ִ���
 *      1��2�����������ļ��д���
 *      3����ʾ�зǷ�����
 */
int lexicalAnalysis()
{
    // ��ʼ�����������ֵ�hashֵ��
    init();

    string token = "";    // token���ڱ���ʶ����ĵ���
    char ch;              // chΪÿ�ζ�����ַ�
    int line = 1, es = 0; //��ǰ�����У�es������룬0��ʾû�д���

    cout << "������Դ�����ļ���������·����: ";
    cin >> openFilename;
    string tmp = "./test/" + openFilename;
    const char *copenFilename = tmp.c_str(); //�ɶ����ɸĵĳ�ָ��

    //�ж������ļ����Ƿ���ȷ
    ifstream fin(copenFilename); //���룬��Ӳ�̵��ڴ�
    if (!fin)
    {
        cout << "\n�򿪴ʷ����������ļ�����!" << endl;
        return (1); //�����ļ��������ش������1
    }
    ofstream fout(outputFilename); //��������ڴ浽Ӳ��
    if (!fout)
    {
        cout << "\n�����ʷ���������ļ�����!" << endl;
        return (2); //����ļ��������ش������2
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
        token = "";
        if (isalpha(ch)) //�������ĸ������б�ʶ������
        {
            token += ch;
            fin.get(ch); //���������ַ�
            //�������ĸ��������ϱ�ʶ��������������ʶ����Ͻ���
            while (isalnum(ch))
            {
                token += ch; //��ϴ�ŵ�token��
                fin.get(ch); //����һ���ַ�
            }
            if (judge_length(token))
            {
                string token1 = token.substr(0, 39);
                token = token.substr(39);
                cout << "��" << line << "�б�ʶ��Խ�磬��ȥ��" << token1 << "��ʣ���ַ�:" << token << endl;
                fout << "��ʶ��Խ�磬�ѽ�ȡ����ǰIDΪ" << token << endl;
            }
            //�鱣����
            if (!find(getHash(token))) //���Ǳ����֣������ʶ��
                fout << "ID\t" << token << endl;
            else
                fout << token << "\t" << token << endl;
        }
        else if (isdigit(ch)) //���ִ���
        {
            token += ch;
            fin.get(ch);        //����һ���ַ�
            while (isdigit(ch)) //�����������������������������������Ͻ���
            {
                token += ch; //�������������token��
                fin.get(ch); //����һ���ַ�
            }
            fout << "NUM\t" << token << endl; //�����������
        }
        else if (singleword.find(ch) != string::npos) //���ַ�����
        {
            token += ch;
            fin.get(ch);                            //����һ�������Ա�ʶ����һ������
            fout << token << "\t" << token << endl; //������ֽ������
        }
        else if (doubleword.find(ch) != string::npos) //˫�ֽ������
        {
            token += ch;
            fin.get(ch);   //����һ���ַ��ж��Ƿ�Ϊ˫�ֽ��
            if (ch == '=') //�����=�����˫�ֽ��
            {
                token += ch;
                fin.get(ch); //����һ�������Ա�ʶ����һ������
            }
            fout << token << "\t" << token << endl; //�������˫�ֽ������
        }
        else if (ch == '/') //ע�ʹ���
        {
            fin.get(ch);   //����һ���ַ�
            if (ch == '*') //�����*����ʼ����ע��
            {
                char ch1;
                fin.get(ch1); //����һ���ַ�
                do
                {
                    ch = ch1; //ɾ��ע��
                    if (fin.eof())
                    {
                        cout << "ERROR\t"
                             << "ע��δ��ȫ"
                             << "\t����: ��" << line << "��" << endl; //����������
                        fout << "ERROR\t"
                             << "ע��δ��ȫ"
                             << "\t����: ��" << line << "��" << endl; //����������
                        return (4);
                    }
                    fin.get(ch1);
                } while ((ch != '*' || ch1 != '/') && ch1 != EOF); //ֱ������ע�ͽ�����*/���ļ�β
                fin.get(ch);                                       //����һ�������Ա�ʶ����һ������
            }
            else //����*�������ֽ��/
            {
                token += ch;
                fout << token << "\t" << token << endl; //������ֽ��/
            }
        }
        else
        { //������
            token += ch;
            fin.get(ch);                                                        //����һ�������Ա�ʶ����һ������
            es = 3;                                                             //���ô������
            fout << "ERROR\t" << token << "\t����: ��" << line << "��" << endl; //����������
            cout << "ERROR\t" << token << "\t����: ��" << line << "��" << endl; //����������
        }
    }
    fout << "end" << endl;
    fin.close();
    fout.close();
    return (es); //����������
}