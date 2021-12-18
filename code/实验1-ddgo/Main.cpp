#include "lab_1.h"

int main() {
    int es;
    es = lexicalAnalysis();
    if(es > 0) cout<<"词法分析有问题, 编译停止!"<<endl;
    else cout<<"词法分析成功"<<endl;
    return 0;
}