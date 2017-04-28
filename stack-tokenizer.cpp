//
//  main.cpp
//  HW7
//
//  Created by Anish Malhotra on 4/5/16.
//  Copyright © 2016 CS2134. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// This is code from Weiss
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>
using namespace std;

class Tokenizer
{
public:
    Tokenizer( istream & input )
    : currentLine( 1 ), errors( 0 ), inputStream( input ) { }
    
    // The public routines
    char getNextOpenClose( );
    string getNextID( );
    int getLineNumber( ) const;
    int getErrorCount( ) const;
    
private:
    enum CommentType { SLASH_SLASH, SLASH_STAR };
    
    istream & inputStream;     // Reference to the input stream
    char ch;                   // Current character
    int currentLine;           // Current line
    int errors;                // Number of errors detected
    
    // A host of internal routines
    bool nextChar( );
    void putBackChar( );
    void skipComment( CommentType start );
    void skipQuote( char quoteType );
    string getRemainingString( );
};


// nextChar sets ch based on the next character in
// inputStream and adjusts currentLine if necessary.
// It returns the result of get.
// putBackChar puts the character back onto inputStream.
// Both routines adjust currentLine if necessary.
bool Tokenizer::nextChar( )
{
    if( !inputStream.get( ch ) )
        return false;
    if( ch == '\n' )
        currentLine++;
    return true;
}

void Tokenizer::putBackChar( )
{
    inputStream.putback( ch );
    if( ch == '\n' )
        currentLine--;
}

// Precondition: We are about to process a comment;
//                 have already seen comment start token.
// Postcondition: Stream will be set immediately after
//                 comment ending token.
void Tokenizer::skipComment( CommentType start )
{
    if( start == SLASH_SLASH )
    {
        while( nextChar( ) && ( ch != '\n' ) )
            ;
        return;
    }
    
    // Look for */
    bool state = false;    // Seen first char in comment ender.
    
    while( nextChar( ) )
    {
        if( state && ch == '/' )
            return;
        state = ( ch == '*' );
    }
    cout << "Unterminated comment at line " << getLineNumber( ) << endl;
    errors++;
}

// Precondition: We are about to process a quote;
//                   have already seen beginning quote.
// Postcondition: Stream will be set immediately after
//                   matching quote.
void Tokenizer::skipQuote( char quoteType )
{
    while( nextChar( ) )
    {
        if( ch == quoteType )
            return;
        if( ch == '\n' )
        {
            cout << "Missing closed quote at line " << ( getLineNumber( ) - 1 ) << endl;
            errors++;
            return;
        }
        // If a backslash, skip next character.
        else if( ch == '\\' )
            nextChar( );
    }
}

// Return the next opening or closing symbol or '\0' (if EOF).
// Skip past comments and character and string constants.
char Tokenizer::getNextOpenClose( )
{
    while( nextChar( ) )
    {
        if( ch == '/' )
        {
            if( nextChar( ) )
            {
                if( ch == '*' )
                    skipComment( SLASH_STAR );
                else if( ch == '/' )
                    skipComment( SLASH_SLASH );
                else if( ch != '\n' )
                    putBackChar( );
            }
        }
        else if( ch == '\'' || ch == '"' )
            skipQuote( ch );
        else if( ch == '\\' )  // Extra case, not in text
            nextChar( );
        else if( ch == '(' || ch == '[' || ch == '{' ||
                ch == ')' || ch == ']' || ch == '}' )
            return ch;
    }
    return '\0';       // End of file
}

// Return current line number.
int Tokenizer::getLineNumber( ) const
{
    return currentLine;
}

// Return current line number.
int Tokenizer::getErrorCount( ) const
{
    return errors;
}

// Return indicates if ch can be part of a C++ identifier.
bool isIdChar( char ch )
{
    return ch == '_' || isalnum( ch );
}

// Return an identifier read from input stream.
// First character is already read into ch.
string Tokenizer::getRemainingString( )
{
    string result;
    
    for( result = ch; nextChar( ); result += ch )
        if( !isIdChar( ch ) )
        {
            putBackChar( );
            break;
        }
    
    return result;
}

// Return next identifier, skipping comments
// string constants, and character constants.
// Return "" if end of stream is reached.
string Tokenizer::getNextID( )
{
    while( nextChar( ) )
    {
        if( ch == '/' )
        {
            if( nextChar( ) )
            {
                if( ch == '*' )
                    skipComment( SLASH_STAR );
                else if( ch == '/' )
                    skipComment( SLASH_SLASH );
                else
                    putBackChar( );
            }
        }
        else if( ch == '\\' )
            nextChar( );
        else if( ch == '\'' || ch == '"' )
            skipQuote( ch );
        else if( !isdigit( ch ) && isIdChar( ch ) )
            return getRemainingString( );
    }
    return "";       // End of file
}

bool isOpeningSymbol(char token){
    if (token == '(' || token == '[' || token == '{')
        return true;
    return false;
}

struct Symbol
{
    char token;
    int  theLine;
};

class Balance
{
public:
    Balance( istream & is ):tok( is ),errors( 0 ){}
    
    // returns the number of mismatched parenthesis
    int checkBalance(){
        stack<Symbol> openClose;
        char openCloseToken = tok.getNextOpenClose();
        while(openCloseToken != '\0'){
            Symbol sym;
            sym.token = openCloseToken;
            sym.theLine = tok.getLineNumber();
            if(isOpeningSymbol(openCloseToken)){
                openClose.push(sym);
            }
            else{
                if(openClose.size() == 0){
                    cerr << "Stack is empty, but found a closing symbol at line " << tok.getLineNumber();
                    errors++;
                }
                else{
                    checkMatch(openClose.top(), sym);
                    openClose.pop();
                }
            }
            openCloseToken = tok.getNextOpenClose();
        }
        if(openClose.size() != 0){
            cerr << "Came to the end of the file, but stack isn't empty! Symbols were left unclosed!";
            errors++;
        }
        return errors;
    }
private:
    Tokenizer tok;
    int errors;
    void checkMatch( const Symbol & oParen, const Symbol & cParen ){
        if ((oParen.token == '(' && cParen.token == ')') || (oParen.token == '{' && cParen.token == '}') || (oParen.token == '[' && cParen.token == ']')) return;
        else{
            cerr << oParen.token << " at line " << oParen.theLine << " isn't closed, but a mismatching closer was found!";
            errors++;
        }
    }
};



int main(int argc, const char * argv[]) {
    //istringstream ifs("parencheck.cpp");
    //Balance bal(ifs);
    //cout << bal.checkBalance();
    return 0;
}
