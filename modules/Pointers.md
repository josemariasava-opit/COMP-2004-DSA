# Pointers & Arrays

Arrays and pointers in C have a very close relationship, and understanding their correlation is crucial for effective programming. Here's a breakdown of their connection, with examples:

**1. Array Names as Pointers:**

- The name of an array, when used without brackets, is equivalent to the memory address of the array's first element.
    - For example, if you declare `int arr;`, then `arr` is the same as `&arr`, which is the address of the first element of the array.
    - Both `arr` and `&arr` represent the same memory address.

**2. Pointer Arithmetic:**

- Pointers can be used to access array elements through pointer arithmetic.
    - If `ptr` points to an element of an array, then `ptr + n` points to the *n*th element after the current element in the array.
    - For example, if `int *ptr = arr;`, then `(ptr + 2)` is equivalent to `arr`, which is the value of the third element in the array.
    - Adding 1 to a pointer increases its value by the size, in bytes, of the pointed-to type.
- The expression `ar[n]` is defined to mean `(ar + n)`.

**3. Array Access Using Pointers:**

- Because of the relationship between array names and pointers, you can access array elements using pointer notation.
    - `arr[i]` is equivalent to `(arr + i)`.
    - For instance, if `int *ptr = arr;`, then you can use `ptr[i]` to access the *i*th element of the array, which is the same as using `arr[i]`.

**4. Passing Arrays to Functions:**

- When an array is passed as an argument to a function, it decays into a pointer to its first element.
    - This means that the function receives the address of the array's first element, not a copy of the entire array.
    - In the function, you can use either array notation or pointer notation to access array elements.
    - For example, in the function definition `int sum(int arr[], int n)`, `arr` is treated as a pointer to an integer. Therefore, `arr[i]` is the same as `(arr+i)` inside the function.

**5.  Pointer as function parameter:**

- Functions that process arrays actually use pointers as arguments, and you have a choice between array notation and pointer notation for writing array processing functions.
- A function working on an array needs to know where to start and stop, which can be achieved by using a pointer parameter to identify the beginning of the array and an integer parameter to indicate how many elements to process. Another way is by passing two pointers, with the first indicating where the array starts and the second where the array ends.

**6.  Pointer Operations:**

- You can assign an address to a pointer, which can be an array name, a variable preceded by the address operator (`&`), or another pointer.
- Incrementing a pointer to an array element makes it move to the next element of the array.
- You can subtract an integer from a pointer.
- You can also decrement a pointer.
- You can find the difference between two pointers, which will be in the same units as the type size.
- You can use relational operators to compare two pointers, provided they are the same type.

**7.  `const` and Pointers:**

- You can use `const` with formal parameters to protect array content, or you can also use it to create a pointer that can neither change where it's pointing nor change the value to which it points.

**Examples:**

```
#include <stdio.h>

int main() {
    int arr = {10, 20, 30, 40, 50};
    int *ptr;

    // 1. Array name as pointer
    ptr = arr;  // ptr now points to arr
    printf("Address of arr: %p\n", (void*)arr);   // Using arr as address of first element
    printf("Address using pointer: %p\n", (void*)ptr);

    // 2. Accessing elements with pointer arithmetic
    printf("Value of arr: %d\n", *(ptr + 2));  // Accessing arr

    // 3. Array access using pointer notation
     printf("Value of arr with pointer notation: %d\n", ptr); // same as arr

    // 4. Modifying elements using pointers
    *ptr = 100; // change arr
    printf("Modified arr: %d\n", arr);
    ptr = 200; // change arr using pointer notation
    printf("Modified arr: %d\n", arr);

    //5. Passing an array to a function
    int sum(int * ar, int n);
    int total = sum(arr, 5);
    printf("Total sum of elements: %d\n", total);

    return 0;
}

//5. Function to demonstrate array as a pointer
int sum (int * ar, int n)
{
    int total = 0;
    for (int i = 0; i < n; i++){
        total += ar[i];
    }
    return total;
}

```

**Key Points:**

- The close relationship between arrays and pointers allows for flexibility in how you work with data in C.
- Understanding this relationship is important for using pointers effectively with array arguments in functions.
- Pointer arithmetic is dependent on the size of the data type the pointer points to, so adding one to a pointer will increase the address by the size of that type.

In summary, arrays and pointers are very closely linked in C. The array name can be treated as a pointer to the first element, and pointers can be used to traverse and access array elements. This duality provides flexibility and efficiency in C programming.