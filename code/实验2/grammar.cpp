/*
<program> S
<declaration_list> A
<declaration_stat> B
<statement_list> C
<statement> D
<if_stat> E
<while_stat> F
<for_stat> G 
<write_stat> H
<read_stat> I
<compound_stat> J
<assignment_expression> K
<assignment_stat> L
<bool_expression> M
<arithmetic_expression> N
<term> O
<factor> P

first(S) = {"{"}
first(A) = {��} U first(B) = {"int",��}
first(B) = {"int"}
first(C) = {��} U first(D) = 
            {"if","while","for","read","write","{","ID",";",��}
first(D) = first(E) U first(F) U first(G) U first(I) U first(H) U 
            first(J) U first(L) U {";"} = 
            {"if","while","for","read","write","{","ID",";"}
first(E) = {"if"}
first(E') = { "else", �� }
first(F) = {"while"}
first(G) = {"for"}
first(H) = {"write"}
first(I) = {"read"}
first(J) = {"{"}
first(K) = {"ID"}
first(L) = first(K) = {"ID"}
first(M) = first(N) = {"(","ID","NUM"}
first(M') = {">","<",">=","<=","==","!="}
first(N) = first(O) = {"(","ID","NUM"}
first(N') = {"+","-",��}
first(O) = first(P) = {"(","ID","NUM"}
first(O') = {"*","/",��}
first(P) = {"(","ID","NUM"}
first(BA) = {"int"}
first(��) = {��}
first(DC) = {"if","while","for","read","write","{","ID",";"}
first(else D) = {"else"}
first(>N) = {">"}
first(<N) = {"<"}
first(>=N) = {">="}
first(<=N) = {"<="}
first(!=N) = {"!="}
first(==N) = {"=="}
first(+ON') = {"+"}
first(-ON') = {"-"}
first(*PO') = {"*"}
first(/PO') = {"/"}
first((N)) = {"("}



follow(S) = {"#"}
follow(A) = {first(C)-��} U {"}"} = 
            {"if","while","for","read","write","{","ID",";","}"}
follow(B) = {first(A)-��} U follow(A) = 
            {"int","if","while","for","read","write","{","ID",";","}"}
follow(C) = {"}"}
follow(D) = {first(C)-��} U follow(C) U {first(E')-��} U follow(E) 
            U follow(E') U follow(F) U follow(G) = 
            {"if","while","for","read","write","{","ID",";","}","else"}
follow(E') = follow(E) U follow(D) = 
            {"if","while","for","read","write","{","ID",";","}","else"}
follow(M') = follow(M) = {";",")"}
follow(N') = follow(N) = {";"} U follow(K) U first(M') U 
                {">","<",">=","<=","==","!="} =
            {";",")",">","<",">=","<=","==","!="}
follow(O') = follow(O) = {first(N')-��} U follow(N) =
            {"+","-",";",")",">","<",">=","<=","==","!="}
follow(P) = {first(O')-��} U follow(O') U follow(O) = 
            {"+","-","*","/",";",")",">","<",">=","<=","==","!="}


first(BA) �� first(��) = ?            
first(BA) �� follow(A) = ?

first(DC) �� first(��) = ?            
first(DC) �� follow(C) = ?

first(else D) �� first(��) = ?        
������LL(1)�ķ�����3
first(else D) �� follow(E') = {"else"}

D -> E|F|G|I|H|J|L|;
first(E) �� first(F) = ? 
first(E) �� first(G) = ?
first(E) �� first(I) = ?
first(E) �� first(H) = ?
first(E) �� first(J) = ?
first(E) �� first(L) = ?
first(E) �� first(;) = ?
first(F) �� first(G) = ?
first(F) �� first(I) = ?
first(F) �� first(H) = ?
first(F) �� first(J) = ?
first(F) �� first(L) = ?
first(F) �� first(;) = ?
first(G) �� first(I) = ?
first(G) �� first(H) = ?
first(G) �� first(J) = ?
first(G) �� first(L) = ?
first(G) �� first(;) = ?
first(I) �� first(H) = ?
first(I) �� first(J) = ?
first(I) �� first(L) = ?
first(I) �� first(;) = ?
first(H) �� first(J) = ?
first(H) �� first(L) = ?
first(H) �� first(;) = ?
first(J) �� first(L) = ?
first(J) �� first(;) = ?
first(L) �� first(;) = ?

first(+ON') �� first(-ON') = ?
first(+ON') �� first(��) = ?
first(-ON') �� first(��) = ?
first(+ON') �� follow(N') = ?
first(-ON') �� follow(N') = ?

first(*PO') �� first(/PO') = ?
first(*PO') �� first(��) = ?
first(/PO') �� first(��) = ?
first(*ON') �� follow(O') = ?
first(/ON') �� follow(O') = ?

 */
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

