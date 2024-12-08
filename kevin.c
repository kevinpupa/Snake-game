#include <stdio.h>

#include <time.h>

#include <stdlib.h>

#define MAX_TAIL 100

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

struct coda {
    int t_x;
    int t_y;
};
struct ogetti {
    int coins;
    int T;
    int moves;
};
struct serpente {
    struct ogetti objects;
    int x;
    int y;
    int f_x;
    int f_y;
    int tail_number;
    struct coda tail[];
};

//FUNCTION DECLARATIONS
char maze_intake(char * maze, int a, int b);
void start_end(char * maze, struct serpente * snake, int a, int b);
void add_values(char * maze, int a, int b);
void maze_refresh(char * maze, int a, int b, struct serpente snake);
void snake_moving(char * maze, int a, int b, struct serpente * snake);
void tail_add(char * maze, int a, int b, struct serpente * snake);
void tail_delete(char * maze, int a, int b, struct serpente * snake);
void tail_move(char * maze, int a, int b, struct serpente * snake);
void tail_print(char * maze, int a, int b, struct serpente * snake);
void tail_find(char *maze,int a,int b,struct serpente * snake, char f);
void game_exit(struct serpente * snake);
void menu();
void ai_mode(char *maze,int a,int b , struct serpente *snake);

int main() {
    //VARIABLE INIZZIALAZATION
    struct serpente snake;
    snake.tail_number = 0;
    snake.objects.coins = 1000;
    snake.objects.moves = 0;
    snake.objects.T = 0;

    menu();
    //MAZE MEMORY ALLOCATION
    int a, b = 0;
    printf("%s", "Enter the number of rows : ");
    scanf(" %d", & a);
    printf("%s", "Enter the number of columns : ");
    scanf(" %d", & b);
    char maze[a][b];
    //INFORMATION INPUT/SCANNING          
    char y= maze_intake((char * ) maze, a, b);
    if(y=='Y'||y=='y')add_values((char * ) maze, a, b);
    start_end((char * ) maze, & snake, a, b);
    //PROGRAM RUNNING
    while (!(snake.x == snake.f_x && snake.y == snake.f_y)) {
        maze_refresh((char * ) maze, a, b, snake);
        snake_moving((char * ) maze, a, b, & snake);
        system(CLEAR_SCREEN);
    }
    game_exit( & snake);

}

char maze_intake(char * maze, int a, int b) {
    printf("Enter the maze:\n");

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            char c = getchar();
            while (c == '\n') {
                c = getchar();
            }
            maze[i * b + j] = c;
        }
    }

    printf("Maze:\n");
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            printf("%c ", maze[i * b + j]);
        }
        printf("\n");
    }
    char check;
    printf("Enter Y if the maze was printed succesfuly,else enter N :");
    scanf(" %c", & check);
    while (!(check == 'Y' || check == 'y' || check == 'N' || check == 'n')) {
        printf("Wrong character entered, try again : ");
        scanf(" %c", & check);
    }
    if (check == 'N' || check == 'n') maze_intake(maze, a, b);
    char y;
        printf("If map items haven't been loaded manualy enter Y to enter them randomly,otherwise enter N :");
    scanf(" %c", & y);
    while (!(y == 'Y' || y == 'y' || y == 'N' || y == 'n')) {
        printf("Wrong character entered,try again : ");
        scanf(" %c", & y);
    }
    system(CLEAR_SCREEN);
    return y;
}

void start_end(char * maze, struct serpente * snake, int a, int b) {
    int s = 0;
    int f = 0;
    //Trova l'inizio e la fine dell'gioco
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (maze[i * a + j] == 'o'||maze[i * a + j] == 'O') {
                snake -> x = i;
                snake -> y = j;
                s++;
                if(maze[i * a + j] == 'o')maze[i * a + j] = 'O';
            }
            if (maze[i * a + j] == 'x'||maze[i * a + j] == '_') {
                snake -> f_x = i;
                snake -> f_y = j;
                f++;
            }
        }
    }//se non trova automaticamente chiede user
    if (s == 0) {
        printf("Start not found enter manually.\n");
        printf("Enter rows : ");
        scanf(" %d", & snake -> x);
        while (!(snake -> x < a)) {
            printf("Wromg row entered, try again : ");
            scanf(" %d", & snake -> x);
        }
        printf("\nEnter cols : ");
        scanf(" %d", & snake -> y);
        while (!(snake -> y < b)) {
            printf("Wromg column entered, try again : ");
            scanf(" %d", & snake -> y);
        }
        maze[snake -> x * a + snake -> y] = 'O';
    }
    if (f == 0) {
        printf("Finish not found enter manually.\n");
        printf("Enter rows : ");
        scanf(" %d", & snake -> f_x);
        while (!(snake -> f_x < a)) {
            printf("Wromg row entered, try again : ");
            scanf(" %d", & snake -> f_x);
        }
        printf("\nEnter cols : ");
        scanf(" %d", & snake -> f_y);
        while (!(snake -> f_y < b)) {
            printf("Wromg column entered, try again : ");
            scanf(" %d", & snake -> f_y);
        }
        maze[snake -> f_x * a + snake -> f_y] = 'x';
    }

}

