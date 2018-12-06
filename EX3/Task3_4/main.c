#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265

void task1();
void task2();
void task3();
void task4();

int main()
{
    /* code */
    //task1();
    //task2();
    //task3();
    //task4();
    return 0;
}

void task1(){
    // declarations and initialization
    long int N;
    double sum = 0;
    double x;
    double I_N;
    double sum2 = 0;
    double sigma_f2;
    double sigma_f;
    double sigma_I;
    long int N_i[4] = {10, 100, 1000, 10000};


	const gsl_rng_type *T;
	gsl_rng *q;
	gsl_rng_env_setup();
	T = gsl_rng_default;
	q = gsl_rng_alloc(T);
	gsl_rng_set(q,time(NULL));

	
    printf("N, I_N, sigma_f, sigma_I\n");

    for(size_t ix = 0; ix < 4; ix++){

        N = N_i[ix];
        for(size_t jx = 0; jx < N; jx++){
            x = gsl_rng_uniform(q);
            sum += x*(1-x);
            sum2 += (x*(1-x))*(x*(1-x));    
        }

        I_N = sum/N;
        sigma_f2 = sum2/N - I_N*I_N;
        sigma_I = sqrt(sigma_f2/N);
        sigma_f = sqrt(sigma_f2);

        printf("%ld, %f, %f, %f\n", N, I_N, sigma_f, sigma_I);
    }
    

	// free memory
	gsl_rng_free(q);
}

void task2(){
    // declarations and initialization
    long int N;
    double x;
    double I_N;
    double sigma_g2;
    double sigma_g;
    double sigma_I;
    long int N_i[4] = {10, 100, 1000, 10000};
   


	const gsl_rng_type *T;
	gsl_rng *q;
	gsl_rng_env_setup();
	T = gsl_rng_default;
	q = gsl_rng_alloc(T);
	gsl_rng_set(q,time(NULL));


    FILE *ptr = fopen("10000samples.txt", "w");
    if(ptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }


	// generate uniform random number
    printf("N, I_N, sigma_g, sigma_I\n");

    for(size_t ix = 0; ix < 4; ix++){
        N = N_i[ix];
        double sum = 0;
        double sum2 = 0;

        for(size_t jx = 0; jx < N; jx++){
            double xi = gsl_rng_uniform(q);
            x = acos(1-2*xi)/PI;
            double f = x*(1-x);
            double p = PI*sin(PI*x)/2;
            double g = f/p; 
            sum += g;
            sum2 += g*g;

            N = N_i[ix];
            if(ix == 3){
                // Save data to plot histogram
                fprintf(ptr, "%.3f\n", x);
            }    
        }

        I_N = sum/N;
        sigma_g2 = sum2/N - I_N*I_N;
        sigma_I = sqrt(sigma_g2/N);
        sigma_g = sqrt(sigma_g2);

        //printf("%f, %f\n", sum2/N, I_N*I_N);
        printf("%ld, %f, %f, %f\n", N, I_N, sigma_g, sigma_I);
    }
    

	// free memory
	gsl_rng_free(q);
    fclose(ptr);
}

