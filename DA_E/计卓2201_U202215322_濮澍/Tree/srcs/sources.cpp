#include "def.h"
using namespace std;
int cnt = 0;
status CreateBiTree(BiTree &T, TElemType definition[])
{
    for (int i = 0; definition[i].key != -1; i++)
    {
        for (int j = i + 1; definition[j].key != -1; j++)
        {
            if (definition[i].key > 0 && definition[i].key == definition[j].key)
                return ERROR;
        }
    }
    BiTree Root;
    CreateBiNode(Root, definition);
    T = Root;
    cnt = 0;
    return OK;
}
void CreateBiNode(BiTree &Root, TElemType definition[])
{
    if (definition[cnt].key == 0)
    {
        Root = NULL;
        cnt++;
        return;
    }
    else if (definition[cnt].key == -1)
    {
        return;
    }

    Root = new BiTNode;
    Root->data = definition[cnt++];
    CreateBiNode(Root->lchild, definition);
    CreateBiNode(Root->rchild, definition);
}
status ClearBiTree(BiTree &T)
{
    if (!T)
        return OK;
    if (ClearBiTree(T->lchild) && ClearBiTree(T->rchild))
    {
        delete T;
    }
    T = NULL;
    return OK;
}

status isEmpty(BiTree T)
{
    if (T == NULL)
        return TRUE;
    return FALSE;
}

int BiTreeDepth(BiTree T)
{
    if (!T)
        return 0;
    return 1 + max<int>(BiTreeDepth(T->lchild), BiTreeDepth(T->rchild));
}