void add_values(char * maze, int a, int b) {
        srand(time(NULL));
        int num_coins = 0;
        int num_obstacles = 0;
        int num_drill = 0;
        int empty= 0;
        for(int j = 0;j<a*b;j++){
            if(maze[j]==' ')empty++;
        }
        int obs, coin, drill;
        printf("Enter number of coins to be present on the map :");
        scanf(" %d", & coin);
        printf("Enter number of drills to be present on the map :");
        scanf(" %d", & drill);
        printf("Enter number of obstacles to be present on the map :");
        scanf(" %d", & obs);
        if(coin+drill+obs>empty){
            puts("Number of values exceedes empety spaces try again.");
            add_values(maze,a,b);
        }
        while (num_coins < coin) {
            int row = rand() % a;
            int col = rand() % b;
            if (maze[row * a + col] == ' ') {
                maze[row * a + col] = '$';
                num_coins++;
            }
        } //METTE GLI OSTACOLI IN MODIALITA RANDOM
        while (num_obstacles < obs) {
            int row = rand() % a;
            int col = rand() % b;
            if (maze[row * a + col] == ' ') {
                maze[row * a + col] = '!';
                num_obstacles++;
            }
        } //METTE GLI TRAPPANI IN MODIALITA RANDOM
        while (num_drill < drill) {
            int drill_row = rand() % a;
            int drill_col = rand() % b;
            if (maze[drill_row * a + drill_col] == ' ') {
                maze[drill_row * a + drill_col] = 'T';
                num_drill++;
            }

        }
    
    system(CLEAR_SCREEN);
}

void maze_refresh(char * maze, int a, int b, struct serpente snake) {
    //stampa gli dati del giocatore alla mossa corrente
    printf("        Coins :  %d\n", snake.objects.coins);
    printf("        Drills : %d\n", snake.objects.T);
    printf("        Total Moves : %d\n", snake.objects.moves);

    //stampa la maze
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            printf("%c ", maze[i * a + j]);
        }
        printf("\n");
    }
}

