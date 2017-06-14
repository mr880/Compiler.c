/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Spring 2017                              *
 *  Author: Ulrich Kremer                    *
 *  Student Version                          *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int reg[100];
int offset[100];

int regUsed = 0;
int offUsed = 0;

int main(){
	
	Instruction *head;

	head = ReadInstructionList(stdin);

	if(!head){
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	head->critical = 1;

	Instruction *curr;
	curr = head;
	curr = LastInstruction(curr);

	
	while(curr != head){

/////////////////////////////////////////////////////////

		/*LOADI*/
		if(curr->opcode == LOADI){
			int i=0;
			int check = 0;

			for(i=0; i<100; i++){
				if(reg[i]==curr->field2)
					check = 1;
			}
			//reset var for reuse
			i = 0;
			if(check == 1){
				offset[offUsed] = curr->field1;
				offUsed++;
				
				curr->critical = 1;
			}
			else{
				curr->critical = 0;
			}
			//reset check for later use
			check = 0;
		}

/////////////////////////////////////////////////////////


		/*LOADAI*/
		else if(curr->opcode == LOADAI){
			int j=0;
			int check2 = 0;
			
			for(j=0; j<100; j++){
				if(reg[j]==curr->field2)
					check2 = 1;
			}
			//reset var for reuse
			j=0;
			if(check2 == 1){
				
				offset[offUsed] = curr->field1;
				offUsed++;	
				
				curr->critical = 1;

			}
			else{
				curr->critical = 0;
			}
			//reset check for later use
			check2 = 0;
		}


/////////////////////////////////////////////////////////

		/*STOREAI*/
		else if(curr->opcode == STOREAI){
			int k = 0;
			int check3 = 0;

			for(k=0;k<100;k++){
				if(offset[k]==curr->field1){
					check3 = 1;
				}
			}
			k = 0;
			if(check3 == 1){
				
				reg[regUsed] = curr->field2;	
				regUsed++;


				int x = 0;
				for(x=0; x<100; x++){
					if(offset[x]==curr->field1){
						offset[x]=-1;
					}
				}
				//reset var for reuse
				x=0;

				curr->critical = 1;				
			}
			else{
				curr->critical = 0;
			}
			//reset check for later use
			check3 = 0;
		}


/////////////////////////////////////////////////////////



		/*ADD, SUB, MUL, DIV*/
		else if(curr->opcode == ADD||curr->opcode == SUB||curr->opcode == MUL||curr->opcode == DIV){
			int l = 0;
			int check4 = 0;

			for(l=0; l<100; l++){
				if(reg[l]==curr->field3)
					check4 = 1;
			}
			//reset var for reuse
			l = 0;
			if(check4 == 1){

				reg[regUsed] = curr->field1;
				regUsed++;
				reg[regUsed] = curr->field2;
				regUsed++;			
							
				curr->critical = 1;
			}
			else{
				curr->critical = 0;
			}
			//reset check for later use
			check4 = 0;
		}



/////////////////////////////////////////////////////////




		/*OUTPUTAI*/
		else if(curr->opcode == OUTPUTAI){
			offset[offUsed]=curr->field1;
			curr->critical = 1;
		}



/////////////////////////////////////////////////////////



		/*ERROR*/
		else{
			ERROR("Check opcode\n");
			exit(EXIT_FAILURE);
		}


/////////////////////////////////////////////////////////

		curr = curr->prev;

	}
	
	/////
	if (head) 
		PrintInstructionList(stdout, head);

	while(head->next){
		curr = head;
		head = head->next;
		free(curr);
	}

	free(head);

	return EXIT_SUCCESS;
}

