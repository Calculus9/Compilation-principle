#include "lab_1.h"
#include "lab_3.h"

int main()
{
    int es;
    es = lexicalAnalysis();
    if (es > 0)
        cout << "�ʷ�����������, ����ֹͣ!" << endl;
    else
    {
        cout << "�ʷ������ɹ�" << endl;
        es = TESTparse();
        if (es > 0)
            cout << "�﷨����������, ����ֹͣ!" << endl;
    }

    return 0;
}