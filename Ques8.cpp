#include<iostream>
using namespace std;

struct Process
{
    char P_name;
    int Burst_Time;
    int Arrival_Time;
    int Waiting_Time;
    int TurnAround_Time;
    int Priority;
    bool check;
    int Remaining_Time;
};

void get_details(struct Process a[],int total)
{
    cout<<endl<<" Enter details of each process"<<endl;
    for(int i=0;i<total;i++)
    {
        cout<<endl<<" Enter details for "<<i+1<<" Process "<<endl;
        cout<<endl<<" Enter name of Process"<<endl;
        cin>>a[i].P_name;

        cout<<endl<<" Enter Burst Time "<<endl;
        cin>>a[i].Burst_Time;
        a[i].Remaining_Time = a[i].Burst_Time;

        cout<<endl<<" Enter Priority "<<endl;
        cin>>a[i].Priority;

        cout<<endl<<" Enter Arrival Time "<<endl;
        cin>>a[i].Arrival_Time;

        a[i].TurnAround_Time = a[i].Waiting_Time = 0;

        a[i].check = false;

    }
}

void display(struct Process *a,int total)
{
    cout<<endl<<"Process Name"<<"  Burst Time"<<"  Arrival Time"<<"  Priority"<<"  TurnAround Time"<<"  Waiting Time"<<endl<<endl;
    for(int i=0;i<total;i++)
    {
      cout<<a[i].P_name<<"\t          "<<a[i].Burst_Time<<"\t    "<<a[i].Arrival_Time<<"\t\t "<<a[i].Priority<<"\t    "<<a[i].TurnAround_Time<<"\t\t\t"<<a[i].Waiting_Time<<endl;
    }

}

void swap_struct(struct Process *temp,struct Process *temp1)
{
    char P_name;
    int Burst_Time,Arrival_Time,Waiting_Time,TurnAround_Time,Priority,Remaining_Time;
    bool check;

      P_name = temp->P_name ;
      Burst_Time = temp->Burst_Time;
      Arrival_Time = temp->Arrival_Time;
      Waiting_Time = temp->Waiting_Time;
     TurnAround_Time = temp->TurnAround_Time;
     Priority = temp->Priority;
     check = temp->check;
     Remaining_Time = temp->Remaining_Time;

     temp->P_name =  temp1->P_name;
     temp->Burst_Time = temp1->Burst_Time;
     temp->Arrival_Time  = temp1->Arrival_Time;
     temp->Waiting_Time = temp1->Waiting_Time;
     temp->TurnAround_Time = temp1->TurnAround_Time;
     temp->Priority = temp1->Priority;
     temp->check = temp1->check;
     temp->Remaining_Time = temp1->Remaining_Time;

     temp1->P_name = P_name;
     temp1->Burst_Time = Burst_Time;
     temp1->Arrival_Time  = Arrival_Time;
     temp1->Waiting_Time = Waiting_Time;
     temp1->TurnAround_Time = TurnAround_Time;
     temp1->Priority = Priority;
     temp1->check = check;
     temp1->Remaining_Time = Remaining_Time;

}

void sorted_burst_time(struct Process a[],int total)
{
    for(int i = 0;i<total;i++)
    {
        for(int j = i+1;j<total;j++)
        {
            if(a[i].Burst_Time>a[j].Burst_Time)
            {
                swap_struct(&a[i],&a[j]);
            }
        }
    }
    return;
}

void FIFS(struct Process a[],int total,float *avg_ttime,float *avg_wtime)
{
    int tb_time = 0;
    for(int i = 0;i<total;i++)
    {
                tb_time += a[i].Burst_Time;
                a[i].TurnAround_Time =  tb_time - a[i].Arrival_Time;
                a[i].Waiting_Time = a[i].TurnAround_Time - a[i].Burst_Time;

        *avg_ttime = *avg_ttime +  a[i].TurnAround_Time;
        *avg_wtime = *avg_wtime + a[i].Waiting_Time;
    }

    return;
}

void SJF_NP(struct Process a[],int total,float *avg_ttime,float *avg_wtime)
{
    int range = 0,select = 0,tb_time = 0,executed = 0;
    Process store[total];

    while(executed != total)
    {
        int eligible = 0;

        for(int i = 0;i<total;i++)
        {
            if(a[i].Arrival_Time <= range && a[i].check == false)
            store[eligible++] = a[i];
        }

        sorted_burst_time(store,eligible);
        range += store[0].Burst_Time;

        for(int i = 0;i<total;i++)
        {
            if(a[i].P_name == store[0].P_name)
                select = i;
        }

        a[select].check = true;
        executed++;
        tb_time += a[select].Burst_Time;
        a[select].TurnAround_Time =  tb_time - a[select].Arrival_Time;
        a[select].Waiting_Time = a[select].TurnAround_Time - a[select].Burst_Time;

        *avg_ttime = *avg_ttime +  a[select].TurnAround_Time;
        *avg_wtime = *avg_wtime +  a[select].Waiting_Time;

    }
    return;
}

