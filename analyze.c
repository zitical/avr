#include "analyze.h"
#include "algorithm.h"

/*
fillArray(a,c,arrTest,1000);
printf("\n");
start_t = clock();
bubble_sort(arrTest, 1000);
end_t = clock();
total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
printf("\nStart_t = %ld \nEnd_t = %ld \nTotal_t = %f \n", start_t, end_t, total_t);
printf("\n");
*/

//
// Private
//

//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{
  clock_t start_t, end_t;
  int key,i;
  int size = SIZE_START;
  int arr[SIZE_MAX];
  for(i = 0; i<n; i++)
  {
    fillArray(a,c,arr,size);
    switch (a)
    {
      case bubble_sort_t:
        start_t = clock();
        bubble_sort(arr,size);
        end_t = clock();
        break;
      case insertion_sort_t:
        start_t = clock();
        insertion_sort(arr,size);
        end_t = clock();
        break;
      case quick_sort_t:
        start_t = clock();
        quick_sort(arr,size);
        end_t = clock();
        break;
      case linear_search_t:
        key = 0;
        start_t = clock();
        linear_search(arr,size,key);
        end_t = clock();
        break;
      case binary_search_t:
        if(c == average_t) //average case random key;
          key = rand() % size; //assuming key is in the array
        else if(c == best_t || c == worst_t)
          key = 0;
        else
        {
          printf("ERROR CREATING KEY");
          return;
        }
        start_t = clock();
        binary_search(arr,size,key);
        end_t = clock();
        break;
      default:
        printf("ERROR in benchmark() switch\n");
        break;
    }
    buf[i].size = size;
    buf[i].time = (double)(end_t-start_t)/CLOCKS_PER_SEC;
    size = size*2;
  }
}

void fillArray(const algorithm_t a, const case_t c, int *arr, int n)
{
  int i;
  switch(a)
  {
    case bubble_sort_t:
      switch(c)
      {
          case best_t: //best case == array is sorted
            for(i = 0; i<n; i++)
              arr[i] = i;
            break;
          case worst_t: //worst case == array is reversd sorted
            for(i = 0; i<n; i++)
              arr[i] = n-i;
            break;
          case average_t: //average case == random number
              for(i = 0; i<n; i++)
                arr[i] = rand() % n;
            break;
          default:
            printf("ERROR creating bubble sort array!");
            break;
      }//switch(c)
      break;
    case insertion_sort_t:
      switch(c)
      {
          case best_t: //best case == array is sorted
            for(i = 0; i<n; i++)
              arr[i] = i;
            break;
          case worst_t: // wrost case == array is reversed sorted
              for(i = 0; i<n; i++)
                arr[i] = n-i;
              break;
          case average_t: //average case == random numbers
            for(i = 0; i<n; i++)
              arr[i] = rand() % n;
            break;
          default:
            printf("ERROR creating insertion sort array");
            break;
      }//switch(c)
      break;
    case quick_sort_t:
      switch(c)
      {
          case best_t://best case == value of pivot is in the "middle"
            for(i = 0; i<n-1; i++)
              arr[i] = i;
            arr[n-1] = (n-1)/2; //pivot is the last element in the algoritg
            break;          //array is filled 1->n, so (n-1)/2 is the "middle" value
          case worst_t: //worst case == array is sorted
            for( i = 0; i<n; i++)
              arr[i] = i;
            break;
          case average_t: //average case == random numbers
            for(i = 0; i<n; i++)
              arr[i] = rand() % n;
            break;
          default:
            printf("ERROR in creating quick_sort array");
            break;
      }//switch(c)
      break;
    case linear_search_t:
    //assuming key == 0
      switch(c)
      {
        case best_t: //best case == key at first element, creating a sorted array
          for(i = 0; i<n; i++)
            arr[i] = i;
          break;
        case worst_t: //worst case == key not in the arrray
          for(i = 0; i<n; i++)
          {
            arr[i] = i+1;
          }
          break;
        case average_t: //avarage case == key in the middle
          for(i = 1; i<=n; i++)
            arr[i] = i;
          arr[(n-1)/2] = 0;
          break;
        default:
          printf("ERROR creating linear serach array");
          break;
      }
      break;
    case binary_search_t:
    //assuming key == 0 for best case and worst case
      switch(c)
      {
        case best_t: //best case == key in the middle
          for(i = 0; i<n; i++)
            arr[i] = i;
          arr[n/2] = 0;
          break;
        case worst_t: //worst case == key not in the array
          for(i = 0; i < n; i++)
            arr[i] = i+1;
          break;
        case average_t: //average case == random key
          for(i = 0; i<n; i++)
            arr[i] = i;
        break;
      }
      break;
    default:
      printf("ERROR in createArray()\n");
      break;
  }//switch
}
