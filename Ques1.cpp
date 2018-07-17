
#include<stdlib.h>
#include<iostream>
using namespace std;

int main()
{
    cout<<"kernel version  is : "<<endl;
    system("cat /proc/sys/kernel/osrelease");

    cout<<" \n CPU INFO  is : "<<endl;
    system("cat /proc/cpuinfo | awk 'NR==3,NR==4 {print}'");

    cout<<" \n Memory  INFO  is : "<<endl;
    system("cat /proc/meminfo | awk '/Mem*/ {print}'");

}
