#include <windows.h>;
#include <iostream>;
#include <conio.h>; //Para getch
#include <time.h>; //Para srand y rand
 
using namespace std;
 
//PROTOTIPOS DE FUNCIONES
void matrixAleatoria(int matrix[][16], int dificultad);
 
void mensajeBienvenida();
void mensajeJuegoPerdido(int matrix[][16],char mapa[][16], int pos[], int pos_ant[], int ll,char &amp;rep,int &amp;puntaje);
void mensajeJuegoGanado(int matrix[][16],char mapa[][16], int pos[], int pos_ant[], int ll,char &amp;rep,int &amp;puntaje);
void creditos();
 
void pideDificultad(int &amp;);
void mueveJaguar(int matrix[][16], int pos[], int pos_ant[], int &amp;);
void contarMinas(int matrix[][16], int pos[], int pos_ant[],int &amp;cont1);
void matrixA_Mapa(int matrix[][16], char mapa[][16], int ll);
void muestraMapa(char mapa[][16], int cont1, int puntaje);
void capturaDireccion(char &amp;x);
void registraMovimiento(char x,int pos[], int pos_ant[]);
 
//FUNCION PRINCIPAL
int main()
{
 
//declaracion de las variables de control global
char x,rep='n'; // 'x' para leer la direccion de movimiento y 'rep' para si el usuario desea repetir el juego
srand(time(NULL));// semilla para generar numeros aleatorios
int dificultad=1, puntaje=0;//inicializamos algunas variables
 
do
{
 
int ciclo=1;// variable para controlar el estado juego: ciclo=1(en juego), ciclo=2(juego perdido), ciclo=4(juego ganado)
int pos[2]={0,0},pos_ant[2]={0,0},cont1=0, ll=0;// variables para guardar las posiciones del jugador, y otras
int matrix[8][16];// mapa numerico de juego
//Campo sin recorrer=0 , jaguar=1 , mina=2, campo recorrido=3, llegada=4
 
char mapa[8][16];// mapa caracter del juego, este es el que se muestra en pantalla
// jaguar='', campo_sin_recorrer='þ', mina='Ï' ,campo_recorrido='.'
 
if((rep=='n'))
mensajeBienvenida();
 
pideDificultad( dificultad);//pide la dificultad al usuario
matrixAleatoria(matrix, dificultad); // se inicializa un mapa numerico aleatorio de acuerdo a la dificultad
system("color 73");// 73 0A cambia el color de los caracteres en pantalla
matrix[7][15]=4; //pone puerta en la ultima casilla
matrix[0][0]=1; //pone al jaguar en la primera casilla
 
while(ciclo==1)//ciclo de contro del juego
{
 
// realiza los movimientos de la piesa (si los hay)
mueveJaguar( matrix, pos, pos_ant, puntaje);
 
// cuenta el numero de minas alrededor de la pieza
contarMinas( matrix, pos, pos_ant,cont1);
 
// pasa matriz numerica a matriz caracter
matrixA_Mapa( matrix,mapa,ll);
 
// muetra el mapa y el contador
muestraMapa( mapa,cont1, puntaje);
 
// captura direccion de movimiento - teclas de direccion
capturaDireccion(x);
 
//registra direccion de movimiento en la matriz
registraMovimiento( x, pos, pos_ant);
 
if(matrix[pos[0]][pos[1]]==2)//verifica si se ha ganado o perdido el juego
ciclo=2; //se ha perdido el juego
else
if(matrix[pos[0]][pos[1]]==4)
ciclo=4;//se ha ganado el juego
 
}//cierre del ciclo de contro del juego
 
if(ciclo==2)//**************************************muestra mensaje en caso de perder
mensajeJuegoPerdido(matrix, mapa, pos, pos_ant, ll, rep, puntaje);
else
if(ciclo==4)//*******************************muestra mensaje en caso de ganar
mensajeJuegoGanado(matrix, mapa, pos, pos_ant, ll, rep, puntaje);
 
}while((rep=='s')||(rep=='S'));
 
//system("pause");
return 0;
 
}
 
