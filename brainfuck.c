#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern void term_putchar(char c);
extern size_t strlen(const char* str);

//char* program = ",[.[-],]";
char* program = "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.++++++++++++++++++++++++++++++++++++++.---------------------.++++++++++.---------.++++++++++++++++++++.";
uint8_t cells[30000];
uint32_t cellpos = 0;

int getNewCellPos(uint8_t direction) {
	int32_t newpos = cellpos + direction;
	uint32_t newpos2 = cellpos + direction;
	if(newpos < 0) {
		return sizeof(cells);
	} else if(newpos2 > sizeof(cells)-1) {
		return 0;
	} else {
		return newpos;
	}
}

void brainfuck_main() {
	for(uint32_t i = 0; i < sizeof(cells); i++) {
		cells[i] = 0;
	}

	for(uint32_t i = 0; i < strlen(program); i++) {
		if(program[i] == '>') {
			// Go up one cell
			cellpos = getNewCellPos(1);

		} else if(program[i] == '<') {
			// Go down one cell
			cellpos = getNewCellPos(-1);

		} else if(program[i] == '+') {
			// Increase number in cell
			cells[cellpos]++;

		} else if(program[i] == '-') {
			// Decrease number in cell
			cells[cellpos]--;

		} else if(program[i] == '.') {
			// Print number in cell
			term_putchar(cells[cellpos]);

		} else if(program[i] == ',') {
			// Get input character
			//cells[cellpos] = getchar();

		} else if(program[i] == '[' && cells[cellpos] == 0) {
			// If the beginning of a loop and the cell content is zero
			// Set some useful values
			bool foundMatch = false;
			uint32_t newpos = i;
			uint32_t innerloops = 0;
			while(foundMatch != true) {
				// Loop until a proper match is found
				newpos++;
				if(program[newpos] == '[') {
					// Detect a nested loop
					innerloops++;
				}
				if(program[newpos] == ']') {
					// Detect loop end bracket
					if(innerloops == 0) {
						// If no inner loops, we've hit the bracket we need
						foundMatch = true;
						//printf("[%i --> %i]\n", newpos, i);
						i = newpos;
					}else if(innerloops > 0) {
						// Detected the end of an inner loop, keep going
						innerloops--;
					}else{
						// Our loop counter went below 0 somehow
						//printf("Invalid innerloops value\n");
						return;
					}
				}
			}

		} else if(program[i] == ']' && cells[cellpos] != 0) {
			// If the end of a loop and the cell content is not zero, keep loop going
			// Set some useful values
			bool foundMatch = false;
			uint32_t newpos = i;
			uint32_t innerloops = 0;
			while(foundMatch != true) {
				// Loop until matching bracket is found
				newpos--;
				if(program[newpos] == ']') {
					// We've detected an inner loop and must keep track
					innerloops++;
				}
				if(program[newpos] == '[') {
					// Detected beginning bracket for loop
					if(innerloops == 0) {
						// If no more inner loops, we've hit the one we need
						foundMatch = true;
						//printf("[%i <-- %i]\n", newpos, i);
						i = newpos;
					}else if(innerloops > 0) {
						// Detected beginning of an inside loop, keep going
						innerloops--;
					}else{
						// Loop counter somehow hit negatives
						//printf("Invalid innerloops value\n");
						return;
					}
				}
			}
		}
	}

	return;
}