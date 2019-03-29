#include<iostream.h>
#include<conio.h>
#include<math.h>
#include<process.h>
#include<iomanip.h>

int rsize,csize;

/*PROTOTYPES OF FUNCTIONS USED IN PROGRAM*/

int *adjoint(int *mat, unsigned size);

void getchoice();

void showmat(int *mat, int s1, int s2=-1);

void showmat(char *mat, int s1, int s2=-1);

int *getmat(int s1, int s2);

float *multiply(float *arr1, int *arr2, int size);

void multiply();

long determinant(int*mat,unsigned size);

int *transpose(int *arr,unsigned size);

int *adjoint(int *mat, unsigned size);

void SEQ();

/*FUNCTION TO FIND PRODUCT OF TWO MATRICES*/

float *multiply(float *arr1, int *arr2, int size)
{
	float *mul;
	mul=new float[size*size];
	for(int i=0; i<size; ++i)
	{
		mul[i]=0;
		for(int j=0; j<size; ++j)
		{
			mul[i]+=(arr1[i*size+j]*arr2[j]);
		}
	}
	return mul;
}

/*MULTIPLY OVERLOADED*/

void multiply()
{
	unsigned r1, r2, c1, c2;

	cout<<"enter dimentions for first matrix\nrow:";
	cin>>r1;
	cout<<"\ncolumn:";
	cin>>c1;
	cout<<"\n\nenter dimentions for second matrix\nrow:";
	cin>>r2;
	cout<<"\ncolumn:";
	cin>>c2;

	if(c1!=r2)
	{
		cout<<"\n\nTHE TWO MATRICES ARE NOT DIMENTIONALLY PERFECT";
		cout<<" TO BE MULTIPLIED.\npress eny key to return to main menu...";
		getch();
		getchoice();
	}

	int *mat1, *mat2, *mul, i, j;
	mat1=new int[r1*c1];
	mat2=new int[r2*c2];
	mul=new int[r1*c2];

	cout<<"\n\nnow enter the first matrix:\n";
	mat1=getmat(r1, c1);

	cout<<"\n\nenter second matrix:\n";
	mat2=getmat(r2, c2);

	cout<<"\n\nmatrices are\n\n";
	showmat(mat1, r1, c1);
	cout<<"\n\nand\n\n";
	showmat(mat2, r2, c2);

	for(i=0; i<r1; ++i)
	{
		for(int j=0; j<c2; ++j)
		{
			mul[i*c2+j]=0;
			for(int k=0; k<r2; k++)
			{
				mul[i*c2+j]+=mat1[i*c1+k]*mat2[k*c2+j];
			}
		}
	}
	cout<<"\n\nAND THE PRODUCT OF MATRICES IS:\n\n";
	showmat(mul, r1, c2);
	cout<<"\n\n\tPRESS ANY KEY TO RETURN TO MAIN MENU...";
	getch();
	getchoice();
}

/*TO FIND ADJOINT OF A MATRIX*/

int *adjoint(int *mat, unsigned size)
{
	int *adj, *tmp;
	unsigned t=size-1;
	adj=new int[size*size];
	tmp=new int[t*t];

	if(size==1)
	{
		adj[0]=1;
		return adj;
	}

	for(int i=0; i<size; ++i)
	{
		for(int j=0; j<size; ++j)
		{
			for(int k=0, m=0; k<size; ++k)
			{
				if(k==i)continue;
				for(int l=0, n=0; l<size; ++l)
				{
					if(l==j)continue;
					tmp[m*t+n]=mat[k*size+l];
					++n;
				}
				++m;
			}
			adj[i*size+j]=(pow(-1,(i+j))*determinant(tmp,t));
		}
	}
	adj=transpose(adj,size);
	return adj;
}

/*TO FIND TRANSPOSE OF MATRIX*/

int *transpose(int *arr,unsigned size)
{
	int *tps;
	tps=new int[size*size];
	for(int i=0; i<size; ++i)
		for(int j=0; j<size; ++j)
			tps[i*size+j]=arr[j*size+i];
	return tps;
}

/*FUNCTION TO FIND DETERMINANT OF A MATRIX.*/

