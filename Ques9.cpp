#include<iostream>
using namespace std;

struct hole
{
    int hole_size;
    bool check;
    hole* next;
};

struct Difference
{
    int difference;
    int number;
};

hole* head = NULL;

hole* create_hole(int hole_size)
{
         hole* temp = new struct hole;
        temp->check = false;
        temp->hole_size = hole_size;
        temp->next = NULL;
        return temp;
}

void insertion_end(int hole_size)
{
    if(head == NULL)
    {
         head = create_hole(hole_size);
    }
    else
    {
        hole* temp = head;

        while(temp->next != NULL)
        temp = temp->next;

       temp->next = create_hole(hole_size);
    }
}
/*void forward_traverse()
{
   if(head == NULL)
        {
            cout<<endl<<" list is empty cannot traverse the list"<<endl;
            return;
        }
        hole* temp = head;

        while(temp!=NULL)
        {
            cout<<temp->hole_size<<"  ";
            temp = temp->next;
        }
}*/

bool first_fit(int hole_size)
{
    bool found = true,is_allocated = false;
    hole* temp = head;

    while(found == true)
    {
            if(temp->hole_size>hole_size)
            {
                int store = temp->hole_size;
                temp->hole_size = hole_size;

                hole* temp1 = new hole;
                temp1->hole_size = store - hole_size;
                temp1->next = temp->next;
                temp->next = temp1;
                temp->check = true;

                found = false;
                is_allocated = true;
            }
            else
            {
                temp = temp->next;
                if(temp == NULL)
                found = false;
            }
    }

    return is_allocated;
}

Difference select_hole_best(Difference *a,int length)
{
    int Min = 0;

    //sort the array
    for(int i = 0;i<length;i++)
    {
        for(int j = i+1;j<length;j++)
        {
            if(a[i].difference >  a[j].difference)
            {
                int t1 ,t2;
                t1 = a[i].difference;
                t2 = a[i].number;

                a[i].difference = a[j].difference;
                a[i].number = a[j].number;

                a[j].difference = t1;
                a[j].number = t2;
            }
        }
    }

    int select = 0;
    //find smallest +ve number
    for(int i = 0;i<length;i++)
    {
        if(a[i].difference < 0)
        Min = a[i].difference;

        if(a[i].difference > 0 && (Min < 0 || Min == 0))
        {
          Min = a[i].difference;
          select = i;
          break;
        }
    }


    return a[select];
}

bool best_fit(int hole_size,int n_blocks,int *a)
{
     hole* temp = head;
     Difference store[n_blocks],selected_hole;
    int i = 0;

     //create array
     while(temp!=NULL)
     {
        if(temp->check == false)
        {
          store[i].difference = temp->hole_size-hole_size;
          store[i].number = temp->hole_size;
          i++;
        }
        temp = temp->next;
     }
       //restore temp
        temp = head;
     selected_hole = select_hole_best(store,n_blocks);

        //if there is no suitable hole return
     if(selected_hole.difference < 0 )
     return false;

            //select the hole from linked list
        while(temp->hole_size != selected_hole.number)
        {
        temp = temp->next;
        }

                //create new hole
                int Store = temp->hole_size;
                temp->hole_size = hole_size;

                hole* temp1 = new hole;
                temp1->hole_size = Store - hole_size;
                temp1->next = temp->next;
                temp->next = temp1;
                temp->check = true;

     return true;
}

Difference select_hole_worst(Difference *a,int length)
{

    //sort the array
    for(int i = 0;i<length;i++)
    {
        for(int j = i+1;j<length;j++)
        {
            if(a[i].difference <  a[j].difference)
            {
                int t1 ,t2;
                t1 = a[i].difference;
                t2 = a[i].number;

                a[i].difference = a[j].difference;
                a[i].number = a[j].number;

                a[j].difference = t1;
                a[j].number = t2;
            }
        }
    }

    return a[0];
}

bool worst_fit(int hole_size,int n_blocks,int *a)
{
    hole* temp = head;
     Difference store[n_blocks],selected_hole;
    int i = 0;

     //create array
     while(temp!=NULL)
     {
        if(temp->check == false)
        {
          store[i].difference = temp->hole_size-hole_size;
          store[i].number = temp->hole_size;
          i++;
        }
        temp = temp->next;
     }
       //restore temp
        temp = head;
     selected_hole = select_hole_worst(store,n_blocks);

        //if there is no suitable hole return
     if(selected_hole.difference < 0 )
     return false;

            //select the hole from linked list
        while(temp->hole_size != selected_hole.number)
        {
        temp = temp->next;
        }

                //create new hole
                int Store = temp->hole_size;
                temp->hole_size = hole_size;

                hole* temp1 = new hole;
                temp1->hole_size = Store - hole_size;
                temp1->next = temp->next;
                temp->next = temp1;
                temp->check = true;

     return true;
}

bool external_frag(int* fragmentation)
{
    hole* temp = head;
    bool is_fragment = false;

    while(temp!=NULL)
    {
        if(temp->check == false)
        {
            *fragmentation = *fragmentation + temp->hole_size;
            is_fragment = true;
        }
        temp = temp->next;
    }
    return is_fragment;
}

bool internal_frag(int hole_size,int* fragmentation)
{
    if(head->hole_size < hole_size)
    return false;

    bool is_allocated = false;
    hole* temp = head;

    while(temp!=NULL)
    {
        if(temp->check == false)
        {
            temp->check = true;
            *fragmentation = temp->hole_size - hole_size;
            is_allocated = true;
            break;
        }
        temp = temp->next;
    }

    return is_allocated;
}

