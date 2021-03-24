#include<stdio.h>
#include<string.h>
#include <math.h>

typedef struct String
{
    char s[1000];

}string;

char txt[1000];

char* intToString(int val);

int main()
{
    int i,j,c,headerLen,nLine=0;
    char text[10000],header[100];
    string fullpath,path,fileName;
    FILE *file;

    //input
    int filesNumber;
    char Path[100],filename[50],extension[10],head[100];

    printf("----------------Header Adder---------------\n\n");
    printf("path : ");
    scanf("%[^\n]",Path);
    strcat(Path,"\\");
    fflush(stdin);
    printf("files name (without index): ");
    scanf("%[^\n]",filename);
    fflush(stdin);
    printf("file extension : ");
    scanf("%[^\n]",extension);
    fflush(stdin);
    printf("files number : ");
    scanf("%d",&filesNumber);
    fflush(stdin);
    printf("header : ");
    scanf("%[^\n]",head);

    //make a new line if the user enter '\n' as input
    for(i=0; i<strlen(head)-1;i++)
    {
        if(head[i] == '\\' && head[i+1] == 'n')
        {
            for(j=i; j<strlen(head)-1-nLine; j++)
                head[j] = head[j+1];

            head[i] = '\n'; nLine++;
        }
    }
    
    head[strlen(head)-nLine] = '\0';
    
    //printf("%s",header);

    for(i=0; i<filesNumber; i++)
    {
        //Path folder
        strcpy(path.s,Path);
        //File name without index (the files should be in the same name)
        strcpy(fileName.s,filename);
        strcpy(fullpath.s,path.s);
        //cancatnation of the index after convert it to string
        strcat(fileName.s,intToString(i+1));
        //file extension
        strcat(fileName.s,extension);
        //the full path
        strcat(fullpath.s,fileName.s);

        //Add whatever you want in the text ex : "//Name : \n//Group : \n\n"
        strcpy(header,head);
        strcpy(text,header);
        headerLen = strlen(header);

        //Read the file and put it in a variable
        file = fopen(fullpath.s,"r");
            if(file == NULL)
            {
                printf("file not found!\nPath : %s",fullpath);
                return 0;
            }
            
            for(j=headerLen;1;j++) 
            {
                c = fgetc(file);
                if(feof(file))
                    break;
                text[j] = c;
            }
        fclose(file);
        //the end of the text
        text[j] = '\0';

        //Write the new text in the file
        file = fopen(fullpath.s,"w");
            if(file == NULL)
            {
                printf("file not found!\nPath : %s",fullpath);
                printf("\nNot copied");
                return 0;
            }

        //fprintf(file,text);
        fputs(text,file);
        
        fclose(file);
    }
   
    return 0; 
}

//convert number to char
char* intToString(int val)
{
    int i,x=0,p=0,c=val;

    //get the length of the number
    while((val/(int)pow(10,p)) != 0)
        p++;p--;

    //divide each individual number and convert it to it's value in character
    for(i=(int)pow(10,p); i>0; i/=10)
    {
        //add the character to a string (char array)
        txt[x] = (c/i)+'0';
        c = c-(c/i * i);
        x++;
    }
    
    txt[x] = '\0';

    return txt;
}