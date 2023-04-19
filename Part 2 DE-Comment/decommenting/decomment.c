/**
 * decomment.c
 *
 * This is the implementation file for the interfaces found in decomment.h.
 * This file implements decommenting a given file.
 * Specifically, it implements the functions declared
 * in the decomment.h file
 */
#include <stdio.h>
#include <ctype.h>
#include "decomment.h"

/*
this function is to define the program that is going to be used when 
the state becomes NORMAL and it returns a state to be executed next accordingly 
with the character or order of characters that it accepts.
*/
enum statetype normal(int ch){
    if(str[i-1] == '/'){
        if(ch == '*'){
            i--;
            str[i] = ' ';
            state = INCOMMENT;
        }
        else if(ch == '\n'){
            str[i] = ch;
            line++;
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
        else if(ch == '\n'){
            str[i] = ch;
            line++;
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
        else if(ch == EOF){
            return state;
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


/*
this function is to define the program that is going to be executed when 
the state becomes INCOMMENT and it returns NORMAL if the comment is finished
and INCOMMENT if the comment is unterminated.
*/
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
            else if(ch == '\n'){
                str[i] = ch;
                line++;
            }
            else if(ch == EOF){
                return state;
            }
            else{
                i--;
            }
        }
        else if(ch == '\n'){
            str[i] = ch;
            line++;
        }
        else if(ch == EOF){
            return state;
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


/*
this function is to define the program that is going to be executed when 
the state becomes CHAR_LITERAL and it returns NORMAL if it is closed
and CHAR_LITERAL if it is unterminated.
*/
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


/*
this function is to define the program that is going to be executed when 
the state becomes STRING_LITERAL and it returns NORMAL if it is closed
and STRING_LITERAL if it is unterminated.
*/
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