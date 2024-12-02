#include "lexical.h"

int main(int argc,char **argv)
{
    char ch,*file,line[256];
    int status;
    if (argc < 2)                                                         //checking if any arguments are passed
    {
        printf("Please enter the file\n");
        return FAILURE;
    }
   /* if((strstr(argv[1], ".c"))!=NULL)                                  //checking if the entered file is .c file
        file = argv[1];                     
    else
    {
        printf("Error: Please a pass a .c file\n ");
        return FAILURE;
    }*/
    file = argv[1]; 
    FILE *fptr=fopen(file,"r");                                             //opening the file in read mode
    if(fptr==NULL)
    {
        printf("Unable to open the file\n");
        return FAILURE;                                                    //returning error if unable to open file
    }
    else
    {
        printf("Open    : %s : Success\n",file);
        printf("Parsing : %s : Started\n",file);
        printf("\n");
    }
    fseek(fptr , 0 ,SEEK_END);                                           //making the file pointer to pointer to point to the end
    if(ftell(fptr)==0)
    {
        printf("File is empty\n");                                  //checking if the file is empty
        return FAILURE;
    }
    fseek(fptr , 0 ,SEEK_SET);                               //setting the file pointer to start 
    while((ch=fgetc(fptr))!=EOF)
    {    
        parsing(ch);                                         //passing character by character to parsing function
    }
    fseek(fptr , 0 ,SEEK_SET);                               //setting the file pointer to start 
    if(line)
    {
        while((fgets(line,sizeof(line),fptr)))
        {    
            status=error(line);                                 //passing line by line
        }
    }
    if(ch==EOF)                                                //checking if the file pointer has reched End of File
    {
        printf("\n");
        printf("Parsing : %s : Completed \n", file);
        if(status==FAILURE)                                     //checking if any error is present or not
            printf("Error present\n");
        else
            printf("No Error\n");
    }      
    fclose(fptr);                                                      //closing file pointer
}