#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct Pair
{
    int x;
    int y;
};

struct Pair_Stack
{
    int size;
    struct Pair *pairs;
    int capacity;
};

struct Pair_Stack create_stack(int capacity)
{
    struct Pair_Stack stack;
    stack.capacity = capacity;
    stack.size = 0;
    stack.pairs = (struct Pair *)malloc(stack.capacity * sizeof(struct Pair));
    return stack;
}

void push(struct Pair_Stack *stack, struct Pair pair)
{
    if (stack->size == stack->capacity - 1)
    {
        stack->capacity = stack->size * 2;
        struct Pair *temp;
        temp = (struct Pair *)realloc(stack->pairs, (stack->capacity * sizeof(struct Pair)));
        if (temp == NULL)
        {
            printf("Error!\n");
            exit(1);
        }
        stack->pairs = temp;
    }
    stack->pairs[stack->size] = pair;
}

void dfs(int r, int c, int pacman_r, int pacman_c, int food_r, int food_c, char grid[r][c])
{
    struct Pair_Stack stack = create_stack(r * c * 2);

    struct Pair_Stack visited = create_stack(r * c * 2);
    struct Pair_Stack result = create_stack(r * c * 2);

    struct Pair current = {0, 0};
    struct Pair pacman = {pacman_r, pacman_c};
    struct Pair food = {food_r, food_c};

    int *counter = (int *)malloc(sizeof(int) * r * c);

    push(&stack, pacman);
    current = pacman;
    grid[pacman_r][pacman_c] = '=';

    struct Pair directions[4] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

    while (current.x != food.x || current.y != food.y)
    {

        stack.size--;
        for (int i = 0; i < 4; i++)
        {
            struct Pair next = {current.x + directions[i].x, current.y + directions[i].y};

            if (next.x < 0 || next.x >= r || next.y < 0 || next.y >= c)
                continue;

            if (grid[next.x][next.y] == '-' || grid[next.x][next.y] == '.')
            {
                push(&stack, next);
                counter[stack.size] = result.size + 1;
                stack.size++;
                grid[next.x][next.y] = '=';
            }
        }
        push(&visited, current);
        push(&result, current);
        visited.size++;
        result.size = counter[stack.size - 1];
        current = stack.pairs[stack.size - 1];
    }
    push(&visited, food);
    push(&result, food);
    visited.size++;
    result.size++;
    printf("%d\n", visited.size);
    for (int i = 0; i < visited.size; i++)
    {
        printf("%d %d\n", visited.pairs[i].x, visited.pairs[i].y);
    }
    printf("%d\n", result.size - 1);
    for (int i = 0; i < result.size; i++)
    {
        printf("%d %d\n", result.pairs[i].x, result.pairs[i].y);
    }

}

int main(void)
{

    int r, c;
    int pacman_r, pacman_c;
    int food_r, food_c;
    scanf("%d %d", &pacman_r, &pacman_c);
    scanf("%d %d", &food_r, &food_c);
    scanf("%d %d", &r, &c);
    char grid[r][c];

    for (int i = 0; i < r; i++)
    {
        scanf("%s[^\\n]%*c", grid[i]);
    }
    dfs(r, c, pacman_r, pacman_c, food_r, food_c, grid);

    return 0;
}