int BiTreeHeight(BiTree T, BiTree p)
{
    //求结点到根结点的高度
    if (!T)
        return 0;
    int ans = 0;
    while (p != T)
    {
        ans++;
        p = Search(T, p);
    }
    return ans;
}
BiTNode *LocateNode(BiTree T, KeyType e)
{
    BiTree ans;
    if (T == NULL)
        return NULL;
    if (e == T->data.key)
    {
        return T;
    }
    else
        return (ans = LocateNode(T->lchild, e)) != NULL ? ans : LocateNode(T->rchild, e);
}
status PreOrderCheck(BiTree T1, BiTree T2)
{
    if (T1 == NULL)
        return OK;
    if (T2->data.key == T1->data.key && T2 != T1)
        return ERROR;
    return PreOrderCheck(T1->lchild, T2) && PreOrderCheck(T1->rchild, T2);
}
status Assign(BiTree &T, KeyType e, TElemType value)
{
    BiTree exc = LocateNode(T, e);
    if (!exc)
        return ERROR;
    exc->data = value;
    if (PreOrderCheck(T, exc) == ERROR)
        return ERROR;
    return OK;
}
BiTNode *GetSibling(BiTree T, KeyType e)
{
    if (T && T->data.key == e || !T->lchild || !T->rchild)
        return NULL;
    if (T->lchild->data.key == e)
        return T->rchild;
    if (T->rchild->data.key == e)
        return T->lchild;
    BiTree ans;
    return ((ans = GetSibling(T->lchild, e)) != NULL) ? ans : GetSibling(T->rchild, e);
}
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
{
    if (LR == -1)
    {
        BiTree NewRoot = new BiTNode;
        NewRoot->data = c;
        NewRoot->lchild = NULL;
        NewRoot->rchild = T;
        T = NewRoot;
        return OK;
    }
    BiTree eNode = LocateNode(T, e);
    if (eNode == nullptr)
        return ERROR;
    BiTree NewNode = new BiTNode;
    NewNode->data = c;
    NewNode->lchild = nullptr;
    if (LR == 0)
    {
        NewNode->rchild = eNode->lchild;
        eNode->lchild = NewNode;
    }
    else
    {
        NewNode->rchild = eNode->rchild;
        eNode->rchild = NewNode;
    }
    if (PreOrderCheck(T, NewNode) == ERROR)
        return ERROR;
    return OK;
}
int flag = -1;
BiTree Search(BiTree T, BiTree eNode)
{
    if (!T)
        return NULL;
    if (T->lchild == eNode)
    {
        flag = 0;
        return T;
    }
    if (T->rchild == eNode)
    {
        flag = 1;
        return T;
    }
    BiTree ans;
    return (ans = Search(T->lchild, eNode)) != NULL ? ans : Search(T->rchild, eNode);
}
BiTree FindMax(BiTree T)
{
    if (T->rchild == NULL)
        return T;
    return FindMax(T->rchild);
}
status DeleteNode(BiTree &T, KeyType e)
{
    BiTree eNode = LocateNode(T, e);
    if (eNode == T)
    {
        if (!T->lchild && !T->rchild)
        {
            free(T);
            return OK;
        }
        BiTree Mem;
        if (!T->lchild)
        {
            Mem = T->rchild;
            free(T);
            T = Mem;
            return OK;
        }
        if (!T->rchild)
        {
            Mem = T->lchild;
            free(T);
            T = Mem;
            return OK;
        }
        Mem = T->lchild;
        BiTree Replacer = FindMax(T->lchild);
        Replacer->rchild = T->rchild;
        free(T);
        T = Mem;
        return OK;
    }
    if (eNode == NULL)
        return ERROR;
    BiTree Parents = Search(T, eNode);
    if (!eNode->lchild && !eNode->rchild)
    {
        if (flag == 0)
        {
            Parents->lchild = NULL;
            free(eNode);
        }
        if (flag == 1)
        {
            Parents->rchild = NULL;
            free(eNode);
        }
        return OK;
    }

    if (!eNode->lchild)
    {
        if (flag == 0)
        {
            Parents->lchild = eNode->rchild;
            free(eNode);
        }
        if (flag == 1)
        {
            Parents->rchild = eNode->rchild;
            free(eNode);
        }
        return OK;
    }
    if (!eNode->rchild)
    {
        if (flag == 0)
        {
            Parents->lchild = eNode->lchild;
            free(eNode);
        }
        if (flag == 1)
        {
            Parents->rchild = eNode->lchild;
            free(eNode);
        }
        return OK;
    }
    BiTree Replacer = FindMax(eNode->lchild);
    Replacer->rchild = eNode->rchild;
    BiTree eNodeLeft = eNode->lchild;
    free(eNode);
    if (flag == 0)
    {
        Parents->lchild = eNodeLeft;
    }
    if (flag == 1)
    {
        Parents->rchild = eNodeLeft;
    }

    return OK;
}
status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    if (T)
    {
        visit(T);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
    return OK;
}
status InOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    if (T)
    {
        InOrderTraverse(T->lchild, visit);
        visit(T);
        InOrderTraverse(T->rchild, visit);
    }
    return OK;
}
status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    BiTree stack[1000];
    int top = 0;
    BiTree r = NULL;
    BiTree p = T;
    while (p || top > 0)
    {
        if (p)
        {
            stack[top++] = p;
            p = p->lchild;
        }
        else
        {
            p = stack[top - 1];
            if (p->rchild && p->rchild != r)
            {
                p = p->rchild;
            }
            else
            {
                p = stack[--top];
                visit(p);
                r = p;
                p = NULL;
            }
        }
    }
    return OK;
}
void visit(BiTree T)
{
    printf(" %d,%s", T->data.key, T->data.others);
}
BiTree queue[1000];
int head = 0, rear = 0;
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    visit(T);

    if (T->lchild)
        queue[rear++] = T->lchild;
    if (T->rchild)
        queue[rear++] = T->rchild;

    if (head < rear)
        LevelOrderTraverse(queue[head++], visit);
    return OK;
}
void SaveBiTreeRec(BiTree T, FILE *f)
{
    if (!T)
    {
        fprintf(f, "0 null\n");
    }
    else
    {
        fprintf(f, "%d %s\n", T->data.key, T->data.others);
        SaveBiTreeRec(T->lchild, f);
        SaveBiTreeRec(T->rchild, f);
    }
}
status SaveBiTree(BiTree T, char FileName[])
{
    FILE *f = fopen(FileName, "w");
    SaveBiTreeRec(T, f);
    fclose(f);
    return OK;
}
BiTree LoadBiTreeRec(FILE *f)
{
    BiTree root;
    TElemType e;
    fscanf(f, "%d %s", &e.key, e.others);
    if (e.key <= 0)
    {
        root = NULL;
    }
    else
    {
        root = (BiTree)malloc(sizeof(BiTNode));
        root->data = e;
        root->lchild = LoadBiTreeRec(f);
        root->rchild = LoadBiTreeRec(f);
    }
    return root;
}
status LoadBiTree(BiTree &T, char FileName[])
{
    FILE *f = fopen(FileName, "r");
    T = LoadBiTreeRec(f);
    fclose(f);
    return OK;
}
BiTree LowestCommonAncestor(BiTree T, BiTree e1, BiTree e2)
{
    int h1 = BiTreeHeight(T,e1);
    int h2 = BiTreeHeight(T,e2);
    int ht = 0;
    if (h1 == ht)
        return e1;
    if (h2 == ht)
        return e2;
    return TestAncestor(e1, h1, e2, h2, T, ht);
}

