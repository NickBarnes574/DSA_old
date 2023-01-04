#include "void_pointer_functions.h"

// INTEGER FUNCTIONS
void print_int(void *num)
{
    printf("%d\n", *((int *)num));
}

void **array_int_to_void(const int **int_arr, int size)
{
    void ** void_arr = NULL;

    if((NULL == int_arr) || (0 > size))
    {
        goto end;
    }
    void_arr = calloc(size, sizeof(void *));
    if(NULL == void_arr)
    {
        goto end;
    }

    for(int i = 0; i < size; i++)
    {
        void_arr[i] = (void *)&int_arr[i];
        printf("void_arr[%d] = %d\n", i, (*(int *)void_arr[i]));
    }

end:
  return void_arr;
}

// FLOAT FUNCTIONS
void print_float(void *flt)
{
    printf("%f\n", *((float *)flt));
}

// STRING FUNCTIONS
void print_string(void *str)
{
    printf("%s\n", *((char **)str));
}

int compare_int(void *num_1, void *num_2)
{
    return (*(int *)num_1) - (*(int *)num_2);
}

int compare_string_ASCII(void *str_1, void *str_2)
{
    return strcmp(*((char **)str_1), *((char **)str_2));
}

int compare_string_length(void *str_1, void *str_2)
{
    const char *string_1 = (*((char **)str_1));
    const char *string_2 = (*((char **)str_2));

    int length_str_1 = strlen(string_1);
    int length_str_2 = strlen(string_2);

    return length_str_1 - length_str_2;
}

void default_free(void *val)
{
    (void) val;
    return;
}

void free_string(void *str)
{
    (void) str;
    return;
}
