#ifndef _MATRICES
    #define _MATRICES
typedef struct{
    int n;
    double *vect ;
}vecteur_t;

typedef struct{
    int nl,nc;
    double **mat ;//allouer nl pointeurs puis pour pointeur allour nc double
}matrice_t;

typedef struct {
			int indice;
			int nmbrZero;
}lgn;

void  creerMatrice(matrice_t *);
void scanMatrice(matrice_t *);
void scanVectr(vecteur_t *);
void printMatrice(const matrice_t *); // pour eviter une copie (lourde)
void printVect(const vecteur_t *);
matrice_t add(const matrice_t *,const matrice_t *);
matrice_t multiplication(const matrice_t *,const matrice_t *);
double getTrace(const matrice_t *);
vecteur_t multMatVect(const matrice_t *,const vecteur_t *);
vecteur_t getDiag(const matrice_t *);
vecteur_t getDiemeDiag(const matrice_t *);
void bestLcode(const matrice_t *);
double determinant( matrice_t );
matrice_t transposee(const matrice_t *);
matrice_t inverse(const matrice_t *);
matrice_t subMat(const matrice_t *,int ,int );
#endif
