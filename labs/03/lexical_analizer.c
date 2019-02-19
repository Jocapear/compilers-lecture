#include <stdio.h>

void lexical_analizer(char* file_name){
	printf("%s\n", file_name);

	FILE *file;
	FILE *output;
	file = fopen(file_name, "r");
	output = fopen("lex.out", "w");

	int c;
	while((c = getc(file)) != EOF){
		if (c == '/'){
			c = getc(file);
			if ( c == '/')
			{
				c = getc(file);
				while(c != '\n'){
					c = getc(file);
				}
			}
		}else if (c == 'f')
		{
			fputs("floatdcl", output);
		}else if(c == 'i'){
			fputs("intdcl", output);
		}else if(c == '='){
			fputs("assign", output);
		}else if(c == 'p'){
			fputs("print", output);
		}else if(c == '-'){
			fputs("minus", output);
		}else if(c == '+'){
			fputs("plus", output);
		}else if(c == ' ' || c == '\n'){
			fputc(c, output);
		}else if(isdigit(c)){
			int isf = 0;
			c = getc(file);
			while(isdigit(c) || c == '.'){
				if (c == '.')
				{
					isf = 1;
				}
				c = getc(file);
			}
			if (isf)
			{
				fputs("fnum", output);
			}else{
				fputs("inum", output);
			}		
			fputc(c, output);
		}else{
			fputs("id", output);
		}
		
	}
	char s[1];
	s[0] = c;
	fclose(file);
	fclose(output);
}

int main(int argc, char **argv){
   
   if(argc < 2 || argc > 2 ){
   	printf("Can only receive one argument\n");
   }else{
   	lexical_analizer(argv[1]);
   }
    return 0;
}
