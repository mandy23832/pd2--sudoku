#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include"Sudoku.h"
using namespace std;
const int size=81;
int Sudoku::giveQuestion()
{
	int i;
	int arr[size]={0,4,0,2,5,0,0,0,8,
	               0,3,0,4,0,9,1,7,0,
				   0,0,0,0,8,1,2,0,0,
				   0,0,6,0,0,0,7,2,0,
				   0,0,0,6,0,4,0,0,0,
				   0,1,2,0,0,0,3,0,0,
				   0,0,3,8,1,0,0,0,0,
				   0,6,4,9,0,2,0,1,0,
				   7,0,0,0,4,5,0,9,0};
	for(i=0;i<size;i++)
		printf("%d%c",arr[i],(i+1)%9==0?'\n':' ');
}
void Sudoku::readIn()
{
	int i;
	if(i!=81)
	{
		cout<<"error! enter again";
		for(i=0;i<size;i++)
		{
			cin>>arr[i];
		}
	}
	else
	{
		for(i=0;i<size;i++)
		{
			cin>>arr[i];
		}
	}
}
void Sudoku::solve()
{
    int k=0;
    int nonzero=0;
	for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            q[i][j]=arr[k++];
            if(q[i][j]!=0)nonzero++;
        }
    }
    if(cor()==0){
		if(nonzero==81){
            cout<<"1"<<endl;
            for(int i=0;i<9;i++){
                for(int j=0;j<9;j++){
                    cout<<q[i][j]<<" ";
                }
            cout<<endl;
            }
        }
		else{
        if(nonzero<10)cout<<2<<endl;
        else{tryans();}
		}
    }
}
int Sudoku::cor(){
    int appear[10]={0};
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(appear[q[i][j]]==1&&q[i][j]!=0){
                cout<<0;
                return -1;
            }
            appear[q[i][j]]=1;
        }
        for(int k=0;k<10;k++)appear[k]=0;
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(appear[q[j][i]]==1&&q[j][i]!=0){
                cout<<0;
                return -1;
            }
            appear[q[j][i]]=1;
        }
        for(int k=0;k<10;k++)appear[k]=0;
    }
    for(int i=0;i<9;i=i+3){
        for(int j=0;j<9;j=j+3){
            for(int k=i;k<i+3;k++){
                for(int l=j;l<j+3;l++){
                    if(appear[q[k][l]]==1&&q[k][l]!=0){
                        cout<<0;
                        return -1;
                    }
                    appear[q[k][l]]=1;
                }
            }
            for(int n=0;n<10;n++)appear[n]=0;
        }
    }
    return 0;
}
void Sudoku::moveforward()
{
	do{place++;}
    while(q[(place-(place%9))/9][place%9]!=0&&place<81);
}
int Sudoku::smallpossible(int n)
{
	int col,row;
    col=n/9;
    row=n%9;
    int use[10]={0};
    int lefttop1,lefttop2;
    for(int i=0;i<9;i++){
        if(q[col][i]!=0)use[q[col][i]]=1;
    }
    for(int i=0;i<9;i++){
        if(q[i][row]!=0)use[q[i][row]]=1;
    }
    lefttop1=(col/3)*3;
    lefttop2=(row/3)*3;
    for(int i=lefttop1;i<lefttop1+3;i++){
        for(int j=lefttop2;j<lefttop2+3;j++){
            if(q[i][j]!=0)use[q[i][j]]=1;
        }
    }
    //for(int i=0;i<9;i++)cout<<use
    for(int i=q[col][row]+1;i<10;i++){
        if(use[i]==0)return i;
    }
    return 0;
}
void Sudoku::tryans(){
    int ans;
	int i, j;
	int check=0;
	int tmp[81];
	int result[9][9];
	tmpp=1;
	place=-1;
	moveforward();
	do{
	    //cout<<place<<endl;
        ans=smallpossible(place);//cout<<ans<<endl;
        if(ans!=0&&place!=81){
            tmp[tmpp]=place;
            tmpp++;
            q[place/9][place%9]=ans;
            moveforward();
        }
        if(ans==0&&place!=81){
            if(tmpp!=1)
            {
                q[place/9][place%9]=ans;
                place=tmp[--tmpp];
            }
            else
            {place=-1;}
        }
        if(ans!=0&&place==81){
            check++;
            for(i=0;i<9;i++){
                for(j=0;j<9;j++){
                    result[i][j]=q[i][j];
                }
            }
            place=tmp[--tmpp];
        }
	}
	while(place>-1&&place<81&&check<2);
	if(check==0&&place==-1)
    {cout<<"0"<<endl;}
	if(check==1){
		cout<<"1"<<endl;
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				cout<<result[i][j]<<" ";
			}
		cout<<endl;
		}
	}
	if(check>1)
		{cout<<"2"<<endl;}
}
void Sudoku::changeNum(int a,int b)
{
	int temp,i,j;
	if(a<=0||b<=0||a>9||b>9)
	{
		cout<<"error!enter again";
	}
	for(i=0;i<size;i++)
	{
		if(arr[i]==a)
			arr[i]=(-1);
		if(arr[i]==b)
			arr[i]=a;
		if(arr[i]==(-1))
			arr[i]=b;
	}
}
void Sudoku::changeRow(int a,int b)
{
	int temparr[27],i,j;
	for(i=0;i<27;i++)
		temparr[i]=0;
	if(a<0||b<0||a>2||b>2)
	{
		cout<<"error!enter again";
	}
	if((a==0&&b==1)||(a==1&&b==0))
	{
		for(i=0;i<27;i++)
		{
			temparr[i]=arr[i];
			arr[i]=arr[i+27];
			arr[i+27]=temparr[i];
		}
	}
	if((a==0&&b==2)||(a==2&&b==0))
	{
		for(i=0;i<27;i++)
		{
			temparr[i]=arr[i];
			arr[i]=arr[i+54];
			arr[i+54]=temparr[i];
		}
	}
	if((a==1&&b==2)||(a==2&&b==1))
	{
		for(i=0;i<27;i++)
		{
			temparr[i]=arr[i+27];
			arr[i+27]=arr[i+54];
			arr[i+54]=temparr[i];
		}
	}
}
void Sudoku::changeCol(int a,int b)
{
	int temp,i,j;
	if(a<0||b<0||a>2||b>2)
	{
		cout<<"error!enter again";
	}
	if((a==1&&b==0)||(a==0&&b==1))
	{
		for(i=0;i<9;i++)
		{
			for(j=0;j<3;j++)
			{
				temp=arr[9*i+j];
				arr[9*i+j]=arr[9*i+(j+3)];
				arr[9*i+(j+3)]=temp;
			}
		}
	}
	if((a==2&&b==0)||(a==0&&b==2))
	{
		for(i=0;i<9;i++)
		{
			for(j=0;j<3;j++)
			{
				temp=arr[9*i+j];
				arr[9*i+j]=arr[9*i+(j+6)];
				arr[9*i+(j+6)]=temp;
			}
		}
	}
	if((a==1&&b==2)||(a==2&&b==1))
	{
		for(i=0;i<9;i++)
		{
			for(j=0;j<3;j++)
			{
				temp=arr[9*i+(j+3)];
				arr[9*i+(j+3)]=arr[9*i+(j+6)];
				arr[9*i+(j+6)]=temp;
			}
		}
	}
}
void Sudoku::rotate(int n)
{
	int i,j=0,k=0,arr2[9][9],temp[size],temp2[9][9];
	if(n<0||n>100)
	{
		cout<<"error! enter again";
	}
	if(n==0||n%4==0)
	{
		for(i=0;i<81;i++)
			arr[i]=arr[i];
	}
	if(n%4==3)
	{
		for(i=0;i<81;i++)
		{
			arr2[j][k]=arr[i];
			k++;
			if(k>8)
			{
				j++;
				k=0;
			}
		}
		for(j=0;j<9;j++)
		{
			for(k=0;k<9;k++)
			{
				temp2[j][k]=arr2[j][k];
			}
		}
		for(j=0;j<9;j++)
		{
			for(k=0;k<9;k++)
			{
				arr2[j][k]=temp2[k][8-j];
				i=j*9+k;
				arr[i]=arr2[j][k];
			}

		}
	}
	if(n%4==2)
	{
		for(i=0;i<81;i++)
			temp[i]=arr[i];
		for(i=0;i<81;i++)
			arr[i]=temp[80-i];
	}
	if(n%4==1)
	{
		for(i=0;i<81;i++)
		{
			arr2[j][k]=arr[i];
			k++;
			if(k>8)
			{
				j++;
				k=0;
			}
		}
		for(j=0;j<9;j++)
		{
			for(k=0;k<9;k++)
			{
				temp2[j][k]=arr2[j][k];
			}
		}
		for(j=0;j<9;j++)
		{
			for(k=0;k<9;k++)
			{
				arr2[j][k]=temp2[8-k][j];
				i=j*9+k;
				arr[i]=arr2[j][k];
			}
		}
	}
}
void Sudoku::flip(int n)
{
	int i,j,k=0,temp[81],temp2[9][9],arr2[9][9];
	if(n<0||n>1)
	{
		cout<<"error!enter again";
	}
	if(n==0)
	{
		for(i=0;i<9;i++)
		{
			for(j=0;j<9;j++)
			{
				temp[k]=arr[(8-j)+9*i];
				k++;
			}
		}
		for(i=0;i<81;i++)
		{
			arr[i]=temp[i];
		}
	}
	if(n==1)
	{
		for(i=0;i<9;i++)
		{
			for(j=0;j<9;j++)
			{
				temp[k]=arr[(8-i)*9+j];
				k++;
			}
		}
		for(i=0;i<81;i++)
		{
			arr[i]=temp[i];
		}
	}
}
void Sudoku::change()
{
	srand(time(NULL));
	changeNum((rand()%9)+1,(rand()%9)+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip((rand()%2));
}
void Sudoku::printOut()
{
	int i;
	for(i=0;i<size;i++)
		printf("%d%c",arr[i],(i+1)%9==0?'\n':' ');
}
void Sudoku::transform()
{
	change();
	printOut();
}
