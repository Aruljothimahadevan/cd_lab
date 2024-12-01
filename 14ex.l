%{
#include <stdio.h>
int vowels = 0;  // Count of vowels
int consonants = 0;  // Count of consonants
%}
%%
[aeiouAEIOU]    { vowels++; }   // Count vowels
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z]   { consonants++; }  // Count consonants
.|\n    { }  // Ignore other characters (like punctuation and spaces)
%%
int main() {
    printf("Enter a string: ");
    yylex();  // Perform lexical analysis
    printf("Total vowels: %d\n", vowels);
    printf("Total consonants: %d\n", consonants);
    return 0;
}
