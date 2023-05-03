import pygame

# Define las dimensiones de la ventana
WINDOW_SIZE = (440, 440)

# Define los colores que se utilizarán en el tablero de damas
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
BROWN = (139, 69, 19)
RED = (255, 0, 0)

# Carga el archivo data.txt y crea una lista de filas
with open("datos2.txt") as f:
    rows = [list(line.strip()) for line in f.readlines()]

# Inicializa pygame
pygame.init()

# Crea una ventana
screen = pygame.display.set_mode(WINDOW_SIZE)

# Establece el título de la ventana
pygame.display.set_caption("Juego de Damas")

# Define el tamaño de cada celda del tablero de damas
CELL_SIZE = 50

# Define el tamaño de las piezas
PIECE_SIZE = int(CELL_SIZE * 0.75)

# Define la fuente utilizada para mostrar los números de columna y fila
FONT = pygame.font.SysFont("Arial", int(CELL_SIZE * 0.4))

# Dibuja el tablero de damas
for row in range(len(rows)):
    for col in range(len(rows[row])):
        # Dibuja el fondo de la celda
        if (row + col) % 2 == 0:
            color = WHITE
        else:
            color = BROWN
        pygame.draw.rect(screen, color, (col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE))

        # Dibuja las piezas en las celdas correspondientes
        if rows[row][col] == "$":
            pygame.draw.circle(screen, RED, (int(col * CELL_SIZE + CELL_SIZE / 2), int(row * CELL_SIZE + CELL_SIZE / 2)), int(PIECE_SIZE / 2))
        elif rows[row][col] == "#":
            pygame.draw.circle(screen, BLACK, (int(col * CELL_SIZE + CELL_SIZE / 2), int(row * CELL_SIZE + CELL_SIZE / 2)), int(PIECE_SIZE / 2))

        # Dibuja los números de fila y columna
        if row == 7:
            text = FONT.render(str(col), True, WHITE)
            screen.blit(text, (col * CELL_SIZE + int(CELL_SIZE * 0.15), WINDOW_SIZE[1] - int(CELL_SIZE * 0.5)))
        if col == 7:
            text = FONT.render(str(row), True, WHITE)
            screen.blit(text, (WINDOW_SIZE[0] - int(CELL_SIZE * 0.5), row * CELL_SIZE + int(CELL_SIZE * 0.15)))

pygame.display.flip()

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

# Cierra pygame
pygame.quit()
