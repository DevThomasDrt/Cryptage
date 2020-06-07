/*
                         
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
 
#define MAX_SIZE 256
 
const wchar_t accents[54]= L"ÀÁÂÃÄÅàáâãäåÒÓÔÕÖØòóôõöøÈÉÊËèéêëÌÍÎÏìíîïÙÚÛÜùúûüÿÑñÇç";
const wchar_t sans_accents[54]= L"AAAAAAaaaaaaOOOOOOooooooEEEEeeeeIIIIiiiiUUUUuuuuyNnCc";
 
int verifierAlphanumerique(wchar_t* str){
    int i = 0;
    while( i < wcslen(str)-1 && iswalpha(str[i]) ) i++;
    return i == (wcslen(str)-1);
}
 
 
void convertirAccents(wchar_t* str){
    size_t index1;
    size_t index2;
    while((index1 = wcscspn(str, accents)) != wcslen(str)){
        index2 = wcscspn(accents, str);
        str[index1]=sans_accents[index2];
    }
}
 
int mod(int a, int b){
    int r = a % b;
    return r < 0 ? r + b : r;
}
 
void chiffrerC(int key, wchar_t* message){
     for( int i = 0; i < wcslen(message)-1; i++){
         message[i] = mod((( message[i]-97) + key ), 26) + 97;
     }
}
 
 
void dechiffrerC(int key, wchar_t* message){
     for( int i = 0; i < wcslen(message)-1; i++){
       message[i] = mod((( message[i]-97) - key ), 26) + 97;
     }
}
 
 
void chiffrerV(const wchar_t* key, wchar_t* message){
   int j=0;
   for (int i=0; i < wcslen(message)-1; i++){
        message[i] = mod(((message[i] - 97) + (key[j] - 97)), 26) + 97;
        j=(j+1)% (wcslen(key));
   }
}
 
 
void dechiffrerV(const wchar_t* key, wchar_t* message){
    int j=0;
    for (int i=0; i < wcslen(message)-1; i++){
        message[i] = mod(((message[i] - 97) - (key[j] - 97)), 26)+ 97;
        j=(j+1)%(wcslen(key));
   }
}
 
 
int main(int argc, char* argv[])
{
 
    setlocale(LC_ALL, "");
    wchar_t msg[MAX_SIZE] = {0};
    wchar_t msg_trimmed[MAX_SIZE] = {0};
 
    wprintf(L"Saisissez le message: \n");
    fgetws(msg, MAX_SIZE, stdin);
   
 
    if(!verifierAlphanumerique(msg)){
        wprintf(L"Le message contient des caracteres speciaux\n");
        exit(1);
    }
 
    for(int i = 0; i < wcslen(msg)-1; i++)msg[i]=towlower(msg[i]);
    convertirAccents(msg);
    wcscpy(msg_trimmed, msg);
    wprintf(L"Message saisi: %ls\n", msg_trimmed);
    fflush(stdin);
 
    int choix_algo=0;
    int choix_operation=0;
 
    wprintf(L"Algorithme: \n1.Cesar\n2.Vigenere\n");
    wscanf(L"%d", &choix_algo);
    wprintf(L"Operation: \n1.Chiffrer\n2.Dechiffrer\n");
    wscanf(L"%d", &choix_operation);
 
    if ((choix_algo != 1 && choix_algo != 2) || (choix_operation != 1 && choix_operation != 2)){
        wprintf(L"Choix invalides !\n");
        exit(2);
    }
 
    if(choix_algo == 1){
        int key=0;
        wprintf(L"Key (nombre entier):\n");
        wscanf(L"%d", &key);
        (choix_operation == 1)?chiffrerC(key, msg_trimmed):dechiffrerC(key, msg_trimmed);
    }
 
    if(choix_algo == 2){
        wchar_t key[MAX_SIZE] = {0};
        wprintf(L"Key (mot alphanumerique):\n");
        wscanf(L"%ls", key);
        if(!verifierAlphanumerique(key)){ wprintf(L"la cle contient des caracteres speciaux"); exit(3);}
        for( int i = 0; i < MAX_SIZE; i++)
            key[i] = tolower(key[i]);
        convertirAccents(key);
        (choix_operation == 1)?chiffrerV(key, msg_trimmed):dechiffrerV(key, msg_trimmed);
    }
 
    wprintf(L"Resultat : %ls\n", msg_trimmed);
    exit(0);
}