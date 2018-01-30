
/*LIST -> LIST , ELEMENT

  LIST -> ELEMENT

  ELEMENT -> a


  --Recursive descent--
  List -> L , List¡¯ -> B , Element -> E ,  ¡® , ¡¯ -> c

  L -> EB
  B -> cEB | epsilon
  E -> a  


*/
#include <stdio.h>
#define END '\n'
char ch;
int errflag = 0;

void error()
{
	if (!errflag) {
		puts("FAIL");
		errflag = 1;
	}}

void pa()
{
	if (ch == 'a')
		ch = getchar();
	else error();
}

void pc()
{
	if (ch == ',')
		ch = getchar();
	else error();
}


void pL();
void pB();
void pE();

void pL()
{
	if (ch == 'a') {
		pE(); pB();
	}
	else error();
}

void pE()
{
	if (ch == 'a') {
		pa();
	}
}
void pB()
{
	if (ch == ',') {
		pc(); pE(); pB();
	}
	else if (ch =='$') {
		;
	}
	else error();
}


print_rules()
{
	puts("Production Rules:");
	puts("\tL -> EB");
	puts("\tB -> cEB");
	puts("\tB -> epsilon");
	puts("\tE -> a");
}

void main()
{
	print_rules();   // production rules
	printf("Input string = ");

	ch = getchar();   
	pL();
	if (!errflag && (ch == END || ch == '$')) puts("OK");
	else error();
	system("pause");
	return 0;
}