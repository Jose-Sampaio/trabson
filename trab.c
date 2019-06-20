#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct Interval
{
	int low,high;
}interval;

typedef struct Inode
{
	interval*i;
	int max;
	struct Inode *left,*right;
  int height;
} inode;

int height(struct Inode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

struct node** createQueue(int *front, int *rear)
{
    struct node **queue =
        (struct node **)malloc(sizeof(struct node*)*500);

    *front = *rear = 0;
    return queue;
}

void enQueue(struct node **queue, int *rear, struct node *new_node)
{
    queue[*rear] = new_node;
    (*rear)++;
}

struct node *deQueue(struct node **queue, int *front)
{
    (*front)++;
    return queue[*front - 1];
}


void printLevelOrder(inode* root)
{
    int rear, front;
    inode **queue = createQueue(&front, &rear);
    inode *temp_node = root;

    while (temp_node)
    {
        printf("%d %d \n", temp_node->i->low, temp_node->i->high);

        if (temp_node->left)
            enQueue(queue, &rear, temp_node->left);

        if (temp_node->right)
            enQueue(queue, &rear, temp_node->right);

        temp_node = deQueue(queue, &front);
    }
}


inode*NewNode(interval i)
{
	inode*n=(inode*)malloc(sizeof(inode));
	n->i=(interval*)malloc(sizeof(interval));
	n->i->low=i.low;
	n->i->high=i.high;
	n->max=i.high;
	n->left=n->right=NULL;
  n->height = 1;
	return n;
}

inode*rightRotate(struct Inode *y)
{
    struct Inode *x = y->left;
    struct Inode *T2 = x->right;

    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

inode *leftRotate(struct Inode *x)
{
    struct Inode *y = x->right;
    struct Inode *T2 = y->left;

    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}

int getBalance(struct Inode *N)
{
    if (N == NULL)
        return 0;

    return height(N->left) - height(N->right);
}

inode*insert(inode*root,interval i)
{

	if(root==NULL)
	return NewNode(i);

	int l=root->i->low;

	if(i.low<l)
	root->left=insert(root->left,i);
	else
	root->right=insert(root->right,i);

	if(root->max<i.high)
	root->max=i.high;
  root->height = 1 + max(height(root->left),height(root->right));
  int balance = getBalance(root);

  if (balance > 1 && root->left->i->high > i.high)
    return rightRotate(root);
		return root;

	if (balance < -1 && root->right->i->low > i.low)
		return leftRotate(root);
		return root;

}


void preorder(inode*root)
{
	if(root==NULL)
	return;

	printf("%d  %d \n",root->i->low,root->i->high);
	preorder(root->left);
	preorder(root->right);
}

int doOverlap(inode*root,interval i)
{
	if(i.low>=root->i->low && i.high<=root->i->high)
	return 1;

	return 0;
}

inode*overlap(inode*root,interval i)
{
	if(root==NULL)
	return NULL;


	if(doOverlap(root,i))
	{
	preorder(root);
}
	overlap(root->left,i);
	overlap(root->right,i);
}

inode*minlowinterval(inode*root)
{
	while(root->left)
	root=root->left;

	return root;
}

int findmax(int a,int b,int c)
{
	return a>b?(a>c?a:c):(b>c?b:c);
}

inode* deleteinterval(inode*root,interval i)
{
	if(root==NULL)
	return NULL;

	inode*temp;

	if(i.low<root->i->low)
	root->left=deleteinterval(root->left,i);
	else if(i.low>root->i->low)
	root->right=deleteinterval(root->right,i);
	else if(i.low==root->i->low)
	{
		if(i.high==root->i->high)
		{
		if(root->left==NULL)
		{
			temp=root->right;
			free(root);
			return temp;
		}
		else if(root->right==NULL)
		{
			temp=root->left;
			free(root);
			return temp;
		}
		temp=minlowinterval(root->right);
		root->i=temp->i;;
		root->right=deleteinterval(root->right,*(temp->i));
	}
	else
	root->right=deleteinterval(root->right,i);
}
	root->max=findmax(root->i->high,((root->left)?root->left->max:INT_MIN),((root->right)?root->right->max:INT_MIN));
	return root;
}

inode* Search(inode*root,interval i){
	if (root==NULL) {
		return NULL;
	}
  else if (doOverlap(root,i)) {
		printf("%d  %d \n",root->i->low,root->i->high);
		return root;
	}
	else if (root->i->high < i.low) {
		Search(root->right, i);
	}
	else if (root->i->low > i.high) {
		Search(root->left, i);
	}
}
int main()
{
	int j,k=-1;
	inode*root=NULL;
	while (k!=0) {
  printf("Selecione sua opção.0-sair, 1-insert, 2-delete, 3-Intervalo Sobrepujante, 4-Encontrar intervalo, 5-Impressão em ordem\n");
	scanf("%d",&k);
	if (k==1) {
		printf("qual o numero de intervalos a serem acrescentados?\n");
		scanf("%d\n",&j);
		interval ins[j];
		int n=sizeof(ins)/sizeof(ins[0]);
		for (int l = 0; l < j; l++) {
		scanf("%d %d",&ins[l].low,&ins[l].high);
	}
	for(int i=0;i<n;i++){
	root=insert(root,ins[i]);
}
printf("Deseja fazer mais alguma operação? insira '0' para sair\n");
scanf("%d", &k);
}
  if (k==2) {
  	interval y;
		printf("Qual intervalo a ser deletado?\n");
		scanf("%d %d",&y.low, &y.high);
		root=deleteinterval(root,y);
		printf("Deseja fazer mais alguma operação? insira '0' para sair e 1 para continuar\n");
		scanf("%d", &k);
  }

	else if (k==3) {
	interval x;
	printf("Insira o intervalo: \n");
	scanf("%d %d",&x.low,&x.high);
	overlap(root,x);
	printf("Deseja fazer mais alguma operação? insira '0' para sair e 1 para continuar\n");
	scanf("%d", &k);
}
	else if (k==4) {
		interval z;
		printf("Insira o intervalo: \n");
		scanf("%d %d", &z.low, &z.high);
		Search(root, z);
		printf("Deseja fazer mais alguma operação? insira '0' para sair e 1 para continuar\n");
		scanf("%d", &k);
	}
	else if (k==5) {
		printLevelOrder(root);
		printf("Deseja fazer mais alguma operação? insira '0' para sair e 1 para continuar\n");
		scanf("%d", &k);
	}

}


	return 0;
}
