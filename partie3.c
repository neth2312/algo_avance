#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct bloc_image{
	bool toutnoir;
	struct bloc_image * fils[4];
} bloc_image;

typedef bloc_image *image ;

image ConstruitBlanc(){
	//image im = (image)malloc(sizeof(image));
	image im = NULL;
	return im;
}

image ConstruitNoir(){
	image im = (bloc_image *)malloc(sizeof(bloc_image));
	im->toutnoir = true;
	im->fils[0] = NULL;
	im->fils[1] = NULL;
	im->fils[2] = NULL;
	im->fils[3] = NULL;
	return im;
}

bool estToutNoir(image im){
	if(im==NULL){
		return false;
	}else{
		return im->toutnoir;
	}
}

bool estToutBlanc(image im){
	return im==NULL;
}

image ConstruitComposee(image i0, image i1, image i2, image i3){
	if(estToutBlanc(i0) && estToutBlanc(i1) && estToutBlanc(i2) && estToutBlanc(i3)){
		return ConstruitBlanc();
	}else if(estToutNoir(i0) && estToutNoir(i1) && estToutNoir(i2) && estToutNoir(i3)){
		return ConstruitNoir();
	}else{
		image im = (bloc_image *)malloc(sizeof(bloc_image));
		im -> toutnoir = false;
		im->fils[0] = i0;
		im->fils[1] = i1;
		im->fils[2] = i2;
		im->fils[3] = i3;
		return im;
	}
}

void afficheSimple(image im){
	if(estToutBlanc(im)){
		printf("B");
	}else if(estToutNoir(im)){
		printf("N");
	}else{
		printf("(");
		afficheSimple(im->fils[0]);
		afficheSimple(im->fils[1]);
		afficheSimple(im->fils[2]);
		afficheSimple(im->fils[3]);
		printf(")");
	}
}

void testAffiche(){
	image tNoir = ConstruitNoir();
	image tBlanc = ConstruitBlanc();
	image composite = ConstruitComposee(ConstruitBlanc()
										, ConstruitNoir()
										, ConstruitNoir()
										, ConstruitBlanc());
	image composite1 = ConstruitComposee(ConstruitComposee(
											ConstruitBlanc(),
											ConstruitNoir(),
											ConstruitBlanc(),
											ConstruitNoir()), 
										ConstruitBlanc(),
										ConstruitNoir(),
										ConstruitNoir());
	image composite2 = ConstruitComposee(ConstruitNoir()
										, ConstruitNoir()
										, composite1
										, ConstruitBlanc());
	afficheSimple(composite);
	printf("\n");
	afficheSimple(composite1);
	printf("\n");
	afficheSimple(composite2);
	printf("\n");
}

char * litArbre(){
	char * arbre = (char *)malloc(sizeof(char)*1000000);
	printf("Entrez l'arbre ('B' ou 'N' ou '()'): ");
	scanf("%999999999999s",arbre);
	return arbre;
}


void testLitArbre(){
	char * arbre = litArbre();
	printf(arbre);
	free(arbre);
}

char * isoleChaine(char * s, int k){
	if(s[k]!='('){
		return "";
	}
	int init = k;
	k++;
	int cpt = 1;
	int taille=sizeof(s)/sizeof(char);
	while(k<taille && cpt!=0){
		if(s[k]=='('){
			cpt++;
		}else if(s[k]==')'){
			cpt--;
		}
		k++;
	}
	int final = k;
	return s[]
}

image Lecture(char * s, int k){
	if(s=="N"){// possible erreur entre char et char*
		return ConstruitNoir();
	}else if(s=="B"){
		return ConstruitBlanc();
	}else{
		image im = ConstruitNoir();
		im->toutnoir = false;
		int cpt = 0;
		while(s[k]!='\0'){
			if(s[k]=='N'){
				im->fils[cpt] = ConstruitNoir();
				cpt++;
				k++;
			}else if(s[k]=='B'){
				im->fils[cpt] = ConstruitBlanc();
				cpt++;
				k++;
			}else if(s[k]=='('){
				im->fils[cpt] = Lecture(isoleChaine(s, k), 0);
			}
		}
	}
}

int main(){
	// fait qqchose
	//testAffiche();
	testLitArbre();
	return 0;
}