void snake_moving(char * maze, int a, int b, struct serpente * snake) {
    char c;
    printf("Enter your move : ");
    scanf(" %c", & c);
    switch (c) {
    case 'W': // W(up)
    case 'w':
        //Controlla se non ci sono muri
        if (maze[(snake -> x - 1) * a + snake -> y] != '#' && snake -> x > 0) {
            int f = 0;
            //AGGIUNGE 10 MONETE NEL CASO DI $ E AGGIORNA LA CODA
            if (maze[(snake -> x - 1) * a + snake -> y] == '$') {
                snake -> objects.coins += 10;
                tail_delete(maze,a,b,snake);
                tail_add(maze, a, b, snake);
                f++;
            }
            //DIVIDE LE MONETE NEL CASO DI !
            else if (maze[(snake -> x - 1) * a + snake -> y] == '!') {
                tail_delete(maze,a,b,snake);
                snake -> objects.coins /= 2;
                snake -> tail_number /= 2;
            }
            //AGGIUNGE LA POSSIBILITA DI MANGIARE MURO
            else if (maze[(snake -> x - 1) * a + snake -> y] == 'T') snake -> objects.T += 3;
            else if (maze[(snake -> x - 1) * a + snake -> y] == 'o') tail_find(maze,a,b,snake, c);
            //ALGORITMO PER MUOVERE LO SNAKE
            tail_delete(maze,a,b,snake);
            if (f == 0) tail_move(maze, a, b, snake);
            maze[snake -> x * a + snake -> y] = ' ';
            snake -> x--;
            maze[snake -> x * a + snake -> y] = 'O';
            snake -> objects.coins--;
            snake -> objects.moves++;
            tail_print(maze, a, b, snake);
            //ALGORITMO PER MUOVERE LO SNAKE NEL CASO IN CUI E' STATO RACCOLTO TRAPPANO
        } else if (maze[(snake -> x - 1) * a + snake -> y] == '#' && snake -> objects.T > 0 && snake -> x > 0) {
            tail_delete(maze, a, b, snake);
            tail_move(maze, a, b, snake);
            maze[snake -> x * a + snake -> y] = ' ';
            snake -> x--;
            maze[snake -> x * a + snake -> y] = 'O';
            snake -> objects.T--;
            snake -> objects.coins--;
            snake -> objects.moves++;
            tail_print(maze, a, b, snake);
        } else puts("You cant go to that direction");
        break;
    case 'S': // S
    case 's':
        if (maze[(snake -> x + 1) * a + snake -> y] != '#' && snake -> x < a - 1) {
            int f = 0;
            //AGGIUNGE 10 MONETE NEL CASO DI $
            if (maze[(snake -> x + 1) * a + snake -> y] == '$') {
                tail_delete(maze,a,b,snake);
                snake -> objects.coins += 10;
                tail_add(maze, a, b, snake);
                f++;
            }
            //DIVIDE LE MONETE NEL CASO DI !
            else if (maze[(snake -> x + 1) * a + snake -> y] == '!') {
                tail_delete(maze,a,b,snake);
                snake -> objects.coins /= 2;
                snake -> tail_number /= 2;
            }
            //AGGIUNGE LA POSSIBILITA DI MANGIARE MURO
            else if (maze[(snake -> x + 1) * a + snake -> y] == 'T') snake -> objects.T += 3;
            else if (maze[(snake -> x + 1) * a + snake -> y] == 'o') tail_find(maze,a,b,snake, c);
            //ALGORITMO PER MUOVERE LO SNAKE
            tail_delete(maze,a,b,snake);
            if (f == 0) tail_move(maze, a, b, snake);
            maze[snake -> x * a + snake -> y] = ' ';
            snake -> x++;
            maze[snake -> x * a + snake -> y] = 'O';
            snake -> objects.coins--;
            snake -> objects.moves++;
            tail_print(maze, a, b, snake);
            //ALGORITMO PER MUOVERE LO SNAKE NEL CASO IN CUI E' STATO RACCOLTO TRAPPANO
        } else if (maze[(snake -> x + 1) * a + snake -> y] == '#' && snake -> objects.T > 0 && snake -> x < a - 1) {
            tail_delete(maze, a, b, snake);
            tail_move(maze, a, b, snake);
            maze[snake -> x * a + snake -> y] = ' ';
            snake -> x++;
            maze[snake -> x * a + snake -> y] = 'O';
            snake -> objects.T--;
            snake -> objects.coins--;
            snake -> objects.moves++;
            tail_print(maze, a, b, snake);
        } else puts("You cant go to that direction");
        break;
    case 'A': // A
    case 'a':
        if (maze[snake -> x * a + snake -> y - 1] != '#' && snake -> y > 0) {
            int f = 0;
            //AGGIUNGE 10 MONETE NEL CASO DI $
            if (maze[snake -> x * a + snake -> y - 1] == '$') {
                tail_delete(maze,a,b,snake);
                snake -> objects.coins += 10;
                tail_add(maze, a, b, snake);
                f++;
            }
            //DIVIDE LE MONETE NEL CASO DI !
            else if (maze[snake -> x * a + snake -> y - 1] == '!') {
                tail_delete(maze,a,b,snake);
                snake -> objects.coins /= 2;
                snake -> tail_number /= 2;
            }
            //AGGIUNGE LA POSSIBILITA DI MANGIARE MURO
            else if (maze[snake -> x * a + snake -> y - 1] == 'T') snake -> objects.T += 3;
            else if (maze[snake -> x * a + snake -> y - 1] == 'o') tail_find(maze,a,b,snake, c);
            //ALGORITMO PER MUOVERE LO SNAKE
            tail_delete(maze,a,b,snake);
            if (f == 0) tail_move(maze, a, b, snake);
            maze[snake -> x * a + snake -> y] = ' ';
            snake -> y--;
            maze[snake -> x * a + snake -> y] = 'O';
            snake -> objects.coins--;
            snake -> objects.moves++;
            tail_print(maze, a, b, snake);
            //ALGORITMO PER MUOVERE LO SNAKE NEL CASO IN CUI E' STATO RACCOLTO TRAPPANO
        } else if (maze[snake -> x * a + snake -> y - 1] == '#' && snake -> objects.T > 0 && snake -> y > 0) {
            tail_delete(maze, a, b, snake);
            tail_move(maze, a, b, snake);
            maze[snake -> x * a + snake -> y] = ' ';
            snake -> y--;
            maze[snake -> x * a + snake -> y] = 'O';
            snake -> objects.T--;
            snake -> objects.coins--;
            snake -> objects.moves++;
            tail_print(maze, a, b, snake);
        } else puts("You cant go to that direction");
        break;
        break;
    case 'D': // D
    case 'd':
        if (maze[snake -> x * a + snake -> y + 1] != '#' && snake -> y < b) {
            int f = 0;
            //AGGIUNGE 10 MONETE NEL CASO DI $
            if (maze[snake -> x * a + snake -> y + 1] == '$') {
                tail_delete(maze,a,b,snake);
                snake -> objects.coins += 10;
                tail_add(maze, a, b, snake);
                f++;
            }
            //DIVIDE LE MONETE NEL CASO DI !
            else if (maze[snake -> x * a + snake -> y + 1] == '!') {
                tail_delete(maze,a,b,snake);
                snake -> objects.coins /= 2;
                snake -> tail_number /= 2;
            }
            //AGGIUNGE LA POSSIBILITA DI MANGIARE MURO
            else if (maze[snake -> x * a + snake -> y + 1] == 'T') snake -> objects.T += 3;

            else if (maze[snake -> x * a + snake -> y + 1] == 'o') tail_find(maze,a,b,snake, c);
            //ALGORITMO PER MUOVERE LO SNAKE
            tail_delete(maze,a,b,snake);
            if (f == 0) tail_move(maze, a, b, snake);
            maze[snake -> x * a + snake -> y] = ' ';
            snake -> y++;
            maze[snake -> x * a + snake -> y] = 'O';
            snake -> objects.coins--;
            snake -> objects.moves++;
            tail_print(maze, a, b, snake);
            //ALGORITMO PER MUOVERE LO SNAKE NEL CASO IN CUI E' STATO RACCOLTO TRAPPANO
        } else if (maze[snake -> x * a + snake -> y + 1] == '#' && snake -> objects.T > 0 && snake -> y < b) {
            tail_delete(maze, a, b, snake);
            tail_move(maze, a, b, snake);
            maze[snake -> x * a + snake -> y] = ' ';
            snake -> y++;
            maze[snake -> x * a + snake -> y] = 'O';
            snake -> objects.T--;
            snake -> objects.coins--;
            snake -> objects.moves++;
            tail_print(maze, a, b, snake);
        } else puts("You cant go to that direction");
        break;
    default:
        puts("Invalid character entered");
        break;
    }

}

