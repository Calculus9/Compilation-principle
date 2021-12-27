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
int error(int es, int line);
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
int line;
#define FIN input()

void input()
{
	fscanf(fp, "%s %s %d\n", token, token1, &line);
	printf("%s %s %d\n", token, token1, line);
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
	es = error(es, line);
	fclose(fp);
	return (es);
}
int error(int es, int line)
{
	printf("=====�﷨�������!======\n");
	if (es)
		printf("��%d��--", line);
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
	return es;
}
// program::={<declaration_list><statement_list>}
int program()
{
	int es = 0, i;
	FIN;
	if (strcmp(token, "{")) //�ж��Ƿ�'{'
	{
		es = 1;
		return error(es, line);
	}
	FIN;
	es = declaration_list();
	if (es > 0)
		return error(es, line);
	es = statement_list();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, "}")) //�ж��Ƿ�'}'
	{
		es = 2;
		return error(es, line);
	}
	return error(es, line);
}
//<��������>::=<��������><�������>|<�������>
//<declaration_list>::=
//<declaration_list><declaration_stat>|<declaration_stat>
//�ĳ�<declaration_list>::={<declaration_stat>}
int declaration_list()
{
	int es = 0;
	while (strcmp(token, "int") == 0)
	{
		es = declaration_stat();
		if (es > 0)
			return error(es, line);
	}
	return error(es, line);
}
//<�������> ::=int <����>��
//<declaration_stat>::=int ID;  -> ID{,ID}; -> ID([NUM]|��){,ID([NUM]|��)};
int declaration_stat()
{
	int es = 0, cnt = 1;
	do
	{
		FIN;
		if (strcmp(token, "ID"))
			return (es = 3); //���Ǳ�ʶ��
		char name[40];
		strcpy(name, token1);
		FIN;
		if (strcmp(token, "[") == 0)
		{
			FIN;
			if (strcmp(token, "NUM"))
				return (es = 8);
			cnt = atoi(token1);
			FIN;
			if (strcmp(token, "]"))
				return (es = 9);
			FIN;
		}
		if (es > 0)
			return (es);
	} while (strcmp(token, ",") == 0);

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
			return error(es, line);
	}
	return error(es, line);
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
	return error(es, line);
}
//<IF ���>::= if (<���ʽ>) <��� > [else <��� >]
//<IF_stat>::= if (<expr>) <statement > [else < statement >]

int if_stat()
{
	int es = 0; // if
	FIN;
	if (strcmp(token, "("))
		return error(es = 5, line); //��������
	FIN;
	es = expression();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, ")"))
		return error(es = 6, line); //��������
	FIN;
	es = statement();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, "else") == 0) // else���ִ���
	{
		FIN;
		es = statement();
		if (es > 0)
			return error(es, line);
	}
	return error(es, line);
}
// <do-while_stat>�� do ��{��<statement>��}��while (<expr >) ;
int do_while_stat()
{
	int es = 0;
	FIN;
	es = statement();
	if (es)
		return error(es, line);
	FIN;
	if (strcmp(token, "while") == 0) // while���ִ���
	{
		FIN;
		es = expression();
		if (es > 0)
			return error(es, line);
		if (strcmp(token, ";"))
		{
			return error(es = 4, line);
		}
		FIN;
	}
	return error(es, line);
}
//<while���>::=while(<���ʽ>) <���>
//<while_stat>::= while (<expr >) < statement >
int while_stat()
{
	int es = 0;
	FIN;
	if (strcmp(token, "("))
		return error(5, line); //��������
	FIN;
	es = expression();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, ")"))
		return error(es = 6, line); //��������
	FIN;
	es = statement();
	return error(es, line);
}