void task3(){
    int M = 3;
    int N = 10000000;
    double delta = 2.5;
    int nr_reject = 0;
    double sum = 0;
    double I_N;

    const gsl_rng_type *T;
	gsl_rng *q;
	gsl_rng_env_setup();
	T = gsl_rng_default;
	q = gsl_rng_alloc(T);
	gsl_rng_set(q,time(NULL));

    /*FILE *ptr = fopen("metrosamples1000.txt", "w");
    if(ptr == NULL){
        printf("Error opening file!\n");
        exit(1);
    }
    */

    double * tauentries = (double*)malloc(sizeof(double)*M*M);
    double ** tau = (double**)malloc(sizeof(double*)*M);

    double * x = (double*)malloc(sizeof(double)*N);
    double * y = (double*)malloc(sizeof(double)*N);
    double * z = (double*)malloc(sizeof(double)*N);
   
    

    for(size_t ix = 0, jx = 0; ix < M; ix++, jx+=M){
        tau[ix] = tauentries + jx;
    }


    x[0] = 1.0;
    y[0] = 1.0;
    z[0] = 1.0;


    for(size_t ix = 1; ix < N; ix++){
        double xm = x[ix-1];
        double ym = y[ix-1];
        double zm = z[ix-1];

        double r = gsl_rng_uniform(q);
        double xn = xm + delta*(r - 0.5);
        r = gsl_rng_uniform(q);
        double yn = ym + delta*(r - 0.5);
        r = gsl_rng_uniform(q);
        double zn = zm + delta*(r - 0.5);

        double pn = powf(PI, -3/2)*exp(-(xn*xn + yn*yn + zn*zn));
        double pm = powf(PI, -3/2)*exp(-(xm*xm + ym*ym + zm*zm));

        double a = pn/pm;
        double xi = gsl_rng_uniform(q);

        if( a >= xi){
            x[ix] = xn;
            y[ix] = yn;
            z[ix] = zn;
        }
        else{
            x[ix] = xm;
            y[ix] = ym;
            z[ix] = zm;
            nr_reject += 1;
        }

        sum += x[ix]*x[ix] + x[ix]*x[ix]*y[ix]*y[ix] + 
        x[ix]*x[ix]*y[ix]*y[ix]*z[ix]*z[ix]; 
        //fprintf(ptr, "%.3f, %.3f, %.3f\n", x[ix], y[ix], z[ix]);
    }

    I_N = sum/N;

    printf("I_N: %f\n", I_N);
    

    free(tau);
    free(tauentries);
    free(x);
    free(y);
    free(z);
    //fclose(ptr);
    gsl_rng_free(q);
}

void task4(){
    int i, N;
    FILE *in_file;
    int k = 0;
    N = 1e6; /* The number of lines in MC.txt. */
    double mean = 0;
    double squaremean = 0;
    double corr = 0;
    double phi_k;
    double varf;
    double state = 1;
    int unused __attribute__((unused));
    

    double *fi = malloc((N) * sizeof (double));
    
  
    /* Read data from file. */
    in_file = fopen("MC.txt","r");
    for (i=0; i<N; i++) {
        unused = fscanf(in_file,"%lf",&fi[i]);
    }

    for(size_t ix = 0; ix < N; ix++){
        mean += fi[ix];
        squaremean += fi[ix]*fi[ix];
    }

    mean = mean/N;
    squaremean = squaremean/N;
    varf = squaremean - mean*mean;



    FILE *ptr = fopen("task4.txt", "w");
    if(ptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }


    for(size_t ix = 0; ix < 50; ix ++){
        corr = 0;
        for(size_t jx = 0; jx < N-k; jx++){
            corr += (fi[jx+k]-mean)*(fi[jx]-mean);
        }

        corr = corr/(N-k);
        phi_k = (corr)/varf;

        if(state){
            if((phi_k-0.135) < 0.001){
                printf("k: %d, phi_k: %f\n", k, phi_k);
                state = 0;
            }
        }

        fprintf(ptr, "%d, %.3f\n", k, phi_k);
        k += 10;
        
    }
    

    // Block averaging

    FILE *ptr1 = fopen("block.txt", "w");
    if(ptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    int N_s = 500;
    int block_size = 10;
    int nbr_blocks;
    double Fj;
    double varF;
    double meanF = 0;
    double squaremeanF = 0;
    double s;


    for(size_t ix = 0; ix < N_s; ix++){
        nbr_blocks = (int)(N/block_size);
        meanF = 0;
        squaremeanF = 0;

        for(size_t jx = 0; jx < nbr_blocks; jx++){
            Fj = 0;
            for(size_t kx = 0; kx < block_size; kx++){
                 Fj += fi[kx + jx*block_size];
            }
            Fj = Fj/block_size;
            meanF += Fj;
            squaremeanF += Fj*Fj;
        }
        meanF = meanF/nbr_blocks;
        squaremeanF = squaremeanF/nbr_blocks;
        varF = squaremeanF - meanF*meanF;
        s = (block_size*varF)/(varf);

        //printf("block size: %d, s: %f\n", block_size, s);
        fprintf(ptr1, "%d, %.3f\n", block_size, s);
        block_size += 10;

        
    }

    

    
    fclose(in_file);
    fclose(ptr);
    free(fi);
    fclose(ptr1);
}