void creatRandomNumber(int *numArr, int num)
{
    int i;
    srand((unsigned)time(NULL));
    for (i = 0; i < num; i++)
    {
        *numArr = rand() % 10000;
        numArr++;
    }
}