//DECLARACION DE FUNCIONES
 
void mensajeBienvenida()// inicio de mensaje inicial
{
 
cout&lt;&lt;"\n\n";
 
cout&lt;&lt;" o88 \n oo ooo oooo oooo oo oooooo ooooooooo8 \n 888 888 888 888 888 888 888oooooo8 \n 888 888 888 888 888 888 888 \n o888o888o888o o888o o888o o888o 88oooo888 \n \n";
 
cout&lt;&lt;" _ \n _____|_|___ ___ \n | | | | -_|\n |_|_|_|_|_|_|___|©\n \n";
 
cout&lt;&lt;"\n\n Mine es un juego clasico, basado en minehunt, un juego en donde el jugador debe moverse atraves de un campo minado con las teclas de direccion; para ganar el\n juego basta alcanzar la ezquina inferior donde se encuentra la salida. \n debes completar tu objetivo solo conociendo cuantas minas hay a tu alrededor.\n\n Buena Suerte!!\t\t\t\t Desarrollado por: Isaac Diaz.\n\n\n\n";
 
system("pause");
// Sleep(1000);
}// fin de mensaje inicial
 
void pideDificultad(int &amp;dif)//funcion que pide dificultad
{
bool w=false;
cout&lt;&lt;" 1 para Facil\n 2 para Medio\n 3 para dificil\n ";
do{
cin&gt;&gt;dif;
if((dif==1)||(dif==2)||(dif==3))
w=true;
}while(!w);
}//fin funcion que pide dificultad
 
void mueveJaguar(int matrix[][16], int pos[], int pos_ant[], int &amp;puntaje)//inicio funcion que mueve al jaguar
{
 
if((pos_ant[0]!=pos[0])||(pos_ant[1]!=pos[1]))// mueve_jaguar_en_la_matrix
{
if((matrix[pos[0]][pos[1]])==0)//si es una casilla por la cual no se ha pasado...
puntaje++;
matrix[pos_ant[0]][pos_ant[1]] =3; //pone un punto en la posicion anterior
matrix[pos[0]][pos[1]] =1; //pone al jaguar en la nueva posicion
 
} //fin mueve_jaguar_en_la_matrix
 
}//fin funcion que mueve al jaguar
 
