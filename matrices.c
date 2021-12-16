#include "Matrices.h"
#include<stdio.h> // prontf, scanf, gets, getchar
#include<stdlib.h> // pour malloc, calloc, realloc
#include<assert.h> // pour assert
#include<math.h>
/**********************************/

void  creerMatrice(matrice_t *ptrMat){
    double **p;
    ptrMat->mat=(double **)malloc(ptrMat->nl*sizeof(double *));
    for(p=ptrMat->mat;p<ptrMat->mat+ptrMat->nl;p++)
        *p=(double *)malloc(ptrMat->nc*sizeof(double));
}

/**********************************/

void  creeVect(vecteur_t *ptrV){
    ptrV->vect=(double *)malloc(ptrV->n * sizeof(double));
}

/**********************************/

void scanMatrice(matrice_t *ptrMat){
    double **p,*q;
    printf("Nombre de lignes ? "); scanf("%d",&ptrMat->nl);
    printf("Nombre de colonnes ? "); scanf("%d",&ptrMat->nc);
    creerMatrice(ptrMat);
    //la saisie des données de la matrice
    printf("les donnees de la matrice \n");
    for(p=ptrMat->mat;p<ptrMat->mat+ptrMat->nl;p++)
        for(q=*p;q<*p+ptrMat->nc;q++){
            printf("[%d][%d] = ",(int)(p-ptrMat->mat),(int)(q-*p));
            scanf("%lf",q);
        }
}

/**********************************/

void scanVectr(vecteur_t *ptrV){
    int i;
    printf("Nombre de colonnes ? "); scanf("%d",&ptrV->n);
    creeVect(ptrV);
    //la saisie des données de vect
    printf("les donnees de vecteurs :  \n");
        for(i=0;i<ptrV->n;i++){
            printf("[%d] = ",i);
            scanf("%lf",&ptrV->vect[i]);
    	}
}

/**********************************/

void printMatrice(const matrice_t *ptrMat){
   double **p,*q;
    puts("Matrice : ");
    printf("\tnbre de lignes = %d\n",ptrMat->nl);
    printf("\tnbre de colonnes = %d\n",ptrMat->nc);
    //la saisie des données de la matrice
    puts("\tValeurs :");
    for(p=ptrMat->mat;p<ptrMat->mat+ptrMat->nl;p++){
        for(q=*p;q<*p+ptrMat->nc;q++)
            printf("%12.0f",*q);
        puts("");
    }   
}

/**********************************/

void printVect(const vecteur_t *v){
	puts(" ");
    puts("vecteur  : ");
    int i;
    printf("\tnbre de colonnes = %d\n",v->n);
    //la saisie des données de la matrice
    puts("\tValeurs :");
    for(i=0;i<v->n;i++){
            printf("%12.0f",v->vect[i]);
    }   
    puts(" ");
}

/**********************************/

matrice_t add(const matrice_t *ptr1,const matrice_t *ptr2){
    matrice_t som;
    double **p1,**p2,**p3,*q1,*q2,*q3;
    assert(ptr1->nl==ptr2->nl && ptr1->nc==ptr2->nc);
    som.nl=ptr1->nl;
    som.nc=ptr1->nc;
    creerMatrice(&som);
    for(p1=ptr1->mat,p2=ptr2->mat,p3=som.mat;p1<ptr1->mat+ptr1->nl;p1++,p2++,p3++)
        for(q1=*p1,q2=*p2,q3=*p3;q1<*p1+ptr1->nc;q1++,q2++,q3++)
            *q3=*q1+*q2;
    return som;
}
/**********************************/

double getTrace(const matrice_t *ptr1){
	int i,j;
	double n=0;
	for(i=0;i<ptr1->nl;i++)
			n += ptr1->mat[i][i];
	return n;
}

/**********************************/

matrice_t multiplication(const matrice_t *ptr1,const matrice_t *ptr2){
    matrice_t result ;
    assert(ptr1->nl==ptr2->nl && ptr1->nc==ptr2->nc);
    result.nl=ptr1->nl;
    result.nc=ptr1->nc;
    creerMatrice(&result);
    int i,j,k;
    for(i=0;i<ptr1->nl;i++)	
        for(j=0;j<ptr1->nc;j++)
            for(k=0;k<ptr1->nl;k++)
            	result.mat[i][j] += ptr1->mat[i][k] * ptr2->mat[k][j];           
    return result;
}
/**********************************/

