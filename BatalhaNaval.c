#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10 // Tamanho do tabuleiro

// Estrutura para representar o tabuleiro e os navios
typedef struct {
    char grid[SIZE][SIZE];
} Board;

// Função para inicializar o tabuleiro com água (~)
void initializeBoard(Board *board) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board->grid[i][j] = '~';
        }
    }
}

// Função para exibir o tabuleiro na tela
void printBoard(Board *board, int reveal) {
    printf("   ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i);
        for (int j = 0; j < SIZE; j++) {
            if (board->grid[i][j] == 'S' && !reveal)
                printf("~ ");
            else
                printf("%c ", board->grid[i][j]);
        }
        printf("\n");
    }
}

// Função para posicionar um único navio aleatoriamente
void placeShip(Board *board) {
    int x, y;
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (board->grid[x][y] == 'S');
    board->grid[x][y] = 'S';
}

// Função para lidar com os tiros do jogador
int shoot(Board *board, int x, int y) {
    if (board->grid[x][y] == 'S') {
        board->grid[x][y] = 'X'; // Acertou um navio
        return 1;
    } else if (board->grid[x][y] == '~') {
        board->grid[x][y] = 'O'; // Tiro na água
    }
    return 0;
}

// Função principal
int main() {
    srand(time(NULL));
    Board playerBoard;
    initializeBoard(&playerBoard);
    placeShip(&playerBoard); // Posiciona um único navio

    int attempts = 10; // Número máximo de tentativas
    int x, y, hits = 0;

    printf("Bem-vindo ao Batalha Naval!\n");
    while (attempts > 0 && hits == 0) {
        printBoard(&playerBoard, 0);
        printf("Digite as coordenadas do tiro (linha e coluna): ");
        if (scanf("%d %d", &x, &y) != 2) {
            printf("Entrada inválida! Tente novamente.\n");
            while (getchar() != '\n'); // Limpar buffer
            continue;
        }

        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            printf("Coordenadas inválidas! Tente novamente.\n");
            continue;
        }

        if (shoot(&playerBoard, x, y)) {
            printf("Parabéns! Você acertou um navio!\n");
            hits++;
        } else {
            printf("Tiro na água!\n");
        }
        attempts--;
    }

    if (hits > 0) {
        printf("Você venceu!\n");
    } else {
        printf("Fim de jogo! Você perdeu!\n");
    }
    printBoard(&playerBoard, 1); // Exibir tabuleiro final

    return 0;
}