void contarMinas(int matrix[][16], int pos[], int pos_ant[],int &amp;cont1)//inicio funcion que cuenta las minas al rededor del jaguar
{
 
cont1=0;
if((pos[0]!=0)&amp;&amp;(pos[0]!=7)&amp;&amp;(pos[1]!=0)&amp;&amp;(pos[1]!=15))//cuenta cuando el jaguar no esta en ningun borde
{
 
if((matrix[(pos[0]-1)][pos[1]])==2)
cont1++;
 
if((matrix[(pos[0]+1)][pos[1]])==2)
cont1++;
 
if((matrix[pos[0]][(pos[1]-1)])==2)
cont1++;
 
if((matrix[pos[0]][(pos[1]+1)])==2)
cont1++;
 
if((matrix[(pos[0]-1)][(pos[1]-1)])==2)
cont1++;
 
if((matrix[(pos[0]+1)][(pos[1]+1)])==2)
cont1++;
 
if((matrix[(pos[0]-1)][(pos[1]+1)])==2)
cont1++;
 
if((matrix[(pos[0]+1)][(pos[1]-1)])==2)
cont1++;
 
}
else
if((pos[0]==0)&amp;&amp;(pos[1]!=0)&amp;&amp;(pos[1]!=15))//cuenta cuando el jaguar esta en el borde superior
{
if(matrix[(pos[0]+1)][pos[1]]==2)
cont1++;
 
if(matrix[pos[0]][(pos[1]-1)]==2)
cont1++;
 
if(matrix[pos[0]][(pos[1]+1)]==2)
cont1++;
 
if(matrix[(pos[0]+1)][(pos[1]-1)]==2)
cont1++;
 
if(matrix[(pos[0]+1)][(pos[1]+1)]==2)
cont1++;
 
}
else
if((pos[0]==7)&amp;&amp;(pos[1]!=0)&amp;&amp;(pos[1]!=15))//cuenta cuando el jaguar esta en el borde inferior
{
if(matrix[(pos[0]-1)][pos[1]]==2)
cont1++;
 
if(matrix[pos[0]][(pos[1]-1)]==2)
cont1++;
 
if(matrix[pos[0]][(pos[1]+1)]==2)
cont1++;
 
if(matrix[(pos[0]-1)][(pos[1]-1)]==2)
cont1++;
 
if(matrix[(pos[0]-1)][(pos[1]+1)]==2)
cont1++;
 
}
else
if((pos[0]!=0)&amp;&amp;(pos[0]!=7)&amp;&amp;(pos[1]==0))//cuenta cuando el jaguar esta en el borde izquierdo
{
if(matrix[(pos[0]-1)][pos[1]]==2)
cont1++;
 
if(matrix[pos[0]][(pos[1]+1)]==2)
cont1++;
 
if(matrix[(pos[0]+1)][pos[1]]==2)
cont1++;
 
if(matrix[(pos[0]-1)][(pos[1]+1)]==2)
cont1++;
 
if(matrix[(pos[0]+1)][(pos[1]+1)]==2)
cont1++;
 
}
else
if((pos[0]!=0)&amp;&amp;(pos[0]!=7)&amp;&amp;(pos[1]==15))//cuenta cuando el jaguar esta en el borde derecho
{
if(matrix[(pos[0]-1)][pos[1]]==2)
cont1++;
 
if(matrix[pos[0]][(pos[1]-1)]==2)
cont1++;
 
if(matrix[(pos[0]+1)][pos[1]]==2)
cont1++;
 
if(matrix[(pos[0]-1)][(pos[1]-1)]==2)
cont1++;
 
if(matrix[(pos[0]+1)][(pos[1]-1)]==2)
cont1++;
 
}
else
if((pos[0]==0)&amp;&amp;(pos[1]==0))//cuenta cuando el jaguar esta en la esquina superior izquierda
{
 
if(matrix[pos[0]][(pos[1]+1)]==2)
cont1++;
 
if(matrix[(pos[0]+1)][pos[1]]==2)
cont1++;
 
if(matrix[(pos[0]+1)][(pos[1]+1)]==2)
cont1++;
 
}
else
if((pos[0]==7)&amp;&amp;(pos[1]==0))//cuenta cuando el jaguar esta en la esquina inferior izquierda
{
 
if(matrix[pos[0]][(pos[1]+1)]==2)
cont1++;
 
if(matrix[(pos[0]-1)][pos[1]]==2)
cont1++;
 
if(matrix[(pos[0]-1)][(pos[1]+1)]==2)
cont1++;
 
}
else
if((pos[0]==0)&amp;&amp;(pos[1]==15))//cuenta cuando el jaguar esta en la esquina superior derecha
{
 
if(matrix[pos[0]][(pos[1]-1)]==2)
cont1++;
 
if(matrix[(pos[0]+1)][(pos[1]-1)]==2)
cont1++;
 
if(matrix[(pos[0]+1)][pos[1]]==2)
cont1++;
 
}
else //cuenta cuando el jaguar esta en la esquina inferior derecha
{
 
if(matrix[pos[0]][(pos[1]-1)]==2)
cont1++;
 
if(matrix[(pos[0]-1)][(pos[1]-1)]==2)
cont1++;
 
if(matrix[(pos[0]-1)][pos[1]]==2)
cont1++;
 
}
// ---------------------------------------&gt; //fin contador_de_minas
 
}//fin funcion que cuenta minas
 
