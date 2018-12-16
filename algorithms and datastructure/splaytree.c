#include <stdio.h>
#include <stdlib.h>
//node of the tree
typedef struct NODE
{
	int v;
	struct NODE *left;
	struct NODE *right;
	struct NODE *p;
} node;
//the tree
typedef struct TREE
{
	node *root;
	node *nil;
} tree;

void create_tree(tree *t)
{
	t->nil=(node*)malloc(sizeof(node));
	t->nil->left = NULL;
	t->nil->right = NULL;
	t->nil->p = NULL;
	t->nil->v = -1;
	t->root = t->nil;
}
//insert a node to the tree
void insert(tree *t, node *x)
{
	if (t->root == t->nil)
	{
		t->root = x;
		return;
	}

	node *y = t->root;
	node *z = t->nil;
	while (y != t->nil)
	{
		z = y;
		if (y->v > x->v)
		{
			y = y->left;
		}
		else
		{
			y = y->right;
		}
	}
	x->p = z;
	if (x->v < z->v)
	{
		z->left = x;
	}
	else
	{
		z->right = x;
	}
}
//find the minimun node of the child tree x
node *minimun(tree *t, node *x)
{
	node *y = x;
	node *z = t->nil;
	while (y != t->nil)
	{
		z = y;
		y = y->left;
	}
}
//use x node inplace the y node in the tree t
void transplant(tree * t,node *x,node *y){

}
//delete x node in the tree t
void delete (tree *t, node *x)
{
	if (x->left == t->nil && x->right == t->nil)
	{
		if (x->p == t->nil)
		{
			t->root = t->nil;
			return;
		}
		if (x == x->p->left)
		{
			x->p->left = t->nil;
		}
		else
		{
			x->p->right = t->nil;
		}
	}
	else if (x->right == t->nil)
	{
		if (x->p == t->nil)
		{
			x->left->p = t->nil;
			t->root = x->left;
			return;
		}
		x->left->p = x->p;
		if (x == x->p->left)
		{
			x->p->left = x->left;
		}
		else
		{
			x->p->right = x->left;
		}
	}
	else
	{
		node *y = minimun(t, x->right);
		if (y->p == x)
		{
			y->p = x->p;
			y->left = x->left;
			if (x->p = t->nil)
			{
				t->root = y;
			}
			else if (x->p->left == x)
			{
				x->p->left = y;
			}
			else
			{
				x->p->right = y;
			}
		}
		else
		{
			y->p->left = y->right;
			y->right->p = y->p;
			y->p = x->p;
			y->left = x->left;
			y->right = x->right;
			x->right->p = y;
			x->left->p = y;
			if (x->p == t->nil)
			{
				t->root = y;
			}
			else if (x->p->left == x)
			{
				x->p->left = y;
			}
			else
			{
				x->p->right = y;
			}
		}
	}
}
//right rotate
void right_rotate(tree *t, node *x)
{
	node *y = x->p;
	if (y->p == t->nil)
	{
		t->root = x;
	}
	else if (y->p->left == y)
	{
		y->p->left = x;
	}
	else
	{
		x->p->p->right = x;
	}
	x->p = y->p;
	y->left = x->right;
	x->right->p = y;
	y->p = x;
	x->right = y;
}
//left rotate
void left_rotate(tree *t, node *x)
{
	node *y = x->p;
	if (y->p == t->nil)
	{
		t->root = x;
	}
	else if (x->p->left == y)
	{
		y->p->left = x;
	}
	else
	{
		y->p->right = x;
	}
	x->p = y->p;
	y->right = x->left;
	x->left->p = y;
	x->left = y;
	y->p = x;
}
//the necessary operation for a splay tree
void splay(tree *t, node *x)
{
	while (x->p != t->nil)
	{
		if (x == x->p->left)
		{
			right_rotate(t, x);
		}
		else
		{
			left_rotate(t, x);
		}
	}
}
//prefix print of a tree
void tree_walk(tree *t, node *x)
{
	if (x!=t->nil)
	{
		printf("%d ", x->v);
		tree_walk(t, x->left);
		tree_walk(t, x->right);
	}
}
 
int main(int argc, char const *argv[])
{
	tree *t = (tree *)malloc(sizeof(tree));
	create_tree(t);
	node *x = (node *)malloc(sizeof(node));
	x->left = t->nil;
	x->right = t->nil;
	x->p = t->nil;
	x->v = 10;

	node *y = (node *)malloc(sizeof(node));
	y->left = t->nil;
	y->right = t->nil;
	y->p = t->nil;
	y->v = 20;


	insert(t, x);
	tree_walk(t, t->root);
	delete(t,x);
	printf("\nhi\n");
	tree_walk(t, t->root);
	insert(t, x);
	insert(t, y);
	printf("\ninsert x,y\n");
	tree_walk(t,t->root);


	printf("\ndelete y\n");
	delete(t,y);
	tree_walk(t,t->root);

	printf("\ndelete x\n");
	delete(t,x);
	tree_walk(t,t->root);
	return 0;
}
