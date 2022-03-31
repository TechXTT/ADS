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
    struct Pair top;
    int capacity;
};

struct Pair_Stack create_stack(int capacity)
{
    struct Pair_Stack stack;
    stack.size = 0;
    stack.pairs = (struct Pair *)malloc(sizeof(struct Pair) * capacity);
    stack.capacity = capacity;
    stack.top.x = 0;
    stack.top.y = 0;
    return stack;
}

void push(struct Pair_Stack *stack, int x, int y)
{
    if (stack->size == stack->capacity)
    {
        stack->capacity *= 2;
        stack->pairs = (struct Pair *)realloc(stack->pairs, sizeof(struct Pair) * stack->capacity);
    }
    stack->pairs[stack->size].x = x;
    stack->pairs[stack->size].y = y;
    stack->size++;
}

struct Pair pop(struct Pair_Stack *stack)
{
    struct Pair position = stack->pairs[stack->size - 1];
    stack->size--;
    return position;
}

void print_stack(struct Pair_Stack *stack)
{

    printf("%d \n", stack->size - 1);
    for (int i = 0; i < stack->size; i++)
    {
        printf("%d %d\n", stack->pairs[i].x, stack->pairs[i].y);
    }
}

void dfs(int r, int c, int pacman_r, int pacman_c, int food_r, int food_c, char grid[r][c])
{
    struct Pair_Stack stack = create_stack(r * c);
    struct Pair directions[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    struct Pair_Stack visited = create_stack(r * c);
    struct Pair *route_pairs = (struct Pair *)malloc(sizeof(struct Pair) * r * c);
    struct Pair_Stack answear_routes;
    push(&stack, pacman_r, pacman_c);
    grid[pacman_r][pacman_c] = '=';
    while (stack.size != 0)
    {
        struct Pair_Stack temp = stack;
        struct Pair position = pop(&temp);
        push(&visited, position.x, position.y);
        if (position.x == food_r && position.y == food_c)
        {
            if (answear_routes.size == 0)
            {
                answear_routes = visited;
                break;
            }
        }
        for (int i = 0; i < 4; i++)
        {
            int new_x = position.x + directions[i].x;
            int new_y = position.y + directions[i].y;
            if (new_x >= 0 && new_x < r && new_y >= 0 && new_y < c && grid[new_x][new_y] != '#')
            {
                if (grid[new_x][new_y] == '.' || grid[new_x][new_y] == '-')
                {
                    push(&stack, new_x, new_y);
                    grid[new_x][new_y] = '=';
                }
            }
        }
        if (&stack.top == &position)
        {
            pop(&stack);
        }
    }
    print_stack(&stack);
    print_stack(&answear_routes);
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

    // printf("Fuck fucking C lANGUAGE!!!!! Marto moje da si ebe majkata!!!\n");
    return 0;
}