void tail_move(char * maze, int a, int b, struct serpente * snake) {
    for (int i = snake -> tail_number - 1; i > 0; i--) {
        snake -> tail[i].t_x = snake -> tail[i - 1].t_x;
        snake -> tail[i].t_y = snake -> tail[i - 1].t_y;
    }
    snake -> tail[0].t_x = snake -> x;
    snake -> tail[0].t_y = snake -> y;
    return;
}

void tail_delete(char * maze, int a, int b, struct serpente * snake) {
    for (int i = 0; i < snake -> tail_number; i++) {
        maze[snake -> tail[i].t_x * a + snake -> tail[i].t_y] = ' ';
    }
    return;
}

void tail_add(char * maze, int a, int b, struct serpente * snake) {
    if (snake -> tail_number < 1) {
        snake -> tail[snake -> tail_number].t_x = snake -> x;
        snake -> tail[snake -> tail_number].t_y = snake -> y;
        snake -> tail_number++;
    } else {
        for (int i = snake -> tail_number; i > 0; i--) {
            snake -> tail[i].t_x = snake -> tail[i - 1].t_x;
            snake -> tail[i].t_y = snake -> tail[i - 1].t_y;
        }
        snake -> tail[0].t_x = snake -> x;
        snake -> tail[0].t_y = snake -> y;
        snake -> tail_number++;
    }
    return;
}

