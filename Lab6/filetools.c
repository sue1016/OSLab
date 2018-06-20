#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<syslog.h>
#include<fcntl.h>
int isOver = 0;
void showMenu();
void createFile();
void writeFile();
void readFile();
void changeMode();
void viewMode();
int main()
{
    
    while(!isOver)
    {
        showMenu();
    }


    printf("Bye\n");
    return 0;
}
void showMenu()
{
    int choice;
    printf("------filetools-menu-------\n");
    printf("-0.exit---------------------\n");
    printf("-1.create new file----------\n");
    printf("-2.write file---------------\n");
    printf("-3.read file----------------\n");
    printf("-4.change mode--------------\n");
    printf("-5.view mode and exit----------\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 0:  
            isOver = 1;
            break;
        case 1:  
            createFile();
            break;
        case 2:   
            writeFile();
            break;
        case 3: 
            readFile();
            break;
        case 4:  
            changeMode();  
            break;
        case 5:  
            viewMode();
            isOver = 1;
            break;
        default:  
            printf("选择无效，请重新选择!\n");
            break;
    }
    sleep(1);
}


void createFile()
{
    char filename[30];
    printf("input filename:\n");
    scanf("%s",filename);
    if( open(filename,O_RDONLY) < 0 )
    {
        //文件不存在
        close(open(filename,O_CREAT));  //创建文件
        printf("create successfully\n");
    }
    else
    {
        printf("Oops,there have exited this file\n");
    }
    
}
void writeFile()
{
    printf("writefile\n");
    char filename[30];
    printf("input filename:\n");
    scanf("%s",filename);
    if( open(filename,O_RDONLY) < 0 )
    {
        //文件不存在
        printf("no such file");
    }
    else
    {
        printf("what to write in:\n");
        int id = open(filename,O_RDWR|O_APPEND); //打开读写，并在文件末尾追加内容
        int size=0;
        char buf[100];
        scanf("%s",buf);
        if((size=write(id,buf,strlen(buf)))<0)  //参数：制定文件、内容、长度
        {
            printf("error when writing\n");
        }
        else 
        {
            printf("write successfully\n");
        }
        close(id);
    } 
}

void readFile()
{
    char filename[30];
    printf("input filename\n");
    scanf("%s",filename);
    if( open(filename,O_RDONLY) < 0 )
    {
        //文件不存在
        printf("no such file");
    }
    else
    {
        int id = open(filename,O_RDONLY); //只读打开文件
        lseek(id,0,SEEK_SET); //定位文件指针在头部，SEEK_SET-文件偏移量被设置为0
        int size=0;
        char buf[1000];
        if((size=read(id,buf,1000))<0)  //参数：制定文件、内容、长度
        {
            printf("error when reading\n");
        }
        else 
        {
            printf("%s\n",buf);
            printf("reading successfully\n");
        }
        close(id);
    } 
    
}
void changeMode()
{
    char filename[30];
    printf("input filename\n");
    scanf("%s",filename);
     if( open(filename,O_RDONLY) < 0 )
    {
        //文件不存在
        printf("no such file");
    }
    else
    {
        int modeChoice;
        mode_t mode = S_IWUSR;
        printf("0.  rwx0700\n1.  r0400\n2.  w0200\n3.  x0100\n");
        scanf("%d",&modeChoice);
        switch(modeChoice)
        {
            case 0:chmod(filename,S_IRWXU);break;
            case 1:chmod(filename,S_IRUSR);break;
            case 2:chmod(filename,S_IWUSR);break;
            case 3:chmod(filename,S_IXUSR);break;
            default:printf("invalid choice!\n");break;
        }
        
    } 

}
void viewMode()
{
    char filename[30];
    printf("input filename\n");
    scanf("%s",filename);
    if( open(filename,O_RDONLY) < 0 )
    {
        //文件不存在
        printf("no such file");
    }
    else
    {
        char* path="/bin/ls";
        char* argv[4]={"ls","-l",filename,NULL};
        execv(path,argv);
    }
 
}