bool is_Same()
{
    int counter1 = 0,counter2 = 0,check = head->hole_size;
    hole* temp = head;

    while(temp!=NULL)
    {
        if(temp->hole_size == check)
        counter1++;

        temp = temp->next;
        counter2++;
    }

    if(counter1 == counter2)
    return true;
    else
    return false;
}


int main(void)
{

    int n_blocks = 0,n_process = 0,temp = 0;
    char option;

    cout<<"Enter number of blocks(holes)"<<endl;
    cin>>n_blocks;
    cout<<endl<<"Enter size(bytes) of each block(hole)"<<endl;

    for(int i = 0;i<n_blocks;i++)
    {
        cout<<endl<<"Enter size of block(hole) "<<i+1<<endl;
        cin>>temp;
        insertion_end(temp);
    }

    cout<<endl<<"Enter number of Processes"<<endl;
    cin>>n_process;
    int Process[n_process];
    cout<<endl<<"Enter size(bytes) of each Process"<<endl;

    for(int i = 0;i<n_process;i++)
    {
         cout<<endl<<"Enter size of Process "<<i+1<<endl;
         cin>>Process[i];
    }

    if(is_Same() == false)
  {
    cout<<endl<<"Select an Memory Management Algorithm"<<endl;
    cout<<"a First-Fit"<<endl;
    cout<<"b Best-Fit"<<endl;
    cout<<"c Worst-Fit"<<endl;
    cin>>option;

    switch(option)
    {
        case 'a':
        {
            int fragmentation = 0;
            bool is_allocated = false;

            for(int i = 0;i<n_process;i++)
            {
                    fragmentation = 0;
                    is_allocated = false;
                    is_allocated = first_fit(Process[i]);

                    if(is_allocated == true)
                    cout<<endl<<"Process "<<i+1<<" is allocated"<<endl;
                    else
                    {
                        bool is_frag = false;
                        cout<<endl<<"Cannot allocate the Process"<<i+1<<endl;

                        is_frag = external_frag(&fragmentation);

                        if(is_frag == true)
                        {
                            cout<<" due to External Fragmentation"<<endl<<" External Fragmentation is = "<<fragmentation<<" bytes"<<endl;
                        }
                        else
                        {
                            cout<<" all blocks(holes) are allocated"<<endl<<" External Fragmentation is = "<<fragmentation<<"bytes"<<endl;
                        }
                    }
            }
            cout<<endl<<" Total External Fragmentation is = "<<fragmentation<<" bytes"<<endl;
        }
        break;
        case 'b':
        {
            int fragmentation = 0;
            bool is_allocated = false;

            for(int i = 0;i<n_process;i++)
            {
                    fragmentation = 0;
                    is_allocated = false;
                    is_allocated = best_fit(Process[i],n_blocks,Process);

                    if(is_allocated == true)
                    cout<<endl<<"Process "<<i+1<<" is allocated";
                    else
                    {
                        bool is_frag = false;
                        cout<<endl<<"Cannot allocate the Process"<<i+1;

                        is_frag = external_frag(&fragmentation);

                        if(is_frag == true)
                        {
                            cout<<" due to External Fragmentation"<<endl<<" External Fragmentation is = "<<fragmentation<<" bytes"<<endl;
                        }
                        else
                        {
                            cout<<" all blocks(holes) are allocated"<<endl<<" External Fragmentation is = "<<fragmentation<<" bytes"<<endl;
                        }
                    }
            }

            cout<<endl<<" Total External Fragmentation is = "<<fragmentation<<" bytes"<<endl;
        }
        break;
        case 'c':
        {
            int fragmentation = 0;
            bool is_allocated = false;

            for(int i = 0;i<n_process;i++)
            {
                    fragmentation = 0;
                    is_allocated = false;
                    is_allocated = worst_fit(Process[i],n_blocks,Process);

                    if(is_allocated == true)
                    cout<<endl<<"Process "<<i+1<<" is allocated";
                    else
                    {
                        bool is_frag = false;
                        cout<<endl<<"Cannot allocate the Process"<<i+1;

                        is_frag = external_frag(&fragmentation);

                        if(is_frag == true)
                        {
                            cout<<" due to External Fragmentation"<<endl<<" External Fragmentation is = "<<fragmentation;
                        }
                        else
                        {
                            cout<<" all blocks(holes) are allocated"<<endl<<" External Fragmentation is = "<<fragmentation;
                        }
                    }
            }

            cout<<endl<<" Total External Fragmentation is = "<<fragmentation;
        }
        break;
        default:
        cout<<"Wrong option select"<<endl;
    }
    }
    else
    {
            int fragmentation = 0;
            bool is_allocated = false;

            for(int i = 0;i<n_process;i++)
            {
                    fragmentation = 0;
                    is_allocated = false;
                    is_allocated = internal_frag(Process[i],&fragmentation);

                    if(is_allocated == true)
                    cout<<endl<<"Process "<<i+1<<" is allocated "<<endl<<" Internal Fragmentation is :  "<<fragmentation<<" bytes"<<endl;
                    else
                    {
                       cout<<endl<<"Process "<<i+1<<" is not allocated "<<endl;
                    }
            }
    }
}
