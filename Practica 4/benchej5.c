#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64)
	const char* os = "Windows.";
#else
#ifdef __linux
	const char* os = "Linux.";
#else
#ifdef __MACOS
    const char* os = "Mac OS.";
#else
	const char* os = "SO desconocido.";
#endif
#endif
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#define T3_ARCH_TYPE 64
#else
#define T3_ARCH_TYPE 32
#endif

void ordenacion(int *A,int n){
	int min,i,j,aux;
	int vein = (n*25)/100;
	int cinc = (n*50)/100;
	int set = (n*75)/100;
	for (i=0; i<n-1; i++){
		min=i;
		for(j=i+1; j<n; j++){
			if(A[min] > A[j]) min=j;
		}
		aux=A[min];
		A[min]=A[i];
		A[i]=aux ; 
		if(i == vein){
			printf("Progreso: 25%%...\n");
		}
		if(i == cinc){
			printf("Progreso: 50%%...\n");
		}
		if(i == set){
			printf("Progreso: 75%%...\n");
		}
	} 
}

int main(int argc,char *argv[]){

	int n=50000;
	int p=5000;
	int i,j,k,a,b,d,mul;
	int c=n;
	double  ttotal=0;
	double titer=0;
	int *x, *y, *z;

	struct timespec cgt1,cgt2; double ncgt; //Variable para el tiempo

	x=(int*) malloc(n*sizeof(int));
	y=(int*) malloc(n*sizeof(int));
	z=(int*) malloc(n*sizeof(int));

	if((x==NULL) || (y==NULL)){
		printf("Error en la reserva");
		exit(-2);
	}
	
	int vein = (p*25)/100;
	int cinc = (p*50)/100;
	int set = (p*75)/100;

	printf("*********************************\n");
	printf("Sistema Operativo = %s\n", os);
	printf("Arquitectura = %d bits \n", T3_ARCH_TYPE);
	printf("*********************************\n");
	printf("\n");

	printf("Iniciando benchmark...\n");
	printf("\n");
	//Benchmark para la CPU
	printf("******Benchmark para la CPU: ******\n");
	for(k=0; k<=p; k++){

		for(i=0; i<=n; i++){
			a=(rand()%10);
			b=(rand()%10);
			d=(rand()%10);
			x[i]=a;
			y[i]=b;
			z[i]=d;
		}

		clock_gettime(CLOCK_REALTIME,&cgt1);
		//Multiplicación vector por escalar
		for(j=0; j<=n; j++){
			y[j]=c*x[j]+y[j];
		}

		//Multiplicación de vectores
		for(i=0; i<=n; i++){
			mul=x[i]*y[i];
			z[i] = mul;
		}

		clock_gettime(CLOCK_REALTIME,&cgt2);
		ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+(double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
		ttotal += ncgt;

		if(k == vein){
			printf("Progreso: 25%%...\n");
		}
		if(k == cinc){
			printf("Progreso: 50%%...\n");
		}
		if(k == set){
			printf("Progreso: 75%%...\n");
		}
	}

	//Benchmark para la memoria
	printf("\n");
	printf("******Benchmark para la memoria: ******\n");
	clock_gettime(CLOCK_REALTIME,&cgt1);
	ordenacion(y,n);
	clock_gettime(CLOCK_REALTIME,&cgt2);

	ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+(double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
	float tmem = ncgt;
	
	printf("\n");

	titer = ttotal/p;
	int aux =  1/titer;
	int aux2 = 1/tmem;
	aux +=aux2;
	printf("**************************************\n");
	printf("Tiempo por iteración: %f\n", titer);
	printf("Tiempo total CPU: %f\n", ttotal);
	printf("Tiempo en ordenar el vector: %f\n",tmem);
	printf("-> PUNTUACION: %d\n",aux);
	printf("**************************************\n");
	return 0;

}