long determinant(int*mat,unsigned size)
	{
		long det=0;

		if(size==1)return mat[0];

		if(size==2)
		{
			det=(mat[0]*mat[3])-(mat[1]*mat[2]);
			return det;
		}

		int *tmat;
		unsigned tmp=size-1;
		tmat=new int[tmp*tmp];

		for(int i=0; i<size; ++i)
		{
			for(int j=1, s1=0; j<size; ++j,++s1)
			{
				for(int k=0, s2=0; k<size; ++k)
				{
					if(k==i)	continue;
					tmat[s1*tmp+s2]=mat[j*size+k];
					++s2;
				}
			}
			det+=((pow(-1,i)*determinant(tmat,tmp))*mat[i]);
		}
		return det;
	}

/*TO SOLVE SYSTEM OF EQUATIONS*/

void SEQ()
{
	unsigned size;
	long det;
	char *X, a;
	int *A, *B, *adj, i, j;
	float *inv, *x;            //AX=B

	clrscr();
	cout<<"ENTER NO OF VARIABLES:";
	cin>>size;

	A=new int[size*size];
	adj=new int[size*size];
	inv=new float[size*size];
	x=new float[size];
	X=new char[size];
	B=new int[size];

	for(i=size-1, a='Z'; i>=0; --i, --a)
		X[i]=a;

	cout<<"\nenter values for equation in following format:\n";
	for(i=0; i<size; ++i)
	{
		for(a='a', j=0; j<size; ++j,++a)
		{
			cout<<a<<X[j]<<" + ";
		}
		cout<<"\b\b=\t"<<a<<"\n";
	}

	for(i=0; i<size; ++i)
	{
		cout<<"\n\nrow "<<i+1<<":\n\n";
		for(a='a', j=0; j<size; ++j,++a)
		{
			cout<<a<<"\t=\t";
			cin>>A[i*size+j];
			cout<<"\n";
		}
		cout<<a<<"\t=\t";
		cin>>B[i];
		cout<<"\n";
	}

	cout<<"the equations formed are:\n\n";
	for(i=0; i<size; ++i)
	{
		for(j=0; j<size; ++j)
		{
			if(A[i*size+j])
			cout<<setw(4)<<A[i*size+j]<<X[j]<<" + ";
		}
		cout<<"\b\b= "<<setw(4)<<B[i]<<"\n";
	}
	cout<<"\n\nPRESS ANY KEY TO PROGRESS...";
	getch();

	cout<<"\n\nthe matrices formed are:\n\n\tA =\n\n";
	showmat(A, size);

	cout<<"\n\n\tX =\n\n";
	showmat(X, size, 1);

	cout<<"\n\n\tB =\n\n";
	showmat(B, size, 1);

	cout<<"\n\nPRESS ANY KEY TO PROCESS FURTHER...";
	getch();

	cout<<"\nsince \" A * X = B \" ,\n";
	for(i=0; i<size; ++i)
	{
		cout<<"\n";
		for(j=0; j<size; ++j)
			cout<<setw(4)<<A[i*size+j]<<"\t";
		cout<<"\b";
		if(i==((size-1)/2))cout<<"\t*\t";
		else cout<<"\t\t";
		cout<<X[i];
		if(i==((size-1)/2))cout<<"\t=\t";
		else cout<<"\t\t";
		cout<<setw(4)<<B[i];
	}
	cout<<"\n\nPRESS ANY KEY...";
	getch();

	adj=adjoint(A, size);
	det=determinant(A, size);
	cout<<"\n\nthe determinant of A = "<<det;
	if(det==0)
	{
		cout<<"\nSINCE det(A) IS 0, THERE EXISTS NO(INFINITE) SOLUTION(S) FOR SYSTEM.";
		cout<<"\npress any key to return to main menu...";
		getch();
		getchoice();
	}
	cout<<"\n\nand the adjoint of A =\n\n";

	showmat(adj,size);

	cout<<"\n\nPRESS ANY KEY...";
	getch();

	cout<<"\nas we know, \" A^(-1) = [1 / det(A)] * [adj(A)] \" ,\n";
	cout<<"\n\" A^(-1) = \"";

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	for(i=0; i<size; ++i)
	{
		cout<<"\n\t\t";
		for(j=0; j<size; ++j)
		{
			inv[i*size+j]=((float)adj[i*size+j]/(float)det);
			cout<<setprecision(2)<<setw(7)<<inv[i*size+j]<<"\t";
		}
	}
	cout<<"\n\nPRESS ANY KEY...";
	getch();

	x = multiply(inv, B, size);
	cout<<"\n\nand now, \" X = A^(-1) * B \" ie.\n";
	for(i=0; i<size; ++i)
	{
		cout<<"\t"<<X[i]<<" = "<<setw(7)<<x[i]<<"\n";
	}

	cout<<"\n\nPRESS ANY KEY TO RETURN TO MAIN MENU...";
	getch();
	getchoice();
}

