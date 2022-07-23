#include <stdio.h>

int get_l_or_r();
void sort(int *, int);
int get_start(int *, int, int, int);

void main() {
  int initial_position;

  printf("Enter the initial head point: ");
  scanf("%d", &initial_position);

  int max_size;

  printf("Enter the number of cylinders in the disk: ");
  scanf("%d", &max_size);

  int number_of_seeks;

  printf("Enter the number of requests in the request sequence: ");
  scanf("%d", &number_of_seeks);

  int request_locations[number_of_seeks];
  int total_seek = 0;

  int actual_seek_order[number_of_seeks + 2];
  actual_seek_order[0] = initial_position;


  printf("Enter the seek locations in order: \n");
  for (int i = 0; i < number_of_seeks; i++) {
    scanf("%d", &request_locations[i]);
  }

  printf("Enter whether to go left or right first(l/L/r/R): ");
  
  sort(request_locations, number_of_seeks);

  int direction = get_l_or_r();

  int second = get_start(request_locations, initial_position, number_of_seeks, direction);
  int seq = 0;

  if (direction == 0) {
    total_seek += initial_position - request_locations[second];
    actual_seek_order[++seq] = request_locations[second];
    
    for (int i = second - 1; i >= 0; i--) {
      total_seek += actual_seek_order[seq] - request_locations[i];
      actual_seek_order[++seq] = request_locations[i];
    }
    total_seek += actual_seek_order[seq] - 0;
    actual_seek_order[++seq] = 0;

    for (int i = second + 1; i < number_of_seeks; i++) {
      total_seek += request_locations[i] - actual_seek_order[seq];
      actual_seek_order[++seq] = request_locations[i];
    }
    
  } else {
    total_seek += request_locations[second] - initial_position;
    actual_seek_order[1] = request_locations[second];

    for (int i = second + 1; i < number_of_seeks; i++) {
      total_seek += request_locations[i] - actual_seek_order[seq];
      actual_seek_order[++seq] = request_locations[i];
    }

    total_seek += max_size - 1 - actual_seek_order[seq];
    actual_seek_order[++seq] = max_size - 1;

    for (int i = second - 1; i >= 0; i--) {
      total_seek += actual_seek_order[seq] - request_locations[i];
      actual_seek_order[++seq] = request_locations[i];
    }
  }

  printf("The request sequence is as follows: \n");
  printf("%d\t", initial_position);
  for (int i = 1; i < number_of_seeks + 2; i++) {
    printf("%d\t", actual_seek_order[i]);
  }
  printf("\nTotal seek operations = %d\n", total_seek);
}

int get_l_or_r() {
  char choice;
  scanf(" %c", &choice);

  if (choice == 'l' || choice == 'L') {
    return 0;
  } else if (choice == 'r' || choice == 'R') {
    return 1;
  } else {
    printf("%cInvalid selection, please enter (l/L/r/R): ", choice);
    return get_l_or_r();
  }
}

void sort(int *array, int size) {
  for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (array[j] > array[j + 1]) {
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

int get_start(int *arr, int start, int size, int flag) {
  for (int i = 0; i < size; i++) {
    if (arr[i] > start) {
      if (flag == 0) {
        return i - 1;
      } else {
        return i;
      }
    }
  }
  return -1;
}