void sorted_remaining_time(struct Process a[],int total)
{
    for(int i = 0;i<total;i++)
    {
        for(int j = i+1;j<total;j++)
        {
            if(a[i].Remaining_Time>a[j].Remaining_Time)
            {
                swap_struct(&a[i],&a[j]);
            }
        }
    }
    return;
}

void SRTF(struct Process a[],int total,float *avg_ttime,float *avg_wtime)
{
    int range = 0,select = 0,tb_time = 0,executed = 0;
    Process store[total];

    while(executed != total)
    {
        int eligible = 0;

        for(int i = 0;i<total;i++)
        {
            if(a[i].Arrival_Time <= range && a[i].check == false)
            store[eligible++] = a[i];
        }

        sorted_remaining_time(store,eligible);
        range += 1;

        for(int i = 0;i<total;i++)
        {
            if(a[i].P_name == store[0].P_name)
                select = i;
        }

        a[select].Remaining_Time = a[select].Remaining_Time - 1;
        tb_time += 1;

        if(a[select].Remaining_Time == 0)
       {
            a[select].check = true;
            executed++;

            a[select].TurnAround_Time =  tb_time - a[select].Arrival_Time;
            a[select].Waiting_Time = a[select].TurnAround_Time - a[select].Burst_Time;

            *avg_ttime = *avg_ttime +  a[select].TurnAround_Time;
            *avg_wtime = *avg_wtime +  a[select].Waiting_Time;
        }
    }

    return;
}

void sorted_priority(struct Process a[],int total)
{
    for(int i = 0;i<total;i++)
    {
        for(int j = i+1;j<total;j++)
        {
            if(a[i].Priority<a[j].Priority)
            {
                swap_struct(&a[i],&a[j]);
            }
        }
    }
    return;
}

void NP_Priority(struct Process a[],int total,float *avg_ttime,float *avg_wtime)
{
    int range = 0,select = 0,tb_time = 0,executed = 0;
    Process store[total];

    while(executed != total)
    {
        int eligible = 0;

        for(int i = 0;i<total;i++)
        {
            if(a[i].Arrival_Time <= range && a[i].check == false)
            store[eligible++] = a[i];
        }

        sorted_priority(store,eligible);
        range += store[0].Burst_Time;

        for(int i = 0;i<total;i++)
        {
            if(a[i].P_name == store[0].P_name)
                select = i;
        }

        a[select].check = true;
        executed++;

        tb_time += a[select].Burst_Time;
        a[select].TurnAround_Time =  tb_time - a[select].Arrival_Time;
        a[select].Waiting_Time = a[select].TurnAround_Time - a[select].Burst_Time;

        *avg_ttime = *avg_ttime +  a[select].TurnAround_Time;
        *avg_wtime = *avg_wtime +  a[select].Waiting_Time;

    }
    return;
}

void P_Priority(struct Process a[],int total,float *avg_ttime,float *avg_wtime)
{
    int range = 0,select = 0,tb_time = 0,executed = 0;
    Process store[total];

    while(executed != total)
    {
        int eligible = 0;

        for(int i = 0;i<total;i++)
        {
            if(a[i].Arrival_Time <= range && a[i].check == false)
            store[eligible++] = a[i];
        }

        sorted_priority(store,eligible);
        range += 1;

        for(int i = 0;i<total;i++)
        {
            if(a[i].P_name == store[0].P_name)
                select = i;
        }

        a[select].Remaining_Time = a[select].Remaining_Time - 1;
        tb_time += 1;

        if(a[select].Remaining_Time == 0)
       {
            a[select].check = true;
            executed++;

            a[select].TurnAround_Time =  tb_time - a[select].Arrival_Time;
            a[select].Waiting_Time = a[select].TurnAround_Time - a[select].Burst_Time;

            *avg_ttime = *avg_ttime +  a[select].TurnAround_Time;
            *avg_wtime = *avg_wtime +  a[select].Waiting_Time;
        }
    }

    return;
}

