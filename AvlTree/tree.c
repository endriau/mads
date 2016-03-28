/*
 * This file contains function definitions
 * regarding the balanced binary tree data
 * structure.
 *
 * @author:	Endri Kastrati
 * @date:	28/03/2016
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"



#define	ALLOWED_IMBALANCE	1
#define HEIGHT(node)        (node==NULL ? -1 : node->height)
#define MAX(a,b)            (a > b ? a : b)




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


/////////////////////////////////////////////////////////////////////////////////////////////////





static node_t *rotate_with_left_child(node_t *node)
{
	node_t *rotate_node=NULL;
	rotate_node=node->left;
	node->left=rotate_node->right;
	rotate_node->right=node;
	node->height=MAX(HEIGHT(node->left),HEIGHT(node->right))+1;
	rotate_node->height=MAX(HEIGHT(rotate_node->left),node->height)+1;
	return rotate_node;
}




static node_t *rotate_with_right_child(node_t *node)
{
	node_t *rotate_node=NULL;
	rotate_node=node->right;
	node->right=rotate_node->left;
	rotate_node->left=node;
	node->height=MAX(HEIGHT(node->left),HEIGHT(node->right))+1;
	rotate_node->height=MAX(HEIGHT(rotate_node->right),node->height)+1;
	return rotate_node;
}




static node_t *double_with_left_child(node_t *node)
{
	node->left=rotate_with_right_child(node->left);
	return rotate_with_left_child(node);
}




static node_t *double_with_right_child(node_t *node)
{
	node->right=rotate_with_left_child(node->right);
	return rotate_with_right_child(node);
}







static node_t *balance(node_t *node)
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







static node_t *tree_recursive_insert(node_t *node,TreeCompareFn cmp,void *data)
{
	int compare=0;
	node_t *new_node=NULL;
	assert(cmp!=NULL);

	if (node==NULL)
	{
		new_node=(node_t *)malloc(sizeof(*new_node));
		assert(new_node!=NULL);
		new_node->data=data;
		new_node->left=NULL;
		new_node->right=NULL;
		new_node->height=0;
		return new_node;
	}

	compare=cmp(data,node->data);

	if (compare<0)
	{
		node->left=tree_recursive_insert(node->left,cmp,data);
	}
	else if (compare>0)
	{
		node->right=tree_recursive_insert(node->right,cmp,data);
	}
	else {}
	return balance(node);
}


/////////////////////////////////////////////////////////////////////////////////////////////////



void tree_insert(tree_t *t,void *data)
{
	assert(t!=NULL);
	t->root=tree_recursive_insert(t->root,t->cmp,data);
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////




static node_t *tree_recursive_search(node_t *node,TreeCompareFn cmp,void *item)
{
	int compare=0;
	assert(cmp!=NULL);
	if (node==NULL) { return node; }
	compare=cmp(item,node->data);

	if (compare<0)
	{
		return tree_recursive_search(node->left,cmp,item);
	}
	else if (compare>0)
	{
		return tree_recursive_search(node->right,cmp,item);
	}
	else
	{
		return node;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////


int tree_search(tree_t *t,void *item)
{
	node_t *query_node=NULL;
	assert(t!=NULL);
	query_node=tree_recursive_search(t->root,t->cmp,item);
	return (query_node!=NULL ? 1 : 0);
}



void *tree_getElem(tree_t *t,void *item)
{
	node_t *query_node=NULL;
	assert(t!=NULL);
	query_node=tree_recursive_search(t->root,t->cmp,item);
	return (query_node!=NULL ? query_node->data : NULL);
}


void *tree_getRoot(tree_t *t)
{
	assert(t!=NULL);
	return (t->root!=NULL ? t->root->data : NULL);
}



/////////////////////////////////////////////////////////////////////////////////////////////////


static node_t *find_min(node_t *node)
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



static node_t *tree_recursive_remove(node_t *node,TreeCompareFn cmp,TreeDestroyFn destroy,void *item)
{
	int compare=0;
	assert(cmp!=NULL);
	if (node==NULL) { return node; }
	compare=cmp(item,node->data);

	if (compare<0)
	{
		node->left=tree_recursive_remove(node->left,cmp,destroy,item);
	}
	else if (compare>0)
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

			node_t *old_node=NULL;
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

			node_t *old_node=NULL;
			old_node=node;
			node=node->left;
			free(old_node);
			old_node=NULL;

		}
		else
		{
			node_t *min_node=NULL;
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


/////////////////////////////////////////////////////////////////////////////////////////////////



void tree_remove(tree_t *t,void *item)
{
	assert(t!=NULL);
	if (tree_isEmpty(t)) { return; }
	t->root=tree_recursive_remove(t->root,t->cmp,t->destroy,item);
	return;
}


void tree_removeRoot(tree_t *t)
{
	assert(t!=NULL);
	tree_remove(t,t->root->data);
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////


int tree_isEmpty(tree_t *t)
{
	assert(t!=NULL);
	return (t->root==NULL ? 1 : 0);
}


int tree_getHeight(tree_t *t)
{
	assert(t!=NULL);
	return (t->root==NULL ? -1 : t->root->height);
}


/////////////////////////////////////////////////////////////////////////////////////////////////



static void tree_recursive_print(node_t *node,TreePrintFn print,int depth)
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


/////////////////////////////////////////////////////////////////////////////////////////////////


void tree_print(tree_t *t)
{
	assert(t!=NULL);
	printf("----------AVL TREE----------\n");
	printf("Height = %d\n",tree_getHeight(t));
	tree_recursive_print(t->root,t->print,0);
	printf("-------------END-------------\n");
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////

void tree_free(tree_t *t)
{
	assert(t!=NULL);
	while (!tree_isEmpty(t)) { tree_removeRoot(t); }
	free(t);
	t=NULL;
	return;
}
