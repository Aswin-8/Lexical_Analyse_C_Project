#include "lexical.h"
static char* preprocessor[]={"#define","#undef","#include","#ifdef","#ifndef","#if","#else","#elif","#endif"};
static char* keywords[] = {"const", "volatile", "extern", "auto", "register",
   						   "static", "signed", "unsigned", "short", "long", 
						   "double", "char", "int", "float", "struct", 
						   "union", "enum", "void", "typedef", "goto","return", "continue", "break", 
							   "if", "else", "for", "while", "do", 
							   "switch", "case", "default","sizeof"
						  };
static char* identifiers[] = {"main","printf" ,"scanf"};

static char operators[] = {'/', '+', '*', '-', '%', '=', '<', '>', '~', '&', ',', '!', '^', '|','(',')','{','}','[',']',':',';'};

static char* headerfile[]={"<assert.h>","<ctype.h>","<locale.h>","<math.h>","<setjmp.h>","<signal.h>","<stdarg.h>","<stdio.h>",
                                 "<stdlib.h>","<string.h>","<time.h>" };


int i,ind,operatorflag=0,keywordflag=0,literalflag=0,identifierflag=0,l=0,spaceflag=1,preprocessorflag=0,opind,preind,headerflag=0,headerind;
void parsing (char ch)
{
    static char str[15];
    static int index=0,flag=0,braceflag=0,changeflag=0,curlyflag=0;
    l=strlen(str);                                                   //getting the string length
    
    for( i=0;i<22;i++)
    {
        if(operators[i]==ch)                           //checking if the given character is a operator
        { 
            operatorflag=1;                            //setting operator flag
            opind=i;                                   //storing the index value in opind
            break;
        }
    }
    
    if(isalnum(ch) || ch=='"' || ch=='\\'   || ch=='\n' || ch=='#' || ch=='<' || ch=='>'  || ch=='.' ||ch =='%'|| ch==' '|| ch=='{')
    {
        if(ch=='{')                                   //checking if the character is open curly braces
        {
            curlyflag=1;    
        }
        if(ch=='}')                                    //checking if the character is open curly braces
        {
            curlyflag=0;    
        }
        if(ch=='<' && curlyflag==0)                    //checking if it is a angled bracket and not a operator
        {
            braceflag=1;   
        }
        if(braceflag)
            operatorflag=0;
        if(ch=='>' && curlyflag==0)                    //checking if it is a angled bracket and not a operator
            braceflag=0;
        if(ch=='"')                                    //checking if it is a double inverted comma
        {
            operatorflag=0;
            flag=!flag;                                 //toggling flag bit
        }
        if(flag)                         
            str[index++]=ch;                            //if the flag is set including all characters
        else if( ch!=' ' && ch!='\t' )
            str[index++]=ch;                            //including alla characters except tabspace and space
        if(ch=='\n' )
            str[index]='\0';                            //if character is a new line character making the index character as null character
        if((ch=='<' || ch=='>') && curlyflag && braceflag==0)
        {
            str[index--]='\0';                              //checking if it is a operator and not a angled braces
        }
    }

    if(index>1 && !isalnum(ch) && ch!='\\' && flag==0 && ch!='.' && ch!='#'  && braceflag==0 ||(operatorflag && flag!=1 ))
    {       
        str[index]='\0';                                      //adding null character at the end to make a string
        if(str[l-1]==' ' )
            {
                str[l-1]='\0';                             //checking if the last character is space and removing the space
                l--;
            }
        if(str[0]=='\n' || str[0]==' '|| str[0]=='\t' )         //checking if the first character is a null,space or tab space
        {
            for(i=0;i<l;i++)
            {
                str[i]=str[i+1];                                //removing all these characters
            }
            l--;
        }
        for(i=0;i<l;i++)
            {
                if(str[i]=='\n' )
                {
                    str[i]='\0';                         //checking if new line character is present at any part of string if so removing it
                    l--;
                    i--;
                }
            }
        for(i=0;i<32;i++)
        {
            if(!strcmp(str,keywords[i]))               //checking if the formed sting is a keyword
            {
                keywordflag=1;                         //if so setting keyword flag
                ind=i;
                break;
            }
            else if(i<9 && !strncmp(str,preprocessor[i],l))                 //checking if the formed sting is a preprocessor
            {
                preprocessorflag=1;                                         //if so setting preprocessor flag
                preind=i;
                break;
            }
            else if(i<11 && !strncmp(str,headerfile[i],l))                //checking if the formed sting is a header file
            {
                headerflag=1;                                             //if so setting header flag
                headerind=i;
                break;
            }
            else if(i<3 && !strcmp(str,identifiers[i]))                   //checking if the formed sting is a identifier
            {
                identifierflag=1;                                         //if so setting identifier flag
                ind=i;
                literalflag=0;
                break;
            }
            else 
            {
                if(l!=0 )                                                 //ensuring that it is not a null character
                    literalflag=1;                                        //setting literal flag
            }
        }
        index=0;
        if(keywordflag)
        {  
            printf("keyword         : %s\n",keywords[ind]);                //printing keywords if keyword flag is set
            keywordflag=0;
        }
        else if(preprocessorflag && operatorflag==0 &&l)
        {
            printf("preprocessor    : %s\n",preprocessor[preind]);           //printing preprocessor if preprocessor flag is set
            preprocessorflag=0;
        }
        else if(headerflag)
        {
            printf("headerfile      : %s\n",headerfile[headerind]);           //printing header file if header flag is set
            headerflag=0;
        }
        else if(identifierflag)
        {
            printf("identifier      : %s\n",identifiers[ind]);                 //printing identifier if identifier flag is set
            identifierflag=0;
        }    
        else if(literalflag   && strcmp(str,"\n") && identifierflag==0  && strcmp(str,"\0") )
        {
            printf("literal         : %s\n",str);                               //printing literals if literal flag is set
            literalflag=0;
            preprocessorflag=0;
        }
        if(operatorflag && flag!=1)
        {
            printf("Operator        : %c\n",operators[opind]);                    //printing operator if operator flag is set
            operatorflag=0;
            literalflag=0; 
            preprocessorflag=0; 
        }     
    }    
}