BiTree TestAncestor(BiTree T1, int h1, BiTree T2, int h2, BiTree T, int ht)
{
    if (h2 < h1)
    {
        BiTree TMP;
        int tmph;
        TMP = T1;
        T1 = T2;
        T2 = TMP;
        tmph = h1;
        h1 = h2;
        h2 = tmph;
    }
    if (h1 == ht)
        return T1;
    if (h1 == h2 && T1 == T2)
        return T1;
    if (h1 == h2)
        return TestAncestor(Search(T, T1), h1 - 1 , Search(T, T2), h2 - 1 , T, ht);
    return TestAncestor(T1, h1, Search(T, T2), h2 - 1, T, ht);
}
int TriMax(int i, int j, int k)
{
    return (i >= j ? i : j) >= k ? (i >= j ? i : j) : k;
}
int MaxPathLength(BiTree T)
{
    if (T == nullptr)
        return 0;
    T->Sum = T->data.key + TriMax(0, MaxPathLength(T->lchild), MaxPathLength(T->rchild));
    return T->Sum;
    //
}
KeyType MaxPathSum(BiTree T)
{
    KeyType solution = 0;
    dfs(T, solution);
    return solution;
}

KeyType dfs(BiTree T, KeyType &solution)
{
    if (!T)
        return 0;
    KeyType Left = dfs(T->lchild, solution);
    KeyType Right = dfs(T->rchild, solution);
    solution = max<KeyType>(solution, T->data.key + max<KeyType>(0, Left) + max<KeyType>(0, Right));
    // 更新结论为当前结点的最大路径值
    return T->data.key + max<KeyType>(Left, Right);
    // 传回单边最大
}
status InverseBiTree(BiTree &T)
{
   if(!T) return OK;
   BiTree TMP = T->lchild;
   T->lchild = T->rchild;
   T->rchild = TMP;
   InverseBiTree(T->lchild);
   InverseBiTree(T->rchild);
   return OK;
}

status Add_BiTree_to_Forest(BiForest &F, char FileName[], TElemType definitions[])
{
    if (F.length == 20)
        return ERROR;
    strcpy(F.elem[F.length].Name, FileName);
    if (CreateBiTree(F.elem[F.length].T, definitions) == ERROR)
        return ERROR;
    F.length++;
    return OK;
}
status Remove_BiTree_from_Forest(BiForest &F, char FileName[])
{
    if (F.length == 0)
        return ERROR;
    for (int i = 0; i < F.length; i++)
    {
        if (strcmp(FileName, F.elem[i].Name) == 0)
        {
            for (int j = i + 1; j < F.length; j++)
            {
                F.elem[j - 1] = F.elem[j];
            }
            F.length--;
            break;
        }
        if (i == F.length - 1)
            return ERROR;
    }
    return OK;
}
status Locate_And_Modify_a_Tree_in_Forest(BiForest F, char FileName[], BiTree &T)
{
    for (int i = 0; i < F.length; i++)
    {
        if (strcmp(FileName, F.elem[i].Name) == 0)
        {
            T = F.elem[i].T;
            return OK;
        }
    }
    return ERROR;
}

status Traverse_Forest_Names(BiForest F)
{
    for (int i = 0; i < F.length; i++)
    {
        printf("%s\n", F.elem[i].Name);
    }
    return OK;
}

status Auto_Add_a_BiTree(BiForest &F,BiTree T){
    //自动存储树到森林里，每次树名有自己的序号
    char FileName[20];
    sprintf(FileName,"Auto_Saved_Tree%d",F.length);
    F.elem[F.length].T=T;
    strcpy(F.elem[F.length].Name,FileName);
    F.length++;
    return OK;
}

int Index_of_Tree(BiForest F,char FileName[]){
    for(int i=0;i<F.length;i++){
        if(strcmp(F.elem[i].Name,FileName)==0){
            return i;
        }
    }
    return -1;
}