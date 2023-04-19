/*
* 
* main.c
*
This is the main function for the decommenting implementation
use "gcc -o main main.c" command to run the program.
*/
#include <stdio.h>
#include <ctype.h>
#include "./decommenting/decomment.c"

int main()

{
    
enum statetype state = NORMAL;
enum status status = EXIT_SUCCESS;

ch = getchar ();

while(ch != EOF)
{
    switch(state){
        case NORMAL:
            state = normal(ch);
            break;
        case INCOMMENT:
            state = incomment(ch);
            break;
        case CHAR_LITERAL:
            state = charliteral(ch);
            break;
        case STRING_LITERAL:
            state = stringliteral(ch);
            break;
    }
    
    ch = getchar();
    i++;
}

str[i] ='\0';
printf("%s",str);

if(state == INCOMMENT){
    fprintf(stderr,"ERROR: line %d: unterminated comment\n",c_line);
    status = EXIT_FAILURE;
    return status;
}

return status;

}


