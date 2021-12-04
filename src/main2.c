
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
//definition structure couleur
typedef struct Color{
    int r;
    int g;
    int b;
}Color;

typedef Point* P_Point ;
//prototypes des fonctions
int minimum(int,int);
int maximum(int,int);
float getDistance(Point,Point);
void afficheCluster(P_Cluster Cluster);
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

    s=sqrt(pow(a.Courage-b.Courage,2)+pow(a.Loyaute-b.Loyaute,2));
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
					printf("\tVille :");
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

	for(i=0;i<n;i++){
        points[i].Courage=rand()%(40 + 1) + 1;
        points[i].Loyaute=rand()%(30 + 1) + 1;
        points[i].Sagesse=rand()%(30 + 1) + 1;
        points[i].Malice =rand()%(30 + 1) + 1;

    } 
}
// fonction pour afficher un cluster
void afficheCluster(P_Cluster cluster)
{
    printf("Medoid: %d\n",cluster->medoid);
    printf("Taille: %d\n",cluster->taille);
}
//fonction d'initialisation de k groupes
void initialiseClusters(P_Point points ,P_Cluster clusters ,int n ,int k){
	int i;
	for(i=0 ;i<k ;i++){
		clusters[i].medoid=i;
		clusters[i].taille=0;
	}
}

//fonction initialisation des distances de touts les points
void initialiseDistance(float *distance[],P_Point points,int n){
	int i,j;
	for(i=0;i<n;i++){
			for(j=0;j<i+1;j++){
				distance[i][j]=getDistance(points[i],points[j]);
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
		int mid = cluster->medoid;
		for(j=1;j<k;j++){
			Cluster *tmpCluster=&clusters[j];
			int tmpmid=tmpCluster->medoid;
			if(distance[maximum(i,tmpmid)][minimum(i,tmpmid)]<distance[maximum(i,mid)][minimum(i,mid)]){
				cluster=tmpCluster;
				mid=cluster->medoid;
			}
		}
		points[i].cluster=cluster;
		cluster->taille++;
	}
}
//fonction retournant le meilleur group
Cluster selectBestClusterMedoids(P_Point points, float *distance[], Cluster cluster , int n,Color color){
	int i,j=0;
	float totalDist=0;
	float tmpTotalDist=0;
	int* medoidPoints=(int*)malloc(sizeof(int)*cluster.taille);
	int medoid=cluster.medoid;
	for(i=0;i<n;i++){

		if(points[i].cluster->medoid==cluster.medoid){
			medoidPoints[j]=i;
			j++;
		}
	}
	for(i=0;i<n;i++)
		totalDist+=distance[maximum(i,medoid)][minimum(i,medoid)];

	for(i=0;i<cluster.taille;i++){
		tmpTotalDist=0;
		int tmpMedoid=medoidPoints[i];

		for(j=0;j<n;j++)
			tmpTotalDist+=distance[maximum(j,tmpMedoid)][minimum(j,tmpMedoid)];

		if(tmpTotalDist<totalDist){
			cluster.medoid=tmpMedoid;
			totalDist=tmpTotalDist;
		}
	}
	free(medoidPoints);
	return cluster;
}
//fonction qui applique l'algorithme KMedoids (PAM)
void pam( int n, int k){

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
	initialisePoints(points,n);
	initialiseClusters(points, clusters , n, k);
	initialiseDistance(distance,points,n);
	do{
		changeTest=0;
		P_Cluster tmpClusters=(P_Cluster)malloc(sizeof(Cluster)*k);
		affecterPointsMedoideProche(points,clusters,distance,n,k);
		for(i=0;i<k;i++){
		tmpClusters[i]=selectBestClusterMedoids(points,distance,clusters[i],n,color[i]);
		}
		for(i=0;i<k;i++)
			if(tmpClusters[i].medoid != clusters[i].medoid){
				changeTest=1;
				afficheCluster(tmpClusters);
				break;
			}
		if(changeTest){
            clusters=tmpClusters;

		}

	}while(changeTest==1);

    for(i=0;i<k;i++){
            int medoid=clusters[i].medoid;

            for(j=0;j<n;j++){
                if(points[j].cluster->medoid==medoid){

                }
            }
        }

}
int main(int argc, char** argv)
{
    int quit = 0;
  
	int n=50;//points
	int k=4;//groupes
	if(k>n)exit(0);

    pam(n,k);

    return 0;
}