void Round_Robin(struct Process a[],int total,float *avg_ttime,float *avg_wtime,int time_quantum)
{
    int range = 0,select_store = 0,tb_time = 0,checked = 0,select_main = 0,executed = 0;
    Process store[total];

    while(executed != total)
    {
        int eligible = 0;

        for(int i = 0;i<total;i++)
        {
            if(a[i].Arrival_Time <= range && a[i].check == false)
            store[eligible++] = a[i];
        }

        for(int i = 0;i<total;i++)
        {
            if(a[i].P_name == store[select_store].P_name)
                select_main = i;
        }

        if(a[select_main].Remaining_Time > 0)
        {
            a[select_main].Remaining_Time = a[select_main].Remaining_Time - time_quantum;

            if(a[select_main].Remaining_Time < 0)
            {
                tb_time = tb_time + time_quantum + a[select_main].Remaining_Time;
                a[select_main].Remaining_Time = 0;
                range = tb_time;
            }
            else
            {
                tb_time += time_quantum;
                range += time_quantum;
            }
        }
        if(a[select_main].Remaining_Time == 0)
        {
            a[select_main].check = true;
            executed++;
            checked++;

            a[select_main].TurnAround_Time =  tb_time - a[select_main].Arrival_Time;
            a[select_main].Waiting_Time = a[select_main].TurnAround_Time - a[select_main].Burst_Time;

            *avg_ttime = *avg_ttime +  a[select_main].TurnAround_Time;
            *avg_wtime = *avg_wtime +  a[select_main].Waiting_Time;

            select_store--;
        }

        select_store++;
        if(select_store == total-checked)
            select_store = 0;
    }
    return;
}

void Reset(struct Process a[],int total)
{
    for(int i = 0;i<total;i++)
    {   a[i].TurnAround_Time = 0;
        a[i].Waiting_Time = 0;
        a[i].check = false;
        a[i].Remaining_Time = a[i].Burst_Time;
    }
}

int main()
{
    char option ,c;
    int total;
    float avg_ttime = 0, avg_wtime = 0;
    cout<<"Enter total number of Processes "<<endl;
    cin>>total;
    cout<<endl<<" We consider Highest the Number High will be it's Priority"<<endl;

    Process scheduler[total];

    get_details(scheduler,total);

    do
    {
        cout<<endl<<" Select a Scheduling Algorithm "<<endl<<endl;
        cout<<" a FIFS (First In First Serve)"<<endl;
        cout<<" b SJF (Shortest Job First) Non-Preemptive"<<endl;
        cout<<" c SRTF (Shortesr Remaining Time First)"<<endl;
        cout<<" d Non-Preemptive Priority Based "<<endl;
        cout<<" e Preemptive Priority Based "<<endl;
        cout<<" f Round-Robin"<<endl;
        cin>>option;
        switch(option)
        {
            case 'a':
            {
                Reset(scheduler,total);
                avg_ttime = 0, avg_wtime = 0;

                FIFS(scheduler,total,&avg_ttime,&avg_wtime);
                display(scheduler,total);

                cout<<endl<<" Average Waiting Time is : "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is : "<<(avg_ttime/total);
            }
                break;
                case 'b':
            {
                Reset(scheduler,total);
                avg_ttime = 0, avg_wtime = 0;

                SJF_NP(scheduler,total,&avg_ttime,&avg_wtime);
                display(scheduler,total);

                cout<<endl<<" Average Waiting Time is : "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is : "<<(avg_ttime/total);
            }
            break;
            case 'c':
            {
                Reset(scheduler,total);
                avg_ttime = 0, avg_wtime = 0;

                SRTF(scheduler,total,&avg_ttime,&avg_wtime);
                display(scheduler,total);

                cout<<endl<<" Average Waiting Time is : "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is : "<<(avg_ttime/total);
            }
            break;
            case 'd':
            {
                Reset(scheduler,total);
                avg_ttime = 0, avg_wtime = 0;

                NP_Priority(scheduler,total,&avg_ttime,&avg_wtime);
                display(scheduler,total);

                cout<<endl<<" Average Waiting Time is : "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is : "<<(avg_ttime/total);
            }
            break;
            case 'e':
            {
                Reset(scheduler,total);
                avg_ttime = 0, avg_wtime = 0;

                P_Priority(scheduler,total,&avg_ttime,&avg_wtime);
                display(scheduler,total);

                cout<<endl<<" Average Waiting Time is : "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is : "<<(avg_ttime/total);
            }
            break;
            case 'f':
            {
                Reset(scheduler,total);
                avg_ttime = 0, avg_wtime = 0;

                int time_quantum = 0;
                cout<<endl<<"Enter Quantum or Time-Slot "<<endl;
                cin>>time_quantum;

                Round_Robin(scheduler,total,&avg_ttime,&avg_wtime,time_quantum);
                display(scheduler,total);

                cout<<endl<<" Average Waiting Time is : "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is : "<<(avg_ttime/total);
            }
            break;
            default:
                cout<<endl<<" Wrong choice enter , try again "<<endl;
        }
        cout<<endl<<" To continue Press C"<<endl;
        cin>>c;
    }
    while(c == 'c' || c == 'C');
}
