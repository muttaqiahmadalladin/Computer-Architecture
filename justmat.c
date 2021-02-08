#include<stdio.h>
#include<sys/time.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
long loop_interchange_0();//code for most unoptimised matrix multiplication
long loop_interchange_1();
long loop_interchange_2();
long loop_interchange_3();
long loop_interchange_4();
long loop_interchange_5();
long matmul_with_tempVar();
long Blocking_mult(int block_size);
bool matmul_checker();
double SD(long time_array[]);// calculates standard deviation for documentation purposes
double mean(long time_array[]);// calculates mean of array
long median(long time_array[]);//calculates median of array
void result_martix_reset();//to reset the result matrix for the next multiplication
//void matrix_initialisation();
// Matrices declared as global variables to avoid stackoverflow (Segmentation error :11)
double MA[1024][1024];
double MB[1024][1024];
double MC[1024][1024];//stores the result from basic multiplication for later comparisn
double MD[1024][1024];
int main()
{

    int i,j,k;

    float average, StandardDeviation;
    long time_record[21],med,tme;
    //initialisation of matrices
    for(i=0;i<1024;i++){
        for(j=0;j<1024;j++){
            MA[i][j]=rand();
            MB[i][j]=rand();
            MC[i][j]=0;
            MD[i][j]=0;
            //printf("   i=%d j=%d  ",i,j);
        }
    }
    printf("matrix initialisation complete\n");
    //initialising matrix c inorder to compare
    for (i=0;i<1024;i++){
        for(j=0;j<1024;j++){
            for(k=0;k<1024;k++){
                MC[i][j]+=MA[i][k]*MB[k][j];

            }
        }
    }
    printf("creation of matrix for comapring multiplications (MC) complete\n");
    //matrix multiplication loop interchange 0 (unoptimised with time)
    printf("time taken for loop interchange 0 order(k,j,i) in microseconds: \n");
    for (i=0;i<21;i++){
        time_record[i]=loop_interchange_0();
        if(matmul_checker()){}
        else {
            printf("error: matrix multiplication not propper(matrices not equal)");
        }
        result_martix_reset();
    }
    printf("\nThe statistics of this operation are as follows:\n");
    printf("median is %ld \n",median(time_record));
    printf("mean is %f \n", mean(time_record));
    printf("standard deviation is %f \n", SD(time_record));

    result_martix_reset();

    //matrix multiplication loop interchange 1 order (i,j,k)
    printf("time taken for loop interchange 1 order (i,j,k) in microseconds: \n");
    for (i=0;i<21;i++){
        time_record[i]=loop_interchange_1();
        if(matmul_checker()){}
        else {
            printf("error: matrix multiplication not propper(matrices not equal)");
        }
        result_martix_reset();
    }
    printf("\nThe statistics of this operation are as follows:\n");
    printf("median is %ld \n",median(time_record));
    printf("mean is %f \n", mean(time_record));
    printf("standard deviation is %f \n", SD(time_record));

    result_martix_reset();

    //loop interchange 2 
    printf("time taken for loop interchange 2 order(i,k,j) in microseconds: \n");
    for (i=0;i<21;i++){
        time_record[i]=loop_interchange_2();
        if(matmul_checker()){}
        else {
            printf("error: matrix multiplication not propper(matrices not equal)");
        }
        result_martix_reset();
    }
    printf("\nThe statistics of this operation are as follows:\n");
    printf("median is %ld \n",median(time_record));
    printf("mean is %f \n", mean(time_record));
    printf("standard deviation is %f \n", SD(time_record));

    result_martix_reset();

    //loop interchange 3
    printf("time taken for loop interchange 3 order(j,k,i) in microseconds: \n");
    for (i=0;i<21;i++){
        time_record[i]=loop_interchange_3();
        if(matmul_checker()){}
        else {
            printf("error: matrix multiplication not propper(matrices not equal)");
        }
        result_martix_reset();
    }
    printf("\nThe statistics of this operation are as follows:\n");
    printf("median is %ld \n",median(time_record));
    printf("mean is %f \n", mean(time_record));
    printf("standard deviation is %f \n", SD(time_record));

    result_martix_reset();

    //loop interchange 4
    printf("time taken for loop interchange 4 order(j,i,k) in microseconds: \n");
    for (i=0;i<21;i++){
        time_record[i]=loop_interchange_4();
        if(matmul_checker()){}
        else {
            printf("error: matrix multiplication not propper(matrices not equal)");
        }
        result_martix_reset();
    }
    printf("\nThe statistics of this operation are as follows:\n");
    printf("median is %ld \n",median(time_record));
    printf("mean is %f \n", mean(time_record));
    printf("standard deviation is %f \n", SD(time_record));

    result_martix_reset();
    
    //loop interchange 5
    printf("time taken for loop interchange 5 order(k,i,j) in microseconds: \n");
    for (i=0;i<21;i++){
        time_record[i]=loop_interchange_5();
        if(matmul_checker()){}
        else {
            printf("error: matrix multiplication not propper(matrices not equal)");
        }
        result_martix_reset();
    }
    printf("\nThe statistics of this operation are as follows:\n");
    printf("median is %ld \n",median(time_record));
    printf("mean is %f \n", mean(time_record));
    printf("standard deviation is %f \n", SD(time_record));

    result_martix_reset();
    
    printf("time taken for blocking is as follows:\n");
    for(j=1;j<=1024;j=j*2){
        for (i=0;i<21;i++){
        
            time_record[i]=Blocking_mult(j);
            if (matmul_checker()){
                //printf("time taken for block size of %d is %ld microseconds \n",i,tme);
            }
            else{
                printf("\nerror: matrix multiplication not propper(matrices not equal)\n");
            }
            result_martix_reset();
        }
        printf("for block size of %d",j);
        printf("\nThe statistics of this operation are as follows:\n");
        printf("median is %ld \n",median(time_record));
        printf("mean is %f \n", mean(time_record));
        printf("standard deviation is %f \n", SD(time_record));


    }



    //the lines below have been used for testing and debugging of program functions
    /*

    tme=loop_interchange_0();
    printf("time taken for loop interchange 0(order k,j,i) is %ld microseconds \n",tme);
    
    result_martix_reset();

    //matrix mult for row interchange 1 (order i,j,k)
    tme=loop_interchange_1();
    if (matmul_checker()){
        printf("time taken for loop interchange 1(order i,j,k) is %ld microseconds \n",tme);
    }//in general found this to be about 10 seconds faster
    
    result_martix_reset();

    tme=loop_interchange_2();//interchamge 2 (order i,k,j)
    if (matmul_checker()){
        printf("time taken for loop interchange 2(order i,k,j) is %ld microseconds \n",tme);
    }

    result_martix_reset();

    tme=loop_interchange_3();//interchamge 3 (order j,k,i)
    if (matmul_checker()){
        printf("time taken for loop interchange 3(order j,k,i) is %ld microseconds \n",tme);
    }
    
    result_martix_reset();

    tme=loop_interchange_4();//interchamge 4 (order j,i,k)
    if (matmul_checker()){
        printf("time taken for loop interchange 4(order j,i,k) is %ld microseconds \n",tme);
    }

    result_martix_reset();

    tme=loop_interchange_5();//interchamge 5 (order k,i,j)
    if (matmul_checker()){
        printf("time taken for loop interchange 5(order k,i,j) is %ld microseconds \n",tme);
    }

    result_martix_reset();


    //best interchange matrix with temp variabe
    tme=matmul_with_tempVar();
    if (matmul_checker()){
        printf("time taken for loop interchange (order i,j,k) with temp is %ld microseconds \n",tme);
    }

    result_martix_reset();
    for(i=1;i<1024;i=i*2){
        tme=Blocking_mult(i);
        if (matmul_checker()){
            printf("time taken for block size of %d is %ld microseconds \n",i,tme);
        }
        result_martix_reset();
    }*/














    return 0;
}


