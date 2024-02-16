struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

#define ElementType int

AvlTree MakeEmpty(AvlTree T);
Position Find(ElementType X, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType X, AvlTree T);
AvlTree Delete(ElementType X, AvlTree T);
ElementType Retrieve(Position P);
static int Height(Position P);
static Position SingleRotateWithLeft(Position K2);
static Position SingleRotateWithRight(Position K1);
static Position DoubleRotateWithLeft(Position K3);
static Position DoubleRotateWithRight(Position K1);