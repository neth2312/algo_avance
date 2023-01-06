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
	return NULL;
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

//utilisee que pour les initialisations
// vrai implementation plus bas
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


// ConstruitComposee
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

void testAfficheSimple(){
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

void afficheProfondeurBis(image im, int profondeur){
	if(estToutBlanc(im)){
		printf("B%d", profondeur);
	}else if(estToutNoir(im)){
		printf("N%d", profondeur);
	}else{
		printf("(");
		afficheProfondeurBis(im->fils[0], profondeur+1);
		afficheProfondeurBis(im->fils[1], profondeur+1);
		afficheProfondeurBis(im->fils[2], profondeur+1);
		afficheProfondeurBis(im->fils[3], profondeur+1);
		printf(")");
	}
}

void afficheProfondeur(image im){
	afficheProfondeurBis(im, 0);
}

void testAfficheProfondeur(){
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
	afficheProfondeur(composite);
	printf("\n");
	afficheProfondeur(composite1);
	printf("\n");
	afficheProfondeur(composite2);
	printf("\n");
	afficheProfondeur(tBlanc);
	printf("\n");
	afficheProfondeur(tNoir);
	printf("\n");}


char * litArbre(){
	char * arbre = (char *)malloc(sizeof(char)*1000000);
	printf("Entrez l'arbre ('B' ou 'N' ou '()'): ");
	scanf("%999999999999s",arbre);
	return arbre;
}


void testLitArbre(){
	char * arbre = litArbre();
	printf("%s", arbre);
	free(arbre);
}

int isoleParentheses(char * s, int k, int taille){
	//au cas ou un genie s'amuserait
	//if(s[k]!='('){
	//	return -1;
	//}
	int cpt = 1;
	while(cpt!=0 && k<taille){
		k++;
		if(s[k]=='('){
			cpt++;
		}else if(s[k]==')'){
			cpt--;
		}
	}
	return k;
}

void testIsoleParentheses(){
	char * s = "NBB(NB(BBNB)N)";
	printf("%d\n", isoleParentheses(s, 3,strlen(s)));
}

image LectureBis(char * s, int debut, int fin){
	if(s=="N"){// possible erreur entre char et char*
		return ConstruitNoir();
	}else if(s=="B"){
		return ConstruitBlanc();
	}else{
		image im = ConstruitNoir();
		if(debut==fin){
			return im;
		}
		im->toutnoir = false;
		int cpt = 0;
		while(debut<fin){//&& s[debut]!='\0'
			if(s[debut]=='N'){
				im->fils[cpt] = ConstruitNoir();
				cpt++;
				debut++;
			}else if(s[debut]=='B'){
				im->fils[cpt] = ConstruitBlanc();
				cpt++;
				debut++;
			}else if(s[debut]=='('){
				int next = isoleParentheses(s, debut, strlen(s));
				//printf("next %d\n", next);
				im->fils[cpt] = LectureBis(s , debut+1, next);
				cpt++;
				debut=next+1;
			}else{
				// ignore characters
				continue;
			}
		}
		return im;
	}
}

image Lecture(char * s){
	//printf("%ld\n", strlen(s));
	LectureBis(s, 0, strlen(s));
}


void testLecture(){
	char * arbre = "";
	image im = Lecture(arbre);
	afficheSimple(im);
	printf("\n");
	char * arbre2 = "NBNN";
	image im2 = Lecture(arbre2);
	afficheSimple(im2);
	printf("\n");
	char * arbre3 = "NB(NBBN)B";
	image im3 = Lecture(arbre3);
	afficheSimple(im3);
	printf("\n");
	char * arbre4 = "B(NBB(BNNB))B(BBNN)";
	image im4 = Lecture(arbre4);
	afficheSimple(im4);
	printf("\n");
}



//forte ambiguite pour ces deux fonctions
// trop de cas problematiques,
bool estNoire(image im){
	if(im==NULL){
		return false;
	}else if(im->toutnoir){
		return true;
	}else{
		return estNoire(im->fils[0])
			   && estNoire(im->fils[1])
			   && estNoire(im->fils[2])
			   && estNoire(im->fils[3]);
	}
}


bool testEstNoire(){
	image im = Lecture("NBNN");
	printf("%d\n", estNoire(im));
	image im2 = Lecture("N(NNNN)NN");
	printf("%d\n", estNoire(im2));
	image im3 = Lecture("NBBN");
	printf("%d\n", estNoire(im3));
}


bool estBlanche(image im){
	if(im==NULL){
		return true;
	}else if(im->toutnoir){
		return false;
	}else{
		return estBlanche(im->fils[0])
			   && estBlanche(im->fils[1])
			   && estBlanche(im->fils[2])
			   && estBlanche(im->fils[3]);
	}
}

bool testEstBlanche(){
	image im = Lecture("BBBB");
	printf("%d\n", estBlanche(im));
	image im2 = Lecture("");
	printf("%d\n", estBlanche(im2));
	image im3 = Lecture("BBBN");
	printf("%d\n", estBlanche(im3));
}


image quartDeTour(image im){
	if(estToutBlanc(im) || estToutNoir(im)){
		return im;
	}else{
		return ConstruitComposee(
				quartDeTour(im->fils[2]),
				quartDeTour(im->fils[0]),
				quartDeTour(im->fils[3]),
				quartDeTour(im->fils[1]));
	}
}

void testQuartDeTour(){
	//revoir les dangers des parentheses en extra
	image im = Lecture("(BNNN)B(NNBB)N");
	image qIm = quartDeTour(im);
	afficheSimple(im);
	printf("\n");
	afficheSimple(qIm);
}

image negatif(image im){
	if(estToutNoir(im)){
		return ConstruitBlanc();
	}else if(estToutBlanc(im)){
		return ConstruitNoir();
	}else{
		return ConstruitComposee(
					negatif(im->fils[0]),
					negatif(im->fils[1]),
					negatif(im->fils[2]),
					negatif(im->fils[3])
					);
	}
}

void testNegatif(){
	image im = Lecture("NBNN");
	image inverse = negatif(im);
	afficheSimple(im);
	printf("\n");
	afficheSimple(inverse);
	printf("\n");
	image im2 = Lecture("N(NBNN)B((BNBN)NB(NBBN))");
	image inverse2 = negatif(im2);
	afficheSimple(im2);
	printf("\n");
	afficheSimple(inverse2);
	printf("\n");
}


image Diagonale(int p){
	if(p==0){
		return ConstruitNoir();
	}else if(p==1){
		image im = ConstruitNoir();
		im->toutnoir = false;
		im->fils[0]=ConstruitNoir();
		im->fils[1]=ConstruitBlanc();
		im->fils[2]=ConstruitBlanc();
		im->fils[3]=ConstruitNoir();
		return im;
	}else{
		image im = ConstruitNoir();
		im->toutnoir = false;
		im->fils[0]=Diagonale(p-1);
		im->fils[1]=ConstruitBlanc();
		im->fils[2]=ConstruitBlanc();
		im->fils[3]=Diagonale(p-1);
		return im;
	}
}

void testDiagonale(){
	//image im = Lecture();
	image im = Diagonale(3);
	afficheSimple(im);
	printf("\n");
}


bool Incluse(image im1, image im2){
	if((estToutNoir(im1) && !estToutNoir(im2)) || estToutBlanc(im2)){
		return false;
	}else if(estToutNoir(im2) || estToutBlanc(im1)){
		return true;
	}else{
		return Incluse(im1->fils[0], im2->fils[0])
			&& Incluse(im1->fils[1], im2->fils[1])
			&& Incluse(im1->fils[2], im2->fils[2])
			&& Incluse(im1->fils[3], im2->fils[3]);
	}
}

void testIncluse(){
	image im1 = Lecture("((BBBB)NBN)BN((BBNN)BB(NBBN))");
	image im2 = Lecture("(BNNN)(BBNB)(NNNN)(NBN(NNNB))");
	image im3 = Lecture("NBN(BBBN)");
	image im4 = Lecture("NNN(NBNN)");
	image im5 = Lecture("NBNN");
	image im6 = Lecture("NNNN");
	printf("%d\n", Incluse(im1, im2));
	printf("%d\n", Incluse(im3, im4));
	printf("%d\n", Incluse(im5, im6));
}

int max(int x, int y){
	if(x > y){
		return x;
	}else{
		return y;
	}
}

int hautMaxBlancBis(image im){
    if (estToutNoir(im)  || estNoire(im)){
        return -1;
    }
    if (estToutBlanc(im) ){
        return 0;
    }
    return 1+max(max(hautMaxBlancBis(im->fils[0]),hautMaxBlancBis(im->fils[1])),
                 max(hautMaxBlancBis(im->fils[2]),hautMaxBlancBis(im->fils[3])));
}

int hautMaxBlanc(image im){
    return hautMaxBlancBis(im);
}

void testHautMaxBlanc(){
    image im1 = Lecture("(BBBB)N(BNBN)(NBN(NB(BB(BBBB)(BBB(BBBB)))N))");//6
    image im2= Lecture("NNNN");//-1
    image im3= Lecture("N");//-1
    image im4= Lecture("B");//0
    image im5= Lecture("BBBB");//1
    image im6= Lecture("BBB(BBBB)");//2
    image im7= Lecture("BB(BBBB)(BBB(BBBB))");//3
    printf("%d\n", hautMaxBlanc(im1));
    printf("%d\n", hautMaxBlanc(im2));
    printf("%d\n", hautMaxBlanc(im3));
    printf("%d\n", hautMaxBlanc(im4));
    printf("%d\n", hautMaxBlanc(im5));
    printf("%d\n", hautMaxBlanc(im6));
    printf("%d\n", hautMaxBlanc(im7));
}

image SimplifieProfP(image im, int p){
	if(estToutNoir(im) || estToutBlanc(im)){
		return im;
	}
	if(p==0){
		if(estNoire(im->fils[0]) && estNoire(im->fils[1]) && estNoire(im->fils[2]) && estNoire(im->fils[3])){
			im = ConstruitNoir();
		}
		else if(estBlanche(im->fils[0]) && estBlanche(im->fils[1]) && estBlanche(im->fils[2]) && estBlanche(im->fils[3])){
			im = ConstruitBlanc();
		}
		return im;
	}else{
		for(int i=0; i<4; i++){
			if(!estToutBlanc(im->fils[i]) && !estToutNoir(im->fils[i])){
				im->fils[i] = SimplifieProfP(im->fils[i], p-1);
			}
		}
		return im;
	}
}

void testSimplifieProfP(){
	image im = Lecture("N(NB(NN(NNNN)N)B)(NBN(NBN(BBBB)))(BB(BBBB)B)");
	afficheSimple(im);
	printf("\n");
	image ims = SimplifieProfP(im, 2);
	afficheSimple(ims);
	printf("\n");
}


/* TODO
	AAAAAAAAAAARGHHHHHH
*/


int main(){
	// fait qqchose
	//testAfficheSimple();
	//testAfficheProfondeur();
	//testLitArbre();
	//testIsoleParentheses();
	//testLecture();
	//testQuartDeTour();
	//testNegatif();
	//testEstNoire();
	//testDiagonale();
	//testIncluse();
	testHautMaxBlanc();
	//testEstBlanche();
	//testSimplifieProfP();
	return 0;
}

