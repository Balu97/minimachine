#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define MAXSIZE 500
#define ADDRESSES 65535

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

struct node{
	char *label;
	int address;
	struct node *next;
};

void list_append(struct node *list, struct node item)
{
	if(list->next == NULL){
		list->next = malloc(sizeof(struct node));
		*(list->next) = item;
	}else{
		list_append(list->next, item);
	}
}
void list_free(struct node *list)
{
	if(list->next == NULL){
		return;
	}else{
		list_free(list->next);
		return; 
	}
}

struct node pop_last(struct node *list)
{
	struct node tmp;
	if(list->next != NULL){
		if(list->next->next == NULL){
			tmp = *(list->next);
			free(list->next);
			list->next = NULL;
			return tmp;
		}else{
			return pop_last(list->next);
		}
	}else{
		tmp.address = -1;
		return tmp;
	}

}

struct node list_search(struct node *list, char label[20]){
	struct node tmp;
	struct node *tmp_ptr;
	if(list->next != NULL){
		if(!strcmp((*(list->next)).label, label)){
			tmp = *(list->next);
			tmp_ptr = list->next->next;
			free(list->next);
			list->next = tmp_ptr;
			return tmp;
		}else{
			return list_search(list->next, label);
		}
	}else{
		struct node n;
		n.address = -1;
		return n;
	}
}
int get_file(char filename[20], char *tokens[MAXSIZE])
{
	char line[255];
	char *cp;
	char *bp;
	FILE *fp = fopen("in.txt", "r");
	int i = 0;
	printf("open file\n");
	if(!fp){
		printf("Error opening file\n");
		exit(1);
	}
	while(fgets(line, sizeof(line), fp) != 0){
		bp = line;
		while(1){
			cp = strtok(bp, " \t\n");
			bp = NULL;

			if(cp == NULL){
				break;
			}
			tokens[i] = malloc(20);
			strcpy(tokens[i++], cp);
		}
	}
	fclose(fp);
	return i;
}

int getOpcode(char *token){

	if(!strcmp(token, "STORE"))return STORE;
	else if(!strcmp( token, "LOADI"))return LOADI;
	else if(!strcmp( token, "LOAD"))return LOAD;

	else if(!strcmp(token, "ADD"))return ADD;
	else if(!strcmp(token, "ADDI"))return ADDI;
	else if(!strcmp(token, "SUBI"))return SUBI;
	else if(!strcmp(token, "SUB"))return SUB;
	else if(!strcmp(token, "MULI"))return MULI;
	else if(!strcmp(token, "MUL"))return MUL;
	else if(!strcmp(token, "DIVI"))return DIVI;
	else if(!strcmp(token, "DIV"))return DIV;
	else if(!strcmp(token, "MODI"))return MODI;
	else if(!strcmp(token, "MOD"))return MOD;
	else if(!strcmp(token, "CMPI"))return CMPI;
	else if(!strcmp(token, "CMP"))return CMP;

	else if(!strcmp(token, "JMPP"))return JMPP;
	else if(!strcmp(token, "JMPNN"))return JMPNN;
	else if(!strcmp(token, "JMPN"))return JMPN;
	else if(!strcmp(token, "JMPNP"))return JMPNP;
	else if(!strcmp(token, "JMPZ"))return JMPZ;
	else if(!strcmp(token, "JMPNZ"))return JMPNZ;
	else if(!strcmp(token, "JMPV"))return JMPV;
	else if(!strcmp(token, "JMP"))return JMP;

	else if(!strcmp(token, "NOOP"))return NOOP;
	else if(!strcmp(token, "HOLD"))return HOLD;
	return -1;
	
}

void assemble(uint16_t memory[ADDRESSES], char *tokens[MAXSIZE], int count){
	int i;
	int pc = 0;
	char *p = NULL;
	long number;
	struct node labels;
	struct node labelusage;
	struct node tmp;
	struct node usage;
	int opcode;

	labels.next = NULL;
	labelusage.next = NULL;


	for(i = 0; i<count; i++){

		p = NULL;
		number = strtol(tokens[i], &p, 0);

		if(tokens[i][strlen(tokens[i])-1] == ':'){

			printf("label ");
			printf("%s\n", tokens[i]);

			tmp.next = NULL;
			tmp.label = tokens[i];
			tmp.label[strlen(tmp.label)-1] = 0;
			tmp.address = pc;
			list_append(&labels, tmp);

		}else if((opcode = getOpcode(tokens[i])) + 1){

			printf("Instruction ");
			printf("%s\n", tokens[i]);

			memory[pc++]=opcode;

			if(opcode == HOLD){
				printf("encountered HOLD, leave the next address be 0");
				pc++;
			}
		}else if(!(tokens[i][0]<='9' && tokens[i][0]>='0')){

			printf("labelusage ");
			printf("%s\n", tokens[i]);

			tmp.next = NULL;
			tmp.label = tokens[i];
			tmp.address = pc++;
			list_append(&labelusage, tmp);

		}else if(p){

			printf("Number ");
			printf("%s\n", tokens[i]);

			memory[pc++] = number;

		}
	}

	while(1){
		tmp = pop_last(&labels);
		if(tmp.address == -1){
			break;
		}
		while(1){
			usage = list_search(&labelusage, tmp.label);
			if(usage.address == -1){
				break;
			}
			memory[usage.address] = tmp.address;
		}
	}

	list_free(&labelusage);
}

void write_file(char filename[20], uint16_t memory[ADDRESSES]){
	FILE *fp = fopen(filename, "w");
	if(!fp){
		printf("Error opening outputfile");
		exit(1);
	}
	fwrite(memory, sizeof(uint16_t), ADDRESSES, fp);
	fclose(fp);
}

int main(){
	printf("DEBUG: Start of programm\n");
	int i, j;
	uint16_t  memout[ADDRESSES];
	char *tokens[MAXSIZE];
	j = get_file("in.txt", tokens);
	for(i=0; i<j; i++)printf("%s\n", tokens[i]);
	memset(&memout, 0, ADDRESSES*sizeof(uint16_t));
	assemble(memout, tokens, j);
	write_file("in.mm", memout);
	for(i=0; i<j; i++)free(tokens[i]);
	exit(0);
}
