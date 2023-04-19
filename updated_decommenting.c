/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <ctype.h>

enum statetype {NORMAL, INCOMMENT, CHAR_LITERAL, STRING_LITERAL, DECOMMENTING};
enum status {EXIT_SUCCESS, EXIT_FAILURE};

char str[1024];
int ch;
int line = 1;
int c_line;
int i = 0;
enum statetype state;


enum statetype normal(int ch){
    if(str[i-1] == '/'){
        if(ch == '*'){
            i--;
            str[i] = ' ';
            state = INCOMMENT;
        }
        else{
            str[i] = ch;
        }
    }
    else if(ch == '/'){
        str[i] = ch;
        ch = getchar();
        if(ch == '*'){
            str[i] = ' ';
            c_line = line;
            state = INCOMMENT;
        }
        else if(ch == '/'){
            i++;
            str[i] = ch;
        }
        else if(ch == '\''){
            i++;
            str[i] = ch;
            state = CHAR_LITERAL;
        }
        else if(ch == '\"'){
            i++;
            str[i] = ch;
            state = STRING_LITERAL;
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
    
    return state;
}


enum statetype incomment(int ch){
    if(ch == '*'){
        ch = getchar();
        if(ch == '/'){
            i--;
            state = NORMAL;
        }
        else if(ch == '*'){
            ch = getchar();
            while(ch == '*'){
                ch = getchar();
            }
            if(ch == '/'){
                i--;
                state = NORMAL;
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
    }
    else if(ch == '\n'){
        str[i] = ch;
        line++;
    }
    else{
        i--;
    }
    
    return state;
}


enum statetype charliteral(int ch){
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
    return state;
}

enum statetype stringliteral(int ch){
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
    return state;
}


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
printf("\n%s",str);

if(state == INCOMMENT){
    printf("\nERROR: line %d: unterminated comment\n",c_line);
    return EXIT_FAILURE;
}

return EXIT_SUCCESS;

}
