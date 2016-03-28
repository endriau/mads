#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"

int compare_doubles(const void *a,const void *b)
{
	double *aa=NULL,*bb=NULL;
	aa=(double *)a;
	bb=(double *)b;
	if (*aa<*bb)
	{
		return -1;
	}
	else if(*aa>*bb)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void print_double(const void *w)
{
    double *temp=NULL;
    temp=(double *)w;
    printf("%.2lf",*temp);
    return;
}


void delete_double(void *d)
{
	free(d);
	d=NULL;
}



int main(int argc,char *argv[])
{
	int i;
	tree_t *tree=tree_create(compare_doubles,print_double,delete_double);
	double *var=NULL;

	for (i=0;i<10;i++)
	{
		var=(double *)malloc(sizeof(double));
		assert(var!=NULL);
		*var=i+0.1;
		tree_insert(tree,var);
	}

	tree_print(tree);
	tree_free(tree);
	return 0;
}