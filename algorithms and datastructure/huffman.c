#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    double freq;
    int left;
    int right;
    int pos;
} node;
int huffman(node nodes[256], int size, node tr[256], int tr_size)
{
    //当只剩下一个节点的时候返回。
    if (tr_size < 2)
    {
        //nodes[size - 1] = tr[tr_size - 1];
        return size;
    }
    //找到最小的两个频度，建立新节点，连接这两个频度，将他加入到数组的末尾，新建立一个数组，重复上述过程。
    //x,y为最小的两个节点的位置
    int x, y;
    //确定最小的两个节点
    if (tr[0].freq < tr[1].freq)
    {
        x = tr[0].pos;
        y = tr[1].pos;
    }
    else
    {
        y = tr[0].pos;
        x = tr[1].pos;
    }

    for (int i = 2; i < tr_size; i++)
    {
        if (tr[i].freq < nodes[x].freq)
        {
            y = x;
            x = tr[i].pos;
        }
        else if (tr[i].freq < nodes[y].freq)
        {
            y = tr[i].pos;
        }
    }
    //创建新的节点
    nodes[size].left = x;
    nodes[size].right = y;
    nodes[size].pos = size;
    nodes[size].freq = nodes[x].freq + nodes[y].freq;
    //将除了x,y的所有节点加入到新的数组中去。
    node new_tr[256];
    int cnt = 0;
    for (int i = 0; i < tr_size; i++)
    {
        if (tr[i].pos != x && tr[i].pos != y)
        {
            new_tr[cnt] = tr[i];
            cnt++;
        }
    }
    new_tr[tr_size - 2] = nodes[size];
    //递归
    huffman(nodes, size + 1, new_tr, tr_size - 1);
}
int main(int argc, char *argv[])
{
    double freq[] = {0.05, 0.29, 0.07, 0.08, 0.14, 0.23, 0.03, 0.11};
    node *nodes = (node *)malloc(sizeof(node) * 8);
    for (int i = 0; i < 8; i++)
    {
        (nodes + i)->pos = i;
        (nodes + i)->freq = freq[i];
        (nodes + i)->left = -1;
        (nodes + i)->right = -1;
    }
    int size = huffman(nodes, 8, nodes, 8);
     
    for (int i = 0; i < size; i++)
    {
        printf("node%-4d%-8.2lf", i, nodes[i].freq);
        if (nodes[i].left != -1)
        {
            printf("%-8d", nodes[i].left);
        }
        else
        {
            printf("%-8s", "NULL");
        }

        if (nodes[i].right != -1)
        {
            printf("%-8d", nodes[i].right);
        }
        else
        {
            printf("%-8s", "NULL");
        }
        printf("\n");
    } 
    return 0;
}