void matrixA_Mapa(int matrix[][16], char mapa[][16], int ll)//inicion funcion que pasa matrix a mapa
{
for(ll=0;ll&lt;8;ll++)//inicio matrix_a_mapa
{
for(int jj=0;jj&lt;16;jj++)
{
if(matrix[ll][jj]==0)//si es igual a cero se pone un campo sin recorrer
mapa[ll][jj]='þ';
else
if(matrix[ll][jj]==1)//si es igual a uno se pone al jaguar
mapa[ll][jj]=0;
else
if(matrix[ll][jj]==3)////si es igual a tres se pone un campo recorrido
mapa[ll][jj]='.';
else
if(matrix[ll][jj]==4)////si es igual a cuatro se pone la llegada
mapa[ll][jj]=((char) 178);
else
if(matrix[ll][jj]==2)
mapa[ll][jj]='þ'; //las minas no se deben mostrar en el juego... no tendria ninguna gracia!
}
 
} //fin matrix_a_mapa
 
}//fin funcion que pasa matrix a mapa
 
void muestraMapa(char mapa[][16], int cont1, int puntaje)//inicio funcion que muestra el mapa
{
system("cls");
cout&lt;&lt;"\n\t\t\t\tMin: "&lt;&lt;cont1&lt;&lt;" Punt: "&lt;&lt;puntaje;
cout&lt;&lt;"\n\n\n\n"; //inicio muetra_mapa
for(int i=0;i&lt;8;i++)
{
 
cout&lt;&lt;"\t\t\t\t";
for(int j=0;j&lt;16;j++)
cout&lt;&lt;mapa[i][j];
 
cout&lt;&lt;endl; //fin muetra_mapa.
};
 
}//fin funcion que muestra el mapa
 
void capturaDireccion(char &amp;x)//inicio funcion que captura direccion
{
 
x= getch();
x= getch();
 
}//fin funcion que captura direccion
 
void registraMovimiento(char x,int pos[], int pos_ant[])//inicio funcion que registra movimiento en matriz
{
if(x=='H') //inicio resgistra_cambio_de_posicion
{
//cout&lt;&lt;"\nArriba. ";
if(pos[0]&gt;0)
{
pos_ant[0]=pos[0];
pos_ant[1]=pos[1];
pos[0]--;
}
}
 
else
 
if(x=='P')
{
//cout&lt;&lt;"\nAbajo. ";
if(pos[0]&lt;7)
{
pos_ant[0]=pos[0];
pos_ant[1]=pos[1];
pos[0]++;
}
}
 
else
if(x=='M')
{
//cout&lt;&lt;"\nDerecha. ";
if(pos[1]&lt;15)
{
pos_ant[0]=pos[0];
pos_ant[1]=pos[1];
pos[1]++;
}
}
else
if(x=='K')
{
//cout&lt;&lt;"\nIzquierda. ";
if(pos[1]&gt;0)
{
pos_ant[0]=pos[0];
pos_ant[1]=pos[1];
pos[1]--;
}
}
else
{
cout&lt;&lt;"Control no programado!. '"&lt;&lt;x&lt;&lt;"'."&lt;&lt;endl;//fin resgistra_cambio_de_posicion
}
}//fin funcion que registra movimiento en matriz
 
