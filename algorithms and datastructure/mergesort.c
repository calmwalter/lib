#include <stdio.h>
#include<string.h>
void merge(int *arr, int l, int mid, int r)
{
    int L = l, R = mid+1;
    int tmp[r-l + 1];
    int i = 0;
    while (L != mid+1 || R != r + 1)
    {
        //如果有一个已经到了最后一个数了
        if (L == mid+1)
        {
            tmp[i] = *(arr+R);
            R++;
            i++;
            continue;
        }
        else if (R == r + 1)
        {
            tmp[i] = *(arr+L);
            L++;
            i++;
            continue;
        }
        //否则
        if (*(arr+L) <= *(arr+R))
        {
            tmp[i] = *(arr+L);
            L++;
        }
        else
        {
            tmp[i] = *(arr+R);
            R++;
        }
        i++;
    }
    //将tmp中的数赋值给原数组完成排序
    int t = 0;
    
    while (t != r - l + 1)
    {
        *(arr+t + l) = tmp[t];
        t++;
    }
}
void mergeSort(int *arr, int l, int r)
{
    //在l<r的的情况下
    if (l < r)
    {
        int mid = (l + r) / 2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid+1, r);
        merge(arr, l, mid, r);
    }
}

int ten(int len){
    int re=1;
    for(int i=0;i<len;i++){
        re*=10;
    }
    return re;
}
int charToInt(const char *arg,int len){
    int re=0;
    for(int i=0;i<len;i++){
        re+=((int)(arg[i])-48)*ten(len-i-1);
    }
    return re;
}
int main(int argc, char const *argv[])
{
    if (argc != 1)
    {
        int arr[argc-1];
        int * p=arr;
        //把输入进来的值都放到数组中
        for (int i = 1; i < argc; i++)
        {
            *(p+i-1)=charToInt(argv[i],strlen(argv[i]));
        }
        mergeSort(p,0,argc-2);
        //输出排序后的数组
        for(int i=0;i<argc-1;i++){
            printf("%d ",*(arr+i));
        }
    }
    else
    {
        printf("Please enter the number you want to sort");
    }
    return 0;
}
