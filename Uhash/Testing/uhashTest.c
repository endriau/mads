/*
 * This file contains function definitions
 * for testing procedures regarding the
 * universal hash function data structure.
 *
 * @author: Endri Kastrati
 * @date:   16/01/2017
 *
 */



/*
 * Including the standard input-output
 * library,the standard utilities library,
 * the standard assertions library,the standard
 * time library and the header file uhashTest.h
 * that contains function prototyping for functions
 * regarding the testing of the universal hash
 * function data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "uhashTest.h"



/*
 * @COMPLEXITY: O(sqrt(n))
 *
 * The static function is_prime() takes only
 * one argument as a parameter,namely an unsigned
 * long long int value and checks whether it constitutes
 * a prime number or not.If the given number is a
 * prime it returns one,otherwise it returns zero.
 *
 * @param:  lluint   n
 * @return: int
 *
 */

static int is_prime(lluint n)
{
    int isprime=1;
    lluint divisor;
    if (n<2) { return 0; }

    for (divisor=2;divisor*divisor<=n;divisor++)
    {
        if (n%divisor==0)
        {
            isprime=0;
            break;
        }
    }

    return isprime;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function print_pass()
 * takes no arguments as parameters
 * and prints a user-friendly success
 * message.
 *
 * @param:  void
 * @return: void
 *
 */

static void print_pass()
{
    fprintf(stderr,"["GRN" PASS "RESET"]\n");
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 * 
 * The static function print_fail(),
 * takes no arguments as parameters
 * and prints a user-friendly fail
 * message.
 *
 * @param:  void
 * @return: void
 *
 */

static void print_fail()
{
    fprintf(stderr,"["RED" FAIL "RESET"]\n");
    return;
}





/*
 * @COMPLEXITY: O(n)
 *
 * The function hashfn_create_test() takes three arguments as
 * parameters.The first two arguments are arrays of long long
 * unsigned integers and the third one is the size of the arrays.
 * This function tests the hashfn_create() procedure.It creates
 * an array of universal hash function data structures and checks
 * whether any of the compnents of the array is null or not.
 * Based on the results it prints the appropriate message to
 * the users.
 *
 * @param:  lluint          *tss
 * @param:  lluint          *ks
 * @return: hashfn_t        **
 *
 */

hashfn_t **hashfn_create_test(lluint *tss,lluint *ks,lluint n)
{
    // In this section we declare the variables
    // that will be used in this testing module
    // and we allocate memory for the array of
    // hashfn_t data structures.
    int pc=0,fc=0;
    lluint i; int flag=0; hashfn_t **Array=NULL; assert(tss!=NULL && ks!=NULL && n>=0);
    Array=(hashfn_t **)malloc(n*sizeof(hashfn_t *)); assert(Array!=NULL);
    fprintf(stderr,YEL "Initiating testing for the hashfn_create() procedure.\n"RESET);
    fprintf(stderr,"\thashfn_create(): iterations = %lld,\t\t\t\t\t\t\t\t",n);


    // Populating the allocated array
    // with hashfn_t data structures.
    // If any of the instantiations fails
    // and the corresponding cell is assigned
    // the value of null then this case fails.
    // Otherwise if all memory allocations were
    // successful then it succeeds.
    for (i=0;i<n;i++)
    {
        Array[i]=hashfn_create(tss[i],ks[i]);
        if (Array[i]==NULL) { flag=1; }
    }
    if (flag==1)    { print_fail(); fc++; }
    else            { print_pass(); pc++; }

    
    // Printing the test results in a user-friendly format.
    // The message includes the total number of fails and suceesses.
    fprintf(stderr,CYN "\ttotal pass = %d/%d, total fail = %d/%d\n"RESET,pc,(pc+fc),fc,(pc+fc));
    fprintf(stderr,YEL "Terminating testing for the hashfn_create() procedure.\n"RESET);
    return Array;   // Returing the array of hashfn_t data structures.
}





/*
 * @COMPLEXITY: O(k*n)
 *
 * The function hashfn_getValues_test() takes four arguments as
 * parameters.The first argument is an array of hashfn_t data
 * structures,the second and third are arrays of long long
 * unsigned integers and the fourth one is the size of the arrays.
 * This function tests the hashfn_getValues() procedure.It checks
 * if the table size and the k values size match the ones that
 * were used during their instantiation.It also checks if the
 * elements of the kvalues components are all primes as expected.
 * If any of these conditions does not hold this case fails,
 * otherwise it is considered success.
 *
 * @param:  hashfn_t        **fs
 * @param:  lluint          *tss
 * @param:  lluint          *ks
 * @param:  lluint          n
 * @return: int             
 */

int hashfn_getValues_test(hashfn_t **fs,lluint *tss,lluint *ks,lluint n)
{
    // In this section we declare
    // the variables that will be
    // used for this unit case and
    // checking whether the given
    // arguments meet the appropriate
    // requirements and assertions.
    lluint i,j; int pc=0,fc=0,flag=0;
    assert(fs!=NULL && tss!=NULL && ks!=NULL && n>=0);
    fprintf(stderr,YEL "Initiating testing for the hashfn_getValues() procedure.\n"RESET);

    
    // In this section we iterate over the array
    // of hashfn_t data structures and compare
    // their sizes with the sizes that were used
    // during their instantiation.If the sizes
    // match up, all is good.Otherwise the case
    // fails because the procedure hashfn_getTableSize()
    // is not doing what it is supposed to.
    fprintf(stderr,"\thashfn_getValues(): iterations = %lld, description = \"testing for table size.\"\t\t\t",n);
    for (i=0;i<n;i++)
    {
        lluint table_size=hashfn_getTableSize(fs[i]);
        if (table_size!=tss[i]) { flag=1; }
    }
    if (flag==1)    { print_fail(); fc++; }
    else            { print_pass(); pc++; }
    flag=0;

    
    // In this section we iterate over the array
    // of hashfn_t data structures and compare
    // the k values sizes with the sizes that 
    // were used during their instantiation.If
    // the sizes match up,all good.Otherwise the
    // case fails because the procedure hashfn_getK()
    // is not doing what it is supposed to.
    fprintf(stderr,"\thashfn_getValues(): iterations = %lld, description = \"testing for values size.\"\t\t\t",n);
    for (i=0;i<n;i++)
    {
        lluint k_size=hashfn_getK(fs[i]);
        if (k_size!=ks[i]) { flag=1; }
    }
    if (flag==1)    { print_fail(); fc++; }
    else            { print_pass(); pc++; }
    flag=0;

    
    // In this section we iterate over the array
    // of hashfn_t data structure and for every
    // hashfn_t we iterate over it's values arrays
    // and check whether the generated values are
    // all prime numbers or not.If the numbers are
    // all primes then everything is good,otherwise
    // there is a problem in either hashfn_create()
    // or hashfn_getValues().
    fprintf(stderr,"\thashfn_getValues(): iterations = %lld, description = \"testing for primeness.\"\t\t\t",n);
    for (i=0;i<n;i++)
    {
        lluint *temp=hashfn_getValues(fs[i]);
        lluint k_size=hashfn_getK(fs[i]);

        for (j=0;j<k_size;j++)
        {
            if (is_prime(temp[j])==0) { flag=1; }
        }
    }
    if (flag==1)    { print_fail(); fc++; }
    else            { print_pass(); pc++; }

    
    // Printing the results in a user-friendly format
    // and indicating the number of failures and successes.
    fprintf(stderr,CYN "\ttotal pass = %d/%d, total fail = %d/%d\n"RESET,pc,(pc+fc),fc,(pc+fc));
    fprintf(stderr,YEL "Terminating testing for the hashfn_getValues() procedure.\n"RESET);
    if (fc>0)   { return UHASH_TEST_FAILURE; }  // If there were any fails return the value of UHASH_TEST_FAILURE.
    else        { return UHASH_TEST_SUCCESS; }  // If there were no fails return the value of UHASH_TEST_SUCCESS.
}





/*
 * @COMPLEXITY: O(n)
 *
 * The function hashfn_getTableSize_test() takes four arguments as
 * parameters.The first argument is an array of hashfn_t data structures,
 * the second and third arguments are arrays of long long unsigned
 * integers and the fourth one is the size of the arrays.This function
 * tests the hashfn_getTableSize() procedure.It checks whether the
 * given table size value matches the value that was used for the
 * instantiation of the data structure.It also checks if the table
 * size is always greater than the k values size.If any of these
 * conditions does not hold,then the test case fails,otherwise
 * it succeeds.
 *
 * @param:  hashfn_t        **fs
 * @param:  lluint          *tss
 * @param:  lluint          *ks
 * @param:  lluint          n
 * @return: int
 *
 */

int hashfn_getTableSize_test(hashfn_t **fs,lluint *tss,lluint *ks,lluint n)
{
    // In this section of the code
    // we declare the variables that
    // will be used for this test case.
    // We also make sure the given arguments
    // adhere to the appropriate assertions.
    lluint i; int pc=0,fc=0,flag=0;
    assert(fs!=NULL && tss!=NULL && ks!=NULL && n>=0);
    fprintf(stderr,YEL "Initiating testing for the hashfn_getTableSize() procedure.\n"RESET);
    

    // In this section we iterate over the array
    // of hashfn_t data structures and check if
    // the table size values match with the values
    // that were used during their instantiation.
    fprintf(stderr,"\thashfn_getTableSize(): iterations = %lld, description = \"testing for table size.\"\t\t",n);
    for (i=0;i<n;i++)
    {
        lluint table_size=hashfn_getTableSize(fs[i]);
        if (table_size!=tss[i]) { flag=1; }
    }
    if (flag==1)    { print_fail(); fc++; }
    else            { print_pass(); pc++; }
    flag=0;
    

    // In this section we iterate over the array
    // of hashfn_t data structures and check if
    // the size of the k values is greater than
    // the size o the tables.If it is greater,
    // then this test case fails.Otherwise if
    // it is smaller,this test case succeeds.
    fprintf(stderr,"\thashfn_getTableSize(): iterations = %lld, description = \"larger than the size of k values.\"\t",n);
    for (i=0;i<n;i++)
    {
        lluint table_size=hashfn_getTableSize(fs[i]);
        lluint k_size=hashfn_getK(fs[i]);
        if (table_size<k_size) { flag=1; }
    }
    if (flag==1)    { print_fail(); fc++; }
    else            { print_pass(); pc++; }
    

    // Printing the results in a user-friendly format
    // and indicating the number of failures and successes.
    fprintf(stderr,CYN "\ttotal pass = %d/%d, total fail = %d/%d\n"RESET,pc,(pc+fc),fc,(pc+fc));
    fprintf(stderr,YEL "Terminating testing for the hashfn_getTableSize() procedure.\n"RESET);
    if (fc>0)   { return UHASH_TEST_FAILURE; } // If there were any fails return the value of UHASH_TEST_FAILURE.
    else        { return UHASH_TEST_SUCCESS; } // If there were no fails return the value of the UHASH_TEST_SUCCESS.
}






/*
 * @COMPLEXITY: O(n)
 *
 * The function hashfn_getK_test() takes four arguments as
 * parameters.The first argument is an array of hashfn_t data
 * structures,the second and third arguments are arrays of long long
 * unsigned integers and the fourth one is the size of the arrays.
 * This function tests the hashfn_getK() procedure.It checks whether
 * the given size of k values matches with the values that were
 * used during the instantiation.It also checks if the returned
 * size of k values is smaller than the size of the table.If
 * these conditions hold,all is good.Otherwise the test case
 * fails.
 *
 * @param:  hashfn_t        **fs
 * @param:  lluint          *tss
 * @param:  lluint          *ks
 * @param:  lluint          n
 * @return: int
 *
 */

int hashfn_getK_test(hashfn_t **fs,lluint *tss,lluint *ks,lluint n)
{
    // In this section we declare the variables
    // that will be used for this test case and
    // checking if the given arguments adhere
    // to the necessary assertions.
    lluint i; int pc=0,fc=0,flag=0;
    assert(fs!=NULL && tss!=NULL && ks!=NULL && n>=0);
    fprintf(stderr,YEL "Initiating testing for the hashfn_getK() procedure.\n"RESET);


    // In this section we iterate over the array 
    // of hashfn_t data structures and check
    // if the value that is returned by the
    // procedure hashfn_getK() matches with
    // the value that was used during instantiation.
    fprintf(stderr,"\thashfn_getK(): iterations = %lld, description = \"testing for values size.\"\t\t\t",n);
    for (i=0;i<n;i++)
    {
        lluint k_size=hashfn_getK(fs[i]);
        if (k_size!=ks[i]) { flag=1; }
    }
    if (flag==1)    { print_fail(); fc++; }
    else            { print_pass(); pc++; }
    flag=0;
    

    // In this section we iterate over the array
    // of hashfn_t data structures and check
    // if the size of k values is smaller than
    // the size of the table.If so then this
    // test case succeeds,otherwise it fails.
    fprintf(stderr,"\thashfn_getK(): iterations = %lld, description = \"less than the table size.\"\t\t\t",n);
    for (i=0;i<n;i++)
    {
        lluint k_size=hashfn_getK(fs[i]);
        lluint table_size=hashfn_getTableSize(fs[i]);
        if (table_size<k_size) { flag=1; }
    }
    if (flag==1)    { print_fail(); fc++; }
    else            { print_pass(); pc++; }
    

    // Printing the results in a user-friendly format
    // and indicating the number of failures and successes.
    fprintf(stderr,CYN "\ttotal pass = %d/%d, total fail = %d/%d\n"RESET,pc,(pc+fc),fc,(pc+fc));
    fprintf(stderr,YEL "Terminating testing for the hashfn_getK() procedure.\n"RESET);
    if (fc>0)   { return UHASH_TEST_FAILURE; } // If there were any fails return the value of UHASH_TEST_FAILURE.
    else        { return UHASH_TEST_SUCCESS; } // If there were no fails return the value of the UHASH_TEST_SUCCESS.
}






/*
 * @COMPLEXITY: O(n)
 *
 * The function hashfn_free_test() takes four arguments as parameters.
 * The first argument is an array of hashfn_t data structures,the
 * second and third are arrays of long long unsigned integers and
 * the fourth one is the size of the arrays.This function checks
 * the hashfn_free() procedure.It basically walks over the entire
 * array of hashfn_t structs and deallocates the memory chunk 
 * associated with it.
 *
 * @param:  hashfn_t        **fs
 * @param:  lluint          *tss
 * @param:  lluint          *ks
 * @param:  lluint          n
 * @return: int
 *
 */

int hashfn_free_test(hashfn_t **fs,lluint *tss,lluint *ks,lluint n)
{
    // In this section we declare the variables
    // that will be used for this test case.We
    // also check if the given arguments adhere
    // to the appropriate assertions.
    lluint i; int pc=0,fc=0,flag=0;
    assert(fs!=NULL && tss!=NULL && ks!=NULL && n>=0);
    fprintf(stderr,YEL "Initiating testing for the hashfn_free() procedure.\n"RESET);
    

    // Walking over the entire array of hashfn_t
    // data structures and deallocating the memory
    // chunk associated with the particular cell.
    fprintf(stderr,"\thashfn_getK(): iterations = %lld, description = \"testing for memory deallocation.\"\t\t",n);
    for (i=0;i<n;i++)
    {
        hashfn_free(fs[i]);
        fs[i]=NULL;
    }
    if (flag==1)    { print_fail(); fc++; }
    else            { print_pass(); pc++; }
    
    // Printing the results in a user-friendly format
    // and indicating the number of fails and successes.
    fprintf(stderr,CYN "\ttotal pass = %d/%d, total fail = %d/%d\n"RESET,pc,(pc+fc),fc,(pc+fc));
    fprintf(stderr,YEL "Terminating testing for the hashfn_free() procedure.\n"RESET);
    if (fc>0)   { return UHASH_TEST_FAILURE; } // If there were any fails return the value of UHASH_TEST_FAILURE.
    else        { return UHASH_TEST_SUCCESS; } // If there were no fails return the value of UHASH_TEST_SUCCESS.
}





/*
 * Main execution program,runs different
 * unit tests for the universal hash function
 * data structure defined in the header file
 * uhash.h.This program was designed in such
 * a way that additional test cases can be
 * inserted.
 *
 */

int main(int argc,char *argv[])
{

    time_t seed;                            // It's address will be used as a seed for srand().
    lluint m=100,i; hashfn_t **A=NULL;      // Declaring the size of iterations and the array of hashfn_t structs.
    srand((unsigned )time(&seed));          // Seeding the random number generator via srand().
    lluint table_sizes[m];                  // The array containing the randomly generated table sizes.
    lluint table_ks[m];                     // The array containing the randomly generated k values sizes.
    

    // Assigning the randomly generated
    // numbers to the corresponding array
    // index.
    for (i=0;i<m;i++)
    {
        table_sizes[i]=1+rand()%m;
        table_ks[i]=(1+rand()%table_sizes[i]);
    } 
    

    // Performing the unit tests for the universal hash function
    // data structure and the operations and functions associated
    // with it.
    fprintf(stderr,BLU "INITIATING UHASH TESTING: author = \"Endri Kastrati\", email = \"endriau@gmail.com\"\n"RESET);
    printf("\n");
    A=hashfn_create_test(table_sizes,table_ks,m);
    printf("\n");
    hashfn_getValues_test(A,table_sizes,table_ks,m);
    printf("\n");
    hashfn_getTableSize_test(A,table_sizes,table_ks,m);
    printf("\n");
    hashfn_getK_test(A,table_sizes,table_ks,m);
    printf("\n");
    hashfn_free_test(A,table_sizes,table_ks,m);
    printf("\n");
    fprintf(stderr,BLU "TERMINATING UHASH TESTING.\n"RESET);
    
    
    // Deallocating memory for the array
    // of hashfn_t data structures.
    free(A); A=NULL;
    return 0;
}
