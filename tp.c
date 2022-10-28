#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const long double E = 2.718281828459045;

//1.1
double e(int borne_inf,int borne_sup,unsigned long int produit,float somme){
	if( borne_sup == borne_inf){
		return 1.0/(borne_sup*produit) + somme;
	}else if(borne_inf==0 || borne_inf==1){
		return e(borne_inf+1, borne_sup, produit, somme+1.0);
	}else{
		return e(borne_inf+1, borne_sup, produit*borne_inf, somme+(1.0/(produit*borne_inf)));
	}
}

//1.2


//1.3
float power_v1(float x, int n){
	if (n==0){
		return 1;
	}
	if (n>=1) {
		return power_v1(x,n-1)*x;
	}
	float res= power_v1(x, -n);
	return 1/res;
}

float power_v2(float x, int n){
	bool n_neg=false;
	if (n<0){
		n=-n;
		n_neg=true;
	}
	float r=1;
	for (int i=1; i<=n;i++){
		r=r*x;
	}
	if (! n_neg){
		return r;
	}
	return 1/r;
}

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

float pow_v4(float x, int n, float r){ 
	if (n==0){
		return r;
	}
	r=r*x;
	return pow_v4(x,n-1,r);
}

float power_v4(float x, int n){
	float r=1;
	r=pow_v4(x,n,r); 
	return r;
	
}

float power_v5(float x, int n){
	if (n==0){
		return 1;
	}
	if (n%2==0){
		return power_v5(x,n/2)*power_v5(x,n/2);
	}
	return power_v5(x,n/2)*power_v5(x,n/2)*x;
	
}

float power_v6(float x, int n){
	if (n==0){
		return 1;
	}
	float y=power_v6(x, n/2);
	if (n%2==0){
		return y*y;
	}
	return y*y*x;
}

float power_v7(float x, int n){
	if (n==0){
		return 1;
	}
	if (n%2==0){
		return power_v7(x*x,n/2);
	}
	return power_v7(x*x,n/2)*x;
}

float pow_8(float x, int n, float r){
	if (n==0){
		return r;
	}
	if (n%2==0){
		return pow_8(x*x,n/2,r);
	}
	return pow_8(x*x,n/2,r*x);
}

float power_v8(float x, int n){
	return pow_8(x,n,1);
}

void pow_v9(float x, int n, float *r){
	if (n==0){
		return;
	}
	else{
		if (n%2!=0){
			*r=*r * x;
		}
		pow_v9(x*x,n/2,r);
	}
}

float power_v9(float x, int n){
	float r=1.0f ;
	float *ptr= &r;
	pow_v9(x,n,ptr);
	return r;
}

float power_v10(float x, int n){
	float r=1;
	while (n!=0){
		if (n%2!=0){
			r=r*x;
		}
		n=n/2;
		x=x*x;
	}
	return r;
}


// e = (1+1/n)^n
double e_1pn_v0(unsigned int N, unsigned int k){
	if(k==1){
		return 1.0;
	}
	return (1.0+1.0/N)*e_1pn_v0(N, k-1);
}

double e_1pn_v1(unsigned int N){
	return power_v1(1.0+1.0/N, N);
}

double e_1pn_v2(unsigned int N){
	return power_v2(1.0+1.0/N, N);
}

double e_1pn_v3(unsigned int N){
	return power_v3(1.0+1.0/N, N);
}

double e_1pn_v4(unsigned int N){
	return power_v4(1.0+1.0/N, N);
}

double e_1pn_v5(unsigned int N){
	return power_v5(1.0+1.0/N, N);
}

double e_1pn_v6(unsigned int N){
	return power_v6(1.0+1.0/N, N);
}

double e_1pn_v7(unsigned int N){
	return power_v7(1.0+1.0/N, N);
}

double e_1pn_v8(unsigned int N){
	return power_v8(1.0+1.0/N, N);
}

double e_1pn_v9(unsigned int N){
	return power_v9(1.0+1.0/N, N);
}

double e_1pn_v10(unsigned int N){
	return power_v10(1.0+1.0/N, N);
}





//1.4
long long int Ackermann(int m, int n){
	if(m==0){
		return n+1;
	}else if(m>0 && n==0){
		return Ackermann(m-1, 1);
	}else if(m>0 && n>0){
		return Ackermann(m-1, Ackermann(m, n-1));
	}
}


//long long int Ackermann(int m, int n){
//	if(m==0){
//		return n+1;
//	}else if(m>0 && n==0){
//		return Ackermann(m-1, 1);
//	}else if(m>0 && n>0){
//		return Ackermann(m-1, Ackermann(m, n-1));
//	}
//}


//1.5
// version recursive simple
float X_rs(int n){ 
    if (n==0){
        return 1;
    }
    float precedent=X_rs(n-1);
    return precedent+(2/precedent);
}

//version iterative
float X_i(int n){
    float res=1.0;
    for (int i=1; i<=n;i++){
        res+=2/res;
    }
    return res;
}

//sous fonction pour la recursive terminale
float X_sous_f(int n, float res){
    if (n==0){
        return res;
    }
    res+=2/res;
    X_sous_f(n-1,res);
}

//version recursive terminale avec sous-fonctions
float X_rtf(int n){
    float res=1;
    res=X_sous_f(n,res);
    return res;
}

//sous-procedure pour la recursive terminale
void X_sous_p(int n, float *ptres){
    if (n==0){
        return;
    }
    *ptres+= 2/ (*ptres);
    X_sous_p(n-1,ptres);

}

//version recursive terminale avec sous-procedures
float X_rtp(int n){
    float res=1;
    float *ptres=&res;
    X_sous_p(n, ptres);
    return *ptres;
}



void test_1_1(){
	printf("%lf\n", e(0, 32, 1L, 0.0));
}

void test_1_3(){
	int N=10000;
	printf("%.10lf\n", e_1pn_v0(N, N));
	printf("%.10lf\n", e_1pn_v1(N));
	printf("%.10lf\n", e_1pn_v2(N));
	printf("%.10lf\n", e_1pn_v3(N));
	printf("%.10lf\n", e_1pn_v4(N));
	printf("%.10lf\n", e_1pn_v5(N));
	printf("%.10lf\n", e_1pn_v6(N));
	printf("%.10lf\n", e_1pn_v7(N));
	printf("%.10lf\n", e_1pn_v8(N));
	printf("%.10lf\n", e_1pn_v9(N));
	printf("%.10lf\n", e_1pn_v10(N));
}


int main(){
	//int M=33;
	//float E = e(0,M,1,0.0);
	//float xn = power_v9(4.5f, 10);
	//printf("%f\n",xn);
	//long long int AAAAAAAAArgh = Ackermann(5,0);
	//printf("%lld",AAAAAAAAArgh);
	test_1_3();

	return 0;
}