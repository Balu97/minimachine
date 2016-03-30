#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define ADRESSES 65535

#define STORE 277
#define LOADI 532
#define LOAD 276

#define ADD 266
#define ADDI 522
#define SUBI 523
#define SUB 267
#define MULI 524
#define MUL 268
#define DIVI 525
#define DIV 269
#define MODI 526
#define MOD 270
#define CMPI 527
#define CMP 271

#define JMPP 286
#define JMPNN 287
#define JMPN 288
#define JMPNP 289
#define JMPZ 290
#define JMPNZ 291
#define JMPV 293
#define JMP 292

#define HOLD 99
#define RESET 1
#define NOOP 0

struct ram{
	uint16_t adresses[ADRESSES];
};

void get_file(char filename[20], struct ram *memmory)
{
	printf("open file\n");
	FILE *fp = fopen("in.mm", "rb");
	if(!fp){
		printf("Error opening file\n");
		exit(1);
	}
	memset(memmory->adresses, 0, ADRESSES * sizeof(uint16_t));
	fread(memmory->adresses, 2, ADRESSES, fp);
	fclose(fp);
}

void print_memory(struct ram *memmory)
{
	int i = 0;
	for(i = 0; i < ADRESSES; i++){
		if(i%10 == 0) printf("\n");
		printf("%04hx ", memmory->adresses[i]);
	}
}

int main(){
	unsigned short acc = 0;
	unsigned short pc = 0;
	unsigned ir = 0;
	unsigned ira = 0;
	unsigned short tmp = 0;
	int vf = 0;
	int nf = 0;
	int zf = 0;
	int holded = 0;
	printf("create mainMemory\n");
	struct ram mainMemmory;
	printf("getFile\n");
	get_file("hallo", &mainMemmory);
	// print_memory(&mainMemmory);
	while(!holded){
		ir = mainMemmory.adresses[pc];
		ira = mainMemmory.adresses[pc+1];

		printf("pc: %d, ir: %d, ira: %d\n", pc, ir, ira);
		switch(ir){
			case ADDI:	acc += ira;
					pc += 2;
					if(acc < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(acc == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;

			case ADD:	acc += mainMemmory.adresses[ira];
					pc += 2;
					if(acc < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(acc == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;

			case SUBI:	acc -= ira;
					pc += 2;
					if(acc < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(acc == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;

			case SUB:	acc -= mainMemmory.adresses[ira];
					pc += 2;
					if(acc < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(acc == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;

			case MULI:	acc *= ira;
					pc += 2;
					if(acc < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(acc == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;

			case MUL:	acc *= mainMemmory.adresses[ira];
					pc += 2;
					if(acc < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(acc == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;

			case MODI:	acc %= ira;
					pc += 2;
					if(acc < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(acc == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;

			case MOD:	acc %= mainMemmory.adresses[ira];
					pc += 2;
					if(acc < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(acc == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;

			case DIVI:	acc %= ira;
					pc += 2;
					if(acc < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(acc == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;

			case DIV:	acc %= mainMemmory.adresses[ira];
					pc += 2;
					if(acc < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(acc == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;


			case LOAD:	acc = mainMemmory.adresses[ira];
					pc += 2;
					if(acc < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(acc == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;

			case LOADI:	acc = ira;
					pc += 2;
					if(acc < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(acc == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;

			case STORE:	mainMemmory.adresses[ira] = acc;
					pc += 2;
					break;

			case CMP:	tmp = acc - mainMemmory.adresses[ira];
					pc += 2;
					if(tmp < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(tmp == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;

			case CMPI:	tmp = acc - ira;
					pc += 2;
					if(tmp < 0){
						nf = 1;
					}else{
						nf = 0;
					}
					if(tmp == 0){
						zf = 1;
					}else{
						zf = 0;
					}
					break;

			case JMP:	pc = ira;
					break;

			case JMPN:	if(nf) pc = ira;
					else pc += 2;
					break;

			case JMPNZ:	if(!zf) pc = ira;
					else pc += 2;
					break;

			case JMPNN:	if(!nf) pc = ira;
					else pc += 2;
					break;

			case JMPP:	if((!zf) || (!nf)) pc = ira;
					else pc += 2;
					break;

			case JMPZ:	if(zf) pc = ira;
					else pc += 2;
					break;
			case JMPNP:	if(zf || nf) pc = ira;
					else pc += 2;
					break;

			case HOLD:	printf("Holded: %40hx", acc);
					holded = 1;
					break;

			default:	printf("Unbekannte Instruction: %04hx, pc: %04hx, argument: %04hx", ir, pc, ira);
					exit(1);

		}
	}
}
