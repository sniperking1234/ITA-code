/*******************************************
 * @CHEN
 * 贪心算法中的任务调度问题
 * 算法导论第三版P255页
 * 样例输入：7 4 70 2 60 4 50 3 40 1 30 4 20 6 10
 * 2015-12-17
 *******************************************/


#include <stdio.h>
#include <stdlib.h>

typedef struct taskInfo
{
    int taskNumber;
    int endLine;
    int publishment;
} Task;

int TaskSchedule(int taskCount, Task *taskList);

int main()
{
    Task *task = NULL;
    int i = 0;
    int num = 0;
    printf("please input the number of task\n");
    scanf("%d", &num);
    if (num)
    {
        task = (Task *)malloc(sizeof(Task) * num);
    }
    else
    {
        printf("please input a correct number\n");
        return 0;
    }

    /*receive the input*/
    for (i = 0; i < num; i++)
    {
        printf("input the %d task end line and publishment:\n", i + 1);
        scanf("%d %d", &task[i].endLine, &task[i].publishment);
        task[i].taskNumber = i + 1;
    }
    TaskSchedule(num, task);

    return 0;
}

int TaskSchedule(int taskCount, Task *taskList)
{
    int i, sum;
    int SortTask(Task * taskList, int low, int high);
    int Solution(Task * taskList, int taskCount);
    int ShowResult(Task * taskList, int taskCount);

    SortTask(taskList, 0, taskCount - 1);
    for (i = 0; i < taskCount; i++)
    {
        printf("%d   ", taskList[i].taskNumber);
    }
    printf("\n");
    Solution(taskList, taskCount);
    for (i = 0; i < taskCount; i++)
    {
        printf("%d   ", taskList[i].taskNumber);
    }
    printf("\n");
    sum = ShowResult(taskList, taskCount);
    printf("sum punshment is %d\n", sum);

    return 0;
}


int Solution(Task * taskList, int taskCount)
{
    int i, j, k;
    Task temp;
    for (i = 0; i < taskCount; i++)
    {
        for (j = i + 1; j < taskCount; j++)
        {
            if (taskList[i].endLine > taskList[j].endLine)
            {
                /*如果交换后不影响，则进行交换*/
                if (taskList[i].endLine >= j + 1)
                {
                    temp = taskList[i];
                    taskList[i] = taskList[j];
                    taskList[j] = temp;
                }
            }
            else if (taskList[i].endLine == taskList[j].endLine && taskList[i].publishment < taskList[j].publishment)
            {
                temp = taskList[i];
                taskList[i] = taskList[j];
                taskList[j] = temp;
            }
            //两个相邻
            if (j - i == 1)
            {
                if (taskList[j].endLine < j + 1)
                {
                    temp = taskList[j];
                    for (k = j + 1; k < taskCount; k++)
                    {
                        taskList[k - 1] = taskList[k];
                    }
                    taskList[k - 1] = temp;
                    j--;
                    taskCount--;
                }
            }
        }
    }
    return 0;
}
/*quick sort*/
int SortTask(Task * numberArray, int low, int high)
{
    int Partition(Task * numberArray, int low, int high);
    if (low >= high) //如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了
    {
        return 0;
    }
    int breakPoint = Partition(numberArray, low, high);
    SortTask(numberArray, low, breakPoint - 1);
    SortTask(numberArray, breakPoint + 1, high);
    return 0;
}

int Partition(Task *numberArray, int low, int high)
{
    int flagNumber = numberArray[high].publishment; //选择数组最后一个数作为标志位
    int i = low - 1;
    int j = 0;
    Task temp ;   //交换位
    for (j = low; j < high; j++)
    {
        /*如果数字比标志位大，进行交换*/
        if (numberArray[j].publishment >= flagNumber)
        {
            i = i + 1;
            temp = numberArray[i];
            numberArray[i] = numberArray[j];
            numberArray[j] = temp;
        }
    }
    /*将标志位放入合式的位置，并且返回下标*/
    temp = numberArray[i + 1];
    numberArray[i + 1] = numberArray[j];
    numberArray[j] = temp;
    return i + 1;
}

int ShowResult(Task * taskList, int taskCount)
{
    int j;
    int sumPunishment = 0;
    printf("select task: ");
    for (j = 0; j < taskCount; j++)
    {
        if (taskList[j].endLine >= j + 1)
        {
            printf("%d  ", taskList[j].taskNumber);
        }
        else
        {
            sumPunishment += taskList[j].publishment;
        }
    }
    return sumPunishment;
}
