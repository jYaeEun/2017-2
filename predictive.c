/*

LIST -> LIST , ELEMENT

LIST -> ELEMENT

ELEMENT -> a

--Predictive parser--

LIST -> A  , List¡¯ -> B  , Element -> C ,  ¡®,¡¯ ->b

A -> CB
B -> bCB | epsilon
C -> a

*/
#include <stdio.h>
#include <string.h>

#define NONTERMINALS 3
#define TERMINALS 2
#define RULESIZE 4
#define MAX 100

#define INPUT_END_MARK ('a'+TERMINALS)
#define STACK_BOTTOM_MARK '_'

char create_rule[RULESIZE][MAX];
int parsing_table[NONTERMINALS][TERMINALS + 1];
char stack[999];
int top;
void changevalue(char *input)
{
	int length = strlen(input);
	for (int i = 0; i < length; i++) {
		if (*input == ',') {
			*input = 'b';
		}
		input++;
	}
}

void input_data(char *str)
{
	int len;

	printf("Input : ");
	scanf("%s", str);
	len = strlen(str);
	str[len] = INPUT_END_MARK;
	str[len + 1] = 0;
	printf("Input string : %s (%c is an endig mark)\n", str, INPUT_END_MARK);
	changevalue(str);
}

void load_create_rule()
{
	strcpy(create_rule[0], "CB");
	strcpy(create_rule[1], "bCB");
	strcpy(create_rule[2], "");
	strcpy(create_rule[3], "a");
}


void load_parsing_table()
{
	parsing_table[0][0] = 0;
	parsing_table[1][1] = 1;
	parsing_table[1][2] = 2;
	parsing_table[2][0] = 3;
}
void check_table()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			parsing_table[i][j] = -1;
		}
	}
}

char stack_top()
{
	return stack[top - 1];
}

void push(char ch)
{
	stack[top++] = ch;
}

void pop()
{
	top--;
}

void init_stack()
{
	top = 0;
	push(STACK_BOTTOM_MARK);
	push('A');
}

int is_nonterminal(char ch)
{
	if ('A' <= ch && ch <= 'Z') return 1;
	else return 0;
}

int is_terminal(char ch)
{
	return (is_nonterminal(ch) == 0);
}

void predictive_parsing(int table[NONTERMINALS][TERMINALS + 1], char rule[RULESIZE][MAX], char *input)
{
	char *p = input;
	char *str_p;
	int i, index = 0, len;

	while (1) {
		if (stack_top() == STACK_BOTTOM_MARK) {
			if (*p == INPUT_END_MARK)
				printf("[accept]\n");	// parsing OK
			else printf("[error] -- Input is not empty!\n");
			return;
		}

		if (is_terminal(stack_top())) {	// pop -- terminal symbol
			if (*p == stack_top()) {
				pop();
				p++;
			}
			else {
				printf("[error] -- Stack is not empty!\n");
				return;
			}
		}
		else { // expand -- nonterminal
			index = parsing_table[stack_top() - 'A'][*p - 'a'];
			if (index != -1) {
				str_p = rule[index];
				len = strlen(str_p);
				printf("[CFG %d] %c -> %s\n", index, stack_top(), str_p);
				pop();
				for (i = len - 1; i >= 0; i--) {
					push(str_p[i]);
				}
			}
			else { // error
				printf("[error] %c -> %c\n", stack_top(), *p);
				return;
			}
		}
	}
}

int main()
{
	char input[100];

	load_create_rule();
	check_table();
	load_parsing_table();

	input_data(input);
	init_stack();

	predictive_parsing(parsing_table, create_rule, input);
	system("pause");
	return 0;
}
