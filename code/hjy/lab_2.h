#include <bits/stdc++.h>
using namespace std;

string token, token1; // token���浥�ʷ��ţ�token1���浥��ֵ
extern string openFilename;
int program();
ifstream fin;
//�﷨��������
int TESTparse()
{
    int es = 0;
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
    if(fin.is_open()) fin.close();
}
//<����>::={<��������><�������>}
// program::={<declaration_list><statement_list>}
int program()
{
    int es = 0;
    
}