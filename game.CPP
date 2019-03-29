#include<conio.h>
#include<iostream.h>
#include<fstream.h>
#include<dos.h>
#include<stdlib.h>
#include<time.h>

#define up 72
#define down 80
#define left 75
#define right 77
#define esc 27
#define nos 6
#define file "tz_gamedata.dat"
static long j=0, score=0, level=0, Time=25;

class obj
{
	int x;
	int y;
	char c;

	public:

	obj*next;

	obj()
	{
		x=1;
		y=12+random(10);
		c='>';
		next=NULL;
	}

	obj(char ch)
	{
		x=1;
		y=12+random(10);
		c=ch;
		next=NULL;
	}

	void go(int X, int Y)
	{
		x=X;
		y=Y;
		gotoxy(x, y);
		cout<<c;
	}
	void go()
	{
		gotoxy(x, y);
		cout<<c;
	}

	void xmm()
	{
			gotoxy(x, y);
			cout<<' ';
			if(x>0)--x;
			else x=79;
			gotoxy(x, y);
			cout<<c;
	}

	void ymm()
	{
			gotoxy(x, y);
			cout<<' ';
			if(y>12)--y;
			else y=21;
			gotoxy(x, y);
			cout<<c;
	}

	void xpp()
	{
			gotoxy(x, y);
			cout<<' ';
			if(x<80)++x;
			else x=1;
			gotoxy(x, y);
			cout<<c;
	}

	void xpps()
	{
			gotoxy(x, y);
			cout<<' ';
			if(x<80)++x;
			else
			{
				x=1;
				y=12+random(10);
			}
			gotoxy(x, y);
			cout<<c;
	}

	void ypp()
	{
			gotoxy(x, y);
			cout<<' ';
			if(y<21)++y;
			else y=12;
			gotoxy(x, y);
			cout<<c;
	}

	int cmp(obj O)
	{
		if(x==O.x && y==O.y)
			return 0;
		return 1;
	}
}pl('O'), *st=NULL;

int compare()
{
	for(obj*tmp=st; tmp!=NULL; tmp=tmp->next)
		if(!(*tmp).cmp(pl))
			return 0;
	return 1;
}

void push()
{
	if(st==NULL)
		st=new obj;
	else
		{
			obj*tmp=new obj;
			tmp->next=st;
			st=tmp;
		}
	(*st).go();
	j++;
}

void main()
{
	randomize();
	clrscr();
	gotoxy(58, 24);
	cout<<"...MANISH KUSHWAHA.(TZ)";
	gotoxy(25,14);
	cout<<"PRESS ANY KEY TO START!!";
	getch();
	clrscr();
	gotoxy(58, 24);
	cout<<"...MANISH KUSHWAHA.(TZ)";
	gotoxy(65, 2);
	cout<<"LEVEL:";
	gotoxy(65, 3);
	cout<<"SCORE:";
	gotoxy(1,11);
	for(int i=0; i<80; ++i)cout<<'-';
	gotoxy(1,22);
	for(i=0; i<80; ++i)cout<<'-';
	pl.go(40,15);
	push();
	while(compare())
	{
		if((score/5000)>=level)
		{
			push();
			--Time;
			level=(score/5000)+1;
			gotoxy(72,2);
			cout<<level;
		}
		delay(Time);
		if(j<nos&&random(20)%19==0)push();
		(*st).xpps();
		score++;
		gotoxy(72,3);
		cout<<score;
		for(obj*tmp=st; tmp->next!=NULL; tmp=tmp->next)
		{
			(*tmp->next).xpps();
			score++;
			gotoxy(72,3);
			cout<<score;
		}
		if(kbhit())
		{
			char ch=getch();
			switch(ch)
			{
				case esc:goto end;
				case up:pl.ymm();break;
				case down:pl.ypp();break;
				case left:pl.xmm();break;
				case right:pl.xpp();break;
			}
		}
	}
	end:
	int hscore=0;
	ifstream f(file);
	if(f)
		f.read((char*)&hscore, sizeof(int));
	gotoxy(30,11);
	cout<<"GAME OVER";
	if(score>=hscore)
	{
		gotoxy(16,12);
		cout<<"CONGRATULATIONS!!you made new highscore..";
		ofstream F(file,ios::trunc);
		F.write((char*)&score,sizeof(score));
		F.close();
	}
	else
	{
		gotoxy(27,12);
		cout<<"high score:"<<hscore;
	}
	gotoxy(27, 13);
	cout<<"your score:"<<score;
	gotoxy(24,14);
	cout<<"PRESS ANY KEY TO EXIT...";
	getch();
	f.close();
}