#include "algorithm.h"

//
// Private
//

//
// Public
//
void bubble_sort(int *a, int n)
{
	// TODO: bubble sort
	int i,j,temp;
	bool swapped = false;

	for(i = 0; i<n-1; i++)
	{
		swapped = false;
		for(j = 0; j<n-1-i; j++)
		{
			if(a[j] > a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				swapped = true;
				/*
				temp = *(a+j);
				*(a+j) = *(a+j+1);
				*(a+j+1) = temp;
				*/
			}//if
		}//for
		if(!swapped)
			break;
	}//for
}//bubblesort()

void insertion_sort(int *arr, int n)
{
	int i, j, key;
	for(i=1; i<n; i++)
	{
		key = arr[i];
		j = i-1;

		while(j>=0 && arr[j] > key)
		{
			arr[j+1] = arr[j];
			j--;
		}//while
		arr[j+1] = key;
	}//for
}//insertion_sort

void quick_sort(int *a, int n)
{
	quick_sort_rec(a, 0, n);
	// TODO: quick sort
}//quick_sort

void quick_sort_rec(int *arr, int low, int high)
{
  	if(low < high)
  	{
  		int pi = partition(arr, low, high);
  		quick_sort_rec(arr, low, pi-1);
  		quick_sort_rec(arr, pi+1, high);
  	}//if
}//quick_sort_rec

int partition(int *arr, int low, int high)
{
	int pivot = *(arr+high);
	int i = (low -1);
	int temp,j;

	for(j = low; j<= high; j++)
	{
		if(*(arr+j) < pivot)
		{
			i++;
			temp = *(arr+i);
			*(arr+i) = *(arr+j);
			*(arr+j) = temp;
		}//if
	}//for
	temp = *(arr+i+1);
	*(arr+i+1) = *(arr+high);
	*(arr+high) = temp;
	return (i+1);
}//partition
bool linear_search(const int *arr, int n, int v)
{
	int i;

	for(i = 0; i<n; i++)
	{
		if(arr[i] == v)
		{
		//	printf("arr = %d v = %d\n",arr[i],v);
			return true;

		}//if
	}//for

	//printf("%d\n", xy);

	return false;
}
//Assuming the list is sorted

bool binary_search_rec(const int *arr, int v, int p, int r)
{
	int mid = (p+r)/2;

	if(r<p)
		return false;
	if(*(arr+mid) ==  v)
	{
//		printf("Found = %d\n", *(arr+mid));
		return true;
	}
	if(*(arr+mid) > v)
	{
	//	printf("mid > = %d\n",*(arr+mid));
		return binary_search_rec(arr, v, p, mid-1);
	}
	if(*(arr+mid) < v)
	{
			//	printf("mid < v = %d\n",*(arr+mid));
				return binary_search_rec(arr,v,mid+1,r);
	}

	printf("overflow\n");
	return false;
}
bool binary_search(const int *arr, int n, int v) //n length, n size, v key
{
	return binary_search_rec(arr,v,0,n);

}//binary_search
