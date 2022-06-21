#include <stdlib.h>
#include <stdio.h>
int main()
{
    const char* filename = "facebook_combined.txt";
    FILE* input_file = fopen(filename, "r");
    if (!input_file)
        exit(EXIT_FAILURE);

    char *contents = NULL;
    size_t len = 0;
    while (getline(&contents, &len, input_file) != -1){
        printf("%s", contents);
    }

    fclose(input_file);
    free(contents);

    exit(EXIT_SUCCESS);
}