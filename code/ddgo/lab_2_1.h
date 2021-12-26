#include <bits/stdc++.h>
using namespace std;
int TESTparse();
int program();
int compound_stat();
int statement();
int expression_stat();
int expression();
int bool_expr();
int additive_expr();
int term();
int factor();
int if_stat();
int while_stat();
int for_stat();
int write_stat();
int read_stat();
int declaration_stat();
int declaration_list();
int statement_list();
int compound_stat();
int do_while_stat();
char token[20], token1[40]; // token���浥�ʷ��ţ�token1���浥��ֵ
// extern char Scanout[300];	//����ʷ���������ļ���
FILE *fp; //����ָ����������ļ���ָ��

#define FIN input()

void input() {
	fscanf(fp, "%s %s\n", token, token1);
	printf("%s %s\n", token, token1);
}

//�﷨��������
int TESTparse()
{
	int es = 0;
	if ((fp = fopen("../Lexical_output.txt", "r")) == NULL)
	{
		printf("\n�򿪴���!\n");
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
	case 8:
		printf("����ȱ��NUM\n");
		break;
	case 9:
		printf("ȱ��]\n");
		break;
	case 10:
		printf("���ļ�ʧ��!\n");
		break;
	}
	fclose(fp);
	return (es);
}
//<����>::={<��������><�������>}
// program::={<declaration_list><statement_list>}
int program()
{
	int es = 0;
	FIN;
	if (strcmp(token, "{")) //�ж��Ƿ�'{'
	{
		es = 1;
		return (es);
	}
	FIN;
	es = declaration_list();
	if (es > 0)
		return (es);
	es = statement_list();
	if (es > 0)
		return (es);
	if (strcmp(token, "}")) //�ж��Ƿ�'}'
	{
		es = 2;
		return (es);
	}
	return (es);
}
//<��������>::=<��������><�������>|<�������>
//<declaration_list>::=
//<declaration_list><declaration_stat>|<declaration_stat>
//�ó�<declaration_list>::={<declaration_stat>}
int declaration_list()
{
	int es = 0;
	while (strcmp(token, "int") == 0)
	{
		es = declaration_stat();
		if (es > 0)
			return (es);
	}
	return (es);
}
//<�������> ::=int <����>��
//<declaration_stat>::=int ID;  -> ID{,ID}; -> ID([NUM]|��){,ID([NUM]|��)};
int declaration_stat()
{
	int es = 0;
	FIN;
	if (strcmp(token, "ID"))
		return (es = 3); //���Ǳ�ʶ��
	
	FIN;
	if(strcmp(token, "[") == 0) {
		FIN;
		if(strcmp(token, "NUM")) return (es = 8);
		FIN;
		if(strcmp(token, "]")) return (es = 9);
		FIN;
	}

	while(strcmp(token, ",") == 0) {
		FIN;
		if (strcmp(token, "ID"))
			return (es = 3); //���Ǳ�ʶ��
		FIN;
		if(strcmp(token, "[") == 0) {
			FIN;
			if(strcmp(token, "NUM")) return (es = 8);
			FIN;
			if(strcmp(token, "]")) return (es = 9);
			FIN;
		}
	}
	if (strcmp(token, ";"))
		return (es = 4);
	FIN;
	return (es);
}
//<�������>::=<�������><���>|<���>
//<statement_list>::=<statement_list><statement>|<statement>
//�ĳ�<statement_list>::={<statement>}
int statement_list()
{
	int es = 0;
	while (strcmp(token, "}"))
	{
		es = statement();
		if (es > 0)
			return (es);
	}
	return (es);
}
//<���>::=<if���>|<while���>|<for���>|<read���>
//         |<write���>|<�������>|<���ʽ���>
//<statement>::= <if_stat>|<while_stat>|<for_stat>
//               |<compound_stat> |<expression_stat>

int statement()
{
	int es = 0;
	if (es == 0 && strcmp(token, "if") == 0)
		es = if_stat(); //<IF���>
	if (es == 0 && strcmp(token, "while") == 0)
		es = while_stat(); //<while���>
	if (es == 0 && strcmp(token, "for") == 0)
		es = for_stat(); //<for���>
	//���ڴ˴����do������
	if (es == 0 && strcmp(token, "do") == 0)
		es = do_while_stat();
	if (es == 0 && strcmp(token, "read") == 0)
		es = read_stat(); //<read���>
	if (es == 0 && strcmp(token, "write") == 0)
		es = write_stat(); //<write���>
	if (es == 0 && strcmp(token, "{") == 0)
		es = compound_stat(); //<�������>
	if (es == 0 && (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0))
		es = expression_stat(); //<���ʽ���>
	return (es);
}
//<IF ���>::= if (<���ʽ>) <��� > [else <��� >]
//<IF_stat>::= if (<expr>) <statement > [else < statement >]

int if_stat()
{
	int es = 0; // if
	FIN;
	if (strcmp(token, "("))
		return (es = 5); //��������
	FIN;
	es = expression();
	if (es > 0)
		return (es);
	if (strcmp(token, ")"))
		return (es = 6); //��������
	FIN;
	es = statement();
	if (es > 0)
		return (es);
	if (strcmp(token, "else") == 0) // else���ִ���
	{
		FIN;
		es = statement();
		if (es > 0)
			return (es);
	}
	return (es);
}
// <do-while_stat>�� do ��{��<statement>��}��while (<expr >) ;
int do_while_stat()
{
	int es = 0;
	FIN;
	es = statement();
	if (es)
		return es;
	FIN;
	if (strcmp(token, "while") == 0) // while���ִ���
	{
		FIN;
		es = expression();
		if (es > 0)
			return es;
		if (strcmp(token, ";"))
		{
			return (es = 4);
		}
		FIN;
	}
	return es;
}
//<while���>::=while(<���ʽ>) <���>
//<while_stat>::= while (<expr >) < statement >
int while_stat()
{
	int es = 0;
	FIN;
	if (strcmp(token, "("))
		return (es = 5); //��������
	FIN;
	es = expression();
	if (es > 0)
		return (es);
	if (strcmp(token, ")"))
		return (es = 6); //��������
	FIN;
	es = statement();
	return (es);
}

