/*
DFA by goto statement.

Regular expression for " ((aa+b)*)ab(a*)b ".
*/
#include <stdio.h>

#define NO 0;
#define YES 1;

int ch;

int dfa()
{
	ch = getchar();
A:
	if (ch == 'a') {
		ch = getchar();
		goto B;
	}
	else if (ch == 'b') {
		ch = getchar();
		goto A;
	}
	else return NO;
B:
	if (ch == 'a') {
		ch = getchar();
		goto A;
	}
	else if (ch == 'b') {
		ch = getchar();
		goto C;
	}
	else return NO;
C:
	if (ch == 'a') {
		ch = getchar();
		goto C;
	}
	else if (ch == 'b') {
		ch = getchar();
		goto D;
	}
	else return NO;

D:
	if (ch == '\n') {
		return YES;
	}
	else return NO;

}

main()
{
	if (dfa())
		puts("YES");
	else puts("NO");
	system("pause");
	return 0;

}
