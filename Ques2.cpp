#include<sys/stat.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

void display_permission(struct stat buffer)
{
    cout<<"Owner access permissions is :  ";

    if(buffer.st_mode & S_IREAD)
    cout<<"r";
    else
    cout<<"-";
    if(buffer.st_mode & S_IWRITE)
    cout<<"w";
    else
    cout<<"-";
    if(buffer.st_mode & S_IEXEC)
    cout<<"x";
    else
    cout<<"-";
}

int main(int argv,char* argvs[])
{
    if(argv == 1)
    {
        cout<<" you have to enter atleast 1 file_name"<<endl;
        return 1;
    }

    struct stat buffer;

    for(int i = 1;i< argv;i++)
    {
        cout<<endl<<" For file "<<argvs[i]<<endl;
        if(stat(argvs[1],&buffer )== 0)
        {
            display_permission(buffer);
            cout<<endl<<"File's last access time is :  "<<ctime(&buffer.st_atim.tv_sec) <<endl;
        }
        else
        {
            cout<<endl<<"stat function do not work properly"<<endl;
            exit(1);
        }
    }
}
