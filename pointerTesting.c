#include <stdio.h>
#include <stdlib.h>
#include "pointerTesting.h"

int main() {
  // Allocate memory on the heap for an integer
  int* data = (int*)malloc(sizeof(int));
  *data = 42; // Assign value 42 to the allocated memory

  // Create a pointer to the integer
  int* ptr = data;

  // Print the value pointed to by the pointer
  printf("%d\n", *ptr); // Output: 42

  // Free the allocated memory to avoid memory leaks
  free(data);

  howPointer();
  return 0;
}

int howPointer()
{
  int x = 1300;
  /* the array type is actually a pointer. printing the array, would return the pointer label
  within the stack. */
  int crossarray[] = {x};
  while (x--)
  {
    printf("%d\n", 0 [crossarray]);
  }
  return 0;
}
