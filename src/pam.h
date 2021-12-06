#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <string.h>


//definition structure pour le groupe
typedef struct Cluster {
	int centre;
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


#define maximum(x, y) (x > y ? x : y)
#define minimum(x, y) (x < y ? x : y)

//prototypes des fonctions
//int minimum(int,int);
//int maximum(int,int);
float DistanceManathan(Point,Point);
void afficheCluster(Cluster);
void initPoints(P_Point,int);
void initClusters(P_Point,P_Cluster,int,int);
void initDistance(float *distance[],P_Point,int);
void affecterPointsMedoideProche(P_Point,P_Cluster, float *distance[], int, int);
Cluster selectBestClusterMedoids(P_Point, float *distance[], Cluster , int , SDL_Renderer * ,Color);
void AlgoPAM( int, int, SDL_Window*);