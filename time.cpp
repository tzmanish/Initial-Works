#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>
using namespace std;
int main()
{
	time_t t;
	putenv("TZ=PST0");
	tzset();
	int i=0;
	cout<<"system time is : \n";
	start:
	i++;
	t = time(0);
	unsigned hour = (t/3600)%24;
	char status[3]="PM";
	if(hour<=12)
	status[0]='A';
	unsigned minut = (t/60)%60;
	unsigned second = t%60;
	cout<<(hour-12)<<':'<<minut<<':'<<second<<' '<<status;
	if(i<60)               //program will run upto 'i' seconds
	{
		while(time(0)==t);
		cout<<"\b\b\b\b\b\b\b\b\b\b\b";
		goto start;
	}
	getch();
}