void program();
void declaration_list();
void declaration_stat();
void statement_list();
void statement();
void if_stat();
void if_stat1();
void while_stat();
void for_stat();
void write_stat();
void read_stat();
void compound_stat();
void assignment_expression();
void assignment_stat();
void bool_expression();
void bool_expression1();
void arithmetic_expression();
void arithmetic_expression1();
void term();
void term1();
void factor();
void error(int);

ifstream infile;
int line;
string id,txt;

void getNext(){
    infile >> line >> id >> txt;
    if(infile.eof()) id = txt = "",++line;
}

void error(int index){
    cout << "line: " << line << " ";
    switch(index) {
        case 1:  cout << "ȱ�ٷֽ��'{'" << endl; break;
        case 2:  cout << "ȱ�ٷֽ��'}'" << endl; break;
        case 3:  cout << "ȱ�ٱ�ʶ��\"int\"" << endl; break;
        case 4:  cout << "ȱ�ٱ���" << endl; break;
        case 5:  cout << "ȱ�ٷֽ��';'" << endl; break;
        case 6:  cout << "ȱ�����" << endl; break;
        case 7:  cout << "ȱ��\"if\"" << endl; break;
        case 8:  cout << "ȱ��'('" << endl; break;
        case 9:  cout << "ȱ��')'" << endl; break;
        case 10: cout << "if������ݴ���" << endl; break;
        case 11: cout << "ȱ��\"while\"" << endl; break;
        case 12: cout << "ȱ��\"for\"" << endl; break;
        case 13: cout << "ȱ��\"write\"" << endl; break;
        case 14: cout << "ȱ��\"read\"" << endl; break;
        case 15: cout << "ȱ��'='" << endl; break;
        case 16: cout << "ȱ���߼������" << endl; break;
    }
    if(infile.is_open()) infile.close();
    exit(0);
}


// <program> -> {<declaration_list><statement_list>}
void program(){
    if(id=="{"){ getNext(); }
    else{ error(1);return; }

    declaration_list();
    statement_list();

    if(id=="}"){ getNext(); }
    else{ error(2);return; }
}

// <declaration_list> -> <declaration_list><declaration_stat> | ��
// ������ݹ�
// <declaration_list> -> <declaration_stat><declaration_list> | ��
void declaration_list(){
    if(id=="int"){
        declaration_stat();
        declaration_list();
    }else if(id=="if"||id=="while"||id=="for"||id=="read"||id=="write"||id=="{"||id=="ID"||id==";"||id=="}"){
        return;
    }else{ error(3);return; }
}


// <declaration_stat> -> int ID;
void declaration_stat(){
    if(id=="int"){ getNext(); }
    else{ error(3);return; }

    if(id=="ID"){ getNext(); }
    else{ error(4);return; }

    if(id==";"){ getNext(); }
    else{ error(5);return; }
}

