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
char token[20], token1[40]; // token保存单词符号，token1保存单词值
// extern char Scanout[300];	//保存词法分析输出文件名
FILE *fp; //用于指向输入输出文件的指针
int line;
#define FIN input()

void input()
{
	fscanf(fp, "%s %s %d\n", token, token1, &line);
	printf("%s %s %d\n", token, token1, line);
}

//语法分析程序
int TESTparse()
{
	int es = 0;
	if ((fp = fopen("../Lexical_output.txt", "r")) == NULL)
	{
		printf("\n打开错误!\n");
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
	printf("=====语法分析结果!======\n");
	if (es)
		printf("第%d行--", line);
	switch (es)
	{
	case 0:
		printf("语法分析成功!\n");
		break;
	case 1:
		printf("缺少{!\n");
		break;
	case 2:
		printf("缺少}!\n");
		break;
	case 3:
		printf("缺少标识符!\n");
		break;
	case 4:
		printf("少分号!\n");
		break;
	case 5:
		printf("缺少(!\n");
		break;
	case 6:
		printf("缺少)!\n");
		break;
	case 7:
		printf("缺少操作数!\n");
		break;
	case 8:
		printf("数组缺少NUM\n");
		break;
	case 9:
		printf("缺少]\n");
		break;
	case 10:
		printf("打开文件失败!\n");
		break;
	}
	return es;
}
// program::={<declaration_list><statement_list>}
int program()
{
	int es = 0, i;
	FIN;
	if (strcmp(token, "{")) //判断是否'{'
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
	if (strcmp(token, "}")) //判断是否'}'
	{
		es = 2;
		return error(es, line);
	}
	return error(es, line);
}
//<声明序列>::=<声明序列><声明语句>|<声明语句>
//<declaration_list>::=
//<declaration_list><declaration_stat>|<declaration_stat>
//改成<declaration_list>::={<declaration_stat>}
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
//<声明语句> ::=int <变量>；
//<declaration_stat>::=int ID;  -> ID{,ID}; -> ID([NUM]|空){,ID([NUM]|空)};
int declaration_stat()
{
	int es = 0, cnt = 1;
	do
	{
		FIN;
		if (strcmp(token, "ID"))
			return (es = 3); //不是标识符
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

//<语句序列>::=<语句序列><语句>|<语句>
//<statement_list>::=<statement_list><statement>|<statement>
//改成<statement_list>::={<statement>}
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
//<语句>::=<if语句>|<while语句>|<for语句>|<read语句>
//         |<write语句>|<复合语句>|<表达式语句>
//<statement>::= <if_stat>|<while_stat>|<for_stat>
//               |<compound_stat> |<expression_stat>

int statement()
{
	int es = 0;
	if (es == 0 && strcmp(token, "if") == 0)
		es = if_stat(); //<IF语句>
	if (es == 0 && strcmp(token, "while") == 0)
		es = while_stat(); //<while语句>
	if (es == 0 && strcmp(token, "for") == 0)
		es = for_stat(); //<for语句>
	if (es == 0 && strcmp(token, "do") == 0)
		es = do_while_stat();
	if (es == 0 && strcmp(token, "read") == 0)
		es = read_stat(); //<read语句>
	if (es == 0 && strcmp(token, "write") == 0)
		es = write_stat(); //<write语句>
	if (es == 0 && strcmp(token, "{") == 0)
		es = compound_stat(); //<复合语句>
	if (es == 0 && (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0))
		es = expression_stat(); //<表达式语句>
	return error(es, line);
}
//<IF 语句>::= if (<表达式>) <语句 > [else <语句 >]
//<IF_stat>::= if (<expr>) <statement > [else < statement >]

int if_stat()
{
	int es = 0; // if
	FIN;
	if (strcmp(token, "("))
		return error(es = 5, line); //少左括号
	FIN;
	es = expression();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, ")"))
		return error(es = 6, line); //少右括号
	FIN;
	es = statement();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, "else") == 0) // else部分处理
	{
		FIN;
		es = statement();
		if (es > 0)
			return error(es, line);
	}
	return error(es, line);
}
// <do-while_stat>→ do ’{‘<statement>’}’while (<expr >) ;
int do_while_stat()
{
	int es = 0;
	FIN;
	es = statement();
	if (es)
		return error(es, line);
	FIN;
	if (strcmp(token, "while") == 0) // while部分处理
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
//<while语句>::=while(<表达式>) <语句>
//<while_stat>::= while (<expr >) < statement >
int while_stat()
{
	int es = 0;
	FIN;
	if (strcmp(token, "("))
		return error(5, line); //少左括号
	FIN;
	es = expression();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, ")"))
		return error(es = 6, line); //少右括号
	FIN;
	es = statement();
	return error(es, line);
}

//<for语句>::=for(<表达式>;<表达式>;<表达式>) <语句 >
//<for_stat>::= for(<expr>,<expr>,<expr>)<statement>
int for_stat()
{
	int es = 0;
	FIN;
	if (strcmp(token, "("))
		return error(es = 5, line); //少左括号
	FIN;
	es = expression();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, ";"))
		return error(es = 4, line); //少分号
	FIN;
	es = expression();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, ";"))
		return error(es = 4, line); //少分号
	FIN;
	es = expression();
	if (es > 0)
		return error(es, line);
	if (strcmp(token, ")"))
		return error(6, line); //少右括号
	FIN;
	es = statement();
	return error(es, line);
}
//<write_语句>::=write <表达式>;
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
//<read_语句>::=read <变量>;
//<read_stat>::=read ID;
int read_stat()
{
	int es = 0;
	FIN;
	if (strcmp(token, "ID"))
		return (es = 3); //少标识符
	if (es > 0)
		return error(es, line);
	FIN;
	if (strcmp(token, ";"))
		return error(es = 4, line); //少分号
	FIN;
	return error(es, line);
}
//<复合语句>::={<语句序列>}
//<compound_stat>::={<statement_list>}
int compound_stat()
{ //复合语句函数
	int es = 0;
	FIN;
	es = statement_list();
	return error(es, line);
}

//<表达式语句>::=<<表达式>;|;
//<expression_stat>::=<expression>;|;·
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
		return error(es, line); //少分号
	}
}
//<表达式>::=<标识符>=<布尔表达式>|<布尔表达式>
//<expr>::=ID=<bool_expr>|<bool_expr>

int expression()
{
	int es = 0, fileadd;
	char token2[20], token3[40];
	if (strcmp(token, "ID") == 0)
	{
		fileadd = ftell(fp); //记住当前文件位置
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
			fseek(fp, fileadd, 0); //若非'='则文件指针回到'='前的标识符
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

//<布尔表达式>::=<算术表达式>|<算术表达式>(>|<|>=|<=|==|!=)<算术表达式>
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
//<算术表达式>::=<项>{(+|-)<项>}
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
//<项>::=<因子>{(%|*|/)<因子>}
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
//<因子>::=(<算术表达式>)|<标识符>|<无符号整数>
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
			return error(es = 6, line); //少右括号
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
			es = 7; //缺少操作数
			return error(es, line);
		}
	}
	return error(es, line);
}