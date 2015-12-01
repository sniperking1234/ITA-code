void NormalQuickSort(int *numberArray, int low, int high)
{
    if (low >= high) //如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了
    {
        return ;
    }
    int breakPoint = Partition(numberArray,low,high);
    NormalQuickSort(numberArray, low, breakPoint - 1);
    NormalQuickSort(numberArray, breakPoint + 1, high);
}

/*快速排序分割算法*/
int Partition(int *numberArray, int low, int high)
{
    int flagNumber = numberArray[high]; //选择数组最后一个数作为标志位
    int i = low - 1;
    int j = 0;
    int temp = 0;   //交换位
    for(j = low; j<high; j++)
    {
        /*如果数字比标志位小，进行交换*/
        if(numberArray[j] <= flagNumber)
        {
            i = i + 1;
            temp = numberArray[i];
            numberArray[i] = numberArray[j];
            numberArray[j] = temp;
        }
    }
    /*将标志位放入合式的位置，并且返回下标*/
    temp = numberArray[i+1];
    numberArray[i+1] = numberArray[j];
    numberArray[j] = temp;
    return i + 1;
}