void matrixAleatoria(int matrix[][16], int dificultad)// inicio de funcion que asigna un mapa de juego aleatorio, dificultad=1,2 ó 3
{
 
int num=0;
num = rand()%5;
 
if(dificultad==2)
num+=5;
else if(dificultad==3)
num+=10;
//facil
int m0[8][16]={{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,2,0,0,2,0,0,0,0,2,2,0,0,2,0},{0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0},{0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,2},{0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0},{0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},{2,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0}}; //term
int m1[8][16]={{1,0,0,0,0,2,0,2,0,0,0,0,0,2,0,0},{0,0,2,0,0,0,0,0,2,0,2,0,0,0,0,0},{2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},{0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},{2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0}}; //term
int m2[8][16]={{1,0,0,0,0,2,0,2,0,2,0,0,0,2,0,2},{0,0,0,0,2,0,0,0,0,2,0,0,0,0,0,2},{0,0,0,0,0,2,0,2,2,2,0,0,2,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2},{0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; //term
int m3[8][16]={{1,0,0,0,0,0,2,0,0,2,0,2,0,0,0,0},{0,0,0,0,0,0,0,2,0,0,0,2,2,0,0,2},{0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},{2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},{0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,2,0,0,0,0,2,0,0,0}}; //term
int m4[8][16]={{1,0,0,0,2,0,2,2,0,0,2,0,0,0,0,2},{0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},{0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,0},{0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},{0,0,2,0,2,0,0,0,2,0,0,0,0,0,0,0}}; //term
 
//medio
int m5[8][16]={{1,0,0,0,0,0,2,0,0,0,2,0,2,0,0,0},{0,2,0,2,0,0,0,0,0,0,0,0,0,0,2,0},{0,0,2,0,0,0,0,0,0,0,0,2,2,2,0,0},{0,2,0,0,2,0,0,0,2,2,0,0,0,0,0,2},{0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0},{0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,2,0,0,0,0,0,0,0,2,0,0,0,2,0,0},{0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0}};// mapa terminado
int m6[8][16]={{1,0,0,0,0,0,0,0,0,0,2,0,0,0,0,2},{0,0,0,2,2,0,2,0,0,0,0,2,2,2,0,0},{0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0},{2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,2,0,0,0,0,2,0,0,0,0,0,0,2,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0}};// mapa terminado
int m7[8][16]={{1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,2},{0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0},{0,2,0,0,0,0,0,0,2,0,0,2,0,0,2,0},{0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0},{0,2,2,0,0,0,0,0,0,0,2,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},{0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,2},{0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0}};// mapa term
int m8[8][16]={{1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},{0,0,0,0,0,0,0,2,0,0,2,2,0,0,0,0},{2,0,2,0,0,0,0,0,0,0,2,0,0,0,0,0},{2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,2,2,0,2,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,2,2,0,0,0,0,0,0,0,0,0,2,2,0,2},{0,0,0,0,0,2,2,0,0,0,0,0,2,0,0,0}};//mapa term
int m9[8][16]={{1,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0},{0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2},{0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0},{0,0,0,0,0,0,2,0,0,0,0,2,2,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0},{0,0,0,0,0,2,0,2,0,0,2,0,2,0,0,0},{2,2,0,0,0,2,0,0,0,2,0,0,2,0,0,0}};//map term
 
//dificil
int m10[8][16]={{1,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0},{0,2,0,0,0,0,2,0,2,0,0,0,0,0,2,0},{0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0},{0,0,0,2,0,0,0,2,0,0,0,0,0,0,2,2},{0,2,0,0,0,0,0,0,0,0,0,2,0,2,0,0},{0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,2},{0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0},{2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0}};//term
int m11[8][16]={{1,0,0,0,2,2,0,0,2,2,0,0,2,2,0,0},{0,0,2,0,0,0,0,2,0,2,0,0,0,0,0,0},{0,2,0,0,0,2,0,0,2,0,0,0,0,0,2,0},{0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2},{0,0,0,0,2,0,0,2,2,0,0,0,0,0,2,0},{0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0},{0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0}};//term
int m12[8][16]={{1,0,2,0,0,0,0,0,0,0,2,0,0,0,0,0},{0,2,2,0,0,2,0,2,0,0,0,2,0,0,2,0},{0,0,2,0,0,0,0,0,2,0,0,0,0,2,0,0},{0,2,0,0,0,0,0,2,0,2,0,0,0,0,2,0},{0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,2,0,0,0,0,0,0,0,0,0,2,0,0,0},{0,2,0,0,2,0,2,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,2,0,0,2,0,2,0,0}}; //term
int m13[8][16]={{1,0,0,0,2,0,0,2,0,0,0,0,2,0,0,2},{0,0,2,0,0,0,0,0,0,0,2,0,0,2,0,2},{2,0,0,0,0,0,2,0,2,0,0,2,0,0,0,2},{0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,2,0,0,0,2,0,0,2,0,0,0,0,0,2,2},{0,0,0,0,2,0,0,2,0,0,0,0,2,0,0,0},{0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0},{0,0,2,0,2,0,2,0,0,0,0,0,0,0,0,0}}; //term
int m14[8][16]={{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0},{0,2,0,2,0,2,0,0,0,2,0,2,2,0,2,0},{0,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0},{0,0,2,0,0,0,0,2,0,0,0,2,0,0,0,2},{0,2,0,0,0,2,0,0,0,2,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0},{0,2,0,2,2,0,0,2,0,2,0,0,2,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; //term
 
switch(num)
{
case 0: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m0[j][k];
break;
case 1: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m1[j][k];
break;
case 2: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m2[j][k];
break;
case 3: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m3[j][k];
break;
 
case 4: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m4[j][k];
break;
case 5: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m5[j][k];
break;
case 6: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m6[j][k];
break;
case 7: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m7[j][k];
break;
case 8: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m8[j][k];
break;
case 9: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m9[j][k];
break;
case 10: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m10[j][k];
break;
case 11: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m11[j][k];
break;
case 12: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m12[j][k];
break;
case 13: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m13[j][k];
break;
case 14: for(int j=0;j&lt;8;j++)
for(int k=0;k&lt;16;k++)
matrix[j][k] = m14[j][k];
break;
 
default: cout&lt;&lt;"\nmapa no existe!";
}
}// fin de funcion que asigna un mapa de juego aleatorio
 
void mensajeJuegoPerdido(int matrix[][16],char mapa[][16], int pos[], int pos_ant[], int ll,char &amp;rep,int &amp;puntaje)//********************************** inicio funcion muestra mensaje en caso de perder
{
for(ll=0;ll&lt;8;ll++)//inicio matrix_a_mapa (se muestran las minas)
{
for(int jj=0;jj&lt;16;jj++)
{
if(matrix[ll][jj]==0)
mapa[ll][jj]='þ';
else
if(matrix[ll][jj]==1)
mapa[ll][jj]=0;
else
if(matrix[ll][jj]==3)
mapa[ll][jj]='.';
else
if(matrix[ll][jj]==4)
mapa[ll][jj]=0;
else
if(matrix[ll][jj]==2)
mapa[ll][jj]='Ï';
}
 
} //fin matrix_a_mapa
 
mapa[pos[0]][pos[1]]=;
mapa[pos_ant[0]][pos_ant[1]]='.';
 
system("cls");
cout&lt;&lt;"\a\n\t\t\t\t Puntaje: "&lt;&lt;puntaje;
 
cout&lt;&lt;"\n\n\n\n"; //inicio muetra_mapa
for(int i=0;i&lt;8;i++)
{
 
cout&lt;&lt;"\t\t\t\t";
for(int j=0;j&lt;16;j++)
cout&lt;&lt;mapa[i][j];
 
cout&lt;&lt;endl;
} //fin muetra_mapa.
cout&lt;&lt;"\t ##### \n\t# # ## # # ###### #### # # ###### ##### \n\t# # # ## ## # # # # # # # # \n\t# #### # # # ## # ##### # # # # ##### # # \n\t# # ###### # # # # # # # # ##### \n\t# # # # # # # # # # # # # # \n\t ##### # # # # ###### #### ## ###### # # \n\n\n\n";
cout&lt;&lt;"Desea repetir? (S/N):";
rep= getch();
puntaje=0;
cout&lt;&lt;endl;
if(rep!='s')
creditos();
}//********************************** fin funcion muestra mensaje en caso de perder
 
void mensajeJuegoGanado(int matrix[][16],char mapa[][16], int pos[], int pos_ant[], int ll,char &amp;rep,int &amp;puntaje)//******************************* inicio funcion muestra mensaje en caso de ganar
{
for(ll=0;ll&lt;8;ll++)//inicio matrix_a_mapa
{
for(int jj=0;jj&lt;16;jj++)
{
if(matrix[ll][jj]==0)
mapa[ll][jj]='þ';
else
if(matrix[ll][jj]==1)
mapa[ll][jj]=;
else
if(matrix[ll][jj]==3)
mapa[ll][jj]='.';
else
if(matrix[ll][jj]==4)
mapa[ll][jj]=;
else
if(matrix[ll][jj]==2)
mapa[ll][jj]='Ï';
}
 
} //fin matrix_a_mapa
 
mapa[pos[0]][pos[1]]=;
mapa[pos_ant[0]][pos_ant[1]]='.';
 
system("cls");
 
cout&lt;&lt;"\a\n\t\t\t\t Puntaje: "&lt;&lt;puntaje;
 
cout&lt;&lt;"\n\n\n\n"; //inicio muetra_mapa
for(int i=0;i&lt;8;i++)
{
 
cout&lt;&lt;"\t\t\t\t";
for(int j=0;j&lt;16;j++)
cout&lt;&lt;mapa[i][j];
 
cout&lt;&lt;endl;
} //fin muetra_mapa.
cout&lt;&lt;" ### \n # # ## #### #### ## # # ## ##### #### ### \n # # # # # # # # # ## # # # # # # # ### \n ###### # # #### # # # # # # # # # # # # # \n # # ###### # # ### ###### # # # ###### # # # # \n # # # # # # # # # # # ## # # # # # # ### \n # # # # #### #### # # # # # # ##### #### ### \n\n\n\n\n";
 
cout&lt;&lt;"Desea repetir? (S/N):";
rep= getch();
puntaje=0;
cout&lt;&lt;endl;
if((rep=='n')||(rep=='N'))
creditos();
 
}//******************************* fin funcion muestra mensaje en caso de ganar
 
void creditos()//funcion que muestra los creditos del programa
{
system("color 0E");//0e
system("cls");
cout&lt;&lt;"\n +----------------------------------------------------------------------+";
cout&lt;&lt;"\n | | \n | | \n | _ |\"| ___ |\"| _ | \n | _|_|_ _|_|_ /\\#/\\ _|_|_ _|_|_ |\n | (o o) (o o) /(o o)\\ (o o) (o o) |\n |ooO--(_)--Ooo-ooO--(_)--Ooo-ooO--(_)--Ooo-ooO--(_)--Ooo-ooO--(_)--Ooo |\n | |\n | --.-- .--. . |\n | | | : o | |\n | | .--. .-. .-. .-. | | . .-. ---. .-. .--..-.. .-. | |\n | | `--.( )( )( | ; | ( ) .' ( ) | ( |(.-' | |\n | --'--`--' `-'`-`-'`-`-' '--'-' `-`-'`-'--- `-'`-' `-`| `--'`- |\n | ._.' |\n | |\n | .---. . . .--. . . |\n | | o | | : | | |\n | |--- . .-.| .-. | | --.. . .-. | .-.| .--..-. .--. |\n | | | ( |(.-' | : || |( ) |( | | ( )| | |\n | ' -' `-`-'`-`--'`- `--'`--`-`-'`-`-`-'`-' `-' ' `- |\n";
cout&lt;&lt;" +----------------------------------------------------------------------+";
cout&lt;&lt;" DESARROLLADORES.\n\n";
Sleep(2000);
//system("color 73");//0A 03 0B
}
