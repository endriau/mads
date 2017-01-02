#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "uhash.h"




int main(int argc,char *argv[])
{
    const uint k=10;
    uint table_size=20;
    hashfn_t *h=NULL;
    h=hashfn_create(table_size,k);
    hashfn_print(h);
    hashfn_free(h);
    return 0;
}


