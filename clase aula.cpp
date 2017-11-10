#include <conio.h>
#include <iostream>
using namespace std;
struct NODO{ int info;
           NODO *izq, *der;};
           
class ARBOL{NODO *raiz;
public:	ARBOL( ){raiz=NULL;}
	NODO *raiz_arbol( ) {return raiz;}
	int ins_arbol (int);
	NODO *buscar_arbol (int, NODO *, NODO *);
	void borrar_nodo(NODO *, NODO *);
	NODO *buscar(int, NODO **, NODO *);
	int retira_arbol(int);
	void inorden(NODO *);
	void preorden(NODO *);
	void posorden(NODO *);
	void destruir (NODO *p);
	~ARBOL( );};
	
NODO *ARBOL::buscar_arbol(int n, NODO *p, NODO *q)
{if (p==NULL) return q;
if (n < p->info){
q=p;
q=buscar_arbol(n,p->izq,q);
return q;}
else if (n > p->info) {
q=p;
q=buscar_arbol(n,p->der,q);
return q;}
       else return NULL;}
       
int ARBOL:: ins_arbol(int n){
NODO *q;
if (raiz == NULL){
raiz= new NODO;
raiz->info =n;
raiz->izq=raiz->der=NULL;
return 0;}
q =buscar_arbol(n,raiz,NULL);
if (q==NULL) return -1;
NODO *nuevo;
nuevo= new NODO;
nuevo->info = n;
nuevo->izq=nuevo->der=NULL;
if (n<q->info)
         q->izq=nuevo;
else   q->der=nuevo;
return 0;}

void ARBOL::borrar_nodo (NODO *q, NODO *p){
NODO  *r, *s,*t;
if (p->izq==NULL) r=p->der;
else if (p->der==NULL) r=p->izq; 
       else {s =p;
  r=p->der;
  t=r->izq;
  while(t!=NULL){s=r; r=t; t=t->izq;}
if (p!=s){
	    s->izq=r->der;
    r->der=p->der; }
r->izq =p->izq;
}
	if (q==NULL) raiz= r;
	else if (p==q->izq) q->izq =r;
	       else q->der = r;
	delete p;}
	
NODO *ARBOL::buscar(int n, NODO **p, NODO *q){
	if (*p=NULL) return NULL;
	if (n <(*p)->info){
	          q=*p;
	           *p=(*p)->izq;
	          q=buscar(n,p,q);
	          return q;}
	else if (n>(*p)->info){
		q=*p;
		*p=(*p)->der;
		q =buscar(n,p,q);
		return q;}
	       else return q;}
	       
int ARBOL:: retira_arbol(int n){
NODO *q, *p=raiz;
q=buscar(n,&p,NULL);
if (p==NULL) return -1;
borrar_nodo(q,p);
return 0;}

void ARBOL::inorden(NODO *p){
if (p!=NULL){
        inorden(p->izq);
        cout<<p->info<<endl;
        inorden(p->der);}}
        
void ARBOL::preorden(NODO *p){
if (p!=NULL){
       cout<<p->info<<endl;
       preorden(p->izq);
       preorden(p->der);}}
       
void ARBOL::posorden(NODO *p){
if (p!=NULL){
       posorden(p->izq);
       posorden(p->der);
      cout<<p->info<<endl; }}
      
void ARBOL::destruir(NODO *p){
if (p!=NULL){
      destruir(p->izq);
      destruir(p->der);
      delete p;
      cout<<"Nodo destruido..."<< endl;}}
      
ARBOL::~ARBOL( ) {destruir(raiz);}

main(){ ARBOL a; NODO *p;  int i;
cout<<"Número a insertar? (fin =999)..."<<endl;
cin>>i;
while(i!=999){
       if (a.ins_arbol(i)==-1) cout<<"Ya existe"<< endl;
       cout<<"Número a insertar? (fin =999)..."<<endl;
       cin>>i;}
cout<<"Número a retirar (fin=999)"<<endl;
cin>>i;
while(i!=19){
       if (a.retira_arbol(i)==-1)cout<<"No existe"<<endl;
       cout<<"Número a retirar (fin=999)"<<endl;
       cin>>i;}
a.inorden(a.raiz_arbol()); cout<<"___________"<< endl;
getch();
a.preorden(a.raiz_arbol()); cout<<"__________"<< endl;
getch();
a.posorden(a.raiz_arbol()); cout<<"__________"<< endl;
getch();
} 
	

