#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

void bubble_sort(int *arr, unsigned int length)
{
  for (int i = 0; i < length - 1; i++)
  {
    for (int j = 0; j < length - 1 - i; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}

void insertion_sort(int *arr, unsigned int length)
{
  for (int i = 1; i < length; i++)
  {
    int j = i - 1;
    while ((j >= 0) && (arr[j] > arr[j + 1]))
    {
      swap(&arr[j], &arr[j + 1]);
      j--;
    }
  }
}

void selection_sort(int *arr, unsigned int length)
{
  int min_idx;
  for (int i = 0; i < length - 1; i++)
  {
    min_idx = i;
    for (int j = i + 1; j < length; j++)
    {
      if (arr[j] < arr[min_idx])
      {
        min_idx = j;
      }
    }
    swap(&arr[i], &arr[min_idx]);
  }
}

void quick_sort(int *arr, int left, int right)
{
  if (left >= right)
    return;
  int middle = left + (right - left) / 2;
  int pivot = arr[middle];
  int i = left, j = right;
  while (i <= j)
  {
    while (arr[i] < pivot)
    {
      i++;
    }
    while (arr[j] > pivot)
    {
      j--;
    }
    if (i <= j)
    {
      swap(&arr[i], &arr[j]);
      i++;
      j--;
    }
  }
  if (left < j)
    quick_sort(arr, left, j);
  if (right > i)
    quick_sort(arr, i, right);
}

void heapify(int *arr, int n, int i)
{
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < n && arr[left] > arr[largest])
    largest = left;
  if (right < n && arr[right] > arr[largest])
    largest = right;
  if (largest != i)
  {
    swap(&arr[i], &arr[largest]);
    heapify(arr, n, largest);
  }
}

void heap_sort(int *arr, int n)
{
  for (int i = n / 2 - 1; i >= 0; heapify(arr, n, i), i--)
    ;
  for (int i = n - 1; i >= 0; i--)
  {
    swap(&arr[0], &arr[i]);
    heapify(arr, i, 0);
  }
}

void rand_fill(int *arr, unsigned int length)
{
  time_t time_seed;
  srand((unsigned)time(&time_seed));
  for (int i = 0; i < length; arr[i] = rand() % 100, i++)
    ;
}

void rand_fill_reverse(int *arr, unsigned int length)
{
  rand_fill(arr, length);
  bubble_sort(arr, length);
  for (int j = 0; j < length / 2; swap(&arr[j], &arr[length - 1 - j]), j++)
    ;
}

void print_array(int *arr, unsigned int length)
{
  for (int i = 0; i < length; printf("%d ", arr[i]), i++)
    ;
  printf("\n");
}

int main()
{
  int length = 100000; // change this

  int arr[length];
  long double elapsed_time;
  clock_t start, end;
  printf("Original array: ");

  rand_fill(arr, length); // and this

  print_array(arr, length);
  start = clock();

  heap_sort(arr, length); // and this

  end = clock();
  elapsed_time = (long double)(end - start) / CLOCKS_PER_SEC;
  elapsed_time *= 10e3;
  printf("Sorted array: ");
  print_array(arr, length);
  printf("My function runs in %LFms\n", elapsed_time);
  return 0;
}