long loop_interchange_0()//most unoptimused function (loop order k j i)
{
    int i,j,k;
    struct timeval before,after;
    gettimeofday(&before, NULL);
    for (k=0;k<1024;k++){
        for(j=0;j<1024;j++){
            for(i=0;i<1024;i++){
                MD[i][j]+=MA[i][k]*MB[k][j];

            }
        }
    }
    gettimeofday(&after, NULL);
    //printf("Time taken to count to 10^5 is : %ld micro seconds\n", ((after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec)));
    return ((after.tv_sec * 1000000 + after.tv_usec) -
    (before.tv_sec * 1000000 + before.tv_usec));
}

long loop_interchange_1()//loop order i j k has been interchanged
{
    int i,j,k;
    struct timeval before,after;
    gettimeofday(&before, NULL);
    for (i=0;i<1024;i++){
        for(j=0;j<1024;j++){
            for(k=0;k<1024;k++){
                MD[i][j]+=MA[i][k]*MB[k][j];

            }
        }
    }
    gettimeofday(&after, NULL);
    //printf("Time taken to count to 10^5 is : %ld micro seconds\n", ((after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec)));
    return ((after.tv_sec * 1000000 + after.tv_usec) -
    (before.tv_sec * 1000000 + before.tv_usec));
}

long loop_interchange_2()//loop order i k j has been interchanged
{
    int i,j,k;
    struct timeval before,after;
    gettimeofday(&before, NULL);
    for (i=0;i<1024;i++){
        for(k=0;k<1024;k++){
            for(j=0;j<1024;j++){
                MD[i][j]+=MA[i][k]*MB[k][j];

            }
        }
    }
    gettimeofday(&after, NULL);
    //printf("Time taken to count to 10^5 is : %ld micro seconds\n", ((after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec)));
    return ((after.tv_sec * 1000000 + after.tv_usec) -
    (before.tv_sec * 1000000 + before.tv_usec));
}