void tail_print(char * maze, int a, int b, struct serpente * snake) {
    for (int i = 0; i < snake -> tail_number; i++) {
        maze[snake -> tail[i].t_x * a + snake -> tail[i].t_y] = 'o';
    }
    return;
}

void tail_find(char *maze,int a,int b,struct serpente *snake, char f) {
    tail_delete(maze,a,b,snake);
    int l = snake->tail_number-1;
    if(f=='A'||f=='a'){
        for (int i =l; i >=0; i--) {
            if (snake -> tail[i].t_x == snake -> x ) {
                if(snake -> tail[i].t_y == snake -> y - 1){
                    snake -> objects.coins -= (snake -> tail_number - i);
                    snake -> tail_number = i;
                }
            }
        }
    }
    else if(f=='D'||f=='d'){
        for (int i =l; i >=0; i--) {
            if (snake -> tail[i].t_x == snake -> x ) {
                if(snake -> tail[i].t_y == snake -> y + 1){
                    snake -> objects.coins -= (snake -> tail_number - i);
                    snake -> tail_number = i;
                }
            }
        }
    }
    else if(f=='S'||f=='s'){
        for (int i =l; i >=0; i--) {
             if (snake -> tail[i].t_x == snake -> x+1 ) {
                if(snake -> tail[i].t_y == snake -> y){
                    snake -> objects.coins -= (snake -> tail_number - i);
                    snake -> tail_number = i;
                }
            }
        }
    }
    else if(f=='W'||f=='w'){
        for (int i =l; i >=0; i--) {
            if (snake->tail[i].t_x == snake->x-1 ) {
                if(snake->tail[i].t_y == snake->y){
                    snake->objects.coins -= (snake->tail_number-i);
                    snake->tail_number = i;
                
                }
            }

        }
    }
}



void game_exit(struct serpente * snake) {
    printf("_________________________________________\n");
    printf("(づ｡◕‿‿◕｡)づ ---------------------( ͡♥ ͜ʖ ͡♥)\n");
    printf("| Hai %d monete rimanenti.             |\n", snake -> objects.coins);
    printf("| Hai completato il gioco con %d mosse.  |\n", snake -> objects.moves);
    printf("_________________________________________\n");
    printf("***************************\n");
    printf("**Buon Lavoro, a presto !**\n");
    printf("***************************\n");
}

void menu() {
    int instruction = 0;
    char show;
    //PART ONE MENU
    printf("───▄▀▀▀▄▄▄▄▄▄▄▀▀▀▄───\n");
    printf("───█▒▒░░░░░░░░░▒▒█───\n");
    printf("────█░░█░░░░░█░░█────\n");
    printf("─▄▄──█░░░▀█▀░░░█──▄▄─\n");
    printf("█░░█─▀▄░░░░░░░▄▀─█░░█\n");
    printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
    printf("█░░╦─╦╔╗╦─╔╗╔╗╔╦╗╔╗░░█\n");
    printf("█░░║║║╠─║─║─║║║║║╠─░░█\n");
    printf("█░░╚╩╝╚╝╚╝╚╝╚╝╩─╩╚╝░░█\n");
    printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n ");
    printf("Enter any character to enter the menu : ");
    show = getchar();
    do {
        puts("Enter 0 to look at the games rules.\n");
        puts("Enter 1 to start maze generating and play.");
        puts("Enter 2 to play with pre-fabricated maze constructed by me ;)");
        scanf(" %d", & instruction);
        while (!(instruction == 0 || instruction == 1)) {
            printf("Wrong command entered, try again : ");
            scanf(" %d", & instruction);

        }

        if (instruction == 0) {
            puts("These are the rules of the game : \n");
            puts("-You can move up(N) , down(S) , left(O) and right(E).\n");
            puts("-You can't go over walls '#' unless you have collected a 'T'.\n");
            puts("-You start the game with 1000 coins, every move costs you 1 coin.");
            puts("-Every '$' you collect gives you 10 points and the snake becomes 1 unit bigger.\n");
            puts("-If the snake eats a '!' your coins divide in half.\n");
            puts("-Collecting a 'T' allows you to eat 3 walls.\n");
            puts("-If you touch your own tail the tail segment will cut at the point you touched/ate. ");
            puts("ENJOY !\n");
        }
    } while (instruction == 0);
}

void ai_mode(char *maze,int a,int b , struct serpente *snake){


}