#include "lab_1.h"
#include "lab_3.h"
#include "lab_3_1.h"

int main()
{
    int es;
    es = lexicalAnalysis();
    if (es > 0)
        cout << "�ʷ�����������, ����ֹͣ!" << endl;
    else
    {
        cout << "�ʷ������ɹ�" <<endl;
        es = TESTparse();
        if (es > 0)
            cout << "�﷨����������, ����ֹͣ!" << endl;
        else {
            cout<<"�﷨�����ɹ�"<<endl;
            es = TESTmachine();
            if(es > 0) cout << "ģ���ת��ʧ��" <<endl;
            else cout << "ģ���ת���ɹ�" <<endl; 
        }
    }

    return 0;
}