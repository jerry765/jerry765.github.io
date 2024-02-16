#include "avl_tree.h"
#include <cstddef>

// Place in the implementation file
struct AvlNode
{
    ElementType Element;
    AvlTree Left;
    AvlTree Right;
    int Height;
};

Position Find(ElementType X, AvlTree T)
{
    if (T == NULL)
        return NULL;
    if (X < T->Element)
        return Find(X, T->Left);
    else if (X > T->Element)
        return Find(X, T->Right);
    else
        return T;
}

Position FindMin(AvlTree T)
{
    if(T != NULL)
        while (T->Left != NULL)
            T = T->Left;
    return T;
}

Position FindMax(AvlTree T)
{
    if (T != NULL)
        while (T->Right != NULL)
            T = T->Right;
    return T;
}

AvlTree Insert(ElementType X, AvlTree T)
{
    if (T == NULL)
    {
        // Create and return a one-node tree
        T = malloc(sizeof(struct AvlNode));
        if (T == NULL)
            FatalError("Out of space!!!");
        else
        {
            T->Element = X;
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if (X < T->Element)
    {
        // X should be inserted to the left subtree
        T->Left = Insert(X, T->Left);
        // Check if the left subtree is out of balance (left-left or left-right)
        if (Height(T->Left) - Height(T->Right) == 2)
            if (X < T->Left->Element)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
    }
    else if (X > T->Element)
    {
        T->Right = Insert(X, T->Right);
        if (Height(T->Right) - Height(T->Left) == 2)
            if (X > T->Right->Element)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
    }
    // Else X is in the tree already; we'll do nothing

    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

AvlTree Delete(ElementType X, AvlTree T)
{
    Position TmpCell;

    if (T == NULL)
        Error("Element not found");
    else if (X < T->Element)
    {
        T->Left = Delete(X, T->Left);
        if (Height(T->Right) - Height(T->Left) == 2)
            if (Height(T->Right->Right) >= Height(T->Right->Left))
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
    }
    else if (X > T->Element)
    {
        T->Right = Delete(X, T->Right);
        if (Height(T->Left) - Height(T->Right) == 2)
            if (Height(T->Left->Left) >= Height(T->Left->Right))
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
    }
    else
    {
        // X == T->Element; found it
        if (T->Left && T->Right)
        {
            // Replace with smallest in right subtree
            TmpCell = FindMin(T->Right);
            T->Element = TmpCell->Element;
            T->Right = Delete(T->Element, T->Right);
            free(TmpCell);
        }
        else
        {
            // One or zero children
            TmpCell = T;
            if (T->Left == NULL)
                T = T->Right;
            else if (T->Right == NULL)
                T = T->Left;
            free(TmpCell);
        }
    }

    if (T != NULL)
        T->Height = Max(Height(T->Left), Height(T->Right)) + 1;

    return T;
}

ElementType Retrieve(Position P)
{
    return P->Element;
}

static int Height(Position P)
{
    if (P == NULL)
        return -1;
    else
        return P->Height;
}

// This function can be called only if K2 has a left child
static Position SingleRotateWithLeft(Position K2)
{
    Position K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = Max(Height(K1->Left), K2->Height) + 1;

    return K1; // New root
}

// This function can be called only if K1 has a right child
static Position SingleRotateWithRight(Position K1)
{
    Position K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1;
    K2->Height = Max(Height(K2->Right), K1->Height) + 1;

    return K2; // New root
}

// This function can be called only if K3 has a left child and K3's left child has a right child
static Position DoubleRotateWithLeft(Position K3)
{
    // Rotate between K1 and K2
    K3->Left = SingleRotateWithRight(K3->Left);

    // Rotate between K3 and K2
    return SingleRotateWithLeft(K3);
}

static Position DoubleRotateWithRight(Position K1)
{
    // Rotate between K3 and K2
    K1->Right = SingleRotateWithLeft(K1->Right);

    // Rotate between K1 and K2
    return SingleRotateWithRight(K1);
}