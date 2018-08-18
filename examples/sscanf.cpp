// Scanning words from a line of text
// Note: The %n in "%s%n" puts the current scan position in n
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

int main(){
    char Word[20],Line[]="This is a word from a line of text.";
    for(int n=0,m=0; m!=strlen(Line);m+=n){
        sscanf(&Line[m],"%s%n",Word,&n);
        cout << Word << endl;
    }
    return 0;
}

