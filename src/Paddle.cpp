#include <Paddle.hpp>


Paddle::Paddle(std::string file, SDL_Renderer *renderer, SDL_Rect area, float speed) : super(file, renderer, area), speed(speed)
{

}

void Paddle::moveLeft(double deltaTime)
{
  Paddle::changePos(-speed * deltaTime, 0);
}

void Paddle::moveRight(double deltaTime)
{
  Paddle::changePos(speed * deltaTime, 0);
}

void Paddle::setVelocity(float vel)
{
  velocity = vel; 
}

float Paddle::getVelocity()
{
  return velocity; 
}

void Paddle::setSpeed(float spd)
{
  speed = spd; 
}

float Paddle::getSpeed()
{
  return speed; 
}



