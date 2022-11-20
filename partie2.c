#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
	int nombre;
	struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
	*L = NULL ;
}

bool estVide(Liste l)
{
	return l == NULL ;
}

int premier(Liste l)
{
	return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
	Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
	tmp->nombre = x ;
	tmp->suivant = l ;
	return tmp ;
}

void empile(int x, Liste *L)
{
	  *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
	return l->suivant ;
}


void depile(Liste *L)
{
	Liste tmp = *L ;
	*L = suite(*L) ;
	free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
	if(estVide(l))
		printf("\n");
	else
	{
		printf("%d ", premier(l));
		affiche_rec(suite(l));
	}
}


void affiche_iter(Liste l)
{
	Liste L2 = l;
	while(!estVide(L2))
	{
		printf("%d ", premier(L2));
		L2 = suite(L2);
	}
	printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
	if (l == NULL)
		 return 0 ;
	else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
	Liste P = l;
	int cpt = 0 ;
	while (P ISNOT NULL)
	{   P = P->suivant ;
		cpt++ ;
	}
	return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
		  // *L non NULL ie liste non vide
{
	 if ( ((**L).suivant) == NULL )
			depile(L) ;   // moralement : depile(& (*L)) ;
	 else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
	 if ( (*L) ISNOT NULL )
		  VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
	if ( (*L) ISNOT NULL)
	{
		while ( ((**L).suivant) ISNOT NULL )
				 L = & ( (**L).suivant ) ;
		free(*L) ;
		*L = NULL ;
	 }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
	if(NOT(estVide(*L)))
	{
		depile(L);
		VideListe(L);
	}
	  
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
		printf("Double Affichage \n") ;
		affiche_rec(l) ;
		affiche_iter(l) ;

		printf("Longueur en double %d %d \n\n", 
						   longueur_rec(l), 
						   longueur_iter(l) 
			   ) ;
}

/*************************************************/
/*                                               */
/*           Nos propres fonctions               */
/*                                               */
/*************************************************/

Liste* PointeurSuite(Liste* L){
	if (estVide(*L)){
		return L;
	}else{
		return &((*L) -> suivant);
	}
}

int pos_0123(Liste l){
	if (estVide(l)){
		return 0;
	} else if (premier(l)==0){
		return 1;
	} else if (NOT (estVide(suite(l))) AND premier(suite(l))==0){
		return 1;
	} else if (NOT (estVide(suite(suite(l)))) AND premier(l->suivant->suivant)==0){
		return 1;
	}
	return 0;
}

int pluscourte(Liste l1, Liste l2){
	while (l1!=NULL AND l2!=NULL){
		l1=suite(l1);
		l2=suite(l2);
	}
	if (l1==NULL AND l2!=NULL){
		return 1;
	}
	return 0;
}

int nb0k_vi(Liste l1, int k){//iteratif
	int cpt=0;
	for(int i=0;i<k;i++){
		if (premier(l1)==0){
			cpt+=1;
		}
		l1=suite(l1);
		if (l1==NULL){
			return cpt;//modif
		}
	}
	return cpt;
}

int nb0k_vr(Liste l1, int k){//recursif simple
	if (estVide(l1) || k==0){
		return 0;
	}
	if (premier(l1)!=0) {
		return nb0k_vr(suite(l1),k-1);
	}
	return 1+nb0k_vr(suite(l1),k-1);
}

void test_bruh(){
	Liste L;
	initVide(&L);
	empile(0, &L);
	empile(0, &L);
	empile(0, &L);
	empile(0, &L);
	empile(0, &L);
	empile(0, &L);
	empile(1, &L);
	empile(0, &L);
	printf("%d", nb0k_vr(L, 0));
}


int s_f(Liste l1, int k , int acc){ //fonction pour recursif terminale
	if (estVide(l1)||k==0){
		return acc;
	}
	if (premier(l1)!=0) {
		return s_f(suite(l1),k-1,acc);
	}
	return s_f(suite(l1),k-1,acc+1);
}

int nb0k_vrtf(Liste l1, int k){//recursif terminale sous_fonctions
	return s_f(l1,k,0);
}

void s_p(Liste l1, int k, int *acc){
	if (l1!=NULL && k!=0){
		if (premier(l1)!=0){
			s_p(suite(l1),k-1,acc);
		}
		else{
			*acc +=1;
			s_p(suite(l1),k-1,acc);
		}
	}
}

int nb0k_vrtp(Liste l1, int k){//recursif terminale sous_procedure
	int acc=0;
	int *p_acc=&acc;
	s_p(l1,k,p_acc);
	return acc;
}

void BisNB0Kretro(Liste l1, int* k, int* acc){
	if (!estVide(l1)){
		BisNB0Kretro(suite(l1),k,acc);
		if (*k!=0){
			*k-=1;
			if (premier(l1)==0){
				*acc +=1;
			}
		}
	}
}

int nb0kretro(Liste l1, int k){
	int acc=0;
	BisNB0Kretro(l1,&k,&acc);
	return acc;
}


Liste Fctbegaye(Liste l1){
	if (estVide(l1)){
		return l1;
	}
	if (premier(l1)>0){
		return ajoute(premier(l1),ajoute(premier(l1),Fctbegaye(suite(l1))));
	}
	else{
		return Fctbegaye(suite(l1));
	}
}



void BisFB(Liste L, Liste* acc){
	if(estVide(L)){
		return;
	}
	else{
		if(premier(L)>0){
			empile(premier(L), acc);
			empile(premier(L), PointeurSuite(acc));
			BisFB(suite(L), PointeurSuite(PointeurSuite(acc)));
		}else{
			BisFB(suite(L), acc);
		}
	}
}

Liste FB(Liste L){
	Liste acc;
	initVide(&acc);
	BisFB(L,&acc);
	return acc;
}



void test_pointeur_suite(){
	Liste E;
	initVide(&E);
	empile(0, &E);
	empile(1, &E);
	empile(2, &E);
	empile(3, &E);
	empile(4, &E);
	Liste *B = PointeurSuite(&E);
	depile(B);
	affiche_rec(E);
	affiche_rec(*B);
}


Liste FBIter(Liste L){
	Liste R;
	initVide(&R);
	Liste* Q = &R;
	Liste P = L;
	while(!estVide(P)){
		if(premier(P)>0){
			empile(premier(P), Q);
			empile(premier(P), PointeurSuite(Q));
			P = suite(P);
			//Q = &((**Q).suivant);
			Q = PointeurSuite(PointeurSuite(Q));

		}else{
			P = suite(P);
		}
	}
	return R;
}



void test_fct_begaye(){
	Liste l2 ;

	Liste l3 ;

		initVide (&l3) ;
		empile(0, &l3);

		initVide (&l2) ;
		empile(3, &l2) ;
		empile(0, &l2) ;

		  //poup(l) ;

			 empile(0, &l2) ;
			 empile(1, &l2) ;
			 empile(0, &l2) ;
			 empile(-1, &l2) ;
			 empile(0, &l2) ;
			 empile(9, &l2) ;
			 empile(6, &l2) ;
			 empile(5, &l2) ;
			 empile(8, &l2) ;
			 empile(2, &l2) ;
	affiche_rec(l2);
	affiche_rec(FB(l2));
}

void test_retro_k(){
	Liste l2 ;

		initVide (&l2) ;
		empile(3, &l2) ;
		empile(0, &l2) ;

		  //poup(l) ;

			 empile(0, &l2) ;
			 empile(1, &l2) ;
			 empile(0, &l2) ;
			 empile(0, &l2) ;
			 empile(0, &l2) ;
			 empile(9, &l2) ;
			 empile(6, &l2) ;
			 empile(5, &l2) ;
			 empile(8, &l2) ;
			 empile(2, &l2) ;
	affiche_rec(l2);
	printf("%d\n",nb0kretro(l2,6));
	printf("%d\n",nb0kretro(l2,7));
	printf("%d\n",nb0kretro(l2,10));
	printf("%d\n",nb0kretro(l2,11));
	printf("%d\n",nb0kretro(l2,12));
	printf("%d\n",nb0kretro(l2,13));
	printf("%d\n",nb0kretro(l2,0));
	printf("%d\n",nb0kretro(l2,1));
}

void ProcBegaye(Liste *L){
	if(estVide(*L)){
		return;
	}else{
		if(premier(*L)>0){
			empile(premier(*L), PointeurSuite(L));
			ProcBegaye(PointeurSuite(PointeurSuite(L)));
		}else{
			depile(L);
			ProcBegaye(L);
		}
	}
}

void test_pb(){
	Liste L;
	initVide(&L);
	empile(8,&L);
	empile(8,&L);
	empile(-2,&L);
	empile(6,&L);
	empile(0,&L);
	empile(1,&L);
	empile(2,&L);
	affiche_rec(L);
	ProcBegaye(&L);
	affiche_rec(L);
}

//???????????????
//typedef struct ListeBis{
//	PBloc *entree;
//};



typedef struct PBloc
{
	int nombre;
	struct PBloc *suivant;
	struct PBloc **pred;
} PBloc;

typedef PBloc *ListeBis ;


//possible surcharge de fonction
//pas tres correcte dinitialiser a vide

void initVideBis( ListeBis *L){//pas sure
	L = NULL;
}

bool estVideBis(ListeBis L){
	return L==NULL;
}

int premierBis(ListeBis L){
	return L->nombre;
}

ListeBis suiteBis(ListeBis L){
	if(! estVideBis(L)){
		return L->suivant;
	}
	else{
		return NULL;
	}
}

void afficheRecBis(ListeBis l){
	if(estVideBis(l) || estVideBis(suiteBis(l))){
		printf("\n");
	}else{
		printf("%d\n",premierBis(l));
		afficheRecBis(suiteBis(l));
	}
}

ListeBis ajouteBis(int x, ListeBis L){
	ListeBis tmp = (ListeBis)malloc(sizeof(PBloc));
	tmp->nombre = x;
	tmp->suivant = L;
	tmp->pred = &tmp;
	L->pred = &tmp->suivant;
	return tmp;
}

void empileBis(int x, ListeBis *l){
	*l = ajouteBis(x, *l);
}

ListeBis* PointeurSuiteBis(ListeBis* L){
	if (estVideBis(*L)){
		return L;
	}else{
		return &((*L) -> suivant);//verifie juste ca
	}
}

void depileBis(ListeBis *L){
	ListeBis tmp = *L;
	*L = suiteBis(*L);
	free(tmp);
}

void retirePBloc(ListeBis *L, PBloc *P){
	if(estVideBis(*L)){
		return;
	}else if((*L)->pred==P->pred){
		depileBis(L);
	}else{
		retirePBloc(PointeurSuiteBis(L),P);
	}
}

//pas ouf la notation 
void test_ListeBis(){
	ListeBis l;
	initVideBis(&l);
	ListeBis L = ajouteBis( 0 , l);
	L = ajouteBis( 1 , L);
	L = ajouteBis( 2 , L);
	L = ajouteBis( 3 , L);
	afficheRecBis(L);
	ListeBis l2 = L;
	empileBis( 4 , &l2);
	empileBis( 5 , &l2);
	empileBis( 6 , &l2);
	afficheRecBis(l2);
	//comportement erratique, fonctionne sur L mais pas sur l2
	PBloc **p = PointeurSuiteBis(&l2);
	retirePBloc(&l2,*p);
	afficheRecBis(l2);
}



// La partie permutation ne donne pas de bons resultats
Liste concat(Liste L1, Liste L2){
    if (estVide(L1)){
        return L2;
    } else {
        return ajoute(premier(L1),concat(suite(L1),L2));
    }
}

Liste AETTL(int x, Liste L){
    if (estVide(L)){
        return L;
    } else {
        return ajoute(ajoute(x,premier(L)),AETTL(x,suite(L)));    
    }
}

Liste ATP(int x, Liste L){
    if (estVide(L)){
        Liste L2;
        initVide(&L2);
        Liste sl;
        initVide(&sl);
        return ajoute(ajoute(x,sl),L2);
    } else{
        return ajoute(ajoute(x,L),
        AETTL(premier(L),ATP(x,suite(L))));
    }
}

Liste ATLTP(int x, Liste L){
    if (estVide(L)){
        return L;
    } else {
        return concat(ATP(x,premier(L)), ATLTP(x,suite(L)));
    }
}

Liste Permutations(int n){
    if (n==0){
        Liste L;
        initVide(&L);
        Liste sl;
        initVide(&sl);
        return ajoute(sl,L);
    } else {
        return ATLTP(n,Permutations(n-1));
    }
}

void test_permutation(){
    Liste per = Permutations(1);
    affiche_rec(per);
}

int main(int argc, char** argv)
{
	Liste l ;
	initVide (&l) ;
	//poup(l) ;
	empile(0, &l) ;
	//poup(l) ;
	empile(5, &l) ;
	empile(0, &l) ;
	empile(7, &l) ;
	empile(8, &l) ;
	empile(9, &l) ;
	//poup(l) ;
	VireDernier_rec  (&l) ;
	VireDernier_iter (&l) ;
	//depile(& l) ;
	//poup(l) ;
	Liste l2 ;
	initVide (&l2) ;
	empile(0, &l) ;
	//poup(l) ;
	empile(0, &l2) ;
	empile(1, &l2) ;
	empile(0, &l2) ;
	empile(0, &l2) ;
	empile(0, &l2) ;
	empile(9, &l2) ;
	empile(6, &l2) ;
	empile(5, &l2) ;
	empile(8, &l2) ;
	empile(2, &l2) ;
	//VideListe(&l);
	test_ListeBis();
	//Nos tests de fonctions ci-dessous
	//affiche_rec(l);
	//affiche_rec(l2);
	//test_pointeur_suite();
	//test_fct_begaye();
	//test_pb();
	//test_bruh();
	//printf("%d\n",pos_0123(l));
	//printf("%d\n",pluscourte(l,l2));
	//printf("%d\n",nb0k_vrtf(l2,7));
	return 0;
}





