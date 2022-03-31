#include <stdio.h>
#include <string.h>
#include <math.h>

struct Pair
{
    int x;
    int y;
};

struct Stack
{
    struct Pair position;
    struct Stack *top;
    int capacity;
    int size;
};

struct Stack create_stack(int capacity)
{
    struct Stack stack;
    stack.position.x = 0;
    stack.position.y = 0;
    stack.top = NULL;
    stack.capacity = capacity;
    stack.size = 0;
    return stack;
}

void push(struct Stack *stack, int x, int y)
{
    struct Stack *new_stack = (struct Stack *)malloc(sizeof(struct Stack));
    new_stack->position.x = x;
    new_stack->position.y = y;
    new_stack->top = stack->top;
    stack->top = new_stack;
    stack->size++;
}

struct Pair pop(struct Stack *stack)
{
    struct Stack *temp = stack->top;
    struct Pair position = stack->top->position;
    stack->top = stack->top->top;
    stack->size--;
    free(temp);
    return position;
}

void print_stack(struct Stack *stack)
{
    struct Stack *temp = stack->top;
    while (temp != NULL)
    {
        printf("%d %d\n", temp->position.x, temp->position.y);
        temp = temp->top;
    }
}

void print_reverse_stack(struct Stack *stack)
{
    if (stack == NULL)
        return;
    print_reverse_stack(stack->top);
    if (stack->position.x != 0 && stack->position.y != 0)
        printf("%d %d\n", stack->position.x, stack->position.y);
}

void dfs(int r, int c, int pacman_r, int pacman_c, int food_r, int food_c, char grid[r][c])
{
    struct Stack stack = create_stack(r * c);
    struct Pair pacman = {pacman_r, pacman_c};
    struct Pair food = {food_r, food_c};
    struct Pair directions[4] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    struct Stack answear_routes;
    struct Stack full_routes = create_stack(r * c);
    push(&stack, pacman.x, pacman.y);
    grid[pacman.x][pacman.y] = '=';
    while (stack.top != NULL)
    {
        struct Pair current_position = pop(&stack);
        struct Stack routes = stack;
        push(&routes, current_position.x, current_position.y);
        push(&full_routes, current_position.x, current_position.y);
        if (current_position.x == food.x && current_position.y == food.y)
        {
            answear_routes = routes;
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            int new_x = current_position.x + directions[i].x;
            int new_y = current_position.y + directions[i].y;
            if (new_x >= 0 && new_x < r && new_y >= 0 && new_y < c && grid[new_x][new_y] != '%')
            {
                if (grid[new_x][new_y] == '-' || grid[new_x][new_y] == '.')
                {
                    grid[new_x][new_y] = '=';
                    push(&stack, current_position.x, current_position.y);
                    push(&stack, new_x, new_y);
                }
            }
        }
    }
    printf("%d\n", full_routes.size);
    print_reverse_stack(&full_routes);
    printf("%d\n", answear_routes.size - 1);
    print_reverse_stack(&answear_routes);
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