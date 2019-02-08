#include <stdio.h>

int syntax_analysis(char *file_name){
	FILE *file;
	char ch;
	file = fopen(file_name, "r");

	int pcounter = 0; // ()
	int bcounter = 0; // []
	int brcounter = 0; // {}
	int qtracker = 0; // "
	int sqtracker = 0; // ''
	int ctracker = 0; // //\n 
	
	int errors = 0;

	int line = 1;

	while( (ch = getc(file)) != EOF ) {
		if (ch == '\n'){
			if(ctracker >= 2){
				ctracker = 0;
			}else if(qtracker){
				printf("Quotes opened but not closed in line %d\n", line);
				errors++;
				qtracker = 0;
			}else if (sqtracker){
				printf("Single quotes opened but not closed in line %d\n", line);
				errors++;
				sqtracker = 0;
			}
			
			line++;
		}else if(ch == '/'){
			ctracker++;
		}else if (ch == '"') {
			if (qtracker){
				qtracker--;
			}else
			{
				qtracker++;
			}		
		}else if (ch == '\''){
			if (sqtracker) {
				sqtracker--;
			}else{
				sqtracker++;
			}
		}else if (ctracker < 2 || !qtracker || !sqtracker){
			ctracker = 0;
			if (ch == '('){
				pcounter++;
			}else if(ch == ')'){
				if (pcounter == 0){
					printf("There is a missing '(' in line %d\n", line);
					errors++;
				}else{
					pcounter--;	
				}
			}else if(ch == '['){
				bcounter++;
			}else if(ch == ']'){
				if (bcounter == 0){
					printf("There is a missing '[' in line %d\n", line);
					errors++;
				}else{
					bcounter--;
				}
			}else if(ch == '{'){
				brcounter++;
			}else if(ch == '}'){
				if (brcounter == 0){
					printf("There is a missing '{' in line %d\n", line);
					errors++;
				}else{
					brcounter--;
				}
			}
		}
	}
	if (pcounter) {
		printf("%d parenthesis opened but not closed\n", pcounter);
		errors += pcounter;
	}
	if (bcounter) {
		printf("%d brackets opened but not closed\n", bcounter);
		errors += bcounter;
	}
	if (brcounter) {
		printf("%d braces opened but not closed\n", brcounter);
		errors += brcounter;
	}
	
	if(errors){
		printf("%d errors found\n", errors);
	}else
	{
		printf("No errors found\n");
	}

	fclose(file);
}


int main(int argc, char *argv[]){
	if( argc == 2 ) {
		syntax_analysis(argv[1]);
   }
   else if( argc > 2 ) {
    	printf("Too many arguments supplied.\n");
   }
   else {
    	printf("My compiler - A01113339\nFile name expected\n");
   }
   return 0;
}
