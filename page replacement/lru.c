#include <stdio.h>

void increase_page_age(int *, int, int);
int get_oldest_page(int *, int);
int check_page_hit(int *, int, int);

void main() {
  int number_of_processes;

  // get number of processes
  printf("Enter the number of processes: ");
  scanf("%d", &number_of_processes);

  int page_size;

  // get number of pages
  printf("Enter the page size: ");
  scanf("%d", &page_size);

  int page_sequence[number_of_processes][page_size];
  int page_age[page_size];

  // init all page ages to max
  for (int i = 0; i < page_size; i++) {
    page_age[i] = number_of_processes + 1;
  }

  int process_id[number_of_processes];
  int page_status[number_of_processes];

  // init all values to -1
  for (int i = 0; i < page_size; i++) {
    for (int j = 0; j < number_of_processes; j++) {
      page_sequence[j][i] = -1;
    }
  }

  // get all the process ids
  printf("Enter all the processes in  order: \n");
  for (int i= 0; i < number_of_processes; i++) {
    scanf("%d", &process_id[i]);
  }

  for (int i = 0; i < number_of_processes; i++) {
    if (check_page_hit(page_sequence[i - 1], i < page_size ? i : page_size, process_id[i])) {
      for (int j = 0; j < page_size; j++) {
        page_sequence[i][j] = page_sequence[i - 1][j];
      }
      increase_page_age(page_age, page_size, i);
      page_status[i] = 0;
      printf("\n\nhit\n\n");
    } else {
      int oldest_page = get_oldest_page(page_age, page_size);
      if (i > 0) {
        for(int j = 0; j < page_size; j++) {
          page_sequence[i][j] = page_sequence[i - 1][j];
        }
      }
      page_sequence[i][oldest_page] = process_id[i];
      increase_page_age(page_age, page_size, oldest_page);
      page_status[i] = 1;

      printf("\n\n%d entered at %d\n\n", process_id[i], oldest_page);
    }
  }

  printf("The final sequence is as follows: \n");
  for(int i = 0; i < number_of_processes; i++) {
    printf("%d\t", process_id[i]);
  }
  printf("\n");
  for (int j = 0; j < page_size; j++) {
    for (int i = 0; i < number_of_processes; i++) {
      if (page_sequence[i][j] < 0) {
        printf(" \t");
      } else {
        printf("%d\t", page_sequence[i][j]);
      }
    }
    printf("\n");
  }
  int number_of_page_faults = 0;
  for (int i = 0; i < number_of_processes; i++) {
    if (page_status[i] == 0) {
      printf("^\t");
    } else {
      printf("*\t");
      number_of_page_faults += 1;
    }
  }
  printf("\nThe number of page-faults = %d\nThe number of page hits = %d\n", number_of_page_faults, number_of_processes - number_of_page_faults);
}

void increase_page_age(int *array, int size, int enter_at) {
  for (int i = 0; i < size; i++) {
    if (i == enter_at) {
      array[enter_at] = 1;
    } else {
      array[i] += 1;
    }
  }
}

int get_oldest_page(int *array, int size) {
  int oldest = 0;

  for (int i = 0; i < size; i++) {
    if (array[i] > array[oldest]) {
      oldest = i;
    }
  }

  return oldest;
}

int check_page_hit(int *array, int size, int check) {
  for (int i = 0; i < size; i++) {
    if (array[i] == check) {
      return 1;
    }
  }
  return 0;
}