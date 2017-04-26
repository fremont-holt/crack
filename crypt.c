#define _XOPEN_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

int main( int argc, string argv[] )
{
    
    if (argc != 2)
    {
        printf("missing command-line argument\n");
        return 1;
    }
    string input;
    
    input = argv[1]; //Gets second value as hashed password
    
    printf( "%s %s\n", input, crypt( input, "50" ) );
    return 0;
    
}