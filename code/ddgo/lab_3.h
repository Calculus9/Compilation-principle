//�﷨�������������������
#include<bits/stdc++.h>
#define maxvartablep 500//������ű������
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
int name_def(char *name,int cnt);
char token[20],token1[40];//token���浥�ʷ��ţ�token1���浥��ֵ
char Codeout[300]; //����ʷ���������ļ���
FILE *fp,*fout; //����ָ����������ļ���ָ��
struct Table{//������ű�ṹ
     char name[40];
     int address;
}vartable[maxvartablep];//�ķ��ű��������maxvartablep����¼
int vartablep=0,labelp=0,datap=0;

#define FIN input()

void input() {
	fscanf(fp, "%s %s\n", token, token1);
	printf("%s %s\n", token, token1);
}

//������ű���@name-def��n, t�ĳ������£�
int name_def(char *name,int cnt)
{
	if(cnt <= 0) return (24);   
	int i,es=0;
    if (vartablep>=maxvartablep) return(21);
	for(i=vartablep-1;i>=0;i--)//����ű�
	{ 
		if (strcmp(vartable[i].name,name)==0)
		{
			es=22;//22��ʾ�����ظ�����
			break;
		}
	}
	if (es>0)   return(es);
	strcpy(vartable[vartablep].name,name);
	vartable[vartablep].address=datap+cnt-1;
	datap += cnt;//����һ����Ԫ��������ָ���1
	vartablep++;	
	return(es);
}
//��ѯ���ű��ص�ַ
int lookup(char *name,int *paddress)
{
	int i,es=0;
	for(i=0;i<vartablep;i++)
	{
		if (strcmp(vartable[i].name,name)==0)
		{
           *paddress=vartable[i].address;
		   return(es);
		}
	}
     es=23;//����û������
	 return(es);
}

//�﷨������������������ɳ���
int TESTparse()
{
	int es=0;
	if((fp=fopen("../Lexical_output.txt","r"))==NULL)
	{  
      printf("\n��../Lexical_output.txt����!\n");
	  es=10;
	  return(es);
	}
	printf("������Ŀ���ļ���������·����: ");
    scanf("%s",Codeout);
	if((fout=fopen(Codeout,"w"))==NULL)
	{  
      printf("\n����%s����!\n",Codeout);
	  es=10;
	  return(es);
	}
	if (es==0) es=program();
	printf("==�﷨������������������ɳ�����==\n");
	switch(es)
	{
		case 0: printf("�﷨����������ɹ��������������ɴ���!\n");break;	
		case 1: printf("ȱ��{!\n");break;
		case 2: printf("ȱ��}!\n");break;
		case 3: printf("ȱ�ٱ�ʶ��!\n");break;
		case 4: printf("�ٷֺ�!\n");break;
		case 5: printf("ȱ��(!\n");break;
		case 6: printf("ȱ��)!\n");break;
		case 7: printf("ȱ�ٲ�����!\n");break;
        case 8: printf("����ȱ��NUM\n");break;
	    case 9: printf("ȱ��]\n");break;
        case 10: printf("���ļ�../Lexical_output.txtʧ��!\n");break;
		case 21: printf("���ű����!\n");break;
		case 22: printf("�����ظ�����!\n");break;
		case 23: printf("����δ����!\n");break;
		case 24: printf("�������õĴ�С�Ƿ�!\n");break;
		
	}
	fclose(fp);
	fclose(fout);
	return(es);
}

//program::={<declaration_list><statement_list>}
int program()
{ 
   int es=0,i;
   FIN;
   if(strcmp(token,"{"))//�ж��Ƿ�'{'
   {
	   es=1;
	   return(es);
   }
   FIN;
   es=declaration_list();
   if (es>0) return(es);
//    printf("\t\t\t���ű�\n");
//    printf("\t\t����\t\t��ַ\n");
//    for(i=0;i<vartablep;i++)
// 	   printf("\t\t%s\t\t%d\n",vartable[i].name,vartable[i].address);
   es=statement_list();
   if (es>0) return(es);
   printf("\t\t\t���ű�\n");
   printf("\t\t����\t\t��ַ\n");
   for(i=0;i<vartablep;i++)
	   printf("\t\t%s\t\t%d\n",vartable[i].name,vartable[i].address);
   if(strcmp(token,"}"))//�ж��Ƿ�'}'
   {
	   es=2;
	   return(es);
   }
   fprintf(fout,"        STOP\n");//����ָֹͣ��
   return(es);
}

