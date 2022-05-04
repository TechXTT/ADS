#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Table
{
    char *output;
    char *str_arr;
    int out_code;
};

void resize(struct Table *table, int size)
{
    table = (struct Table *)realloc(table, sizeof(struct Table) * size);
    for (int i = size / 2; i < size; i++)
    {
        table[i].output = (char *)malloc(sizeof(char) * 10);
        table[i].str_arr = (char *)malloc(sizeof(char) * 10);
    }
}

int encode(struct Table *table, char *string)
{
    int table_size = 20;
    int table_count = 0;
    int jumper = 0;

    for (int i = 0; string[i]; i += jumper)
    {
        if (table_count == table_size)
        {
            table_size *= 2;
            resize(table, table_size);
        }
        char *temp = (char *)malloc(sizeof(char) * 10);
        jumper = 1;
        table[table_count].out_code = string[i];
        temp[0] = string[i];
        for (int j = 0; j < table_count; j++)
        {
            if (strcmp(temp, table[j].output) == 0 && string[i + jumper] == table[j].str_arr[jumper])
            {
                strcat(temp, &string[i + jumper]);
                jumper++;
                table[table_count].out_code = 256 + j;
                j = -1;
            }
        }
        strcpy(table[table_count].output, temp);
        strcpy(table[table_count].str_arr, temp);
        strcat(table[table_count].str_arr, &string[i + jumper]);
        table_count++;
    }
    return table_count;
}

int decode(struct Table *table, int *code)
{
    
}

int main()
{
    char *str = "BABAABAAA";
    int *code = {66, 65, 256, 257, 65, 260};
    struct Table *table;
    table = (struct Table *)malloc(sizeof(struct Table) * 30);
    for (int i = 0; i < 30; i++)
    {
        table[i].output = (char *)malloc(sizeof(char) * 20);
        table[i].str_arr = (char *)malloc(sizeof(char) * 20);
    }
    int *output = (int *)malloc(sizeof(int) * strlen(str));
    int size = decode(table, str);
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", table[i].output);
    }
}