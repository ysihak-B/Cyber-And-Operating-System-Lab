/**
 * decomment.h
 *
 * This is the header file. It contains the interfaces for the decommenting implementation.
 * Specifically, it contains the enum statetype and status 
 * and the function declarations.
 */

// this enum is used to define the different states
enum statetype {NORMAL, INCOMMENT, CHAR_LITERAL, STRING_LITERAL};

// this is used to the exit status of the program
enum status {EXIT_SUCCESS, EXIT_FAILURE};

// the following are global variables which is going to be used through out the whole program

// this is the array that is used to store the characters that are found out of comment.
char str[1024];
// this the declaration for the character that is going to be read.
int ch;
// this variable is used to count the line number starting from one.
int line = 1;

/* this variable is used to keep track of the line number at which the comment begines
so that we can find the line number for the unterminated comment.
*/
int c_line;
// initializing i as astarting index of the array
int i = 0;
enum statetype state;
enum status status;


/*
this function is to define the program that is going to be used when 
the state becomes NORMAL and it returns a state to be executed next accordingly 
with the characters that it accepts.
*/
enum statetype normal(int ch);


/*
this function is to define the program that is going to be executed when 
the state becomes INCOMMENT and it returns NORMAL if the comment is finished
and INCOMMENT if the comment is unterminated.
*/
enum statetype incomment(int ch);


/*
this function is to define the program that is going to be executed when 
the state becomes CHAR_LITERAL and it returns NORMAL if it is closed
and CHAR_LITERAL if it is unterminated.
*/
enum statetype charliteral(int ch);


/*
this function is to define the program that is going to be executed when 
the state becomes STRING_LITERAL and it returns NORMAL if it is closed
and STRING_LITERAL if it is unterminated.
*/
enum statetype stringliteral(int ch);