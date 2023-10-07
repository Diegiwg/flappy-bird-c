#include "include/stdio.h"
#include "include/stdlib.h"
#include "include/windows.h"

#include "draw.c" // Ref: move_to, draw_border

int WINDOW_WIDTH = 20;
int WINDOW_HEIGHT = 10;

int PIPE_GAP = 3;

typedef struct {
  int x;
  int y;
} obj_2d;

obj_2d bird = {5, 2};
obj_2d pipes[3] = {{20, 6}, {30, 4}, {40, 2}}; // Y limit is 6 ?

void drawBird() {
  move_to(bird.x, bird.y);
  printf(">");
}

void drawPipe(int index) {
  if (pipes[index].x > WINDOW_WIDTH) {
    return;
  }

  // Print the Top of Pipe
  for (int i = 1; i <= pipes[index].y; i++) {
    move_to(pipes[index].x, i);
    printf("H");
  }

  // Print the Bottom of Pipe
  for (int i = pipes[index].y + PIPE_GAP; i < WINDOW_HEIGHT; i++) {
    move_to(pipes[index].x, i);
    printf("Y");
  }
}

void drawFrame() {
  clear_screen();
  draw_border();

  drawBird();

  for (int i = 0; i < 3; i++) {
    drawPipe(i);
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
}

int main(void) {

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