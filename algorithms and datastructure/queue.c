//队列，用链表实现
#include<stdio.h>
#include<stdlib.h>
//用来存放不同类型数据
typedef int datatype;
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
void Enqueue(queue *q, datatype x)
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