//<declaration_list>::=
//<declaration_list><declaration_stat>|<declaration_stat>
//�ĳ�<declaration_list>::={<declaration_stat>}
int declaration_list()
{
	int es=0;
	while (strcmp(token,"int")==0)
	{
		es=declaration_stat();
		if (es>0) return(es);
	}
	return(es);
}

//<declaration_stat>��vartablep,datap,codep ->int ID��n��c@name-def��n,t,c;
//<declaration_stat>::=int ID;  -> ID{,ID}; -> ID([NUM]|��){,ID([NUM]|��)};
int declaration_stat()
{
	int es = 0,cnt = 1;
	do {
		FIN;
		if (strcmp(token, "ID"))
			return (es = 3); //���Ǳ�ʶ��
		char name[40];
		strcpy(name,token1);
		FIN;
		if(strcmp(token, "[") == 0) {
			FIN;
			if(strcmp(token, "NUM")) return (es = 8);
			cnt = atoi(token1);
			FIN;
			if(strcmp(token, "]")) return (es = 9);
			FIN;
		}
		es=name_def(name,cnt);//������ű�
		if (es>0) return(es);
	}while(strcmp(token, ",") == 0);

	if (strcmp(token, ";"))
		return (es = 4);
	FIN;
	return (es);
}

//<statement_list>::=<statement_list><statement>|<statement>
//�ĳ�<statement_list>::={<statement>}
int statement_list()
{
	int es=0;
	while (strcmp(token,"}"))
	{
		es=statement();
		if (es>0) return(es);
	}
	return(es);
}

//<statement>::= <if_stat>|<while_stat>|<for_stat>
//               |<compound_stat> |<expression_stat>

int statement()
{
	int es=0;
	if (es==0 && strcmp(token,"if")==0) es=if_stat();//<IF���>
	if (es==0 && strcmp(token,"while")==0) es=while_stat();//<while���>
	if (es==0 && strcmp(token,"for")==0) es=for_stat();//<for���>
    if (es==0 && strcmp(token, "do") == 0) es = do_while_stat();
	if (es==0 && strcmp(token,"read")==0) es=read_stat();//<read���>
	if (es==0 && strcmp(token,"int")==0) es=declaration_list();//<int���>
	if (es==0 && strcmp(token,"write")==0) es=write_stat();//<write���>
	if (es==0 && strcmp(token,"{")==0) es=compound_stat();//<�������>
	if (es==0 && (strcmp(token,"ID")==0||strcmp(token,"NUM")==0||strcmp(token,"(")==0)) es=expression_stat();//<���ʽ���>
	return(es);
}

//<IF_stat>::= if (<expr>) <statement > [else < statement >]
/*
if (<expression>)@BRF��label1 <statement > @BR��label2 @SETlabel��label1 
                  [ else < statement >] @SETlabel��label2

���ж������ŵĺ�������
  @BRF��label1 ����� BRF label1, 
  @BR��label2����� BR label2, 
  @SETlabel��label1�����ñ��label1 
  @SETlabel��label2�����ñ��label2
*/
int if_stat(){
	int es=0,label1,label2;  //if
	FIN;
	if (strcmp(token,"(")) 	return(es=5);  //��������
	FIN;
	es=expression();
	if (es>0) return(es);
	if (strcmp(token,")"))  return(es=6); //��������
	label1=labelp++;//��label1��ס����Ϊ��ʱҪת��ı��
	fprintf(fout,"        BRF LABEL%d\n",label1);//�����ת��ָ��
	FIN;
	es=statement(); 
	if (es>0) return(es);
	label2=labelp++;//��label2��סҪת��ı��
	fprintf(fout,"        BR LABEL%d\n",label2);//���������ת��ָ��
	fprintf(fout,"LABEL%d:\n",label1);//����label1��ס�ı��
	if (strcmp(token,"else")==0)//else���ִ���
	{  
		FIN;
		es=statement(); 
	    if (es>0) return(es);
	}
	fprintf(fout,"LABEL%d:\n",label2);//����label2��ס�ı��
	return(es);
}

