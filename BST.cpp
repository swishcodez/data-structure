#include <iostream>
using namespace std;

struct node
{
    int key;
    struct node *left, *right;
};

struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

int height(node* node){
    if(node == NULL)
        return 0;
    return max(height(node->left), height(node->right)) + 1 ;
}

int weight(node* node){
    if(node == NULL)
        return 0;
    return weight(node->left) + weight(node->right) + 1;
}

void inorder(struct node *root, int space = 0, int height = 10)
{
    if (root != NULL)
    {
        space += height;
        inorder(root->right, space);
        cout << endl;
        for (int i = height; i < space; i++)
        {
            cout << ' ';
        }
        cout << root->key;

        cout << endl;
        inorder(root->left, space);
    }
    else
    {
        return;
    }
}

struct node *insert(struct node *node, int key)
{

    if (node == NULL)
    {
        return newNode(key);
    };
    if (key < node->key)
    {
        node->left = insert(node->left, key);
    }
    else
        node->right = insert(node->right, key);

    return node;
}

struct node *minValueNode(struct node *node)
{
    struct node *current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct node *deleteNode(struct node *root, int key)
{

    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        // ^4 sariin 28 delete node
        struct node *temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int main()
{
    struct node *root = NULL;
    root = insert(root, 2);
    root = insert(root, 8);
    root = insert(root, 10);
    root = insert(root, 9);
    root = insert(root, 15);
    root = insert(root, 6);
    root = insert(root, 18);
    root = insert(root, 10);
    root = insert(root, 11);

    cout << "Inorder traversal: ";
    inorder(root);   
    cout << "height : " << height(root) << endl;
    cout << "weight : " << weight(root) << endl;
    cout << "\nAfter deleting 10\n";
    root = deleteNode(root, 10);
    cout << "Inorder traversal: ";
    inorder(root);
    cout << "height : " << height(root) << endl;
    cout << "weight : " << weight(root) << endl;
}
