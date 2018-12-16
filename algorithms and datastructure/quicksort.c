//quicksort
#include <stdio.h>
#include <string.h>
int partion(int * arr,int l ,int r){
    //记录左边节点位置
    int p=l;
    //记录标记位置
    int m=r;
    //暂时存储数据用
    int tmp;
    while(p<m){
        if(*(arr+m)<=*(arr+p)){
            tmp=*(arr+m-1);
            *(arr+m-1)=*(arr+m);
            *(arr+m)=*(arr+p);
            *(arr+p)=tmp;
            m--;
        }
        else{
            p++;
        }
    }
    return m;
}   

int quickSort(int *arr,int l,int r){
    
    if(l<r){
        int mid=partion(arr,l,r);
        quickSort(arr,l,mid-1);
        quickSort(arr,mid+1,r);
    }
    
}

//用来验证代码的正确性
int ten(int len)
{
    int re = 1;
    for (int i = 0; i < len; i++)   
    {
        re *= 10;
    }
    return re;
}
int charToInt(const char *arg, int len)
{
    int re = 0;
    for (int i = 0; i < len; i++)
    {
        re += ((int)(arg[i]) - 48) * ten(len - i - 1);
    }
    return re;
}
int main(int argc, char const *argv[])
{
    if (argc != 1)
    {
        int arr[argc - 1];
        int *p = arr;
        //把输入进来的值都放到数组中
        for (int i = 1; i < argc; i++)
        {
            *(p + i - 1) = charToInt(argv[i], strlen(argv[i]));
        }
        quickSort(p, 0, argc - 2);
        //输出排序后的数组
        for (int i = 0; i < argc - 1; i++)
        {
            printf("%d ", *(arr + i));
        }
    }
    else
    {
        printf("Please enter the number you want to sort");
    }
    return 0;
}