//<for���>::=for(<���ʽ>;<���ʽ>;<���ʽ>) <��� >
//<for_stat>::= for(<expr>,<expr>,<expr>)<statement>
int for_stat()
{
	int es = 0;
	FIN;
	if (strcmp(token, "("))
		return (es = 5); //��������
	FIN;
	es = expression();
	if (es > 0)
		return (es);
	if (strcmp(token, ";"))
		return (es = 4); //�ٷֺ�
	FIN;
	es = expression();
	if (es > 0)
		return (es);
	if (strcmp(token, ";"))
		return (es = 4); //�ٷֺ�
	FIN;
	es = expression();
	if (es > 0)
		return (es);
	if (strcmp(token, ")"))
		return (es = 6); //��������
	FIN;
	es = statement();
	return (es);
}
//<write_���>::=write <���ʽ>;
//<write_stat>::=write <expression>;
int write_stat()
{
	int es = 0;
	FIN;
	es = expression();
	if (es > 0)
		return (es);
	if (strcmp(token, ";"))
		return (es = 4); //�ٷֺ�
	FIN;
	return (es);
}
//<read_���>::=read <����>;
//<read_stat>::=read ID;
int read_stat()
{
	int es = 0;
	FIN;
	if (strcmp(token, "ID"))
		return (es = 3); //�ٱ�ʶ��
	FIN;
	if (strcmp(token, ";"))
		return (es = 4); //�ٷֺ�
	FIN;
	return (es);
}
//<�������>::={<�������>}
//<compound_stat>::={<statement_list>}
int compound_stat()
{ //������亯��
	int es = 0;
	FIN;
	es = statement_list();
	return (es);
}

//<���ʽ���>::=<<���ʽ>;|;
//<expression_stat>::=<expression>;|;��
int expression_stat()
{
	int es = 0;
	if (strcmp(token, ";") == 0)
	{
		FIN;
		return (es);
	}
	es = expression();
	if (es > 0)
		return (es);
	if (es == 0 && strcmp(token, ";") == 0)
	{
		FIN;
		return (es);
	}
	else
	{
		es = 4;
		return (es); //�ٷֺ�
	}
}
//<���ʽ>::=<��ʶ��>=<�������ʽ>|<�������ʽ>
//<expr>::=ID=<bool_expr>|<bool_expr>

int expression()
{
	int es = 0, fileadd;
	char token2[20], token3[40];
	if (strcmp(token, "ID") == 0)
	{
		fileadd = ftell(fp); //��ס��ǰ�ļ�λ��
		fscanf(fp, "%s %s\n", &token2, &token3);
		printf("%s %s\n", token2, token3);

		if (es > 0)
			return (es);
		if (strcmp(token2, "=") == 0) //'='
		{
			fscanf(fp, "%s %s\n", &token, &token1);
			printf("%s %s\n", token, token1);
			es = bool_expr();
		}
		else
		{
			fseek(fp, fileadd, 0); //����'='���ļ�ָ��ص�'='ǰ�ı�ʶ��
			printf("%s %s\n", token, token1);
			es = bool_expr();
			if (es > 0)
				return (es);
		}
	}
	else
		es = bool_expr();

	return (es);
}

//<�������ʽ>::=<�������ʽ>|<�������ʽ>(>|<|>=|<=|==|!=)<�������ʽ>
//<bool_expr>::=<additive_expr>
//           |< additive_expr >(>|<|>=|<=|==|!=)< additive_expr >

int bool_expr()
{
	int es = 0;
	es = additive_expr();
	if (es > 0)
		return (es);
	if (strcmp(token, ">") == 0 || strcmp(token, ">=") == 0 || strcmp(token, "<") == 0 || strcmp(token, "<=") == 0 || strcmp(token, "==") == 0 || strcmp(token, "!=") == 0)
	{
		FIN;
		es = additive_expr();
		if (es > 0)
			return (es);
	}
	return (es);
}
//<�������ʽ>::=<��>{(+|-)<��>}
//<additive_expr>::=<term>{(+|-)< term >}
int additive_expr()
{
	int es = 0;
	es = term();
	if (es > 0)
		return (es);
	while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0)
	{
		FIN;
		es = term();
		if (es > 0)
			return (es);
	}
	return (es);
}
//<��>::=<����>{(%|*|/)<����>}
//< term >::=<factor>{(%|*|/)< factor >}
int term()
{
	int es = 0;
	es = factor();
	if (es > 0)
		return (es);
	while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0 || strcmp(token, "%") == 0)
	{
		FIN;
		es = factor();
		if (es > 0)
			return (es);
	}
	return (es);
}
//<����>::=(<�������ʽ>)|<��ʶ��>|<�޷�������>
//< factor >::=(<additive_expr>)| ID|NUM

int factor()
{
	int es = 0;

	if (strcmp(token, "(") == 0)
	{
		FIN;
		es = expression();
		if (es > 0)
			return (es);
		if (strcmp(token, ")"))
			return (es = 6); //��������
		FIN;
	}
	else
	{

		if (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0)
		{
			fscanf(fp, "%s %s\n", &token, &token1);
			printf("%s %s\n", token, token1);
			return (es);
		}
		else
		{
			es = 7; //ȱ�ٲ�����
			return (es);
		}
	}
	return (es);
}