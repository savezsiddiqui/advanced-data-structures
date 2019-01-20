#include <bits/stdc++.h>
using namespace std;

int min(int x, int y)
{
    return x < y ? x : y;
}

void buildTree(int inputArray[], int segTree[], int start, int end, int currIndex)
{
    if (start == end)
    {
        segTree[currIndex] = inputArray[start];
    } 
    else
    {

        int mid = (start + end) / 2;
        //for left child
        buildTree(inputArray, segTree, start, mid, 2 * currIndex + 1);
        //for right child
        buildTree(inputArray, segTree, mid + 1, end, 2 * currIndex + 2);
        //updatinng the internal nodes
        segTree[currIndex] = min(segTree[2 * currIndex + 1], segTree[2 * currIndex + 2]);
    }
}

int minQuery(int *segTree, int qst, int qend, int st, int end, int currIndex)
{

    if ((st < qst && end < qst) || (st > qend && end > qend))
    {
        return INT_MAX;
    }

    else if (st >= qst && end <= qend)
    {
        return segTree[currIndex];
    }
    else
    {
        int mid = (st + end) / 2;

        return min(
            minQuery(segTree, qst, qend, st, mid, 2 * currIndex + 1),
            minQuery(segTree, qst, qend, mid + 1, end, 2 * currIndex + 2));
    }
}

void update(int *segTree, int st, int end, int qst, int qend, int currIndex, int value)
{
    // No overlap Condition
    if ((st < qst && end < qst) || (st > qend && end > qend))
        return;

    if (st == end)
    {
        segTree[currIndex] += value;
        return;
    }

    else
    {
        int mid = (st + end) / 2;
        //recursing the left child
        update(segTree, st, mid, qst, qend, 2 * currIndex + 1, value);
        //recursing the right child
        update(segTree, mid + 1, end, qst, qend, 2 * currIndex + 2, value);
        // updating the nodes as we go up
        segTree[currIndex] = min(segTree[2 * currIndex + 1], segTree[2 * currIndex + 2]);
    }
}

int main()
{
    int n;
    cin >> n;
    int inputArray[n], segTree[4 * n];

    for (int i = 0; i < n; i++)
    {
        cin >> inputArray[i];
    }

    buildTree(inputArray, segTree, 0, n - 1, 0);
    int qst, qend, value;
    cout << "enter query start and end " << endl;
    cin >> qst >> qend;
    cout << minQuery(segTree, qst, qend, 0, n - 1, 0) << endl;
    cout << "enter query start, end , and value to update" << endl;
    cin >> qst >> qend >> value;
    update(segTree, 0, n - 1, qst, qend, 0, value);
    cout << "enter query start and end " << endl;
    cin >> qst >> qend;
    cout << minQuery(segTree, qst, qend, 0, n - 1, 0) << endl;
}