#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char* program = ",[.[-],]";
int8_t cells[30000];
uint32_t cellpos = 0;

int getNewCellPos(uint8_t direction) {
	uint32_t newpos = cellpos + direction;
	if(cellpos < 0) {
		return sizeof(cells);
	} else if(cellpos > sizeof(cells)-1) {
		return 0;
	} else {
		return newpos;
	}
}

void main() {
	for(int i = 0; i < sizeof(cells); i++) {
		cells[i] = 0;
	}

	for(int i = 0; i < strlen(program); i++) {
		if(program[i] == '>') {
			cellpos = getNewCellPos(1);

		} else if(program[i] == '<') {
			cellpos = getNewCellPos(-1);

		} else if(program[i] == '+') {
			cells[cellpos]++;

		} else if(program[i] == '-') {
			cells[cellpos]--;

		} else if(program[i] == '.') {
			printf("%c", cells[cellpos]);

		} else if(program[i] == ',') {
			cells[cellpos] = getchar();

		} else if(program[i] == '[' && cells[cellpos] == 0) {
			bool foundMatch = false;
			uint32_t newpos = i;
			uint32_t innerloops = 0;
			while(foundMatch != true) {
				newpos++;
				if(program[newpos] == '[') {
					innerloops++;
				}
				if(program[newpos] == ']') {
					if(innerloops == 0) {
						foundMatch = true;
						//printf("[%i --> %i]\n", newpos, i);
						i = newpos;
					}else if(innerloops > 0) {
						innerloops--;
					}else{
						printf("Invalid innerloops value\n");
						return;
					}
				}
			}

		} else if(program[i] == ']' && cells[cellpos] != 0) {
			bool foundMatch = false;
			uint32_t newpos = i;
			uint32_t innerloops = 0;
			while(foundMatch != true) {
				newpos--;
				if(program[newpos] == ']') {
					innerloops++;
				}
				if(program[newpos] == '[') {
					if(innerloops == 0) {
						foundMatch = true;
						//printf("[%i <-- %i]\n", newpos, i);
						i = newpos;
					}else if(innerloops > 0) {
						innerloops--;
					}else{
						printf("Invalid innerloops value\n");
						return;
					}
				}
			}
		}
	}

	return;
}