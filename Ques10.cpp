#include<iostream>
using namespace std;

void create_table(int *a)
{
    a[0] = 1;
    a[1] = 0;
    a[2] = 7;
    a[3] = 3;
    a[4] = 4;
    a[5] = 9;
    a[6] = 5;
    a[7] = 2;
    a[8] = 6;
    a[9] = 8;
}

void display_table(int *a)
{
    cout<<endl<<"Page Table is :--"<<endl;
    cout<<endl<<" Page No  Frame No"<<endl<<endl;;

    for(int i = 0;i<10;i++)
    cout<<"   "<<i<<"       "<<a[i]<<endl;
}

int calculate(int *a,int p_number,int offset)
{
    if(p_number >=0 && p_number <=9)
    {
        if(offset >=0 && offset <= 10)
        {
            return (a[p_number]*10+offset);
        }
        else
        {
            cout<<endl<<"Wrong offset enter"<<endl;
            return -2;
        }
    }
    else
    {
        cout<<endl<<"Wrong page number enter"<<endl;
        return -1;
    }
}

int main(void)
{
    int p_table[10],p_number = 0,offset = 0,p_add = 0;
    char ch;

    cout<<endl<<"Total number of Pages = 10"<<endl;
    cout<<endl<<"Total number of Frames = 10"<<endl;
    cout<<endl<<"Page Size = 10 bytes"<<endl;
    cout<<endl<<"Frame Size = 10 bytes"<<endl;
    cout<<endl<<"Logical Memory Size = 100 bytes"<<endl;

    create_table(p_table);
    display_table(p_table);

    do
  {
    cout<<endl<<"Enter Logical Address"<<endl;

    cout<<endl<<"Enter Page Number"<<endl;
    cin>>p_number;
    cout<<endl<<"Enter Offset"<<endl;
    cin>>offset;

    cout<<endl<<"Phsical Address is = "<<calculate(p_table,p_number,offset);
    cout<<endl<<"Press c to continue"<<endl;
    cin>>ch;
    }
    while(ch == 'c'|| ch == 'C');
}
