#include<fcntl.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

void copye(int old,int newe)
{
    int counter = 0;
    int success = 0;
    char buffer[280];

    while((counter = read(old,buffer,sizeof(buffer)))>0)
    {
        success = write(newe,buffer,counter);
        cout<<" Successfull writes = "<<success<<"  "<<" Read from buffer "<<counter<<endl;
    }

    cout<<endl<<" copy complete "<<endl<<endl;
}

void display(int newe)
{
    int counter = 0;
    char buffer[1];

    while((counter = read(newe,buffer,1))>0)
    {
        cout<<buffer;
    }
    cout<<endl;
}

int main(int argv,char* argvs[])
{
    if(argv <3 || argv >3)
    {
        cerr<<endl<<" you have to enter two file_names"<<endl;
        exit(1);
    }

    int fold = open(argvs[1],0);

    if(fold == -1)
    {
        cerr<<" Unable to open the file"<<argvs[1]<<endl;
        exit(1);
    }


    int fnew = creat(argvs[2],00700);

     if(fnew == -1)
    {
        cerr<<" Unable to create the file  "<<argvs[2]<<endl;;
        exit(1);
    }

    copye(fold,fnew);
    close(fold);
    close(fnew);

    fnew = open(argvs[2],0);
    cout<<" contents of file "<<argvs[2]<<" is "<<endl<<endl;
     display(fnew);

    close(fnew);
}
