/*
 * This file contains data type definitions
 * and function prototypings regarding the
 * balanced binary tree data structure.
 *
 * @author:	Endri Kastrati
 * @date:	28/03/2016
 *
 */




/*
 * Using include guards to check if the
 * tree.h header file has been included
 * at least once.If it hasn't the compiler
 * copy-pastes everything into the file that
 * is including it.If the file on the other
 * hand has been included the compiler
 * skips the contents entirely.
 *
 */

#ifndef TREE_H
#define TREE_H





/*
 * Defining three new data types of function pointers called
 * TreeCompareFn,TreePrintFn,TreeDestroyFn.These functions 
 * enable polymorphism by specifying an interface for the
 * comparison,printing and memory deallocation function.
 * These functions have to be written by the user and meet
 * the following criteria.
 *
 */

typedef int 	(*TreeCompareFn)(const void *,const void *);
typedef void	(*TreePrintFn)(const void *);
typedef void	(*TreeDestroyFn)(void *);




/*
 * Defining a new data type that represents
 * the abstract concept of a node in a binary
 * tree.This structure has as components a void
 * pointer to some data, an integer that represents
 * the height and two pointers to node structs.
 * This data structure is a recursive one, meaning
 * it can have as components instances of itself.
 *
 */

typedef struct avlnode avlnode_t;

struct avlnode
{
	void           *data;
	int            height;
	avlnode_t      *left;
	avlnode_t      *right;
};




/*
 * This is the C implementation of the Balanced
 * binary tree data sttructure.This enhaced version
 * contains as components a pointer to avlnode_t which
 * represents the root of the tree and three function
 * pointers cmp,print,destroy to enable polymorphism.
 *
 */

typedef struct
{
	avlnode_t 		*root;
	TreeCompareFn	cmp;
	TreePrintFn		print;
	TreeDestroyFn	destroy;
} tree_t;




/*
 * Function prototypings of procedures regarding
 * the balanced binary tree data structure such
 * as create,insert,search,remove, etc..
 *
 */

tree_t 		*tree_create(TreeCompareFn fn,TreePrintFn print,TreeDestroyFn destroy);
void		tree_insert(tree_t *t,void *data);
int 		tree_search(tree_t *t,void *item);
void		*tree_getElem(tree_t *t,void *item);
void 		*tree_getRoot(tree_t *t);
void 		tree_remove(tree_t *t,void *item);
void		tree_removeRoot(tree_t *t);
int 		tree_isEmpty(tree_t *t);
int 		tree_getHeight(tree_t *t);
void 		tree_print(tree_t *t);
void 		tree_free(tree_t *t);




/*
 * Once everything has been copy-pasted by
 * the compiler and the macro TREE_H has
 * been defined, the tree.h header file 
 * will not be included more than once.
 *
 */

#endif