// <statement_list> -> <statement_list><statement> | ��
// ������ݹ�
// <statement_list> -> <statement><statement_list> | ��
void statement_list(){
    if(id=="if"||id=="while"||id=="for"||id=="read"||id=="write"||id=="{"||id=="ID"||id==";"){
        statement();
        statement_list();
    }else if(id=="}"){
        return;
    }else{ error(2);return; }
}

// <statement> -> <if_stat>|<while_stat>|<for_stat>|<read_stat>
//              |<write_stat>|<compound_stat>|<assignment_stat>|;
void statement(){
    if(id=="if"){ if_stat(); }
    else if(id=="while"){ while_stat(); }
    else if(id=="for"){ for_stat(); }
    else if(id=="read"){ read_stat(); }
    else if(id=="write"){ write_stat(); }
    else if(id=="{"){ compound_stat(); }
    else if(id=="ID"){ assignment_stat(); }
    else if(id==";"){ getNext(); }
    else{ error(6);return; }
}


// <if_stat> -> if(<bool_expression>) <statement> 
//              |if(<bool_expression>) <statement> else <statement> 
// ��ȡ������
// <if_stat> -> if(<bool_expression>) <statement> <if_stat1>
// <if_stat1> -> �� | else <statement>
void if_stat(){
    if(id=="if"){ getNext(); }
    else{ error(7);return; }

    if(id=="("){ getNext(); }
    else{ error(8);return; }

    bool_expression();

    if(id==")"){ getNext(); }
    else{ error(9);return; }

    statement();
    if_stat1();
}



// <if_stat1> -> �� | else <statement>
void if_stat1(){
    //first(else <statement>) �� follow(<if_stat1>) = {"else"}
    if(id=="else"){
        //�洢��ǰ�ļ�getָ��λ�ú͵���
        auto front = infile.tellg();
        string cur = id;
        //��ȡ��һ������
        getNext();
        //����õ�������<statement>��first��
        //��ѡ��<if_stat1> -> else <statement>
        if(id=="if"||id=="while"||id=="for"||id=="read"||id=="write"||id=="{"||id=="ID"||id==";"){
            statement();
        }else{ 
            //ѡ��<if_stat1> -> ��
            //�ļ�getָ������֮ǰ��λ�ò������ʸĻ�ȥ
            id = cur;
            infile.seekg(front);return; 
        }
    }else if(id=="if"||id=="while"||id=="for"||id=="read"||id=="write"||id=="{"||id=="ID"||id==";"||id=="}"){
        return;
    }else{ error(10);return; }
}


// <while_stat> -> while(<bool_expression>) <statement>
void while_stat(){
    if(id=="while"){ getNext(); }
    else{ error(11);return; }

    if(id=="("){ getNext(); }
    else{ error(8);return; }

    bool_expression();

    if(id==")"){ getNext(); }
    else{ error(9);return; }

    statement();
}


// <for_stat> -> for(<assignment_expression>;<bool_expression>;
//                  <assignment_expression>) <statement>
void for_stat(){
    if(id=="for"){ getNext(); }
    else{ error(11);return; }

    if(id=="("){ getNext(); }
    else{ error(8);return; }

    assignment_expression();

    if(id==";"){ getNext(); }
    else{ error(5);return; }

    bool_expression();

    if(id==";"){ getNext(); }
    else{ error(5);return; }

    assignment_expression();

    if(id==")"){ getNext(); }
    else{ error(9);return; }

    statement();
}

// <write_stat> -> write <arithmetic_expression>;
void write_stat(){
    if(id=="write"){ getNext(); }
    else{ error(13);return; }

    arithmetic_expression();

    if(id==";"){ getNext(); }
    else{ error(5);return; }
}


// <read_stat> -> read ID;
void read_stat(){
    if(id=="read"){ getNext(); }
    else{ error(14);return; }

    if(id=="ID"){ getNext(); }
    else{ error(4);return; }

    if(id==";"){ getNext(); }
    else{ error(5);return; }
}


