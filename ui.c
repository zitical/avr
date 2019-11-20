#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

//
// Private
//
static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0) {
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i=0; i<num_options; i++) {
		printf("    %c) %s\n", 'a'+i, options[i]);
	}
}

static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort average case\n",
		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort average case\n",
		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort average case\n",
		"Linear search best case",
		"Linear serach worst case",
		"Linear serach average case\n",
		"Binary serach best case",
		"Binary serach worst case",
		"Binary serach average case"
		// TODO: complete menu
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}
static bigO_t calcResults(const algorithm_t a, const case_t c, result_t result)
{
	bigO_t bigO;
	if(a == bubble_sort_t || a == insertion_sort_t|| a == quick_sort_t)//ifcase1
	{
		if(c == best_t)//ifcase2
		{
			bigO.d1 = result.time / log(result.size);
			bigO.d2 = result.time / result.size;
			bigO.d3 = result.time / (result.size * log(result.size));
		}
		else if(c == worst_t || c == average_t)
		{
			bigO.d1 = result.time / (result.size * log(result.size));
			bigO.d2 = result.time / (result.size*result.size);
			bigO.d3 = result.time / (result.size*result.size*result.size);
		}
		else
			printf("ERROR in calcResults ifcase2");
	}
	else if(a == linear_search_t || a == binary_search_t)
	{
		bigO.d1 = result.time / log(result.size);
		bigO.d2 = result.time / result.size;
		bigO.d3 = result.time * CLOCKS_PER_SEC;
	}
	else
			printf("ERROR in calcResults ifcase1");


	return bigO;
}
static void printResultsTop(const algorithm_t a, const case_t c)
{
	ui_line('*', MENU_WIDTH);
	switch (a)//switch1
	{
		case bubble_sort_t:
			printf("                          Bubble sort: ");
			break;
		case insertion_sort_t:
			printf("                          Insertion sort: ");
			break;
		case quick_sort_t:
		printf("                          Quick sort: ");
			break;
		case linear_search_t:
			printf("                          Linear serach: ");
			break;
		case binary_search_t:
			printf("                          Binary serach: ");
			break;
		default:
			printf("ERROR in printResultsTop() switch1");
			break;
	}//swich(a)
	switch(c)//switch2
	{
		case best_t:
			printf("best case\n");
			break;
		case worst_t:
			printf("worst case\n");
			break;
		case average_t:
			printf("average case\n");
			break;
		default:
			printf("ERROR in printResultsTop switch2");
			break;
	}
	ui_line('-', MENU_WIDTH);

	if(a == bubble_sort_t || a == quick_sort_t || a == insertion_sort_t) //ifcase1
	{
		if(c == best_t)//ifcase2
			printf("size     time T(s)    T/logn            T/n                T/nlogn\n");
		else if(c == worst_t || c == average_t)
			printf("size     time T(s)    T/nlogn            T/n^2                T/n^3\n");
		else
			printf("ERROR in printResultsTop ifcase2");
	}
	else if (a == linear_search_t|| a == binary_search_t)
	 	printf("size     time T(s)    T/logn            T/n               n(CPU clock cycles)\n");
	else
		printf("ERROR in printResultsTop ifcase1");

	ui_line('-', MENU_WIDTH);
}

static void printResults(const algorithm_t a, const case_t c, result_t *result)
{

	bigO_t bigO[RESULT_ROWS];
 	printResultsTop(a,c);
	for(int i = 0; i<RESULT_ROWS; i++)
	{
		bigO[i] = calcResults(a,c,result[i]);
		if(a == bubble_sort_t || a == insertion_sort_t || a == quick_sort_t)
			printf("%d	 %f     %e      %e       %e\n", result[i].size,result[i].time,
			bigO[i].d1,bigO[i].d2,bigO[i].d3);
		else if(a == linear_search_t || a == binary_search_t)
		printf("%d	 %f     %e      %e       %d\n", result[i].size,result[i].time,
		bigO[i].d1,bigO[i].d2,(int)bigO[i].d3);
	}
	ui_line('-', MENU_WIDTH);
}



//
// Public
//
void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];

	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice()) {
			// House keeping
			case 'a':
				show_menu = true;
				break;
			case 'b':
				running = false;
				break;
			// Bubble sort
			case 'c':
				benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
				printResults(bubble_sort_t, best_t, result);
				break;
			case 'd':
				benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
				printResults(bubble_sort_t, worst_t, result);
				break;
			case 'e':
				benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
				printResults(bubble_sort_t, average_t, result);
				break;
			case 'f':
				benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
				printResults(insertion_sort_t, best_t, result);
				break;
			case 'g':
				benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
				printResults(insertion_sort_t, worst_t, result);
				break;
			case 'h':
				benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
				printResults(insertion_sort_t, average_t, result);
				break;
			case 'i':
				benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
				printResults(quick_sort_t,best_t,result);
				break;
			case 'j':
				benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
				printResults(quick_sort_t, worst_t,result);
				break;
			case 'k':
				benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
				printResults(quick_sort_t, average_t,result);
				break;
			case 'l':
				benchmark(linear_search_t, best_t, result, RESULT_ROWS);
				printResults(linear_search_t, best_t, result);
				break;
			case 'm':
				benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
				printResults(linear_search_t, worst_t, result);
				break;
			case 'n':
				benchmark(linear_search_t, average_t, result, RESULT_ROWS);
				printResults(linear_search_t, average_t, result);
				break;
			case 'o':
				benchmark(binary_search_t, best_t, result, RESULT_ROWS);
				printResults(binary_search_t, best_t, result);
				break;
			case 'p':
					benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
					printResults(binary_search_t, worst_t, result);
					break;
			case 'q':
					benchmark(binary_search_t, average_t, result, RESULT_ROWS);
					printResults(binary_search_t, average_t, result);
					break;
			default:// Invalid input
				show_menu = false;
				ui_invalid_input();
				break;
		}
	}
	ui_exit();
}
