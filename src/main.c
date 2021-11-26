#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <string.h>


//definition structure pour le groupe
typedef struct Cluster {
	int medoid;
	int taille;
}Cluster;
typedef Cluster* P_Cluster ;

//definition structure point
typedef struct Point {
	float Courage;
	float Loyaute;
	float Sagesse;
	float Malice;
	P_Cluster cluster;
}Point;
typedef Point* P_Point ;

//definition structure couleur
typedef struct Color{
    int r;
    int g;
    int b;
}Color;

//prototypes des fonctions
int minimun(int,int);
int maximum(int,int);
float getDistance(Point,Point);
void afficheCluster(Cluster);
void initialisePoints(P_Point,int);
void initialiseClusters(P_Point,P_Cluster,int,int);
void initialiseDistance(float *distance[],P_Point,int);
void affecterPointsMedoideProche(P_Point,P_Cluster, float *distance[], int, int);







//Definition des fonctions
//retourne le min de 2 valeur
int minimum(int i , int j){
    int m=(i<j) ? i:j;
	return m;
}

//retourne le max de 2 valeur
int maximum(int i , int j){
    int m=(i>j) ? i:j;
	return m;
}

//fonction qui retourne distance entre 2points
float getDistance(Point a,Point b){
    float s=sqrt(pow(a.Courage-b.Courage,2)+pow(a.Loyaute-b.Loyaute,2)+ pow(a.Sagesse-b.Sagesse,2)+
                 pow(a.Malice-b.Malice,2));
	return s;



	int main(int argc, char** argv)
{
    

    return 0;
}