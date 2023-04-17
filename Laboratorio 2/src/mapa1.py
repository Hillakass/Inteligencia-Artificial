import pygame

pygame.init()

PISO = (0, 255, 255, 1)
CAMINO_EXPANSION = (128, 0, 128, 1)
CAMINO_INICIO_FIN = (255, 188, 0, 1)
INICIO = (255, 0, 210, 1)
FIN = (14, 255, 0, 1)
VACIO = (0, 0, 0, 1)

colors = {
    "0": PISO,  # PISO
    "+": CAMINO_INICIO_FIN,  # CAMINO_INICIO_FIN
    "-": CAMINO_EXPANSION,  # CAMINO EXPANSION
    "A": INICIO,  # INICIO
    "B": FIN,  # FIN
    " ": VACIO,  # VACIÓ
}

with open("datos.txt", "r") as f:
    all_lines = f.readlines()
    data = [list(line.strip('\n')) for line in all_lines[5:]]
    data1 = all_lines[:5]
    for i in range(len(data1)):
        data1[i] = data1[i].strip()

    DFS_BFS_TEXT = data1[0]
    INICIO_TEXT = data1[1][8:]
    FIN_TEXT = data1[2][5:]
    ROWS_TEXT = data1[3][5:]
    COLS_TEXT = data1[4][6:]

rows = len(data)
cols = len(data[0])

square_size = min(600 // rows, 600 // cols)

grid_width = square_size * cols
grid_height = square_size * rows

window_width = grid_width
window_height = grid_height + 100
window_size = (window_width, window_height)

window = pygame.display.set_mode(window_size)
pygame.display.set_caption(DFS_BFS_TEXT)

clock = pygame.time.Clock()

grid_rect = pygame.Rect(0, 0, grid_width, grid_height)
pygame.draw.rect(window, VACIO, grid_rect)

for row in range(rows):
    for col in range(cols):
        rect = pygame.Rect(col * square_size, row * square_size, square_size, square_size)
        color = colors[data[row][col]]
        pygame.draw.rect(window, color, rect)

font = pygame.font.SysFont("Consolas", 30)
dfs_text = font.render(DFS_BFS_TEXT + ROWS_TEXT + "x" + COLS_TEXT, True, CAMINO_EXPANSION)
inicio_text = font.render("A:" + INICIO_TEXT, True, INICIO)
fin_text = font.render("B:" + FIN_TEXT, True, FIN)

dfs_rect = dfs_text.get_rect()
dfs_rect.centerx = (grid_width // 4) - 50
dfs_rect.centery = (grid_height + 50)

inicio_rect = inicio_text.get_rect()
inicio_rect.centerx = (grid_width // 2) - 10
inicio_rect.centery = grid_height + 50

fin_rect = fin_text.get_rect()
fin_rect.centerx = 3 * (grid_width // 4) + 50
fin_rect.centery = grid_height + 50

window.blit(dfs_text, dfs_rect)
window.blit(inicio_text, inicio_rect)
window.blit(fin_text, fin_rect)

pygame.display.flip()

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    pygame.display.flip()

    clock.tick(60)

pygame.quit()