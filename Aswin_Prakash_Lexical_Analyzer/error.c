#include "lexical.h"

static char brackets[] = {'(',')','{','}','[',']','<','>'};

static char operators[] = {'/', '+', '*', '-', '%', '=', '<', '>', '~', '&', ',', '!', '^', '|','(',')','{','}','[',']',':',';'};


int error (char *line)
{
    static char ch;
    static int squareflag=0,curlyflag=0,roundflag=0,invertflag=0,colonflag=0,start=0;
    int i,l;
    l=strlen(line);
    for(i=0;i<l-2;i++)
    {
        ch=line[i];
        if(ch=='{' )                          //checking if the character is a opening curly bracket
        {
            start=!start;
        }
        else if (ch=='}' )                    //checking if the character is a closing curly bracket
        {
            start=!start;
        }
        if(ch=='{' || ch =='}')  
            curlyflag=!curlyflag;
        if(ch=='(' || ch ==')')  
            roundflag=!roundflag;
        if(ch=='{' || ch =='}')                      //toggling flags depending up on the opening and closing of brackets
            curlyflag=!curlyflag;
        if(ch=='[' || ch ==']')  
            squareflag=!squareflag;
        if(ch=='"')
            invertflag=!invertflag;
    }
    if(start && ch!='{' ) 
    {
        if(line[l-3]!=';')                            //checking the presence of semicolon at end of line after the beggining of open curly brackets
            colonflag=1;
    }
    if(roundflag || curlyflag || squareflag  || invertflag || colonflag) //checking if any flag bits set indicating the error
        return FAILURE;
    return SUCCESS;
}
