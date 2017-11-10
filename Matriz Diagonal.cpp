#include <iostream>

using namespace std;
int i,j;
int a =0 ;
int tam()
{
	cout<<"de que tamanio es la matriz\n";
	cin>>a;
	int mat[a][a];
	return (a);
}
int llenar(int a)
{ 
	int mat[a][a];
	for (i=0;i<a;i++)
	{
		for(j=0;j<a;j++)
		{
			cout<<"Llena la posicion "<<i+1<<","<<j+1<<" de la matriz ";
			cin>>mat[i][j];
		}
	}
	return (mat[a][a]);		
} 
int matriz(int a)
{
	llenar(a);
	int mat[a][a];
	for (i=0;i<a;i++)
	{
		for(j=0;j<a;j++)
		{
			cout<<mat[i][j]<<"\t";
		}
		cout<<endl;
	}
}
main()
{
	matriz(tam());
}
