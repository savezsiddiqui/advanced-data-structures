#include <bits/stdc++.h>
using namespace std;

class Node
{
  public:
    int low, high, max;
    Node *left, *right;

    Node(int low, int high)
    {
        this->low = low;
        this->high = high;
        max = high;
        left = right = NULL;
    }
};

class IntervalTree
{
  public:
    Node *insert(Node *root, int low, int high)
    {
        if (root == NULL)
            root = new Node(low, high);
        else if (low < root->low)
            root->left = insert(root->left, low, high);
        else
            root->right = insert(root->right, low, high);

        if (high > root->max)
            root->max = high;

        return root;
    }

    void overlap(Node *root, int low, int high)
    {
        if (root == NULL)
            return;

        if (root->low <= high && low <= root->high)
        {
            cout << "[" << root->low << ", " << root->high << "]" << endl;
            // return root;
        }

        if (root->left != NULL && root->left->max >= low)
            overlap(root->left, low, high);

        overlap(root->right, low, high);
    }

    Node *min(Node *root)
    {
        if (root->left == NULL)
            return root;
        else
            return min(root->left);
    }

    int UpdateMax(Node *root)
    {
        if (root == NULL)
            return -1;
        root->max = max(root->high, max(UpdateMax(root->left), UpdateMax(root->right)));
        return root->max;
    }

    Node *deleteNode(Node *root, int low)
    {
        if (root == NULL)
            return NULL;

        else if (low > root->low)
            root->right = deleteNode(root->right, low);
        else if (low < root->low)
            root->left = deleteNode(root->left, low);
        else
        {

            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                return NULL;
            }

            else if (root->right == NULL)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }

            else if (root->left == NULL)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }

            else
            {
                Node *temp = min(root->right);
                root->low = temp->low;
                root->high = temp->high;
                root->right = deleteNode(root->right, temp->low);
            }
        }

        return root;
    }

    void inOrder(Node *root)
    {
        if (root == NULL)
            return;

        inOrder(root->left);
        cout << "[" << root->low << ", " << root->high << ", " << root->max << "]"
             << " ";
        inOrder(root->right);
    }
};

int main()
{
    int n, low, high;
    IntervalTree it;
    Node *root = NULL;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> low >> high;
        root = it.insert(root, low, high);
    }

    it.inOrder(root);
    cout << endl;
    // cout << "Enter an interval to check" << endl;
    // cin >> low >> high;
    // it.overlap(root, low, high);
    cout << "Enter a node to delete" << endl;
    cin >> low;
    it.deleteNode(root, low);
    it.UpdateMax(root);
    it.inOrder(root);
}