vecteur_t multMatVect(const matrice_t *m,const vecteur_t *v){
	vecteur_t res;
	res.n=v->n;
	creeVect(&res);
	int i,j;
	for(i=0;i<m->nl;i++)	
        for(j=0;j<m->nc;j++)
			res.vect[i] += m->mat[i][j] * v->vect[j];
	return res;
}
/**********************************/
vecteur_t getDiag(const matrice_t *m){
	vecteur_t res;
	int i;
	res.n=m->nl;
	creeVect(&res);
	for(i=0;i<m->nl;i++)
		res.vect[i]=m->mat[i][i];
	return res;
}
/**********************************/
vecteur_t getDiemeDiag(const matrice_t *m){
	vecteur_t res;
	int i;
	res.n=m->nc;
	creeVect(&res);
	int ind=m->nc-1;
	for(i=0;i<m->nc;i++)
		res.vect[i]=m->mat[i][ind-i];
	return res;
}
/**********************************/
lgn bestlgn(const matrice_t *m){
		int in=0,i,j;
		lgn best;
		
		best.indice=0;
		best.nmbrZero=0;
		for(i=0;i<m->nl;i++){
			for(j=0;j<m->nc;j++){
				if(m->mat[i][j]==0)	in++;
			}
			if(best.nmbrZero<in){
				best.indice=i;
				best.nmbrZero=in;
			}
			in=0;
		}
		return best;
}		
lgn bestcln(const matrice_t *m){
		int in=0,i,j;
		lgn best;
		best.indice=0;
		best.nmbrZero=0;
		for(i=0;i<m->nc;i++){
			for(j=0;j<m->nl;j++){
				if(m->mat[j][i]==0)	in++;
			}
			if(best.nmbrZero<in){
				best.indice=i;
				best.nmbrZero=in;
			}
			in=0;
		}
		return best;
}		
void bestLcode(const matrice_t *m){
	
	lgn l=bestlgn(m);
	lgn c=bestcln(m);
	
	if(l.nmbrZero >= c.nmbrZero ){
		printf ("\n \t\t best ligne est : %d nmbr des zeros  : %d \n",l.indice+1,l.nmbrZero);
	}else {
		
		printf ("\n \t\t best colonne est : %d nmbr des zeros  : %d \n",c.indice+1,c.nmbrZero);
	}	
}
/******************/
matrice_t subMat(const matrice_t *m,int l,int c){
	int i,j,k=0,f=0;
	matrice_t U;
	if(l!=0)U.nl=m->nl-1;else U.nl=m->nl;
	if(c!=0)U.nc=m->nc-1;else U.nc=m->nc;
	creerMatrice(&U);
	assert(m->nc>=c-1 && m->nl >=l-1);
	for(i=0;i<m->nl;i++){
		f=0;
		if(i != l-1){
			for(j=0;j<m->nc;j++){
				if(j != c-1){
					U.mat[k][f]=m->mat[i][j];
					f++;
				}
			}
			k++;
		}
	}
	
	return U;
}
/******************/
//Calcul r�cursif de d�terminant 
double determinant(matrice_t m)
 {
 	assert(m.nc==m.nl);
 	int j=0;
 	double det=0;
 	if(m.nc>2){
 		for(j=0;j<m.nc;j++) det +=pow(-1,j)*m.mat[0][j]*determinant(subMat(&m,0,j));
 		return det;
	 }
	 else{
	 	return det=(m.mat[0][0]*m.mat[1][1])-(m.mat[0][1]*m.mat[1][0]);
	 }
	 
 }
 
 /*************************************/
 matrice_t produitScalaire(const matrice_t A, double scalaire)
{
	int i,j;
	matrice_t res;
	res.nc=A.nc;
	res.nl=A.nl;
	creerMatrice(&res);
        for (i = 0; i < A.nl; i++)
            for (j = 0; j < A.nc; j++)
                 res.mat[i][j] = A.mat[i][j] * scalaire;
         return res;
}
/*************************************/
matrice_t transposee(const matrice_t *A){
            matrice_t T;
            int i,j;
            T.nl = A->nc;
            T.nc = A->nl;
            creerMatrice(&T);
            for ( i = 0; i < A->nl; i++)
                 for ( j = 0; j < A->nc; j++)
                       T.mat[j][i] = A->mat[i][j];
            return T;
}


/*************************/
matrice_t coMatrice(const matrice_t *m){
    matrice_t coMAt ;
    coMAt.nl=m->nl;
    coMAt.nc=m->nc;
    creerMatrice(&coMAt);
    int i,j;
    for(i=0;i<coMAt.nl;i++){
        for(j=0;j<coMAt.nc;j++){
            coMAt.mat[i][j]=pow(-1,i+j)*determinant(subMat(m,i,j));
        }
    }
    return coMAt;
}
/**********************/

matrice_t inverse(const matrice_t *m)
{
    double det;
    int i,j;
    
    assert(determinant(*m)!=0);
    det =1/determinant(*m);
    matrice_t m2,m3;
    m2.nl=m->nl;m2.nc=m->nc;m3.nl=m->nl;m3.nc=m->nc;
    m3=coMatrice(m);
    m3=transposee(&m3);
	m2=produitScalaire(m3,det);
    
    return m2;
}
/**************************/



