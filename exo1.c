#include <stdio.h>
#include <stdbool.h>
#include <string.h>

float e(int borne_inf,int borne_sup,unsigned long int produit,float somme){
	if( borne_sup == borne_inf){
		return 1.0/(borne_sup*produit) + somme;
	}else if(borne_inf==0 || borne_inf==1){
		return e(borne_inf+1, borne_sup, produit, somme+1.0);
	}else{
		return e(borne_inf+1, borne_sup, produit*borne_inf, somme+(1.0/(produit*borne_inf)));
	}
}

const long double E = 2.718281828459045;

void pow_v3(float x, int n, float *r){
	if(n==0){
		return;
	}
	*r *= x;
	pow_v3(x, n-1, r);
}


float power_v3(float x, int n){
	float r = 1.0f;
	float *ptr = &r;
	pow_v3(x, n, ptr);
	return r;
}


int main(){
	//int M=33;
	//float E = e(0,M,1,0.0);
	float xn = power(4.5f, 10);
	printf("%f\n",xn);
	return 0;
}