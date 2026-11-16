#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void invalidcharcheck(const char *bin){
    int i;
    for(i=0;i<strlen(bin);i++){
        if(bin[i]!='0' && bin[i]!='1'){
            printf("Invalid char");
            exit(0); //completely terminates the program
        }
    }
    printf("/n");
}

void nrzlevel(const char *bin){
    int i;
    printf("nrz-encoding:");
    for(int i=0;i<strlen(bin);i++){
        if(bin[i]=='0')  printf(" | + ");
        else printf(" | - ");
    }
    printf("/n");
}

void nrzi(const char *bin){
    int curr=0;
    printf("IN NRZI");
    for(int i=0;i<strlen(bin);i++){
        if(bin[i]=='1') curr=1-curr;
        if(curr==1) printf(" | - ");
        else printf(" | + ");
    }
}

int main(void){
    char bin[100];
    printf("Enter bin data:");
    scanf("%s",bin);
    invalidcharcheck(bin);
    nrzlevel(bin);
    nrzi(bin);
    return 0;
}