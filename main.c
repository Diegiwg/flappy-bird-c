#include "include/stdio.h"
#include "include/stdlib.h"
#include "include/windows.h"

HANDLE hConsole;

int WINDOW_WIDTH = 20;
int WINDOW_HEIGHT = 10;

int PIPE_GAP = 3;

int PLAYER_POINTS = 0;

typedef struct {
  int x;
  int y;
} obj_2d;

obj_2d bird = {5, 2};
obj_2d pipes[3] = {{20, 6}, {30, 4}, {40, 2}}; // Y limit is 6 ?

void drawScoreboard();

void clearScreen() { system("cls"); }

void moveTo(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;

  SetConsoleCursorPosition(hConsole, coord);
}

void drawBorder() {
  clearScreen();

  moveTo(0, 0);
  printf("---------------------|");

  // PIPE
  for (int i = 1; i < WINDOW_HEIGHT; i++) {
    moveTo(21, i);
    printf("|");
  }

  moveTo(0, 10);
  printf("---------------------|");

  drawScoreboard();
}

void clearGameArea() {
  // clear only X for bird and pipes
  int xCoords[] = {0, bird.x, pipes[0].x + 1, pipes[1].x + 1, pipes[2].x + 1};

  for (int i = 0; i <= 5; i++) {
    if (xCoords[i] > WINDOW_WIDTH) {
      continue;
    }

    for (int y = 1; y < WINDOW_HEIGHT; y++) {
      moveTo(xCoords[i], y);
      printf(" ");
    }
  }
}

void drawBird() {
  moveTo(bird.x, bird.y);
  printf(">");
}

void drawPipe(int index) {
  if (pipes[index].x > WINDOW_WIDTH) {
    return;
  }

  // Print the Top of Pipe
  for (int i = 1; i <= pipes[index].y; i++) {
    moveTo(pipes[index].x, i);
    printf("H");
  }

  // Print the Bottom of Pipe
  for (int i = pipes[index].y + PIPE_GAP; i < WINDOW_HEIGHT; i++) {
    moveTo(pipes[index].x, i);
    printf("Y");
  }
}

void drawScoreboard() {
  moveTo(WINDOW_WIDTH + 3, WINDOW_HEIGHT / 2);
  printf("Score: %d", PLAYER_POINTS);
}

void drawFrame() {
  clearGameArea();

  drawBird();

  for (int i = 0; i < 3; i++) {
    drawPipe(i);
  }
}

void earnPoint() {
  // if player passed in a pipe, add 1 to score
  for (int index = 0; index < 3; index++) {
    if (pipes[index].x == bird.x) {
      PLAYER_POINTS++;
      drawScoreboard();
    }
  }
}

void updatePositions() {
  // Apply gravity to the bird
  bird.y++;

  // Apply movement to pipes
  for (int index = 0; index < 3; index++) {
    if (--pipes[index].x < 0) {
      switch (index) {
      case 0:
        pipes[index].x = WINDOW_WIDTH + pipes[1].x;
        break;
      case 1:
        pipes[index].x = WINDOW_WIDTH + pipes[2].x;
        break;
      case 2:
        pipes[index].x = WINDOW_WIDTH + pipes[0].x;
        break;
      }
    }
  }
}

void updateGame() {
  updatePositions();

  if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
    bird.y -= 2;
  }

  if (bird.y <= 0) {
    bird.y = 1;
  }

  if (bird.y >= WINDOW_HEIGHT) {
    bird.y = WINDOW_HEIGHT - 1;
  }

  earnPoint();
}

int main(void) {
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  drawBorder();

  while (1) {
    updateGame();
    drawFrame();

    Sleep(500); // Adjust as needed

    if (GetAsyncKeyState(0x51) & 0x8000) {
      break;
    }
  }

  return 0;
}