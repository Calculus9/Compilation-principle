#include "lab_1.h"
#include "lab_2.h"
string openFilename;

int main()
{
    int es;
    es = lexicalAnalysis();
    if (es > 0)
        cout << "词法分析有问题, 编译停止!" << endl;
    else
        cout << "词法分析成功" << endl;
    if (es == 0)
    {
        es = TESTparse(); //调语法分析
        if (es == 0)
            printf("语法分析成功!\n");
        else
            printf("语法分析错误!\n");
    }
    return 0;
}