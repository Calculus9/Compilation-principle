#include<bits/stdc++.h>
using namespace std;

// �������б�����
#define keywordSum 8
#define mod (keywordSum + keywordSum - 3)
string keyword[keywordSum] = {"if", "else", "for", "while", "do", "int", "read", "write"};
bool isKeyword[mod];
int base1 = 31;
int base2 = 131;
int base3 = 1313;
int base4 = 13131;
int base5 = 131313;

//���涨�崿���ֽ��������Ҫ�����
string singleword = "+-*(){};,:";

//���涨��˫�ֽ�������ַ�
string doubleword = "><=!";

string openFilename;
const char *outputFilename = "../Lexical_output.txt";

int getHash(string &s) {
    int hashsum1 = 0;
    for(int i=0;i<(int)s.size();i++) hashsum1 = (hashsum1 * base1 % mod + s[i]) % mod;
    int hashsum2 = 0;
    for(int i=0;i<(int)s.size();i++) hashsum2 = (hashsum2 * base2 % mod + s[i]) % mod;
    int hashsum3 = 0;
    for(int i=0;i<(int)s.size();i++) hashsum3 = (hashsum3 * base3 % mod + s[i]) % mod;
    int hashsum4 = 0;
    for(int i=0;i<(int)s.size();i++) hashsum4 = (hashsum4 * base4 % mod + s[i]) % mod;
    int hashsum5 = 0;
    for(int i=0;i<(int)s.size();i++) hashsum5 = (hashsum5 * base5 % mod + s[i]) % mod;
    int hashsum = (hashsum1*base1 + hashsum2*base2 + hashsum3*base3 + hashsum4*base4 + hashsum5*base5) % mod;
    return hashsum;
}

void init() {
    for(int i=0;i<keywordSum;i++) isKeyword[getHash(keyword[i])] = true;
}

int lexicalAnalysis() {
    // ��ʼ���������ֵ�hashֵ��
    init();
    for(int i=0;i<mod;i++) cout<<isKeyword[i]<<" ";
    cout<<endl;

    string token = "";          // token���ڱ���ʶ����ĵ���
    char ch;                    //chΪÿ�ζ�����ַ�
    int line = 1, es = 0;       //��ǰ�����У�es������룬0��ʾû�д���
    
    cout<<"������Դ�����ļ���������·����: ";
    cin>>openFilename;
    const char *copenFilename=openFilename.c_str();
    
    //�ж������ļ����Ƿ���ȷ
    ifstream fin(copenFilename);
    if (!fin){
        cout<<"\n�򿪴ʷ����������ļ�����!"<<endl;
        return (1);             //�����ļ������ش������1
    }
    ofstream fout(outputFilename);
    if (!fout){
        cout<<"\n�����ʷ���������ļ�����!"<<endl;
        return (2);             //����ļ������ش������2
    }

    fin.get(ch);
    while(!fin.eof()) {
        while(ch == '\n') fin.get(ch), line++;
        while(ch == ' ' || ch == '\t') fin.get(ch);
        token = "";

        if(isalpha(ch)) { //��ĸ����
            token += ch;
            fin.get(ch);
            //�������ĸ��������ϱ�ʶ��������������ʶ����Ͻ���
            while(isalnum(ch)) token += ch, fin.get(ch);
            //���Ǳ����֣������ʶ��
            if(!isKeyword[getHash(token)]) fout<<"ID\t"<<token<<endl;
            else fout<<token<<"\t"<<token<<endl;

        }else if(isdigit(ch)) { //���ִ���
            token += ch;
            fin.get(ch);
            //�����������������������������������Ͻ���
            while(isdigit(ch)) token += ch, fin.get(ch);
            fout<<"NUM\t"<<token<<endl;         //�����������

        }else if(singleword.find(ch) != string::npos) { //���ַ�����
            token += ch;
            fin.get(ch);                            //����һ�������Ա�ʶ����һ������
            fout<<token<<"\t"<<token<<endl;     //������ֽ������

        }else if(doubleword.find(ch) != string::npos) { //˫�ֽ������
            token += ch;
            fin.get(ch);                            //����һ���ַ��ж��Ƿ�Ϊ˫�ֽ��
            if(ch == '=') {                     //�����=�����˫�ֽ��
                token += ch;
                fin.get(ch);                        //����һ�������Ա�ʶ����һ������
            }
            fout<<token<<"\t"<<token<<endl;      //�������˫�ֽ������
        }
        else if(ch == '/') {                    //ע�ʹ���
            fin.get(ch);                            //����һ���ַ�
            if(ch == '*') {                     //�����*����ʼ����ע��
                char ch1; fin.get(ch1);
                do {
                    ch = ch1;                   //ɾ��ע��
                    if(fin.eof()) {
                        fout<<"ERROR\t"<<"ע��δ���"<<"\t����: ��"<<line<<"��"<<endl; //����������
                        es = 4;
                        break;
                    }
                    fin.get(ch1);
                } while ((ch != '*' || ch1 != '/') && ch1 != EOF); //ֱ������ע�ͽ�����*/���ļ�β
                fin.get(ch);                        //����һ�������Ա�ʶ����һ������
            }
            else {                              //����*�����ֽ��/
                token += ch;
                fout<<token<<"\t"<<token<<endl; //������ֽ��/
            }
        }else {                                  //������
            token += ch;
            fin.get(ch);                            //����һ�������Ա�ʶ����һ������
            es = 3;                             //���ô������
            fout<<"ERROR\t"<<token<<"\t����: ��"<<line<<"��"<<endl; //����������
        }
    }
    fout<<"end"<<endl;
    fin.close();
    fout.close();
    return (es); //����������
}