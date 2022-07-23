#include <stdio.h>

void main() {
  int initial_position;

  printf("Enter the initial head point: ");
  scanf("%d", &initial_position);

  int number_of_seeks;

  printf("Enter the number of requests in the request sequence: ");
  scanf("%d", &number_of_seeks);
  number_of_seeks += 1;

  int request_locations[number_of_seeks];
  int total_seek = 0;
  request_locations[0] = initial_position;

  printf("Enter the seek locations in order: \n");
  for (int i = 1; i < number_of_seeks; i++) {
    scanf("%d", &request_locations[i]);
  }

  printf("The request sequence is as follows: \n");
  printf("%d\t", initial_position);
  for (int i = 1; i < number_of_seeks; i++) {
    printf("%d\t", request_locations[i]);
    total_seek += (request_locations[i] - request_locations[i - 1] < 0 ? request_locations[i - 1] - request_locations[i] : request_locations[i] - request_locations[i - 1]);
  }
  printf("\nTotal seek operations = %d\n", total_seek);
}