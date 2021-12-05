#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include "pam.h"




//Definition des fonctions
//retourne le min de 2 valeur
/*int minimum(int i , int j){
    int m=(i<j) ? i:j;
	return m;
}
//retourne le max de 2 valeur
int maximum(int i , int j){
    int m=(i>j) ? i:j;
	return m;
}*/
//fonction qui retourne distance entre 2points
float DistanceManathan(Point a,Point b){
    float s=sqrt(pow(a.Courage-b.Courage,2)+pow(a.Loyaute-b.Loyaute,2)+ pow(a.Sagesse-b.Sagesse,2)+
                 pow(a.Malice-b.Malice,2));
	return s;
}
//fonction pour l'intialisation de n points
void initialisePoints(P_Point points,int n){
	int i;

	char* file_path = "choixpeauMagique.csv";
	FILE* fp = fopen(file_path, "r");

	if (!fp)
		printf("Can't open file\n");

	else {
		// Here we have taken size of
		// array 1024 you can modify it
		char buffer[1024];

		int row = 0;
		int column = 0;

		while (fgets(buffer,
					1024, fp)) {
			column = 0;
			row++;

			// To avoid printing of column
			// names in file can be changed
			// according to need
			if (row == 1)
				continue;

			// Splitting the data
			char* value = strtok(buffer, ";");

			while (value) {
				// Column 1
				if (column == 0) {
					printf("Name :");

				}

				// Column 2
				if (column == 1) {
					printf("\tCourage :");
					points[row-1].Courage = atof(value);
				}


				// Column 3
				if (column == 2) {
					printf("\tLoyaute :");
					points[row-1].Loyaute = atof(value);
				}


				// Column 4
				if (column == 3) {
					printf("\tSagesse :");
					points[row-1].Sagesse = atof(value);
				}


				// Column 5
				if (column == 4) {
					printf("\tMalice :");
					points[row-1].Malice = atof(value);
				}


				// Column 6
				if (column == 5) {
					printf("\tMaison :");
				}

				printf("%s", value);
				value = strtok(NULL, ";");
				column++;
			}

			printf("\n");
		}

		// Close the file
		fclose(fp);
	}

	/*for(i=0;i<n;i++){
        points[i].Courage=rand()%(40 + 1) + 1;
        points[i].Loyaute=rand()%(30 + 1) + 1;
        points[i].Sagesse=rand()%(30 + 1) + 1;
        points[i].Malice =rand()%(30 + 1) + 1;

    } */
}
// fonction pour afficher un cluster
void afficheCluster(P_Cluster cluster)
{
    printf("cluster : %d\n",cluster->centre);
    printf("Taille du cluster : %d\n",cluster->taille);
}
//fonction d'initialisation de k groupes
void initClusters(P_Point points ,P_Cluster clusters ,int n ,int k){
	int i;
	for(i=0 ;i<k ;i++){
		clusters[i].centre=i;
		clusters[i].taille=0;
	}
}

//fonction initialisation des distances de touts les points
void initDistance(float *distance[],P_Point points,int n){
	int i,j;
	for(i=0;i<n;i++){
			for(j=0;j<i+1;j++){
				distance[i][j]=DistanceManathan(points[i],points[j]);
			}
	}
}

//fonction affectation des points au medoid le plus proche
void affecterPointsMedoideProche(P_Point points, P_Cluster clusters, float *distance[], int n, int k){
	int i,j;
	for(i=0;i<k;i++)
		clusters[i].taille=0;
	for(i=0;i<n;i++){
		Cluster *cluster=&clusters[0]; 
		int tp = cluster->centre;
		for(j=1;j<k;j++){
			Cluster *clust=&clusters[j];
			int tmp=clust->centre;
			if(distance[maximum(i,tmp)][minimum(i,tmp)]<distance[maximum(i,tp)][minimum(i,tp)]){
				cluster=clust;
				tp=cluster->centre;
			}
		}
		points[i].cluster=cluster;
		cluster->taille++;
	}
}
//fonction retournant le meilleur group
Cluster selectBestClusterMedoids(P_Point points, float *distance[], Cluster cluster , int n, SDL_Renderer * renderer,Color color){
	int i,j=0;
	float dist=0;
	float t=0;
	int* kmed=(int*)malloc(sizeof(int)*cluster.taille);
	int b=cluster.centre;
	for(i=0;i<n;i++){
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,255);
		if(points[i].cluster->centre==cluster.centre){
            SDL_RenderDrawLine(renderer,points[b].Courage*15,points[b].Loyaute*15,points[i].Courage*15,points[i].Loyaute*15);
            SDL_RenderPresent(renderer);
			kmed[j]=i;
			j++;
		}
	}
	for(i=0;i<n;i++)
		dist+=distance[maximum(i,b)][minimum(i,b)];

	for(i=0;i<cluster.taille;i++){
		t=0;
		int a=kmed[i];

		for(j=0;j<n;j++)
			t+=distance[maximum(j,a)][minimum(j,a)];

		if(t<dist){
			cluster.centre=a;
			dist=t;
		}
	}
	free(kmed);
	return cluster;
}
//fonction qui applique l'algorithme KMedoids (PAM)
void AlgoPAM( int n, int k, SDL_Window * window){
    //Code--
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    P_Point points=(P_Point)malloc(n*sizeof(Point));
	P_Cluster clusters=(P_Cluster)malloc(k*sizeof(Cluster));
    int i,j,changeTest;
    float *distance[n];
	for(i=0;i<n;i++){
			distance[i]=(float*)malloc((i+1)*sizeof(float));
	}
    Color color[k];
	for(i=0,j=k;i<k;i++,j--)
        {
            color[i].r=j*200;
            color[i].g=i*80;
            color[i].b=j*130;
        }
	initPoints(points,n);
	initClusters(points, clusters , n, k);
	initDistance(distance,points,n);
	do{
		changeTest=0;
		P_Cluster tmpClusters=(P_Cluster)malloc(sizeof(Cluster)*k);
		affecterPointsMedoideProche(points,clusters,distance,n,k);
		for(i=0;i<k;i++){
		tmpClusters[i]=selectBestClusterMedoids(points,distance,clusters[i],n,renderer,color[i]);
		}
		for(i=0;i<k;i++)
			if(tmpClusters[i].centre != clusters[i].centre){
				changeTest=1;
				afficheCluster(tmpClusters);
				break;
			}
		if(changeTest){
            clusters=tmpClusters;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
            SDL_RenderClear(renderer);
		}

	}while(changeTest==1);

    for(i=0;i<k;i++){
            int medoid=clusters[i].centre;
            SDL_SetRenderDrawColor(renderer, color[i].r, color[i].g, color[i].b,255);
            for(j=0;j<n;j++){
                if(points[j].cluster->centre==medoid){
                    SDL_Rect rectangle;
                    rectangle.x = points[j].Courage*15;
                    rectangle.y = points[j].Loyaute*15;
                    rectangle.w = 4;
                    rectangle.h = 4;
                    SDL_RenderFillRect(renderer, &rectangle);
                }
            }
        }
    SDL_RenderPresent(renderer);
}
