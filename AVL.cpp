#include<bits/stdc++.h>
using namespace std;

class node
{
    private:
        int data,height;
        node* left;
        node* right;
    public:
        node()
        {
            data = 0;
            height = 0;
            left = NULL;
            right = NULL;
        }
        node(int key)
        {
            this->data = key;
            this->height = 1;
            this->left = NULL;
            this->right = NULL;
        }

        friend class AVL;
};

class AVL
{
    private:
        node* root;
    public:
        AVL()   {root = NULL;}
        void setroot(node* x)      {root = x;}
        node* getroot()         {return root;}
        int getHeight(node*);
        int getBalanceFactor(node* node);
        node* insert(node*,int);
        void traversal(node*);
        int height_of_tree(node*);
        node* left_rotate(node*);
        node* right_rotate(node*);
};

int AVL :: getBalanceFactor(node* node) 
{
        if (node == nullptr)             return 0;
        return getHeight(node->left) - getHeight(node->right);
}

int AVL :: getHeight(node* n)
{
        if (n == nullptr)             return 0;
        return n->height;
}

node* AVL :: insert(node* current,int key)
{
    if(current == NULL)
    {
        node* temp = new node(key);
        return temp;
    }
    if(key<current->data)  current->left = insert(current->left,key);

    else    current->right = insert(current->right,key);

    current->height = 1 + max(getHeight(current->left) , getHeight(current->right));

    int balance_factor = getBalanceFactor(current);

    if(balance_factor > 1 && key < current->left->data)     return right_rotate(current);
    
    else if(balance_factor > 1 && key > current->left->data)
    {
        current->left = left_rotate(current->left);
        return right_rotate(current);
    }
    else if (balance_factor < -1 && key > current->right->data)  return left_rotate(current);
    
    else if (balance_factor < -1 && key < current->right->data)
    {
        current->right = right_rotate(current->right);
        return left_rotate(current);
    }

    return current;
}

node* AVL :: right_rotate(node* current)
{
    node* y = current->left;
    node* z = y->right;

    y->right = current;
    current->left = z;
    current->height = 1 + max(getHeight(current->left), getHeight(current->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

node* AVL :: left_rotate(node* current)
{
    node* y = current->right;
    node* z = y->left;

    y->left = current;
    current->right = z;
    current->height = 1 + max(getHeight(current->left), getHeight(current->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

void AVL :: traversal(node* Root)
{
    if(Root== NULL) return;
    queue<node*> q;
    q.push(Root);
    while(!q.empty())
    {
        node* temp = q.front();
        q.pop();
        cout<<temp->data<<" ";
        if(temp->left != NULL)     q.push(temp->left);
        if(temp->right != NULL)    q.push(temp->right);
    }
    cout<<endl;
}

int AVL :: height_of_tree(node* Root)
{
    if(Root == NULL)    return 0;
    return 1 + max(height_of_tree(Root->left), height_of_tree(Root->right));
}

int main()
{
    AVL tree;
    int n;
    cout<<"Enter no of elements to enter :";
    cin>>n;

    int x;
    cout<<"Enter elements :";
    for(int i=0; i<n ; i++)
    {
        cin>>x;
        tree.setroot(tree.insert(tree.getroot(),x));
    }

    cout<<"Traversal :";
    tree.traversal(tree.getroot());

    x = tree.getHeight(tree.getroot());
    cout<<"Height "<<x<<endl;
}
    