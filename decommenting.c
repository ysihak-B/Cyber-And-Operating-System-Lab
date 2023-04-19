/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <ctype.h>

enum statetype {NORMAL, INCOMMENT, CHAR_LITERAL, STRING_LITERAL, DECOMMENTING};
enum status {EXIT_SUCCESS, EXIT_FAILURE};

int main()

{

char str[1024], ch;
int line = 1;
int c_line;
int i = 0;

printf("Enter a string: ");


enum statetype state = NORMAL;
enum status status = EXIT_SUCCESS;
ch = getchar ();
while(ch != EOF)

{
    switch(state){
        case NORMAL:
            if(ch == '/'){
                str[i] = ch;
                ch = getchar();
                if(ch == '*'){
                    str[i] = ' ';
                    c_line = line;
                    state = INCOMMENT;
                }
                else if(ch == '/'){
                    i++;
                    continue;
                }
                else{
                    i++;
                    str[i] = ch;
                }
            }
            else if(ch == '\''){
                str[i] = ch;
                state = CHAR_LITERAL;
            }
            else if(ch == '\"'){
                str[i] = ch;
                state = STRING_LITERAL;
            }
            else if(ch == '\n'){
                str[i] = ch;
                line++;
            }
            else{
                str[i] = ch;
            }
            break;
        case INCOMMENT:
            if(ch == '*'){
                ch = getchar();
                if(ch == '/'){
                    i--;
                    state = NORMAL;
                }
                else if(ch == '*'){
                    continue;
                }
                else if(ch == '\n'){
                    str[i] = ch;
                    line++;
                }
                else{
                    i--;
                }
            }
            else if(ch == '\n'){
                str[i] = ch;
                line++;
            }
            else{
                i--;
            }
            break;
        case CHAR_LITERAL:
            if(ch == '\''){
                str[i] = ch;
                state = NORMAL;
            }
            else if(ch == '\n'){
                str[i] = ch;
                line++;
            }
            else{
                str[i] = ch;
            }
            break;
        case STRING_LITERAL:
            if(ch == '\"'){
                str[i] = ch;
                state = NORMAL;
            }
            else if(ch == '\n'){
                str[i] = ch;
                line++;
            }
            else{
                str[i] = ch;
            }
            break;
    }
    
    
    ch = getchar();
    i++;
}

str[i] ='\0';

printf("\n\nEntered string is:\n\n%s",str);

if(state == INCOMMENT){
    printf("ERROR: line %d: unterminated comment\n",c_line);
}

return state;

}
