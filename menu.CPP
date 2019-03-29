#include <stdio.h>
#include <conio.h>
#include<iostream.h>

#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27
#define C 3

struct operators
{
	char name[7];
	char symbol;
};

const operators ope[C]={"sin",'S',"cos",'C',"tan",'T'};


int main()
{
	clrscr();
	int k=0;

	re:

	for(int i=0; i<C; ++i)
	{
		cout<<'\n'<<(i==k?">>":"  ")<<ope[i].name;
	}

	int KB_code=0;

	while(KB_code != KB_ESCAPE )
	{
	  if (kbhit())
		{
				KB_code = getch();

				switch (KB_code)
				{
					 case KB_LEFT:
						if(k)--k;
						else k=C-1;
						clrscr();
						goto re;

					 case KB_RIGHT:
						if(k==C-1)k=0;
						else ++k;
						clrscr();
						goto re;

					 case KB_UP:
						if(k)--k;
						else k=C-1;
						clrscr();
						goto re;

					 case KB_DOWN:
						if(k==C-1)k=0;
						else ++k;
						clrscr();
						goto re;

				}

		}
  }

  return 0;
}