// <do-while_stat>�� do ��{��<statement>��}��while (<expr >) ;
// <do-while_stat>�� do@SETlabel��label1 
// ��{��<statement>��}��while (<expr >)@BRF��label2@BR��label1@SETlabel��label2;
// 	 ���ж������ŵĺ�������
//   @BRF��label2 ����� BRF label2, 
//   @BR��label1����� BR label1, 
//   @SETlabel��label1�����ñ��label1 
//   @SETlabel��label2�����ñ��label2

int do_while_stat()
{
	int es = 0,label1,label2;
	label1=labelp++;//��label1��ס������ʱҪת��ı��
	fprintf(fout,"LABEL%d:\n",label1);
	FIN;
	es = statement();
	if (es) return es;
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
	label2=labelp++;//��label2��סҪת��ı��
	fprintf(fout,"        BRF LABEL%d\n",label2);//�����ת��ָ��
	fprintf(fout,"        BR LABEL%d\n",label1);//���������ת��ָ��
	fprintf(fout,"LABEL%d:\n",label2);
	return es;
}

//<while_stat>::= while (<expr >) < statement >
//<while_stat>::=while @SET��labellabel1(<expression>) @BRF��label2 
//				<statement >@BR��label1 @SETlabel��label2
//�����������£�
//@SETlabel��label1�����ñ��label1
//@BRF��label2 ����� BRF label2,
//@BR��label1����� BR label1,
//@SETlabel��label2�����ñ��label2
int while_stat()
{
	int es=0,label1,label2;  
	label1=labelp++;
	fprintf(fout,"LABEL%d:\n",label1);//����label1���
	FIN;
	if (strcmp(token,"("))  return(es=5);  //��������
	FIN;
	es=expression();
	if (es>0) return(es);
	if (strcmp(token,")"))  return(es=6); //��������
	label2=labelp++;
	fprintf(fout,"        BRF LABEL%d\n",label2);//�����ת��ָ��
	FIN;
	es=statement();
	if (es>0) return(es);
	fprintf(fout,"        BR LABEL%d\n",label1);//���������ת��ָ��
	fprintf(fout,"LABEL%d:\n",label2);//����label2���
	return(es);
}

//<for_stat>::= for(<expr>,<expr>,<expr>)<statement>
/*
<for_stat>::=for (<expression>@POP;
             @SETlabel��label1< expression >@BRF��label2@BR��label3;
             @SETlabel��label4 < expression >@POP@BR��label1) 
             @SETlabel��label3 <��� >@BR��label4@SETlabel��label2 
�������ͣ�
1.	@SETlabel��label1�����ñ��label1
2.	@BRF��label2 ����� BRF label2,
3.	@BR��label3����� BR label3,
4.	@SETlabel��label4�����ñ��label4
5.	@BR��label1����� BR label1,
6.	@SETlabel��label3�����ñ��label3
7.	@BR��label4����� BR label4,
8.	@SETlabel��label2�����ñ��label2 
*/
int for_stat()
{
	int es=0,label1,label2,label3,label4;  
	FIN;
	if (strcmp(token,"("))  return(es=5);  //��������
	FIN;
	es=expression();
	if (es>0) return(es);
	fprintf(fout,"        POP\n");
	if (strcmp(token,";")) 	return(es=4);  //�ٷֺ�
	label1=labelp++;
	fprintf(fout,"LABEL%d:\n",label1);//����label1���
	FIN;
	es=expression();
	if (es>0) return(es);
	label2=labelp++;
	fprintf(fout,"        BRF LABEL%d\n",label2);//���������ת��ָ��
	label3=labelp++;
	fprintf(fout,"        BR LABEL%d\n",label3);//���������ת��ָ��
	if (strcmp(token,";"))  return(es=4);  //�ٷֺ�
	label4=labelp++;
	fprintf(fout,"LABEL%d:\n",label4);//����label4���
	FIN;
	es=expression();
	if (es>0) return(es);
	fprintf(fout,"        POP\n");
	fprintf(fout,"        BR LABEL%d\n",label1);//���������ת��ָ��
	if (strcmp(token,")"))  return(es=6); //��������
	fprintf(fout,"LABEL%d:\n",label3);//����label3���
	FIN;
	es=statement();
	if (es>0) return(es);
	fprintf(fout,"        BR LABEL%d\n",label4);//���������ת��ָ��
	fprintf(fout,"LABEL%d:\n",label2);//����label2���
	return(es);
	
}

