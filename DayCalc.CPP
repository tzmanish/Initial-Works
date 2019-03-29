//to find day of a given date.
#include<iostream.h>
#include<conio.h>
void main()
{
	clrscr();
	unsigned date, month, year, od=0, temp;
	char ch;
	cout<<"\nENTER DATE(dd/mm/yyyy):";
	cin>>date>>ch>>month>>ch>>year;
	temp=(year-1)%400;
	od+=(temp/100)*5;
	temp%=100;
	od+=(temp/4)*2;
	temp-=temp/4;
	od+=temp;
	switch(month-1)
	{
		case 12:od+=3;
		case 11:od+=2;
		case 10:od+=3;
		case 9:od+=2;
		case 8:od+=3;
		case 7:od+=3;
		case 6:od+=2;
		case 5:od+=3;
		case 4:od+=2;
		case 3:od+=3;
		case 2:
			if(((year%400)%4)==0)od+=1;
			else od+=0;
		case 1:od+=3;
	}
	od+=date;
	od%=7;
	cout<<"\nTHE DATE IS\t";
	switch(od)
	{
		case 0:cout<<" SUNDAY";
			break;
		case 1:cout<<" MONDAY";
			break;
		case 2:cout<<" TUESDAY";
			break;
		case 3:cout<<" WEDNESDAY";
			break;
		case 4:cout<<" THURSDAY";
			break;
		case 5:cout<<" FRIDAY";
			break;
		case 6:cout<<" SATURDAY";
	}
	cout<<", "<<date;
	if((date<14)&&(date>10))
		cout<<"th ";
	else
	cout<<((date%10)==1?"st ":((date%10)==2?"nd ":((date%10)==3?"rd ":"th ")));
	switch(month)
	{
		case 1:cout<<"JANUARY";break;
		case 2:cout<<"FEBRUARY";break;
		case 3:cout<<"MARCH";break;
		case 4:cout<<"APRIL";break;
		case 5:cout<<"MAY";break;
		case 6:cout<<"JUNE";break;
		case 7:cout<<"JULY";break;
		case 8:cout<<"AUGUST";break;
		case 9:cout<<"SEPTEMBER";break;
		case 10:cout<<"OCTOBER";break;
		case 11:cout<<"NOVEMBER";break;
		case 12:cout<<"DECEMBER";break;
	}
	cout<<' '<<year<<'.';
	getch();
}