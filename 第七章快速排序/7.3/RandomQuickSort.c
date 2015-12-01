void RandomQuickSort(int *numberArray, int low, int high)
{
    if (low >= high) //�������������ڻ��ߵ����ұߵ������ʹ����Ѿ��������һ������
    {
        return ;
    }
    int breakPoint = RandomPartition(numberArray,low,high);
    NormalQuickSort(numberArray, low, breakPoint - 1);
    NormalQuickSort(numberArray, breakPoint + 1, high);
}
/*��������ָ��㷨*/
int Partition(int *numberArray, int low, int high)
{
    int flagNumber = numberArray[high]; //ѡ���������һ������Ϊ��־λ
    int i = low - 1;
    int j = 0;
    int temp = 0;   //����λ
    for(j = low; j<high; j++)
    {
        /*������ֱȱ�־λС�����н���*/
        if(numberArray[j] <= flagNumber)
        {
            i = i + 1;
            temp = numberArray[i];
            numberArray[i] = numberArray[j];
            numberArray[j] = temp;
        }
    }
    /*����־λ�����ʽ��λ�ã����ҷ����±�*/
    temp = numberArray[i+1];
    numberArray[i+1] = numberArray[j];
    numberArray[j] = temp;
    return i + 1;
}

int RandomPartition(int *numberArray, int low, int high)
{
    int temp;
    int r = (rand() % (high-low+1))+ low;  //����low��high֮��������
    temp = numberArray[r];
    numberArray[r] = numberArray[high];
    numberArray[high] = temp;
    return Partition(numberArray, low, high);
}