//<write_stat>::=write <expression>;
//<write_stat>::=write <expression>@OUT;
//�������ͣ�
//@ OUT����� OUT

int write_stat()
{
	int es=0;
	FIN;
	if(strcmp(token,"\"") == 0) {
		do {
			FIN;
		}while(strcmp(token,"\""));
		FIN;
	}else {
		es=expression();
		if (es>0)return(es);
	}
	if (strcmp(token,";"))  return(es=4);  //�ٷֺ�
	fprintf(fout,"        OUT\n");//���ָ��
	FIN;
	return(es);
}

//<read_stat>::=read ID;
//<read_stat>::=read ID��n LOOK��n��d @IN@STI��d@POP;
//�������ͣ�
//@LOOK��n��d:����ű�n������������ַd; û�У�����û����
//@IN�����IN
//@STI��d�����ָ�����STI  d


int read_stat()
{
	int es=0,address;
	FIN;
	if (strcmp(token,"ID"))  return(es=3);  //�ٱ�ʶ��
	es=lookup(token1,&address);
	if (es>0) return(es);
	fprintf(fout,"        IN   \n");//����ָ��
	fprintf(fout,"        STI   %d\n",address);//ָ��
	fprintf(fout,"        POP\n");
	FIN;
	if (strcmp(token,";"))  return(es=4);  //�ٷֺ�
	FIN;
	return(es);
}

//<compound_stat>::={<statement_list>} 
int compound_stat(){   //������亯��
	int es=0;
	FIN;
	es=statement_list();
	return(es);
}

//<expression_stat>::=<expression>@POP;|;
int expression_stat()
{
	int es=0;
	if (strcmp(token,";")==0) 
	{
		FIN;
		return(es);
	}
	es=expression();
	if (es>0) return(es);
	fprintf(fout,"        POP\n");
	if (strcmp(token,";")==0) 
	{
		FIN;
		return(es);
	} else
	{
		es=4;
		return(es);//�ٷֺ�
	}
}

//<expression>::=ID��n@LOOK��n��d@ASSIGN=<bool_expr>@STO��d |<bool_expr>
// <expression>::= ID[NUM]��n��c@LOOK��n��c��d@ASSIGN=<bool_expr>@STO��d
int expression()
{
	int es=0,fileadd;
	char token2[20],token3[40];
	if (strcmp(token,"ID")==0)
	{   
		fileadd=ftell(fp);   //@ASSIGN��ס��ǰ�ļ�λ��
		fscanf(fp,"%s %s\n", &token2,&token3);
		printf("%s %s\n",token2,token3);
		if (strcmp(token2,"=")==0)  //'='
		{
			int address;
			es=lookup(token1,&address);
			if (es>0) return(es);
			FIN;
			es=bool_expr();
			if (es>0) return(es);
			fprintf(fout,"        STO %d\n",address);

		} else 
		{
			fseek(fp,fileadd,0); //����'='���ļ�ָ��ص�'='ǰ�ı�ʶ��
			printf("%s %s\n",token,token1);
			es=bool_expr();
			if (es>0) return(es);
		}
	} else es=bool_expr();
	
	return(es);
}


