/*
 * This file contains function definitions
 * regarding the balanced binary tree data
 * structure.
 *
 * @author:	Endri Kastrati
 * @date:	28/03/2016
 *
 */



/*
 * Including the standard input-output library,
 * the standard general utilities library,the
 * standard assertion library and the header file
 * tree.h which contains datatype definitions and
 * function prototypings for the balanced binary
 * tree data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"




/*
 * Defining one macro constant to represent the
 * maximum allowed imbalance of a node in a balanced
 * binary tree and two macro-like functions that return
 * the height component of a avlnode_t structure and the
 * maximum of two given arguments consecutively.
 *
 */

#define	ALLOWED_IMBALANCE	1
#define HEIGHT(node)        (node==NULL ? -1 : node->height)
#define MAX(a,b)            (a > b ? a : b)





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function tree_create() takes three function pointers 
 * as arguments.It creates a new tree_t data structure by
 * allocating memory for it and it's components and instantiates
 * it's components to the default values.The print and cmp components
 * are mandatory and cannot be null.The users have to create their own
 * cmp,print,destroy (optional) functions.Failure to do so will 
 * result in program termination due to invalid assertions.
 *
 * @param:	TreeCompareFn	cmp
 * @param:	TreePrintFn		print
 * @param:	TreeDestroyFn	destroy
 * @return:	tree_t 			*
 *
 */

tree_t *tree_create(TreeCompareFn cmp,TreePrintFn print,TreeDestroyFn destroy)
{
	tree_t *new_tree=NULL;
	assert(cmp!=NULL && print!=NULL);
	new_tree=(tree_t *)malloc(sizeof(*new_tree));
	assert(new_tree!=NULL);
	new_tree->root=NULL;
	new_tree->cmp=cmp;
	new_tree->print=print;
	new_tree->destroy=destroy;
	return new_tree;
}






/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function rotate_with_left_child() takes as an
 * argument a avlnode_t data structure and performs a rotation
 * with it's left child.Once the rotation has been completed
 * the heights are updated.
 *
 * @param:	avlnode_t 		*node
 * @return:	avlnode_t		*
 *
 */

