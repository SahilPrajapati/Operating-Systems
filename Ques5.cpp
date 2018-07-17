#include<iostream>
using namespace std;

#define MAX 3
class Queue_circular
{
    public:

    int out,in;
    int container[MAX];

    void create_empty_queue()
    {
        this->out = -1;
        this->in = -1;
    }

    bool is_full()
    {
        if(this->out == (this->in + 1)%MAX)
        return true;
        else
        return false;
    }

    bool is_empty_()
    {
        if(this->out == -1 && this->in == -1 )
        return true;
        else
        return false;
    }

    void enqueue(int element)
    {
        if(this->is_full() == false)
        {
            if(this->out == -1&&this->in == -1)
            {
                this->out =0;
                this->in = 0;
                this->container[this->in] = element;
            }
            else
            {
                this->in = (this->in + 1)%MAX;
                this->container[this->in] = element;
            }
        }
        else
        cout<<endl<<"cannot produce, buffer is full"<<endl;

    }

    void dequeue()
    {
        if(this->is_empty_() == false)
        {
            if(this->out == this->in && this->is_full() == false)
            {
                cout<<endl<<this->container[this->out];
            this->out = this->in = -1;
            }
            else
            {
                cout<<endl<<this->container[this->out];
                this->out = (this->out + 1)%MAX;
            }
        }
        else
        {
            cout<<endl<<"cannot consume, buffer do not contain any element"<<endl;
        }
    }

    void display_queue()
    {
        if(this->is_empty_() == false)
        {
            cout<<endl<<" elements in buffer are : "<<endl;
            for(int i = this->out ; i<= this->in;i++)
                cout<<this->container[i]<<"  ";
        }
        else
        {
            cout<<endl<<" buffer is empty"<<endl;
        }
    }
};


int main(void)
{
    char option , ch;
    Queue_circular q;
    q.create_empty_queue();
    do
    {
        cout<<endl<<" enter an option"<<endl;
        cout<<"a produce an element in buffer"<<endl;
        cout<<"b consume an element from buffer"<<endl;
        cout<<"c display buffer"<<endl;
        cin>>option;

        switch(option)
        {
            case 'a':
            {
                int element;
                cout<<endl<<" enter an element"<<endl;
                cin>>element;
                q.enqueue(element);

            }
            break;
            case 'b':
            {
                q.dequeue();
            }
            break;
            case 'c':
            {
                q.display_queue();
            }
            break;
            default:
            cout<<endl<<" wrong option choose"<<endl;

        }
        cout<<endl<<" do you want to continue"<<endl;
        cin>>ch;
    }
    while(ch == 'c'|| ch == 'C');

}
