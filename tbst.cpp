#include <bits/stdc++.h>
#include <cstdlib>
#define MAX_VALUE 1e7
using namespace std;

class node
{
public:
    int key;
    node *left, *right;
    bool left_thread, right_thread;
};

class Threaded_BST
{
private:
    node *root;

public:
    Threaded_BST()
    {
        root = new node();
        root->right = root->left = root;
        root->left_thread = true;
        root->key = MAX_VALUE;
    }

    void insert(int key);
    bool search(int key);
    void inorder();
    void Delete(int key);
    void BST_to_threaded();
    void Bst_insert(int val);
};

void Threaded_BST ::BST_to_threaded()
{

    vector<node *> vec;

    node *T = root->left;
    stack<node *> stk;
    int ct = 0;
    while (T != NULL || !stk.empty())
    {
        while (T != NULL)
        {
            stk.push(T);
            T = T->left;
        }
        T = stk.top();
        stk.pop();

        vec.push_back(T);

        T = T->right;
        ct++;
    }

    int n = vec.size();

    node *t = vec[0];
    t->left = root;
    t->left_thread = true;
    t = vec[n - 1];
    t->right = root;
    t->right_thread = true;

    root->left_thread = false;

    for (int i = 0; i < n; i++)
    {
        node *t = vec[i];

        if (i)
            if (t->left == NULL)
            {
                t->left = vec[i - 1];
                t->left_thread = true;
            }
            else
            {
                t->left_thread = false;
            }

        if (i != n - 1)
            if (t->right == NULL)
            {
                t->right = vec[i + 1];
                t->right_thread = true;
            }
            else
            {
                t->right_thread = false;
            }
    }
}

void Threaded_BST ::Bst_insert(int val)
{

    node *p = root;

    if (p->left == p)
    {
        // first insertion
        node *tmp = new node();
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->key = val;
        p->left = tmp;
        return;
    }

    while (true)
    {
        if (p->key < val)
        {
            if (p->right == NULL)
                break;
            p = p->right;
        }
        else if (p->key > val)
        {
            if (p->left == NULL)
                break;
            p = p->left;
        }
        else
        {
            return;
        }
    }

    node *tmp = new node();
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->key = val;

    if (p->key < val)
    {
        p->right = tmp;
    }
    else
    {
        p->left = tmp;
    }
}

void Threaded_BST ::insert(int key)
{
    node *p = root;
    while (true)
    {
        if (p->key < key)
        {
            if (p->right_thread)
                break;
            p = p->right;
        }
        else if (p->key > key)
        {
            if (p->left_thread)
                break;
            p = p->left;
        }
        else
        {
            return;
        }
    }

    node *tmp = new node();
    tmp->key = key;
    tmp->right_thread = tmp->left_thread = true;

    if (p->key < key)
    {
        tmp->right = p->right;
        tmp->left = p;
        p->right = tmp;
        p->right_thread = false;
    }
    else
    {
        tmp->right = p;
        tmp->left = p->left;
        p->left = tmp;
        p->left_thread = false;
    }
}

bool Threaded_BST ::search(int key)
{
    node *tmp = root->left;
    while (true)
    {
        if (tmp->key < key)
        {
            if (tmp->right_thread)
                return false;
            tmp = tmp->right;
        }
        else if (tmp->key > key)
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

void Threaded_BST ::inorder()
{
    node *tmp = root, *p;
    while (true)
    {
        p = tmp;
        tmp = tmp->right;
        if (!p->right_thread)
        {
            while (!tmp->left_thread)
            {
                tmp = tmp->left;
            }
        }
        if (tmp == root)
            break;
        cout << tmp->key << "   ";
    }
    cout << endl;
}

void Threaded_BST ::Delete(int key)
{
    node *dest = root->left, *p = root;

    while (true)
    {
        if (dest->key < key)
        {
            if (dest->right_thread)
                return;
            p = dest;
            dest = dest->right;
        }
        else if (dest->key > key)
        {
            if (dest->left_thread)
                return;
            p = dest;
            dest = dest->left;
        }
        else
        {
            break;
        }
    }

    node *target = dest;
    if (!dest->right_thread && !dest->left_thread)
    {
        p = dest;
        target = dest->left;
        while (!target->right_thread)
        {
            p = target;
            target = target->right;
        }
        dest->key = target->key;
    }

    if (p->key >= target->key)
    {
        if (target->right_thread && target->left_thread)
        {
            p->left = target->left;
            p->left_thread = true;
        }
        else if (target->right_thread)
        {
            node *largest = target->left;
            while (!largest->right_thread)
            {
                largest = largest->right;
            }
            largest->right = p;
            p->left = target->left;
        }
        else
        {
            node *smallest = target->right;
            while (!smallest->left_thread)
            {
                smallest = smallest->left;
            }
            smallest->left = target->left;
            p->left = target->right;
        }
    }
    else
    {
        if (target->right_thread && target->left_thread)
        {
            p->right = target->right;
            p->right_thread = true;
        }

        else if (target->right_thread)
        {

            node *largest = target->left;
            while (!largest->right_thread)
            {
                largest = largest->right;
            }
            largest->right = target->right;
            p->right = target->left;
        }
        else
        {
            node *smallest = target->right;
            while (!smallest->left_thread)
            {
                smallest = smallest->left;
            }
            smallest->left = p;
            p->right = target->right;
        }
    }
}

int main()
{
    Threaded_BST tbst, bst;

    char ch;
    int choice, val;

    do
    {
        cout << "1. Insert " << endl;
        cout << "2. Display" << endl;
        cout << "3. Delete" << endl;
        cout << "4. Search" << endl;
        cout << "5. BST insert" << endl;
        cout << "6. BST_to_threaded" << endl;
        cout << "7. exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter element to insert: ";
            cin >> val;
            tbst.insert(val);
            break;

        case 2:
            cout << "\nInorder: ";
            tbst.inorder();
            break;

        case 3:
            cout << "Enter element to delete: ";
            cin >> val;
            tbst.Delete(val);
            break;
          
        case 4:
            cout << "Enter element to search: ";
            cin >> val;
            if (tbst.search(val) == true)
                cout << "Element " << val << " found " << endl;
            else
                cout << "Element " << val << " not found " << endl;
            break;

        case 5:
            cout << "Enter  element to insert: ";
            cin >> val;
            tbst.Bst_insert(val);
            break;

        case 6:
            tbst.BST_to_threaded();
            break;

        case 7:
            exit(0);

        default:
            cout << "Wrong Entry \n ";
            break;
        }

    } while (true);
}