/*TO PRINT A MATRIX*/

void showmat(int *mat, int s1, int s2)
{
	if(s2==-1)s2=s1;

	for(int i=0; i<s1; ++i)
	{
		for(int j=0; j<s2; ++j)
		{
			cout<<"\t"<<setw(4)<<mat[i*s2+j];
		}
		cout<<"\n";
	}
}

/*SHOWMAT OVERLOADED*/

void showmat(char *mat, int s1, int s2)
{
	if(s2==-1)s2=s1;

	for(int i=0; i<s1; ++i)
	{
		for(int j=0; j<s2; ++j)
		{
			cout<<"\t"<<mat[i*s2+j];
		}
		cout<<"\n";
	}
}

/*TO GET A MATRIX FROM USER*/

int *getmat(int s1=-1, int s2=-1)
{
	int *mat;

	if(s1==-1)
	{
		unsigned size;

		cout<<"enter matrix size:";
		cin>>size;

		mat=new int[size*size];
		s1=s2=size;
	}
	else mat=new int[s1*s2];

	rsize=s1;
	csize=s2;

	cout<<"enter matrix elements:\n\n";

	for(int i=0; i<s1; ++i)
	{
		for(int j=0; j<s2; ++j)
		{
			cout<<"\t";
			cin>>mat[i*s2+j];
		}
		cout<<"\n";
	}
	cout<<"\n\nthe matrix is:\n\n";
	showmat(mat, s1, s2);
	getch();
	return mat;
}

/*TO GET CHOICE FROM USER*/

void getchoice()
{
	unsigned choice;

	clrscr();

	cout<<"\n\t\t***************************************";
	cout<<"\n\t\t               MAIN MENU               ";
	cout<<"\n\t\t***************************************";
	cout<<"\n\n01.To find DETERMINANT of a square matrix.";
	cout<<"\n\n02.To find ADJOINT of a square matrix.";
	cout<<"\n\n03.To find the PRODUCT of two matrices.";
	cout<<"\n\n04.To find the INVERSE of a square matrix.";
	cout<<"\n\n05.To SOLVE A SYSTEM OF LINEAR EQUATIONS.";
	cout<<"\n\n06.EXIT.";
	cout<<"\n\n\tENTER YOUR CHOICE ( 1 TO 6 ) : ...";

	cin>>choice;

	switch(choice)
	{

		case 1:

			clrscr();
			int*mat=getmat();
			long det=determinant(mat,rsize);
			cout<<"\n\nand its determinant is "<<det;
			cout<<"\n\nPRESS ANY KAY TO RETURN TO MAIN MENU...";
			break;

		case 2:

			clrscr();
			int *adj;
			mat=getmat();
			cout<<"\n\nand its adjoint is \n\n";
			adj=adjoint(mat,rsize);
			showmat(adj,rsize);
			cout<<"\n\nPRESS ANY KEY TO RETURN TO MAIN MENU...";
			break;

		case 3:

			clrscr();
			multiply();
			cout<<"\n\npress any key to return to main menu...";
			break;

		case 4:

			clrscr();
			cout.setf(ios::fixed);
			cout.setf(ios::showpoint);
			mat=getmat();
			det=determinant(mat, rsize);
			cout<<"\n\nits adjoint is \n\n";
			float *inv;
			adj=adjoint(mat,rsize);
			showmat(adj,rsize);
			cout<<"\n\nand its determinant is = "<<det;
			getch();
			cout<<"\n\nsince inv(A) = [1/det(A)] * [adj(A)],\ninv(A) =\n\n ";
			for(int i=0; i<rsize; ++i)
			{
				cout<<"\n\t\t";
				for(int j=0; j<rsize; ++j)
				{
					inv[i*rsize+j]=((float)adj[i*rsize+j]/(float)det);
					cout<<setprecision(2)<<setw(7)<<inv[i*rsize+j]<<"\t";
				}
			}
			cout<<"\n\nPRESS ANY KEY TO RETURN TO MAIN MENU...";
			break;

		case 5:

			clrscr();
			SEQ();
			break;

		case 6:

			cout<<"press any key to EXIT...";
			getch();
			exit(0);

		default:

			cout<<"\n\nWRONG CHOICE, press any key to return to MAIN MENU...";

	}
	getch();
	getchoice();
}

/***********************MAIN****************************/

void main()
{
	getchoice();
}