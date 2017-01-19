template <class T>
int partition(T array[], int left, int right, int pivot)
{
    while (left <= right)
    {
        while (array[left]  < pivot && left <= right) left++;
        while (array[right] > pivot && left <= right) right--;
        if (left <= right)
        {
            T temp = array[right];
            array[right] = array[left];
            array[left] = temp;
            left++;
            right--;
        }
    }
    return left;
}

///Class T mush have total order and the operators >, <, >=, <= defined
template <class T>
void quicksort(T array[], int left, int right)
{
    // srand(time(0));
    if (left >= right) return;

    int pivotIndex = left + rand() % (right-left+1);
    int pivot = array[pivotIndex];

    int partitionIndex = partition(array, left, right, pivot);

    quicksort(array, left, partitionIndex-1);
    quicksort(array, partitionIndex, right);
}