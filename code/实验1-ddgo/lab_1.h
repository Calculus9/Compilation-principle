#include <bits/stdc++.h>
using namespace std;

// �������б�����
#define keywordSum 8
#define mod (keywordSum + keywordSum)
string keyword[keywordSum] = {"if", "else", "for", "while", "do", "int", "read", "write"};
bool isKeyword[mod];
int base = 131;

//���涨�崿���ֽ��������Ҫ�����
string singleword = "+-*(){};,:";

//���涨��˫�ֽ�������ַ�
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
 * @brief ��ʼ�������ؼ��ֵ�hashֵ
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
 * @brief �ʷ���������
 * @return int ����ֵ
 *      0���ʷ�����û�з��ִ���
 *      1��2�����������ļ��д���
 *      3����ʾ�зǷ�����
 */
int lexicalAnalysis()
{
    // ��ʼ���������ֵ�hashֵ��
    init();

    string token = "";    // token���ڱ���ʶ����ĵ���
    char ch;              // chΪÿ�ζ�����ַ�
    int line = 1, es = 0; //��ǰ�����У�es������룬0��ʾû�д���

    cout << "������Դ�����ļ���������·����: ";
    cin >> openFilename;
    const char *copenFilename = openFilename.c_str(); //�ɶ����ɸĵĳ�ָ��

    //�ж������ļ����Ƿ���ȷ
    ifstream fin(copenFilename); //���룬��Ӳ�̵��ڴ�
    if (!fin)
    {
        cout << "\n�򿪴ʷ����������ļ�����!" << endl;
        return (1); //�����ļ������ش������1
    }
    ofstream fout(outputFilename); //��������ڴ浽Ӳ��
    if (!fout)
    {
        cout << "\n�����ʷ���������ļ�����!" << endl;
        return (2); //����ļ������ش������2
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
        if (isalpha(ch)) //�������ĸ������б�ʶ������
        {
            token += ch;
            fin.get(ch); //���������ַ�
            //�������ĸ��������ϱ�ʶ��������������ʶ����Ͻ���
            while (isalnum(ch))
            {
                token += ch; //��ϴ�ŵ�token��
                fin.get(ch);   //����һ���ַ�
            }
            //�鱣����
            if (!isKeyword[getHash(token)]) //���Ǳ����֣������ʶ��
                fout << "ID\t" << token << endl;
            else
                fout << token << "\t" << token << endl;
        }
        else if (isdigit(ch)) //���ִ���
        {
            token += ch;
            fin.get(ch);          //����һ���ַ�
            while (isdigit(ch)) //�����������������������������������Ͻ���
            {
                token += ch; //�������������token��
                fin.get(ch);   //����һ���ַ�
            }
            fout << "NUM\t" << token << endl; //�����������
        }
        else if (singleword.find(ch) != string::npos) //���ַ�����
        {
            token += ch;
            fin.get(ch);                              //����һ�������Ա�ʶ����һ������
            fout << token << "\t" << token << endl; //������ֽ������
        }
        else if (doubleword.find(ch) != string::npos) //˫�ֽ������
        {
            token += ch;
            fin.get(ch);     //����һ���ַ��ж��Ƿ�Ϊ˫�ֽ��
            if (ch == '=') //�����=�����˫�ֽ��
            {
                token += ch;
                fin.get(ch); //����һ�������Ա�ʶ����һ������
            }
            fout << token << "\t" << token << endl; //�������˫�ֽ������
        }
        else if (ch == '/') //ע�ʹ���
        {
            fin.get(ch);     //����һ���ַ�
            if (ch == '*') //�����*����ʼ����ע��
            {
                char ch1;
                fin.get(ch1); //����һ���ַ�
                do
                {
                    ch = ch1; //ɾ��ע��
                    if (fin.eof())
                    {
                        fout << "ERROR\t"
                             << "ע��δ���"
                             << "\t����: ��" << line << "��" << endl; //����������
                        return (4);
                    }
                    fin.get(ch1);
                } while ((ch != '*' || ch1 != '/') && ch1 != EOF); //ֱ������ע�ͽ�����*/���ļ�β
                fin.get(ch);                                         //����һ�������Ա�ʶ����һ������
            }
            else //����*�����ֽ��/
            {
                token += ch;
                fout << token << "\t" << token << endl; //������ֽ��/
            }
        }
        else
        { //������
            token += ch;
            fin.get(ch);                                                          //����һ�������Ա�ʶ����һ������
            es = 3;                                                             //���ô������
            fout << "ERROR\t" << token << "\t����: ��" << line << "��" << endl; //����������
        }
    }
    fout << "end" << endl;
    fin.close();
    fout.close();
    return (es); //����������
}