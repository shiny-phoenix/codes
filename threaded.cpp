#include <bits/stdc++.h>
using namespace std;

class node
{
    int data;
    node *left;
    node *right;
    bool left_thread, right_thread;

public:
    node(int val, bool l = 0, bool r = 0)
    {
        this->data = val;
        this->left = NULL;
        this->right = NULL;
        this->left_thread = l;
        this->right_thread = r;
    }
    friend class Threaded_BST;
};

class Threaded_BST
{
    node *root;
    node *dummy_node = new node(-1);

public:
    Threaded_BST()
    {
        root = NULL;
        dummy_node->left = root;
    }
    node *getroot() { return root; }
    void BST_insert(int);
    void insert(int data);

    void inorder();
    bool search(int);
    void bst_to_threaded();

    void delete_node(int);
};

void Threaded_BST ::BST_insert(int data)
{
    node *ptr = new node(data);
    if (root == NULL)
        root = ptr;
    else
    {
        node *temp = root;
        while (1)
        {
            if (data < temp->data)
            {
                if (temp->left == NULL)
                {
                    temp->left = ptr;
                    break;
                }
                else
                    temp = temp->left;
            }
            else
            {
                if (temp->right == NULL)
                {
                    temp->right = ptr;
                    break;
                }
                else
                    temp = temp->right;
            }
        }
    }
}

void Threaded_BST ::insert(int data)
{
    node *ptr = new node(data);

    if (root == NULL)
    {
        root = ptr;
        dummy_node->data = root->data;
        /*
        dummy_node->left = root;
        dummy_node->right = dummy_node;
        dummy_node->left_thread = 0;
        dummy_node->right_thread = 0;
        */
        root->left = dummy_node;
        root->left_thread = 1;
        root->right = dummy_node;
        root->right_thread = 1;
    }

    else
    {
        node *temp = root;
        bool left_child = 0;
        bool right_child = 0;

        while (1)
        {
            if (temp->data > data)
            {
                if (!temp->left_thread)
                    temp = temp->left;
                else
                {
                    left_child = 1;
                    break;
                }
            }
            else if (temp->data < data)
            {

                if (!temp->right_thread)
                    temp = temp->right;
                else
                {
                    right_child = 1;
                    break;
                }
            }

            else
            {
                return;
            }
        }

        if (left_child)
        {
            ptr->left = temp->left;
            ptr->right = temp;
            ptr->left_thread = 1;
            ptr->right_thread = 1;

            temp->left = ptr;
            temp->left_thread = 0;
        }

        if (right_child)
        {
            ptr->right = temp->right;
            ptr->left = temp;
            ptr->left_thread = 1;
            ptr->right_thread = 1;

            temp->right = ptr;
            temp->right_thread = 0;
        }
    }
}

void Threaded_BST ::inorder()
{

    cout<<"inorder : ";
    if (root == NULL)
        return;

    while (root->left_thread == 0)
        root = root->left;

    while (root != dummy_node)
    {
        cout << root->data << " ";

        if (root->right_thread)
            root = root->right;
        else
        {
            root = root->right;
            while (root->left_thread == 0)
                root = root->left;
        }
    }
}

bool Threaded_BST ::search(int key)
{
    node *tmp = root->left;
    while (true)
    {
        if (tmp->data < key)
        {
            if (tmp->right_thread)
                return false;
            tmp = tmp->right;
        }
        else if (tmp->data > key)
        {
            if (tmp->left_thread)
                return false;
            tmp = tmp->left;
        }
        else
        {
            return true;
        }
    }
}

void Threaded_BST ::delete_node(int key)
{

    // Initialize the current node as the left child of the root node and the parent node as the root node
    node *dest = root, *p = root;

    // Loop through the tree until the desired node is found or the end of the tree is reached
    while (1)
    {
        if (dest->data < key)
        {
            /* not found */
            // If the current node's data is less than the desired key and the right thread is present, then the node does not exist
            if (dest->right_thread)
                return;
            // Otherwise, update the parent and current nodes and continue searching
            p = dest;
            dest = dest->right;
        }
        else if (dest->data > key)
        {
            /* not found */
            // If the current node's data is greater than the desired key and the left thread is present, then the node does not exist
            if (dest->left_thread)
                return;
            // Otherwise, update the parent and current nodes and continue searching
            p = dest;
            dest = dest->left;
        }
        else
        {
            /* found */
            // If the desired node is found, break out of the loop
            break;
        }
    }

    // Store the target node in a separate pointer
    node *target = dest;

    // If the target node has two children
    if (!dest->right_thread && !dest->left_thread)
    {
        /* dest has two children*/
        // Store the parent of the target node in p
        p = dest;
        // Find the largest node in the left subtree of the target node
        target = dest->left;
        while (!target->right_thread)
        {
            p = target;
            target = target->right;
        }
        // Replace the target node's data with the data of the largest node in its left subtree
        dest->data = target->data;
    }

    // If the target node is the left child of its parent
    if (p->data >= target->data)
    {
        // If the target node has no children, simply set the parent's left thread to true
        if (target->right_thread && target->left_thread)
        {
            p->left = target->left;
            p->left_thread = true;
        }
        // If the target node has only a right child
        else if (target->right_thread)
        {
            // Find the largest node in the left subtree of the target node
            node *largest = target->left;
            while (!largest->right_thread)
            {
                largest = largest->right;
            }
            // Set the right thread of the largest node to the parent node and update the parent's left child pointer
            largest->right = p;
            p->left = target->left;
        }
        // If the target node has only a left child
        else
        {
            // Find the smallest node in the right subtree of the target node
            node *smallest = target->right;
            while (!smallest->left_thread)
            {
                smallest = smallest->left;
            }
            // Set the left thread of the smallest node to the parent node and update the parent's left child pointer
            smallest->left = target->left;
            p->left = target->right;
        }
    }
    else
    {
        /* Case 2: target has only one child */
        if (target->right_thread && target->left_thread)
        {
            /* Case 2.1: target has no children */
            p->right = target->right;
            p->right_thread = true;
        }
        else if (target->right_thread)
        {
            /* Case 2.2: target has only left child */
            /* Find the largest node in the left subtree of target */
            node *largest = target->left;
            while (!largest->right_thread)
            {
                largest = largest->right;
            }
            /* Make largest's right child point to p, the parent of target */
            largest->right = target->right;
            /* Make p's right child point to target's left child */
            p->right = target->left;
        }
        else
        {
            /* Case 2.3: target has only right child */
            /* Find the smallest node in the right subtree of target */
            node *smallest = target->right;
            while (!smallest->left_thread)
            {
                smallest = smallest->left;
            }
            /* Make smallest's left child point to p, the parent of target */
            smallest->left = p;
            /* Make p's right child point to target's right child */
            p->right = target->right;
        }
    }
}

