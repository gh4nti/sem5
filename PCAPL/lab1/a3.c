// Implement a program in C to toggle the character of a given string. Example: suppose the string is "HeLLo", then the output should be "hEllO".

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <omp.h>

int main()
{
    char str[100];

    printf("Enter a string: ");
    scanf("%s", str);

#pragma omp parallel for
    for (int i = 0; i < strlen(str); i++)
    {
        if (islower(str[i]))
            str[i] = toupper(str[i]);
        else if (isupper(str[i]))
            str[i] = tolower(str[i]);

        printf("Thread %d processed character %d\n",
               omp_get_thread_num(), i);
    }

    printf("\nToggled String: %s\n", str);

    return 0;
}