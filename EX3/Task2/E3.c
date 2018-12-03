#include <gsl/gsl_rng.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define M_PI 3.14159265358979323846
#define EXACT_VALUE 0.16667
void funcRandUni(double *arr, int N){
	// declarations and initialization
  double u[N];
	const gsl_rng_type *T;
	gsl_rng *q;
	gsl_rng_env_setup();
	T = gsl_rng_default;
	q = gsl_rng_alloc(T);
	gsl_rng_set(q,time(NULL));

	// generate uniform random number
  for(size_t i; i<N; i++)
	  u[i] = gsl_rng_uniform(q);
    memcpy(arr,u,sizeof(u));
  for(size_t i; i<N; i++)
    arr[i]=acos(1-2*arr[i])/M_PI;

  for(size_t i; i<N; i++)
    arr[i]=(arr[i]*(1-arr[i]))/(((M_PI/2)*sin(M_PI*arr[i])));
	// free memory
	gsl_rng_free(q);
}

int main()
{
double tempSum;
int N[3]={10,100,1000};
double Predicted[3];
//double error[N];
printf("\n--------------------------------------\n");
for(size_t i=2; i<3; i++){
  tempSum = 0;
  double *randNums = (double*) malloc(sizeof(double) * N[i]);
  funcRandUni(randNums, N[i]);
  for(size_t j=0; j<N[i]; j++)
    tempSum+=randNums[j];
  
  Predicted[i]=tempSum/N[i];
  printf("Predicted integral: %f\n", Predicted[i]);
  printf("Absolute Error: %f\n\n", fabs(Predicted[i]-EXACT_VALUE));
  free(randNums);

}
printf("--------------------------------------\n");

return 0;
}
