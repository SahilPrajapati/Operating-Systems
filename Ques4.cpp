#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<sys/wait.h>
using namespace std;

int main(void)
{
    char option;

    int chp_pid = 0,pp_pid = 0;

    cout<<endl<<"a parent & child same process"<<endl;
    cout<<endl<<"b parent & child different process"<<endl;
    cout<<endl<<"c parent & child different program"<<endl;
    cout<<endl<<"d parent & child different program with wait()"<<endl;
    cin>>option;
    int pid = fork();

            if(pid < 0 )
            {
                cout<<"syserror";
            }
            else
            {
                switch(option)
                {
                    case 'a' :
                    {
                        pp_pid = getppid();
                        chp_pid = getpid();

                        cout<<" my Parent pid is : "<<pp_pid<<endl;
                        cout<<"my  own pid is : "<<chp_pid<<endl;
                    }
                    break;
                    case 'b':
                    {

                        if(pid == 0)
                        {
                            cout<<endl<<" In child process"<<endl;
                            cout<<endl<<"my Parent pid is "<<getppid()<<endl;
                            cout<<" my own pid is : "<<getpid()<<endl;
                        }
                        else
                        {
                            cout<<endl<<" In parent process"<<endl;
                            cout<<"my parent pid is : "<<getppid()<<endl<<" my own pid is :"<<getpid()<<endl;
                        }
                    }
                    break;

                    case 'c':
                    {
                        if(pid == 0)
                        {
                            cout<<endl<<"In Child Process"<<endl<<" own pid is : "<<getpid()<<endl<<" parent pid is :"<<getppid()<<endl;
                            execlp("/bin/ls","ls",NULL);
                            cout<<endl;
                        }
                        else
                        {
                            cout<<endl<<"In Parent process"<<endl<<" own pid is : "<<getpid()<<endl<< " parent pid is :"<<getppid()<<endl;
                        }

                    }

                    break;
                    case 'd':
                    {
                        if(pid == 0)
                        {
                            cout<<"IN Child Process  "<<endl<<" own pid is : "<<getpid()<<endl<<"  parent pid is : "<<getppid()<<endl;
                            execlp("/bin/ls","ls",NULL);
                            cout<<endl;
                        }
                        else
                        {
                            int process = 0;
                            process = wait(NULL);
                            cout<<endl<<"In Parent Process "<<endl<<" own pid is "<<getpid()<<endl<<" child process terminated is :"<<process<<endl;
                       }

                    }

                    break;
                    default:
                            cout<<endl<<"wrong option select"<<endl;
            }
        }

}