static avlnode_t *rotate_with_left_child(avlnode_t *node)
{
	avlnode_t *rotate_node=NULL;
	rotate_node=node->left;
	node->left=rotate_node->right;
	rotate_node->right=node;
	node->height=MAX(HEIGHT(node->left),HEIGHT(node->right))+1;
	rotate_node->height=MAX(HEIGHT(rotate_node->left),node->height)+1;
	return rotate_node;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function rotate_with_right_child() takes as
 * an argument a avlnode_t data structure and performs a rotation
 * with it's right child.Once the rotation has been completed
 * the heights are updated.
 *
 * @param:	avlnode_t 		*node
 * @return:	avlnode_t		*
 *
 */

static avlnode_t *rotate_with_right_child(avlnode_t *node)
{
	avlnode_t *rotate_node=NULL;
	rotate_node=node->right;
	node->right=rotate_node->left;
	rotate_node->left=node;
	node->height=MAX(HEIGHT(node->left),HEIGHT(node->right))+1;
	rotate_node->height=MAX(HEIGHT(rotate_node->right),node->height)+1;
	return rotate_node;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function double_with_left_child() takes as
 * an argument a avlnode_t data structure and performs a
 * rotation with the right child of the given node's left
 * child and another rotation with the left child of the node.
 *
 * @param: 	avlnode_t 		*node
 * @return:	avlnode_t 		*
 *
 */

static avlnode_t *double_with_left_child(avlnode_t *node)
{
	node->left=rotate_with_right_child(node->left);
	return rotate_with_left_child(node);
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function double_with_right_child() takes as
 * and argument a avlnode_t data structure and performs a
 * rotation with the left child of the given node's right
 * child and another rotation with the right child of the node.
 *
 * @param:	avlnode_t 		*node
 * @return:	avlnode_t		*
 *
 */

static avlnode_t *double_with_right_child(avlnode_t *node)
{
	node->right=rotate_with_left_child(node->right);
	return rotate_with_right_child(node);
}






/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function balance() takes as argument
 * a avlnode_t data structure and checks whether the
 * given node satisfies the balanced binary tree
 * properties.If the tree is not balanced it performs
 * the necessary rotations, depending on the heights
 * of the nodes, to rebalance it and update the height.
 *
 * @param:	avlnode_t 		*node
 * @return:	avlnode_t		*
 *
 */

static avlnode_t *balance(avlnode_t *node)
{
	if (node==NULL)
	{
		return node;
	}

	if (HEIGHT(node->left)-HEIGHT(node->right)>ALLOWED_IMBALANCE)
	{
		if (HEIGHT(node->left->left)>=HEIGHT(node->left->right))
		{
			node=rotate_with_left_child(node);
		}
		else
		{
			node=double_with_left_child(node);
		}
	}
	else if (HEIGHT(node->right)-HEIGHT(node->left)>ALLOWED_IMBALANCE)
	{
		if (HEIGHT(node->right->right)>=HEIGHT(node->right->left))
		{
			node=rotate_with_right_child(node);
		}
		else
		{
			node=double_with_right_child(node);
		}
	}
	else {}

	node->height=MAX(HEIGHT(node->left),HEIGHT(node->right))+1;
	return node;
}






/*
 * @COMPLEXITY: O(logn)
 *
 * The static function tree_recursive_insert() takes three arguments,
 * a avlnode_t data structure, a TreeCompareFn function and a void pointer
 * to some data and checks whether the given element exists within the
 * balanced binary tree.If the element does not exist it inserts it into
 * the tree and rebalances it when necessary via the static function balance().
 * If on the other the element already exists in the tree, nothing happesn.
 * No duplicates are allowed.The given TreeCompareFn has to be not null.
 *
 * @param:	avlnode_t 			*node
 * @param:	TreeCompareFn		cmp
 * @param:	void				*data
 * @return:	avlnode_t			*
 *
 */

static avlnode_t *tree_recursive_insert(avlnode_t *node,TreeCompareFn cmp,void *data)
{
	int compare=0;
	avlnode_t *new_node=NULL;
	assert(cmp!=NULL);

	if (node==NULL)
	{
		new_node=(avlnode_t *)malloc(sizeof(*new_node));
		assert(new_node!=NULL);
		new_node->data=data;
		new_node->left=NULL;
		new_node->right=NULL;
		new_node->height=0;
		return new_node;
	}

	compare=cmp(node->data,data);

	if (compare>0)
	{
		node->left=tree_recursive_insert(node->left,cmp,data);
	}
	else if (compare<0)
	{
		node->right=tree_recursive_insert(node->right,cmp,data);
	}
	else {}
	return balance(node);
}





/*
 * @COMPLEXITY: O(logn)
 *
 * The function tree_insert() takes two arguments,
 * a tree_t data structure and a void pointer to
 * some data and inserts the given element into the
 * tree by invoking the static function tree_recursive_insert().
 *
 * @param:	tree_t 		*t
 * @param:	void		*data
 * @return:	void
 *
 */

void tree_insert(tree_t *t,void *data)
{
	assert(t!=NULL);
	t->root=tree_recursive_insert(t->root,t->cmp,data);
	return;
}





/*
 * @COMPLEXITY: O(logn)
 *
 * The static function tree_recursive_search() takes three arguments,
 * a avlnode_t data structure,a TreeCompareFn function,a void pointer to
 * some data and searches the balanced binary tree for the given element.
 * If the element exists within the tree it returns the node containing
 * the element otherwise it returns null.
 *
 * @param:	avlnode_t 				*node
 * @param:	TreeCompareFn		cmp
 * @param:	void				*item
 * @return:	avlnode_t				*
 *
 */

static avlnode_t *tree_recursive_search(avlnode_t *node,TreeCompareFn cmp,void *item)
{
	int compare=0;
	assert(cmp!=NULL);
	if (node==NULL) { return node; }
	compare=cmp(node->data,item);

	if (compare>0)
	{
		return tree_recursive_search(node->left,cmp,item);
	}
	else if (compare<0)
	{
		return tree_recursive_search(node->right,cmp,item);
	}
	else
	{
		return node;
	}
}




/*
 * @COMPLEXITY: O(logn)
 *
 * The function tree_search() takes two arguments,
 * a tree_t data structure, a void pointer to some
 * data and searches the balanced binary tree for
 * the given element by invoking the static function
 * tree_recursive_search().If the element exists it
 * returns one, otherwise it returns zero.
 *
 * @param:	tree_t 		*t
 * @param:	void		*item
 *
 */

int tree_search(tree_t *t,void *item)
{
	avlnode_t *query_node=NULL;
	assert(t!=NULL);
	query_node=tree_recursive_search(t->root,t->cmp,item);
	return (query_node!=NULL ? 1 : 0);
}




/*
 * @COMPLEXITY: O(logn)
 *
 * The function tree_getElem() takes two arguments,
 * a tree_t data structure, a void pointer to some
 * data and searches the tree for the given element.
 * If the element is within the tree it is returned,
 * otherwise it returns null.
 *
 * @param:	tree_t 		*t
 * @param:	void		*item
 * @return:	void		*
 *
 */

void *tree_getElem(tree_t *t,void *item)
{
	avlnode_t *query_node=NULL;
	assert(t!=NULL);
	query_node=tree_recursive_search(t->root,t->cmp,item);
	return (query_node!=NULL ? query_node->data : NULL);
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function tree_getRoot() takes as an argument
 * a tree_t data structure and returns the data
 * component of the root node.It the root is null,
 * it returns null.
 *
 * @param:	tree_t 		*t
 * @return:	void		*
 *
 */

void *tree_getRoot(tree_t *t)
{
	assert(t!=NULL);
	return (t->root!=NULL ? t->root->data : NULL);
}






/*
 * @COMPLEXITY: O(logn)
 *
 * The static function find_min() takes a avlnode_t
 * data structure as an argument and returns it's
 * left most node grandchild.if the given node
 * is null, null is returned.
 *
 * @param:	avlnode_t		*node
 * @return:	avlnode_t 		*
 *
 */

static avlnode_t *find_min(avlnode_t *node)
{
	if (node==NULL)
	{
		return node;
	}

	while (node->left!=NULL)
	{
		node=node->left;
	}

	return node;
}




/*
 * @COMPLEXITY: O(logn)
 *
 * The static function tree_recursive_remove() takes four arguments,
 * a avlnode_t data structure,a TreeCompareFn function,a TreeDestroyFn
 * function,a void pointer to some data and searches the balanced
 * binary tree for the given element,if the element exists,it is 
 * deleted  from the binary tree.Once deleted, the tree is rebalanced 
 * where necessary.If the element does not exist then nothing happens.
 *
 * @param:	avlnode_t 			*node
 * @param:	TreeCompareFn		cmp
 * @param:	TreeDestroyFn		destroy
 * @param:	void				*item
 * @return:	avlnode_t			*
 *
 */

static avlnode_t *tree_recursive_remove(avlnode_t *node,TreeCompareFn cmp,TreeDestroyFn destroy,void *item)
{
	int compare=0;
	assert(cmp!=NULL);
	if (node==NULL) { return node; }
	compare=cmp(node->data,item);

	if (compare>0)
	{
		node->left=tree_recursive_remove(node->left,cmp,destroy,item);
	}
	else if (compare<0)
	{
		node->right=tree_recursive_remove(node->right,cmp,destroy,item);
	}
	else
	{
		if (node->right==NULL && node->left==NULL)
		{
			if (destroy!=NULL)
			{
				destroy(node->data);
				node->data=NULL;
			}

			free(node);
			node=NULL;
		}
		else if (node->right!=NULL && node->left==NULL)
		{
			if (destroy!=NULL)
			{
				destroy(node->data);
				node->data=NULL;
			}

			avlnode_t *old_node=NULL;
			old_node=node;
			node=node->right;
			free(old_node);
			old_node=NULL;
		}
		else if (node->left!=NULL && node->right==NULL)
		{
			if (destroy!=NULL)
			{
				destroy(node->data);
				node->data=NULL;
			}

			avlnode_t *old_node=NULL;
			old_node=node;
			node=node->left;
			free(old_node);
			old_node=NULL;

		}
		else
		{
			avlnode_t *min_node=NULL;
			min_node=find_min(node->right);
			void *temp_data=NULL;
			temp_data=node->data;
			node->data=min_node->data;
			min_node->data=temp_data;
			node->right=tree_recursive_remove(node->right,cmp,destroy,temp_data);

		}
	}

	return balance(node);
}






/*
 * @COMPLEXITY: O(logn)
 *
 * The function tree_remove() takes two arguments,
 * a tree_t data structure, a void pointer to some
 * data and removes that element from the tree by
 * invoking the static function tree_recursive_remove() .
 * If the element does not exist nothing happesn.
 *
 * @param:	tree_t 		*t
 * @param:	void		*item
 * @return:	void
 *
 */

void tree_remove(tree_t *t,void *item)
{
	assert(t!=NULL);
	if (tree_isEmpty(t)) { return; }
	t->root=tree_recursive_remove(t->root,t->cmp,t->destroy,item);
	return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function tree_removeRoot() takes as an argument
 * a tree_t data tructure and removes the root element
 * from the tree, without violating tree properties.
 *
 * @param:	tree_t 		*t
 * @return:	void
 *
 */

void tree_removeRoot(tree_t *t)
{
	assert(t!=NULL);
	tree_remove(t,t->root->data);
	return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function tree_isEmpty() takes as an argument
 * a tree_t data structure and checks whether the
 * given tree is empty or not.If the tree is empty
 * it returns one, otherwise if the tree is not
 * empty it returns zero.
 *
 * @param:	tree_t 		*t
 * @return:	int
 *
 */

int tree_isEmpty(tree_t *t)
{
	assert(t!=NULL);
	return (t->root==NULL ? 1 : 0);
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function tree_getHeight() takes as an argument
 * a tree_t data structure and returns the height of
 * of the balanced binary tree.
 *
 * @param:	tree_t 		*t
 * @return:	int
 *
 */

int tree_getHeight(tree_t *t)
{
	assert(t!=NULL);
	return (t->root==NULL ? -1 : t->root->height);
}





/*
 * @COMPLEXITY: O(n)
 *
 * The static function tree_recursive_print() takes three arguments,
 * a avlnode_t data structure,a TreePrintFn function,a integer that
 * represents the current depth of recursion and prints out all of the
 * elements within the tree from the right most element to the left most.
 *
 * @param:	avlnode_t 			*t
 * @param:	TreePrintFn			print
 * @param:	int 				depth
 * @return:	void
 *
 */

static void tree_recursive_print(avlnode_t *node,TreePrintFn print,int depth)
{
	int i;
	assert(print!=NULL);
	if (node==NULL) { return; }
	tree_recursive_print(node->right,print,depth+1);
	for (i=0;i<depth;i++) { printf("	"); }
	print(node->data);
	printf("\n");
	tree_recursive_print(node->left,print,depth+1);
	return;
}




/*
 * @COMPLEXITY: O(n)
 *
 * The function tree_print() takes as an argument
 * a tree_t data structure and prints the tree
 * in a user-friendly format.This function makes
 * use of the static function tree_recursive_print().
 *
 * @param:	tree_t 		*t
 * @return:	void
 *
 */

void tree_print(tree_t *t)
{
	assert(t!=NULL);
	printf("----------AVL TREE----------\n");
	printf("Height = %d\n",tree_getHeight(t));
	tree_recursive_print(t->root,t->print,0);
	printf("-------------END-------------\n");
	return;
}




/*
 * @COMPLEXITY: O(n)
 *
 * The function tree_free() takes as an argument
 * a tree_t data structure and removes the root
 * of the tree until the tree becomes empty by
 * invoking the static function tree_removeRoot().
 * If the user has provided a destroy function
 * the data components of each node is deallocated
 * as well.Otherwise only the node components are.
 * Once the tree is empty, the tree data structure
 * is deallocated and it's components set to null.
 *
 * @param:	tree_t 		*t
 * @return:	void
 *
 */

void tree_free(tree_t *t)
{
	assert(t!=NULL);
	while (!tree_isEmpty(t)) { tree_removeRoot(t); }
	t->cmp=NULL;
	t->print=NULL;
	t->destroy=NULL;
	free(t);
	t=NULL;
	return;
}
