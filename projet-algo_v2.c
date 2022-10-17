#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

int main(){
	printf ("%f\n", power_v1(4,2));
	printf ("%f\n", power_v1(4,-2));
	printf ("%f\n", power_v2(4,2));
	printf ("%f\n", power_v2(4,-2));
	printf ("%f\n", power_v4(4,2));
	printf ("%f\n", power_v5(3,5));
	printf ("%f\n", power_v6(3,5));
	printf ("%f\n", power_v7(3,5));
	printf ("%f\n", power_v8(3,5));
	printf ("%f\n", power_v10(3,5));
	return 0;
}