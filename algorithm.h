#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdbool.h> // bool
#include <stdio.h>

// bubble_sort sorts an array arr of length n
void bubble_sort(int *arr, int n);

// insertion_sort sorts an array arr of length n
void insertion_sort(int *arr, int n);

// starts quick_sort sorts an array arr of length n
void quick_sort(int *arr, int n);
//recursive quick_sort algrorithm
void quick_sort_rec(int *arr, int low, int high);

int partition(int *arr, int low, int high);
// linear_search checks whether a value v is in an array arr of length n
bool linear_search(const int *arr, int n, int v);

// binary_search checks whether a value v is in a sorted arrray arr of length n
bool binary_search(const int *arr, int n, int v);

bool binary_search_rec(const int*arr, int v, int p, int r);

#endif