// <compound_stat> -> {<statement_list>}
void compound_stat(){
    if(id=="{"){ getNext(); }
    else{ error(1);return; }

    statement_list();

    if(id=="}"){ getNext(); }
    else{ error(2);return; }
}


// <assignment_expression> -> ID=<arithmetic_expression>
void assignment_expression(){
    if(id=="ID"){ getNext(); }
    else{ error(4);return; }

    if(id=="="){ getNext(); }
    else{ error(15);return; }

    arithmetic_expression();
}

// <assignment_stat> -> <assignment_expression>;
void assignment_stat(){
    assignment_expression();

    if(id==";"){ getNext(); }
    else{ error(5);return; }
}


// <bool_expression> -> <arithmetic_expression> >  <arithmetic_expression>
//                   |<arithmetic_expression> <  <arithmetic_expression>
//                   |<arithmetic_expression> >= <arithmetic_expression>
//                   |<arithmetic_expression> <= <arithmetic_expression>
//                   |<arithmetic_expression> == <arithmetic_expression>
//                   |<arithmetic_expression> != <arithmetic_expression>
// ��ȡ������
// <bool_expression> -> <arithmetic_expression> <bool_expression1>
// <bool_expression1> -> >  <arithmetic_expression>
//                   |<  <arithmetic_expression>
//                   |>= <arithmetic_expression>
//                   |<= <arithmetic_expression>
//                   |== <arithmetic_expression>
//                   |!= <arithmetic_expression>
void bool_expression(){
    arithmetic_expression();
    bool_expression1();
}

// <bool_expression1> -> >  <arithmetic_expression>
//                   |<  <arithmetic_expression>
//                   |>= <arithmetic_expression>
//                   |<= <arithmetic_expression>
//                   |== <arithmetic_expression>
//                   |!= <arithmetic_expression>
void bool_expression1(){
    if(id==">"||id=="<"||id==">="||id=="<="||id=="=="||id=="!="){
        getNext();
        arithmetic_expression();
    }else{ error(16);return; }
}


// <arithmetic_expression> -> <arithmetic_expression> + <term>
//                          |<arithmetic_expression> - <term>
//                          |<term>
// ������ݹ�
// <arithmetic_expression> -> <term> <arithmetic_expression1>
// <arithmetic_expression1> -> +<term> | -<term> | ��
void arithmetic_expression(){
    term();
    arithmetic_expression1();
}


// <arithmetic_expression1> -> + <term><arithmetic_expression1> | - <term><arithmetic_expression1> | ��
void arithmetic_expression1(){
    if(id=="+"||id=="-"){
        getNext();
        term();
        arithmetic_expression1();
    }else if(id==";"||id==")"||id==">"||id=="<"||id==">="||id=="<="||id=="=="||id=="!="){
        return;
    }else{ error(5);return; }
}


// <term> -> <term>*<factor> | <term>/<factor> | <factor>
// ������ݹ�
// <term> -> <factor> <term1>
// <term1> -> *<factor><term1> | /<factor><term1> | ��
void term(){
    factor();
    term1();
}


// <term1> -> *<factor><term1> | /<factor><term1> | ��
void term1(){
    if(id=="*"||id=="/"){
        getNext();
        factor();
        term1();
    }else if(id=="+"||id=="-"||id==";"||id==")"||id==">"||id=="<"||id==">="||id=="<="||id=="=="||id=="!="){
        return;
    }else{ error(5);return; }
}


// <factor> -> (<arithmetic_expression>) | ID | NUM
void factor(){
    if(id=="("){
        getNext();
        arithmetic_expression();

        if(id==")"){ getNext(); }
        else { error(9);return; }
    }else if(id=="ID"||id=="NUM"){ getNext(); }
    else{ error(4);return; }
}

signed main(int argc,char **argv) {
    infile.open(argv[1],ios::in);
    //freopen("./error.txt","a",stdout);
    getNext();
    program();
    if(infile.is_open()) infile.close();
    return 0;
}
