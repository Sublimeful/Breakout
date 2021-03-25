#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <stdio.h>
#include <string>
#include <Sprite.hpp>
#include <Paddle.hpp>
#include <Ball.hpp>
#include <iostream>
#include <vector>

//Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PI 3.141592f

int main(int argc, char **argv)
{
  bool quit = false;
  SDL_Event event;
  Uint64 LAST = 0;
  Uint64 NOW = SDL_GetPerformanceCounter();
  double deltaTime = 0;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Rect paddleRect = {SCREEN_WIDTH/2,SCREEN_HEIGHT-50,125,25};
  SDL_Rect ballRect = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 32, 32};
  float paddleSpeed = 500.f;
  float ballSpeed = 300.f;

  SDL_Window *window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  Paddle paddle("res/pixel.png", renderer, paddleRect, paddleSpeed);
  paddle.offsetOrigin(0.5, 0.5);

  Ball ball("res/ball.bmp", renderer, ballRect, ballSpeed);
  ball.offsetOrigin(0.5, 0.5);

  std::vector<Sprite> bricks;

  int brickRows = 7;
  int brickCols = 15;
  int gap_x = 5;
  int gap_y = 5;
  int brickWidth = (SCREEN_WIDTH - gap_x - brickCols * gap_x)/brickCols;
  int brickHeight = 15;
  int offset_x = brickWidth - 2 * gap_x;
  int offset_y = brickHeight - 2 * gap_y + 40;
  for(int y = 0; y < brickRows; y++)
  {
    for(int x = 0; x < brickCols; x++)
    {
      Sprite brick("res/pixel.png", renderer, {offset_x + (brickWidth + gap_x) * x, offset_y + (brickHeight + gap_y) * y, brickWidth, brickHeight});
      brick.offsetOrigin(.5, .5);
      bricks.push_back(brick);
    }
  }
  
  while(!quit)
  {
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    deltaTime = (float) (NOW-LAST) * 1000 / SDL_GetPerformanceFrequency();
    deltaTime /= 1000; // convert milliseconds to seconds

    SDL_PollEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT:
        quit = true;
        break;
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if(keystates[SDL_SCANCODE_A])
    {
      paddle.moveLeft(deltaTime);
      paddle.setVelocity(-paddle.getSpeed());
    }
    else if(keystates[SDL_SCANCODE_D])
    {
      paddle.moveRight(deltaTime);
      paddle.setVelocity(paddle.getSpeed());
    }
    else
    {
      paddle.setVelocity(0);
    }

    ball.collision(paddle);
    for(int i = 0; i < bricks.size(); i++)
    {
      Sprite brick = bricks.at(i);
      if(ball.collision(brick))
      {
        bricks.erase(bricks.begin() + i);
        ball.setSpeed((1 - (float)bricks.size()/(brickCols * brickRows)) * 700.f + ballSpeed);
      }
    }
    if(ball.collision(SCREEN_WIDTH, SCREEN_HEIGHT) == false)
    {
      quit = true;
    }

    ball.move(deltaTime);

    for(Sprite brick : bricks) brick.render();
    ball.render();
    paddle.render();
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
  }
  SDL_Quit();
  return 0;
}
