#include "lab_1.h"
#include "lab2.h"
int main()
{
    int es;
    es = lexicalAnalysis();
    if (es > 0)
        cout << "�ʷ�����������, ����ֹͣ!" << endl;
    else
        cout << "�ʷ������ɹ�" << endl;
    if (es == 0)
    {
        es = TESTparse(); //���﷨����
        if (es == 0)
            printf("�﷨�����ɹ�!\n");
        else
            printf("�﷨��������!\n");
    }
    return 0;
}