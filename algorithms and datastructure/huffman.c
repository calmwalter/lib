#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    char c;
    double freq;
    int left;
    int right;
    int parent;
    int pos;
} node;
int huffman(node nodes[256], int size, node tr[256], int tr_size)
{
    if (tr_size < 2)
        return size;
    int x, y;
    if (tr[0].freq < tr[1].freq){
        x = tr[0].pos;y = tr[1].pos;
    }else{
        y = tr[0].pos;x = tr[1].pos;
    }
    for (int i = 2; i < tr_size; i++)
    {
        if (tr[i].freq < nodes[x].freq)
        {
            y = x;
            x = tr[i].pos;
        }
        else if (tr[i].freq < nodes[y].freq)
            y = tr[i].pos;
    }
    nodes[size].left = x;
    nodes[size].right = y;
    nodes[size].parent=-1;
    nodes[x].parent=size;
    nodes[y].parent=size;
    nodes[size].pos = size;
    nodes[size].freq = nodes[x].freq + nodes[y].freq;
    node new_tr[256];
    int cnt = 0;
    for (int i = 0; i < tr_size; i++)
        if (tr[i].pos != x && tr[i].pos != y)
            new_tr[cnt++] = tr[i];
    new_tr[tr_size - 2] = nodes[size];
    int new_size=huffman(nodes, size + 1, new_tr, tr_size - 1);
    return new_size;
}

void encoding_char(node nodes[256],int size,int pos,char *code){
    if(pos>=size)
        return ;
    strcpy(code,"");
    int cnt=0;
    while(pos!=-1){
        if(pos==nodes[nodes[pos].parent].left){
            *(code+cnt)='0';
            cnt++;
        }
        else if(pos==nodes[nodes[pos].parent].right){
            *(code+cnt)='1';
            cnt++;
        }
        pos=nodes[pos].parent;
    }
    *(code+cnt)='\0';
    int l=strlen(code);
    //reverse the code
    for(int i=0;i<l/2;i++){
        char tmp=*(code+i);
        *(code+i)=*(code+l-1-i);
        *(code+l-1-i)=tmp;
    }
}
void encoding_string(node nodes[256],int size,int pos[256],int num,char *code){
    char tmp[256];
    strcpy(code,"");
    for(int i=0;i<num;i++){
        encoding_char (nodes, size, pos[i], tmp);
        strcat(code,tmp);
    }
}
void decoding(node nodes[256],int size,char *code,char *str){
    int l=strlen(code);
    int pos=size-1;
    int cnt=0;
    strcpy(str,"");
    for(int i=0;i<l;i++){
        if(nodes[pos].left==-1 && nodes[pos].right==-1){
            str[cnt]=nodes[pos].c;
            pos=size-1;
            cnt++;
        }
        if(code[i]=='0'){
            pos=nodes[pos].left;
        }
        else if(code[i]=='1'){
            pos=nodes[pos].right;
        }
    }
    str[cnt]='\0';
}
int main(int argc, char *argv[])
{
    //the input data
    double freq[] = {0.05, 0.29, 0.07, 0.08, 0.14, 0.23, 0.03, 0.11};
    node nodes[256];
    for (int i = 0; i < 8; i++){
        nodes[i].pos = i;nodes[i].freq = freq[i];
        nodes[i].left = -1;nodes[i].right = -1;
        nodes[i].parent=-1;
        nodes[i].c='a'+i;
    }
    //build huffman tree
    int size=huffman(nodes, 8, nodes, 8);
    //test the huffman tree
    printf("%-8s%-8s%-8s%-8s%-8s\n","node","freq","left","right","parent");
    for (int i = 0; i < size; i++){
        printf("node%-4d%-8.2lf", i, nodes[i].freq);
        if (nodes[i].left != -1)
            printf("%-8d", nodes[i].left);
        else
            printf("%-8s", "NULL");
        if (nodes[i].right != -1)
            printf("%-8d", nodes[i].right);
        else
            printf("%-8s", "NULL");
        if (nodes[i].parent != -1)
            printf("%-8d", nodes[i].parent);
        else
            printf("%-8s", "NULL");
        printf("\n");
    }

    //encoding the infomation
    // single char encoding
    printf("\nsingle char encoding\n");
    int a[]={0,1,2,3,4,5,6,7};
    for(int i=0;i<8;i++){
        char code[256]="";
        encoding_char (nodes, size, i,code);
        printf ("%s\n",code);
    }

    //string encoding
    printf("\nstring encoding\n");
    char code[256];
    encoding_string (nodes, size, a, 8,code);
    printf("%s\n",code);

    //decoding the infomation
    // string decoding
    printf("\nstring decoding\n");
    char str[256];
    decoding (nodes, size, code, str);
    printf("%s\n",str);
    return 0;
}
