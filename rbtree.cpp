#include <bits/stdc++.h>
using namespace std;

class Node
{
  public:
    int data;
    char color;
    Node *left, *right, *parent;

    Node(int data)
    {
        this->data = data;
        color = 'r';
        left = right = parent = NULL;
    }
};

class RBtree
{
  public:
    Node *insert(Node *root, int data)
    {
        if (root == NULL)
        {
            root = new Node(data);
            return root;
        }
        if (data > root->data)
        {
            root->right = insert(root->right, data);
            root->right->parent = root;
        }
        else
        {
            root->left = insert(root->left, data);
            root->left->parent = root;
        }

        return root;
    }

    char uncle_color(Node *root)
    {
        Node *parent = root->parent;
        Node *grandparent = parent->parent;
        Node *uncle = NULL;
        if (grandparent->left == parent)
            uncle = grandparent->right;
        else
            uncle = grandparent->left;

        return uncle->color;
    }

    void fixViolation(Node *root, Node *pt)
    {
        Node *parent = NULL, *grandparent = NULL;
        while ((pt != root) && root->color != 'b') )
    }
}
