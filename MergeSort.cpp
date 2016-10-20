void merge(int left, int mid, int right, int arr[]) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 =  right - mid;

    int left_array[maxN],
        right_array[maxN];

    for (i = 0; i < n1; i++)
        left_array[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        right_array[j] = arr[mid + 1+ j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (left_array[i] <= right_array[j]) {
            arr[k] = left_array[i];
            i++;
        } else {
            arr[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left_array[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right_array[j];
        j++;
        k++;
    }
}

void merge_sort(int left, int right, int arr[]) {
    if (left < right) {
        int mid = left+(right-left)/2;
        merge_sort(left, mid, arr);
        merge_sort(mid+1, right, arr);

        merge(left, mid, right, arr);
    }
}