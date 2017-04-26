#define _XOPEN_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

void get_salt( char salt[], char hash[] );
bool crack( char hash[] );
bool guessCase( char guess[], char hash[], char salt[] );
void toLower( char word[] );
void toUpper( char word[] );
bool checkAnswer( char guess[], char crypted[], char hash[] );
bool checkEveryLetter( char hash[], char salt[], int length );


int main( int argc, string argv[] )
{
    
    if (argc != 2)
    {
        printf("missing command-line argument\n");
        return 1;
    }
    string input;
    char hash[255];
    
    input = argv[1]; //Gets second value as hashed password
    strcpy( hash, input );
    crack( hash );
    return 0;
    
}

//Gets the first two characters (salt) of passed hash
void get_salt( char salt[], char hash[] )
{
    strncpy(salt, hash,2);
}

bool crack( char hash[] )
{
    char salt[3];
    get_salt( salt, hash );
    bool cracked = checkEveryLetter( hash, salt, 1 );
    
    return cracked;
    
}

bool guessCase( char guess[], char hash[], char salt[] )
{
    char crypted[255];
    toLower(guess);
    strcpy( crypted, crypt( guess, salt ) );
    if( checkAnswer( guess, crypted, hash ) )
    {
        return true;
    }
    
    for( int i = 0, length = strlen( guess ); length > i; i++ )
    {
        
        toLower( guess ); //rest to lower
        guess[i] = toupper( guess[i] );
        strcpy( crypted, crypt( guess, salt ) );
        if( checkAnswer( guess, crypted, hash ) )
        {
            return true;
        }
    }
    
    for( int i = 0, length = strlen( guess ); length > i; i++ )
    {
        toUpper( guess ); //rest to lower
        guess[i] = tolower( guess[i] );
        strcpy( crypted, crypt( guess, salt ) );
        if( checkAnswer( guess, crypted, hash ) )
        {
            return true;
        }
    }
    
    toUpper( guess );
    strcpy( crypted, crypt( guess, salt ) );
    if( checkAnswer( guess, crypted, hash ) )
    {
        return true;
    }
    
    return false;
}

// Loops through word until null terminator and lowercases everything
void toLower( char word[] )
{
    for( int i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }
}

// Loops through word until null terminator and uppercases everything
void toUpper( char word[] )
{
    for( int i = 0; word[i]; i++){
        word[i] = toupper(word[i]);
    }
}

bool checkAnswer( char guess[], char crypted[], char hash[] )
{
    if( strcmp(crypted, hash) == 0 )
    {
        printf( "RIGHT!!!!%s\n", guess );
        return true;
    }
    return false;
}

bool checkEveryLetter( char hash[], char salt[], int length )
{
    char guess[length + 1];
    guess[length] = '\0';
    
    // Make all of the characters of guess A
    for( int i = 0; i < length; i++ )
    {
        guess[i] = 'A';
    }
    
    //Loop through each character of guess starting with the last
    for( int j = length - 1; j >= 0; j-- )
    {
        while( guess[j] != 'Z' ) //While the current character is not Z
        {
            if( j != length - 1 ) // If the current character is not the last character
            {
                guess[j] = guess[j] + 1; // Current character becomes the next letter in the alphabet.
                j = j + 2; // For loop subs at end of cycle so add 2 to get it to the next lowest
                guess[j - 1] = 'A';
                break;
            }
            if( guessCase( guess, hash, salt ) )
            {
                return true;
                printf( "RIGHT!!!!%s\n", guess );
            }
            guess[j] = guess[j] + 1; // Current character becomes the next letter in the alphabet.
        }
    }
    
    return checkEveryLetter( hash, salt, length + 1 );
    
}