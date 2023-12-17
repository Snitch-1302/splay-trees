#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *left, *right;
};


struct node* newNode(int key)
{
	struct node* node = malloc(sizeof(struct node));
	node->data = key;
	node->left = node->right = NULL;
	return (node);
}

//Zig Rotation
struct node *rightRotate(struct node *x)
{
	struct node *y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}

//Zag Rotation
struct node *leftRotate(struct node *x)
{
	struct node *y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

//Splaying process
struct node *splay(struct node *root, int key)
{
	// Base cases: root is NULL or key is present at root
	if (root == NULL || root->data == key)
		return root;

	// Data in left subtree
	if (root->data > key)
	{
		// 1st Rotation is alone done here

		// Data is not in tree, we are done
		if (root->left == NULL)
            return root;

		// Zig-Zig Rotation (Left Left)
		if (root->left->data > key)
		{
			// Recursive function to make the data as root of left-left
			root->left->left = splay(root->left->left, key);

			// Zig rotation for root
			root = rightRotate(root);
		}

		//Zig-Zag Rotation (Left - Right)
		else if (root->left->data < key)
		{
			//Recursive function to make the data as root of left-right
			root->left->right = splay(root->left->right, key);

			if (root->left->right != NULL)
				root->left = leftRotate(root->left);
		}

        //2nd rotation for root
		return (root->left == NULL)? root: rightRotate(root);
	}

	//Data in right subtree
	else
	{
		// Base cases: root is NULL or key is present at root
		if (root->right == NULL)
            return root;

        //Zag - Zig Rotation (Right-Left)
		if (root->right->data > key)
		{

			//Making the key as root
			root->right->left = splay(root->right->left, key);

			//Zag rotation
			if (root->right->left != NULL)
				root->right = rightRotate(root->right);
		}

		//Zag-Zag rotation
		else if (root->right->data < key)
		{

			//Recursive function to make the data as root
			root->right->right = splay(root->right->right, key);
			root = leftRotate(root);
		}

        //2nd rotation for root node
		return (root->right == NULL)? root: leftRotate(root);
	}
}

//Insertion of node
struct node *insert(struct node *root, int k)
{

	if (root == NULL) return newNode(k);


	root = splay(root, k);

	if (root->data == k) return root;

	struct node *newnode = newNode(k);

	if (root->data > k)
	{
		newnode->right = root;
		newnode->left = root->left;
		root->left = NULL;
	}

	else
	{
		newnode->left = root;
		newnode->right = root->right;
		root->right = NULL;
	}

	return newnode;
}

//Delete function for node
struct node *Delete(struct node *root, int key)
{
    struct node *temp;
    if(!root)
        return NULL;

    //splaying the given key node
    root = splay(root, key);

    //if key not present, return root, making no changes
    if(key!=root->data)
        return root;

    //key in left child of root
    if(!root->left)
    {
        temp = root;
        root = root->right;
    }
    //else
    else
    {
        temp = root;
        root = splay(root->left, key);
        //right child of previous child is made as new root's right child
        root->right = temp->right;
    }
    free(temp);

    //root of new splay tree is returned
    return root;
};

//Preorder traversal of Tree
void preOrder(struct node *root)
{
	if (root != NULL)
	{
		printf("%d ", root->data);
		preOrder(root->left);
		preOrder(root->right);
	}
}

int main()
{

    struct node *root = NULL;
    int n,value;
    int i;
    printf("Enter the number of nodes to be inserted:  \n");
    scanf("%d", &n);
    for(i=0; i<n; i++)
    {
        printf("Enter the node: ");
        scanf("%d",&value);
        root = insert(root,value);
    }
    printf("PreOrder traversal: \n");
	preOrder(root);

	int splay;
	printf("\nEnter the node to be splayed:  \n");
	scanf("%d", &splay);
	root = insert(root, splay);
	printf("\nPreOrder traversal of the modified Splay tree is \n");
	preOrder(root);

	int key;
	printf("\nEnter the node to be deleted:  \n");
	scanf("%d", &key);
	root = Delete(root, key);
	printf("PreOrder traversal of modified Splay Tree is: \n");
	preOrder(root);
	return 0;
}
