 /*
Simple DFA recognition program.
DFA -- ((aa+b)*)ab(a*)b
*/
#include <stdio.h>

#define STATES	4	/* number of states */
#define SYMBOLS	2	/* number of symbols */

/*
State Tranisition Table 
*/
int ST_TAB[STATES][SYMBOLS] = {
	/* state A */{ 1, 0 },
	/* state B */{ 0, 2 },
	/* state C */{ 2, 3 },
	/* state D */
};

void put_table(int tab[][SYMBOLS], int m, int n)
{
	int i;

	puts("State Transition Table");
	puts("\ta\tb");
	for (i = 0; i < m; i++) {
		if (i == 0 || i == 1 || i == 2) {
			printf("%c\t%c\t%c\n",
				'A' + i, 'A' + tab[i][0], 'A' + tab[i][1]);
		}
		else {
			printf("%c\t%c\t%c\n",
				'D', ' ' ,' ');
		}
	}
	puts("Final states = { D }");
}

void main()
{
	int ch;	/* input symbol */
	int cur_state = 0;	/* start state */

	put_table(ST_TAB, STATES, SYMBOLS);

	ch = getchar();
	while (ch != '\n') {
		cur_state = ST_TAB[cur_state][ch - 'a'];
		if (cur_state < 0) { puts("NO"); return; }
		ch = getchar();
	}

	if (cur_state == 3) puts("YES");	/* final states = { 3 } */
	else puts("NO");
	system("pause");
	return 0;
}
