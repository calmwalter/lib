//用邻接链表的方式实现判断一个图是否是循环图
//自己写了    队列     及      图     的实现

#include <stdio.h>
#include <stdlib.h>

//graph的代码
//********************************
typedef struct NODE
{
    //存储该节点的出点
    struct NODE *next;
    //该节点的出度
    int outdegree;
    //该节点的入度
    int indegree;
    //该节点的值
    int v;
    //该节点的父节点
    struct NODE *p;
    //该节点的状态，0是没有被发现过，1是已经被发现的节点，2是被使用过的节点
    int state;
    //节点开始被访问的时间
    int d;
    //节点完成访问的时间
    int f;
} node;

typedef struct GRAPH
{
    node *node;
    int nodesize;
} graph;
void initGraph(graph *g)
{
    g->node = NULL;
    g->nodesize = 0;
}

void addNode(graph *g, node *x)
{
    g->nodesize++;
    g->node = (node *)realloc(g->node, sizeof(node) * (g->nodesize));
    node *y = g->node + g->nodesize - 1;
    *y = *x;
}

void createNode(int v, int indegree, int outdegree, node *next) //默认的参数值是indegree=0，outdegree=0，next=NULL
{
    node *x = (node *)malloc(sizeof(node));
    x->state = 0;
    x->outdegree = outdegree;
    x->indegree = indegree;
    x->v = v;
    x->next = (node *)malloc(sizeof(node) * outdegree);
    for (int i = 0; i < outdegree; i++)
    {
        *(x->next + i) = *(next + i);
    }
    return x;
}
//********************************




