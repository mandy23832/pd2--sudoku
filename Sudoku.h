#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
using namespace std;
class Sudoku{
	public:
		int giveQuestion();
		void readIn();
		void solve();
		int cor();
		void tryans();
		void moveforward();
        int smallpossible(int n);
		void changeNum(int a,int b);
		void changeRow(int a,int b);
		void changeCol(int a,int b);
		void rotate(int n);
		void flip(int n);
		void change();
		void printOut();
		void transform();
		static const int size=81;
	private:
		int a,b,n,arr[size];
		int place;
        int q[9][9];
        int tmpp;

};
