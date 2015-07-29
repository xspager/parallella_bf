#include <stdlib.h>
#include <stdio.h>
#include "bf_vm.h"

#define STACK_LEVELS  32
// 16kb
#define MEM_SIZE     16 * 1024

typedef unsigned int u__int;


void run(char prog[], byte mem[], char output[])
{
	/* program vars */
	byte *p; /* Brain'sFuck Memory pointer */
	u__int i=0;
	byte *stack[STACK_LEVELS] = { 0 };
	u__int stack_l=0;

	/* BF vars */
	byte *pos;
	char *out = &output[0];

	p = prog; // program pointer point to program memory start
int out_i = 0;

	pos = &mem[0];

	while(*p){
		switch(*p){
			case '+': (*pos)++; break;
			case '-': (*pos)--; break;
			case '<': pos--; break;
			case '>': pos++; break;
			case '[':
				i=0;
				if(!*pos){
					while(*++p != ']' || i){
						switch(*p){
							case '[': i++; break;
							case ']': i--; break;
						}
					}
				}
				else{
					stack[++stack_l]=p;
					sprintf(output, "%i", stack_l);
				}
				break;
			case ']':
				if(stack_l > 0){
					p = stack[stack_l]-1;
					stack_l--;
				}
				else{
					sprintf(output, "Syntax error missed ]");
					exit(1);
				}
				break;
			case '.':
				output[out_i] = *pos; out++;
				break;
			//case ',': *pos = getchar();	break;
		}
		p++; out_i++;
	}
}