//**************************************
//下面都是队列的代码
//用来存放不同类型数据
typedef node *datatype;
//队列的每一个节点
typedef struct QNODE
{
    struct QNODE *next;
    datatype v;
} qnode;
//队列的链表的表示
typedef struct QUEUE
{
    qnode *head;
    qnode *nil;
} queue;
//初始化创建一个队列
void createQueue(queue *q)
{
    q->nil = (qnode *)malloc(sizeof(qnode));
    q->nil->v = NULL;
    q->nil->next = NULL;
    q->head = q->nil;
}
//在队列中加入元素
void Enqueue(queue *q, node *x)
{

    //如果是一个空队列
    if (q->head == q->nil)
    {
        q->head = (qnode *)malloc(sizeof(qnode));
        q->head->v = x;
        q->head->next = q->nil;
        //用q.nil.next记录队列的末尾元素
        q->nil->next = q->head;
        return;
    }
    //如果不是一个空队列
    qnode *y = q->head;
    qnode *newnode = (qnode *)malloc(sizeof(qnode));
    newnode->next = y;
    newnode->v = x;
    q->head = newnode;
}
//从队列中删除元素
qnode *Dequeue(queue *q)
{
    if (q->head == q->nil)
    {
        return q->nil;
    }
    qnode *y = q->head;
    qnode *z = q->nil;
    while (y->next != q->nil)
    {
        z = y;
        y = y->next;
    }
    if (z == q->nil)
    {
        q->head = q->nil;
        q->nil->next = NULL;
        return y;
    }
    z->next = q->nil;
    q->nil->next = z;
    return y;
}
//判断队列是不是空的
int empty(queue *q)
{
    if (q->head == q->nil)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//**************************************

//判断是不是循环图
int iscycle(graph *g)
{
    //创建一个队列，记录入度为0的点
    queue *q;
    q = (queue *)malloc(sizeof(queue));
    createQueue(q);
    //计数判断是否是一个有环图
    int cnt = 0;

    for (int i = 0; i < g->nodesize; i++)
    {
        if ((g->node + i)->indegree == 0)
        {
            Enqueue(q, g->node + i);
            cnt++;
        }
    }
    //如果队列不是空的队列
    while (!empty(q))
    {
        //从队列中拿出来一个元素
        qnode *y = Dequeue(q);
        //提取y中包含的node的值
        node *tmp = y->v;
        //对于每一个node,我对它进行判断
        for (int i = 0; i < tmp->outdegree; i++)
        {
            //如果这个节点减一后是0，就把他加入到队列中
            if (--((tmp->next + i)->indegree) == 0)
            {
                Enqueue(q, tmp->next + i);
                cnt++;
            }
        }
    }
    if (cnt != g->nodesize)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//时间，用来记录每个节点的访问时间和完成时间
int time=0;
//BFS算法，遍历整个邻接表
void bfs(graph *g)
{
    //初始化时间为0
    time=0;
    //初始化所有的节点的父节点为空，状态为0
    for (int i = 0; i < g->nodesize; i++)
    {
        (g->node + i)->p = NULL;
        (g->node + i)->state = 0;
    }
    //建立队列存储即将要遍历的节点
    queue *q;
    createQueue(q);
    //遍历每一个节点
    for (int i = 0; i < g->nodesize; i++)
    {
        Enqueue(q, g->node + i);
        //队列不为空的情况下一直遍历
        while (!empty(q))
        {
            qnode *x = Dequeue(q);
            node *y = x->v;
            y->state = 2;
            for (int k = 0; k < y->outdegree; k++)
            {
                if ((y->next + k)->state == 0)
                {
                    Enqueue(q, y->next + k);
                    (y->next + k)->p = y;
                    (y->next + k)->state = 1;
                }
            }
        }
    }
}

//*************************************
//dfs算法，遍历整个图
void dfsVisit(graph *g, node *x)
{
    time++;
    x->d=time;
    x->state = 1;
    for (int i = 0; i < x->outdegree; i++)
    {
        if ((x->next + i)->state == 0)
        {
            (x->next + i)->p = x;
            dfsVisit(g, x->next + i);
        }
    }
    time++;
    x->f=time;
    x->state = 1;
}
void dfs(graph *g)
{
    //初始化时间为0
    time=0;
    //初始化所有的节点的父节点为空，状态为0
    for (int i = 0; i < g->nodesize; i++)
    {
        (g->node + i)->p = NULL;
        (g->node + i)->state = 0;
    }

    //对于每一个节点对他进行dfs-visit
    for (int i = 0; i < g->nodesize; i++)
    {

        node *x = (g->node + i)->v;
        if ((x->next + i)->state == 0)
        {
            dfsVisit(g, x);
        }
    }
}
//***************************************

//最短路径算法（可行性未知）
int shortestPath(graph *g, node *x, node *y)
{
    bfs(g);
    int distance = 0;
    node *z = y;
    while (z->p != NULL || z->p != x)
    {
        z = z->p;
        distance++;
    }
    if (z->p == NULL)
    {
        return -1;
    }
    return distance;
}
int main(int argc, char const *argv[])
{
    //以下代码是非循环图
    /* 
    graph *g = (graph *)malloc(sizeof(graph));
    initGraph(g);
    node *tmp;
    node *firstnode;
    
    for (int i = 0; i < 10; i++)
    {
        node *newnode = (node *)malloc(sizeof(node));
        newnode->next = tmp;
        if (i == 0)
        {
            firstnode = newnode;
            newnode->indegree = 1;
            newnode->outdegree = 0;
        }
        else if (i == 9)
        {
            newnode->indegree = 0;
            newnode->outdegree = 1;
        }
        else
        {
            newnode->indegree = 1;
            newnode->outdegree = 1;
        }

        newnode->v = i;
        tmp = newnode;
        addNode(g, newnode);
    }

    if (iscycle(g))
    {
        printf("its a cycle graph\n");
    }
    else
    {
        printf("its not a cycle graph\n");
    }

 */
    //以下代码是循环图
    graph *g = (graph *)malloc(sizeof(graph));
    initGraph(g);
    node *tmp;
    node *firstnode;
    for (int i = 0; i < 10; i++)
    {
        node *newnode = (node *)malloc(sizeof(node));
        newnode->next = tmp;
        if (i == 0)
        {
            firstnode = newnode;
            newnode->indegree = 1;
            newnode->outdegree = 1;
        }
        else if (i == 9)
        {
            newnode->indegree = 1;
            newnode->outdegree = 1;
            firstnode->next = newnode;
        }
        else
        {
            newnode->indegree = 1;
            newnode->outdegree = 1;
        }

        newnode->v = i;
        tmp = newnode;
        addNode(g, newnode);
    }

    if (iscycle(g))
    {
        printf("its a cycle graph\n");
    }
    else
    {
        printf("its not a cycle graph\n");
    }
    return 0;
}
