#include<iostream>
#include<pthread.h>
#include<stdlib.h>
using namespace std;

#define MAX 5

void *RoutineStart(void *a)
{
        cout<<"This is Thread "<< (long)a<<endl;

        pthread_exit(NULL);
}

int main()
{
    //create array of pthread objects
    pthread_t MyThread[MAX];

    int check;
    long id;

        for(id = 0; id < MAX; id++)
        {
            //create Threads
                check =  pthread_create(&MyThread[id], NULL, &RoutineStart, (void*)id);

                //check whether the thread is created or not
                if(check != 0)
                {
                        cout<<endl<<"Error has occured to create the thread."<<endl;
                        exit(0);
                }
        }

        cout<<endl<<"Waiting for threads to finish..."<<endl;

        for(id = 0; id < MAX; id++)
        {
            check = pthread_join(MyThread[id],NULL);
             if(check != 0)
                {
                        cout<<endl<<"Error: pthread_join() failed"<<endl;
                        exit(0);
                }

            cout<<endl<<"Thread joined is :- Thread "<<id<<endl;

        }

        cout<<endl<<" FINISH MAIN"<<endl;
}
