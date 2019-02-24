%{
#include <stdio.h>
%}

%%
(" ")+  printf(" ");
f   printf("floatdcl");
i   printf("intdcl");
p   printf("print");
[a-eghj-oq-z]   printf("id");
([0-9]+)    printf("inum");
([0-9]+"."[0-9]+)   printf("fnum");
"=" printf("assign");
"+" printf("plus");
"-" printf("minus");
"*" printf("mul");
"/" printf("div");
"\n" printf("\n");
(\/\/.*)    printf("COMMENT\n");
%%
