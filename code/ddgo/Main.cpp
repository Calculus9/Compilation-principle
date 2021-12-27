#include "lab_1.h"
#include "lab_3.h"
#include "lab_3_1.h"

int main()
{
    int es;
    es = lexicalAnalysis();
    if (es > 0)
        cout << "词法分析有问题, 编译停止!" << endl;
    else
    {
        cout << "词法分析成功" <<endl;
        es = TESTparse();
        if (es > 0)
            cout << "语法分析有问题, 编译停止!" << endl;
        else {
            cout<<"语法分析成功"<<endl;
            es = TESTmachine();
            if(es > 0) cout << "模拟机转换失败" <<endl;
            else cout << "模拟机转换成功" <<endl; 
        }
    }

    return 0;
}