//<for���>::=for(<���ʽ>;<���ʽ>;<���ʽ>) <��� >
//<for_stat>::= for(<expr>,<expr>,<expr>)<statement>
int for_stat()
{
	int es = 0;
	FIN;
	if (strcmp(token, "("))
		return error(es = 5, line); //��������
	FIN;
	es = expression();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, ";"))
		return error(es = 4, line); //�ٷֺ�
	FIN;
	es = expression();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, ";"))
		return error(es = 4, line); //�ٷֺ�
	FIN;
	es = expression();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, ")"))
		return error(6, line); //��������
	FIN;
	es = statement();
	return error(es, line);
}
//<write_���>::=write <���ʽ>;
//<write_stat>::=write <expression>;
int write_stat()
{
	int es = 0;
	FIN;
	if (strcmp(token, "\"") == 0)
	{
		do
		{
			FIN;
		} while (strcmp(token, "\""));
		FIN;
	}
	else
	{
		es = expression();
		if (es > 0)
			return error(es, line);
	}
	if (strcmp(token, ";"))
		return error(es = 4, line);
	FIN;
	return error(es, line);
}
//<read_���>::=read <����>;
//<read_stat>::=read ID;
int read_stat()
{
	int es = 0;
	FIN;
	if (strcmp(token, "ID"))
		return (es = 3); //�ٱ�ʶ��
	if (es > 0)
		return error(es, line);
	FIN;
	if (strcmp(token, ";"))
		return error(es = 4, line); //�ٷֺ�
	FIN;
	return error(es, line);
}
//<�������>::={<�������>}
//<compound_stat>::={<statement_list>}
int compound_stat()
{ //������亯��
	int es = 0;
	FIN;
	es = statement_list();
	return error(es, line);
}

//<���ʽ���>::=<<���ʽ>;|;
//<expression_stat>::=<expression>;|;��
int expression_stat()
{
	int es = 0;
	if (strcmp(token, ";") == 0)
	{
		FIN;
		return error(es, line);
	}
	es = expression();
	if (es > 0)
		return error(es, line);
	if (es == 0 && strcmp(token, ";") == 0)
	{
		FIN;
		return error(es, line);
	}
	else
	{
		es = 4;
		return error(es, line); //�ٷֺ�
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
		fscanf(fp, "%s %s %d\n", &token2, &token3, &line);
		printf("%s %s %d\n", token2, token3, line);

		if (es > 0)
			return error(es, line);
		if (strcmp(token2, "=") == 0) //'='
		{
			fscanf(fp, "%s %s %d\n", &token, &token1, &line);
			printf("%s %s %d\n", token, token1, line);
			es = bool_expr();
		}
		else
		{
			fseek(fp, fileadd, 0); //����'='���ļ�ָ��ص�'='ǰ�ı�ʶ��
			printf("%s %s %d\n", token, token1, line);
			es = bool_expr();
			if (es > 0)
				return error(es, line);
		}
	}
	else
	{
		es = bool_expr();
		if (es > 0)
			return error(es, line);
	}
	return error(es, line);
}

//<�������ʽ>::=<�������ʽ>|<�������ʽ>(>|<|>=|<=|==|!=)<�������ʽ>
//<bool_expr>::=<additive_expr>
//           |< additive_expr >(>|<|>=|<=|==|!=)< additive_expr >

int bool_expr()
{
	int es = 0;
	es = additive_expr();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, ">") == 0 || strcmp(token, ">=") == 0 || strcmp(token, "<") == 0 || strcmp(token, "<=") == 0 || strcmp(token, "==") == 0 || strcmp(token, "!=") == 0)
	{
		FIN;
		es = additive_expr();
		if (es > 0)
			return error(es, line);
	}
	return error(es, line);
}
//<�������ʽ>::=<��>{(+|-)<��>}
//<additive_expr>::=<term>{(+|-)< term >}
int additive_expr()
{
	int es = 0;
	es = term();
	if (es > 0)
		return error(es, line);
	while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0)
	{
		FIN;
		es = term();
		if (es > 0)
			return error(es, line);
	}
	return error(es, line);
}
//<��>::=<����>{(%|*|/)<����>}
//< term >::=<factor>{(%|*|/)< factor >}
int term()
{
	int es = 0;
	es = factor();
	if (es > 0)
		return error(es, line);
	while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0 || strcmp(token, "%") == 0)
	{
		FIN;
		es = factor();
		if (es > 0)
			return error(es, line);
	}
	return error(es, line);
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
			return error(es, line);
		if (strcmp(token, ")"))
			return error(es = 6, line); //��������
		FIN;
	}
	else
	{
		if (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0)
		{
			fscanf(fp, "%s %s %d\n", &token, &token1, &line);
			printf("%s %s\n", token, token1);
			return error(es, line);
		}
		else
		{
			es = 7; //ȱ�ٲ�����
			return error(es, line);
		}
	}
	return error(es, line);
}