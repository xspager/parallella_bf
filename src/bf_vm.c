#include <stdlib.h>
#include <stdio.h>
#include "bf_vm.h"

#define STACK_LEVELS  32
// 16kb
#define MEM_SIZE     16 * 1024

typedef unsigned int u__int;


void run(byte prog[], byte mem[], byte output[])
{
	/* program vars */
	byte *p; /* Brain'sFuck Memory pointer */
	u__int i=0;
	byte *stack[STACK_LEVELS] = { 0 };
	u__int stack_l=0;

	/* BF vars */
	byte *pos;
	byte *out = output;

	p = prog; // program pointer point to program memory start

	pos = mem;

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
				*out = *pos; out++;
				break;
			//case ',': *pos = getchar();	break;
		}
		p++;
	}
}

