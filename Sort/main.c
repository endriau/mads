/*
 * This file contains a simple demostration
 * of the polymorphic sorting library defined
 * defined in the header file sort.h
 *
 * @author: Endri Kastrati
 * @date:   25/11/2016
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "sort.h"




int compare_doubles(const void *a,const void *b);
int test_equality(void **A,void **B,int n);



int compare_doubles(const void *a,const void *b)
{
    int result;
    double *aa=NULL,*bb=NULL;
    aa=(double *)&a;
    bb=(double *)&b;
    if (*aa<*bb)  { result=-1; }
    if (*aa>*bb)  { result=1;  }
    if (*aa==*bb) { result=0;  }
    return result;
}



int test_equality(void **A,void **B,int n)
{
    int i;
    assert(A!=NULL && B!=NULL && n>=0);

    for (i=0;i<n;i++)
    {
        if (compare_doubles(A[i],B[i])!=0)
        {
            return 0;
        }
    }

    return 1;
}


int main(int argc,char *argv[])
{
    int size,i,flag;
    time_t seed;
    clock_t start,end,tt1,tt2,tt3;
    double *A=NULL,*B=NULL,*C=NULL;
    srand((unsigned )time(&seed));
    size=1;

    while (size<100000000)
    {    
        A=(double *)malloc(size*sizeof(double ));
        assert(A!=NULL);
        B=(double *)malloc(size*sizeof(double ));
        assert(B!=NULL);
        C=(double *)malloc(size*sizeof(double ));
        assert(C!=NULL);
        for (i=0;i<size;i++) { A[i]=rand()%size; }
        memcpy(B,A,size*sizeof(double ));
        memcpy(C,A,size*sizeof(double ));

        start=clock();
        quick_sort((void **)A,size,compare_doubles,ITERATIVE_SORT);
        end=clock();
        tt1=(end-start+500)/1000;

        start=clock();
        merge_sort((void **)B,size,compare_doubles,ITERATIVE_SORT);
        end=clock();
        tt2=(end-start+500)/1000;
        
        start=clock();
        //insertion_sort((void **)C,size,compare_doubles);
        end=clock();
        //tt3=(end-start+500)/1000;

        flag=test_equality((void **)A,(void **)B,size);
        printf("%d, %ld, %ld %ld\n",size,tt1,tt2,flag);
        size*=2;
    }


    free(A); A=NULL;
    free(B); B=NULL;
    return 0;
}