//<bool_expr>::=<additive_expr>
//           |< additive_expr >(>|<|>=|<=|==|!=)< additive_expr >
/*
<bool_expr>::=<additive_expr>
|< additive_expr >><additive_expr>@GT
|< additive_expr ><<additive_expr>@LES
|< additive_expr >>=<additive_expr >@GE
|< additive_expr ><=< additive_expr >@LE
|< additive_expr >==< additive_expr >@EQ
|< additive_expr >!=< additive_expr >@NOTEQ
*/
int bool_expr()
{
	int es=0;
	es=additive_expr();
	if(es>0) return(es);
	if ( strcmp(token,">")==0 || strcmp(token,">=")==0
	   ||strcmp(token,"<")==0 || strcmp(token,"<=")==0
	   ||strcmp(token,"==")==0|| strcmp(token,"!=")==0)
	{
		char token2[20];
		strcpy(token2,token);//���������
		FIN;
		es=additive_expr();
		if(es>0) return(es);
		if ( strcmp(token2,">")==0 ) fprintf(fout,"        GT\n");
		if ( strcmp(token2,">=")==0 ) fprintf(fout,"        GE\n");
		if ( strcmp(token2,"<")==0 ) fprintf(fout,"        LES\n");
		if ( strcmp(token2,"<=")==0 ) fprintf(fout,"        LE\n");
		if ( strcmp(token2,"==")==0 ) fprintf(fout,"        EQ\n");
		if ( strcmp(token2,"!=")==0 ) fprintf(fout,"        NOTEQ\n");
	}
	return(es);
}

//<additive_expr>::=<term>{(+|-)< term >} 
//< additive_expr>::=<term>{(+< term >@ADD |-<��>@SUB)}

int additive_expr()
{
	int es=0;
	es=term();
	if(es>0) return(es);
	while (strcmp(token,"+")==0 || strcmp(token,"-")==0)
	{
		char token2[20];
		strcpy(token2,token);
		FIN;
		es=term();
		if(es>0) return(es);
		if ( strcmp(token2,"+")==0 ) fprintf(fout,"        ADD\n");
		if ( strcmp(token2,"-")==0 ) fprintf(fout,"        SUB\n");
	}
	return(es);
}

//< term >::=<factor>{(*| /|%)< factor >} 
//< term >::=<factor>{(*< factor >@MULT | /< factor >@DIV)|%< factor >@MOD)} 

int term()
{
	int es=0;
	es=factor();
	if(es>0) return(es);
	while (strcmp(token,"*")==0 || strcmp(token,"/")==0 || strcmp(token,"%")==0)
	{
		char token2[20];
		strcpy(token2,token);
		FIN;
		es=factor();
		if(es>0) return(es);
		if ( strcmp(token2,"*")==0 ) fprintf(fout,"        MULT\n");
		if ( strcmp(token2,"/")==0 ) fprintf(fout,"        DIV\n");
		if ( strcmp(token2,"%")== 0) fprintf(fout,"        MOD\n");
	}
	return(es);
}

//< factor >::=(<additive_expr>)| ID|NUM
//< factor >::=(< expression >)| ID��n@LOOK��n��d@LOAD��d |NUM��i@LOADI��i

int factor()
{
	int es=0;
	
	if (strcmp(token,"(")==0)  
	{
		FIN;
		es=expression();
		if (es>0) return(es);
		if (strcmp(token,")"))  return(es=6); //��������
		FIN;
	} else
	{
		
		if (strcmp(token,"ID")==0)
		{
			int address;
			es=lookup(token1,&address);//����ű���ȡ������ַ
			if (es>0) return(es);//����û����
			fprintf(fout,"        LOAD %d\n",address);
			FIN;
			return(es);
		} 
		if (strcmp(token,"NUM")==0)
		{
			fprintf(fout,"        LOADI %s\n",token1);
			FIN;
			return(es);
		}else
		{
			es=7;//ȱ�ٲ�����
			return(es);
		}
	}
	return(es);
}