long loop_interchange_3()//loop order j k i has been interchanged
{
    int i,j,k;
    struct timeval before,after;
    gettimeofday(&before, NULL);
    for (j=0;j<1024;j++){
        for(k=0;k<1024;k++){
            for(i=0;i<1024;i++){
                MD[i][j]+=MA[i][k]*MB[k][j];

            }
        }
    }
    gettimeofday(&after, NULL);
    //printf("Time taken to count to 10^5 is : %ld micro seconds\n", ((after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec)));
    return ((after.tv_sec * 1000000 + after.tv_usec) -
    (before.tv_sec * 1000000 + before.tv_usec));
}

long loop_interchange_4()//loop order j i k has been interchanged
{
    int i,j,k;
    struct timeval before,after;
    gettimeofday(&before, NULL);
    for (j=0;j<1024;j++){
        for(i=0;i<1024;i++){
            for(k=0;k<1024;k++){
                MD[i][j]+=MA[i][k]*MB[k][j];

            }
        }
    }
    gettimeofday(&after, NULL);
    //printf("Time taken to count to 10^5 is : %ld micro seconds\n", ((after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec)));
    return ((after.tv_sec * 1000000 + after.tv_usec) -
    (before.tv_sec * 1000000 + before.tv_usec));
}

long loop_interchange_5()//loop order k i j has been interchanged
{
    int i,j,k;
    struct timeval before,after;
    gettimeofday(&before, NULL);
    for (k=0;k<1024;k++){
        for(i=0;i<1024;i++){
            for(j=0;j<1024;j++){
                MD[i][j]+=MA[i][k]*MB[k][j];

            }
        }
    }
    gettimeofday(&after, NULL);
    //printf("Time taken to count to 10^5 is : %ld micro seconds\n", ((after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec)));
    return ((after.tv_sec * 1000000 + after.tv_usec) -
    (before.tv_sec * 1000000 + before.tv_usec));
}

long matmul_with_tempVar()
{
    int i,j,k;
    double temp;
    struct timeval before,after;
    gettimeofday(&before, NULL);
    for (i=0;i<1024;i++){
        for(j=0;j<1024;j++){
            temp=0;
            for(k=0;k<1024;k++){
                temp+=MA[i][k]*MB[k][j];

            }
            MD[i][j]=temp;
            
        }
    }
    gettimeofday(&after, NULL);
    //printf("Time taken to count to 10^5 is : %ld micro seconds\n", ((after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec)));
    return ((after.tv_sec * 1000000 + after.tv_usec) -
    (before.tv_sec * 1000000 + before.tv_usec));

}

long Blocking_mult(int bsize)// this code has been taken and improvised from Bryant and O'Hallaron
 {
    int i, j, k, kk, jj;
    double sum;
    int en = bsize * (1024/bsize); /* Amount that fits evenly into blocks */
    struct timeval before,after;
    gettimeofday(&before, NULL);

    for (kk = 0; kk < en; kk += bsize) {
        for (jj = 0; jj < en; jj += bsize) {
            for (i = 0; i < 1024; i++) {
                for (j = jj; j < jj + bsize; j++) {
                    sum = MD[i][j];
                    for (k = kk; k < kk + bsize; k++) {
                        sum += MA[i][k]*MB[k][j];
                    }
                    MD[i][j] = sum;
                }
            }
        }
    }
     gettimeofday(&after, NULL);
    //printf("Time taken to count to 10^5 is : %ld micro seconds\n", ((after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec)));
    return ((after.tv_sec * 1000000 + after.tv_usec) -
    (before.tv_sec * 1000000 + before.tv_usec));

}




bool matmul_checker()
{
    int i,j,k=0;
    bool v=true;
    for (i=0;i<1024;i++){
        for(j=0;j<1024;j++){
            if(MD[i][j]!=MC[i][j]){
                v=false;
                k++;
                //printf("\nmatrix values are not equal\n");
            }
        }
    }
    if(v==false){
        printf("matrices are not equeal %d",k);
    }
    return v;
}

double SD(long time_array[]) {
    double sum = 0.0, mean, SD = 0.0;
    int i;
    for (i = 0; i < 21; ++i) {
        sum += time_array[i];
    }
    mean = sum / 21;
    for (i = 0; i < 21; ++i)
        SD += pow(time_array[i] - mean, 2);
    return sqrt(SD / 21);
}
double mean(long time_array[]){
    double sum=0.0,mean;
    int i;
    for (i = 0; i < 21; ++i) {
        sum += time_array[i];
    }
    mean = sum / 21;
    return mean;
}
long median(long time_array[])
{
    int i, j, temp,n;
    n=21;
    for(i = 0; i < n; i++)//bubble sort for calculating median
    {
        for(j = 0; j < n-i-1; j++)
        {
            if(time_array[j] >time_array[j+1])
            {
                // swap the elements
                temp =time_array[j];
               time_array[j] =time_array[j+1];
               time_array[j+1] = temp;
            } 
        }
    }
    for (i=0;i<21;i++) printf("%ld, ",time_array[i]);
    printf("\n range is=%ld  (%ld - %ld) \n",(time_array[20]-time_array[0]),time_array[20],time_array[0]);
    return time_array[11];//returns median
}
void result_martix_reset()
{
    int i,j;
    for(i=0;i<1024;i++){
        for(j=0;j<1024;j++){
            MD[i][j]=0.0;
        }
    }
}