static vector<node *> v;
void Threaded_BST ::bst_to_threaded()
{
    stack<node *> st;
    node *curr = root;

    while (curr != NULL || st.empty() == false)
    {
        while (curr != NULL)
        {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top();
        st.pop();
        v.push_back(curr);
        curr = curr->right;
    }
    /*for(int i = 0; i < v.size(); i++){
        cout<<v[i]->data<<" ";
    }*/
    for (int i = 0; i < v.size(); i++)
    {
        if (i == 0)
        {
            if (v[i]->right == NULL && v[i]->left != NULL)
            {
                v[i]->right = v[i + 1];
                v[i]->right_thread = 1; // denoting that thread is built.
            }
            if (v[i]->left == NULL && v[i]->right != NULL)
            {
                v[i]->left = dummy_node;
                v[i]->left_thread = 1; // denoting that thread is built.
            }
            if (v[i]->left == NULL && v[i]->right == NULL)
            {
                v[i]->right = v[i + 1];
                v[i]->right_thread = 1; // denoting that thread is built.
                v[i]->left = dummy_node;
                v[i]->left_thread = 1; // denoting that thread is built.
            }
        }
        else if (i == v.size() - 1)
        {
            if (v[i]->right == NULL && v[i]->left != NULL)
            {
                v[i]->right = dummy_node;
                v[i]->right_thread = 1; // denoting that thread is built.
            }
            if (v[i]->left == NULL && v[i]->right != NULL)
            {
                v[i]->left = v[i - 1];
                v[i]->left_thread = 1; // denoting that thread is built.
            }
            if (v[i]->left == NULL && v[i]->right == NULL)
            {
                v[i]->left = v[i - 1];
                v[i]->left_thread = 1; // denoting that thread is built.
                v[i]->right = dummy_node;
                v[i]->right_thread = 1; // denoting that thread is built.
            }
        }
        else
        {
            if (v[i]->right == NULL && v[i]->left != NULL)
            {
                v[i]->right = v[i + 1];
                v[i]->right_thread = 1; // denoting that thread is built.
            }
            if (v[i]->left == NULL && v[i]->right != NULL)
            {
                v[i]->left = v[i - 1];
                v[i]->left_thread = 1; // denoting that thread is built.
            }
            if (v[i]->left == NULL && v[i]->right == NULL)
            {
                v[i]->left = v[i - 1];
                v[i]->left_thread = 1; // denoting that thread is built.
                v[i]->right = v[i + 1];
                v[i]->right_thread = 1; // denoting that thread is built.
            }
            else
            { // if both not NULL in case of root.
                continue;
            }
        }
    }
}

int main()
{
    Threaded_BST tree, tree1;
    int data;
    int choice;
    int ch;
    int key;
    bool result;
    node *xz;

    do
    {
        cout << "1. Threaded Insert" << endl;
        cout << "2. Traversal " << endl;
        cout << "3. Delete a node " << endl;
        cout << "4. Search" << endl;
        cout << "5. BST insert" << endl;
        cout << "6. convert" << endl;
        cout << "7. EXIT" << endl;
        cout << "Enter the choice : ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
            cout << "enter the data :";
            cin >> data;
            tree.insert(data);
            break;

        case 2:
            tree.inorder();
            cout << endl;
            break;

        case 3:
            cout << "Enter the node to be deleted : ";
            cin >> key;
            tree.delete_node(key);
            if (xz == NULL)
                tree = tree1;
            break;
        case 4:
            cout << "Enter key to be searched : ";
            cin >> key;
            result = tree.search(key);
            if (result)
                cout << "key found" << endl;
            else
                cout << "key is absent" << endl;
            break;
        case 5:
            cout << "enter the data :";
            cin >> data;
            tree.BST_insert(data);
            break;

        case 6:
            tree.bst_to_threaded();

        default:
            exit(0);
        }
    } while (0 < choice < 5);

    return 0;
}