#include <stdio.h>
#include <stdbool.h>
#include <string.h>

float X_rs(int n){ // version recursive simple
    if (n==0){
        return 1;
    }
    float precedent=X_rs(n-1);
    return precedent+(2/precedent);
}

float X_i(int n){ //version iterative
    float res=1.0;
    for (int i=1; i<=n;i++){
        res+=2/res;
    }
    return res;
}
float X_sous_f(int n, float res){ //sous fonction pour la recursive terminale
    if (n==0){
        return res;
    }
    res+=2/res;
    X_sous_f(n-1,res);
}


float X_rtf(int n){ //version recursive terminale avec sous-fonctions
    float res=1;
    res=X_sous_f(n,res);
    return res;
}

void X_sous_p(int n, float *ptres){
    if (n==0){
        return;
    }
    *ptres+= 2/ (*ptres);
    X_sous_p(n-1,ptres);

}

float X_rtp(int n){
    float res=1;
    float *ptres=&res;
    X_sous_p(n, ptres);

}


int main(){
    printf("%f",X_rtp(3));
    return 0;
}
