/*
 * This file contains data type definitions
 * and function prototypings regarding the
 * balanced binary tree data structure.
 *
 * @author:	Endri Kastrati
 * @date:	28/03/2016
 *
 */


typedef int 	(*TreeCompareFn)(const void *,const void *);
typedef void	(*TreePrintFn)(const void *);
typedef void	(*TreeDestroyFn)(void *);


typedef struct node node_t;

struct node
{
	void		*data;
	int 		height;
	node_t		*left;
	node_t		*right;
};



typedef struct
{
	node_t 			*root;
	TreeCompareFn	cmp;
	TreePrintFn		print;
	TreeDestroyFn	destroy;
} tree_t;



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
