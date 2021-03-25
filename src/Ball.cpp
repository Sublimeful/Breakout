#include <Ball.hpp>
#include <Paddle.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>

#define PI 3.141592f

Ball::Ball(std::string file, SDL_Renderer *renderer, SDL_Rect area, float speed) : super(file, renderer, area), speed(speed)
{
  vel_x = 0;
  vel_y = -1;
};

bool Ball::collision(Paddle p)
{
  if(!collided(p)) return false;
  float x = getRect().x;
  float y = getRect().y;
  float s_x = p.getRect().x;
  float s_y = p.getRect().y;
  float s_h = p.getRect().h;
  float angle = atan2(vel_y, vel_x);//angle of vel vector in radians
  if(y > s_y + s_h/2 && vel_y > 0) //Hit was from below
  {
    angle = -angle;
  }
  else if(y < s_y - s_h/2 && vel_y < 0) //Hit was from above
  {
    //changes angle based on direction paddle moves
    if(p.getVelocity() > 0)
    {
      angle = PI/6 + (PI/3 - PI/6) * (std::rand() % 101 / 100.f);
    }
    else if(p.getVelocity() < 0)
    {
      angle = 2*PI/3 + (5*PI/6 - 2*PI/3) * (std::rand() % 101 / 100.f);
    }
    else
    {
      angle = PI/3 + (2*PI/3 - PI/3) * (std::rand() % 101 / 100.f);
    }
  }
  else if(x > s_x && vel_x < 0) //Hit was on left
  {
    angle = PI - angle;
  }
  else if(x < s_x && vel_x > 0) //Hit was on right
  {
    angle = PI - angle;
  }
  vel_x = cos(angle);
  vel_y = sin(angle);
  return true;
}

bool Ball::collision(Sprite s)
{
  if(!collided(s)) return false;
  float x = getRect().x;
  float y = getRect().y;
  float s_x = s.getRect().x;
  float s_y = s.getRect().y;
  float s_h = s.getRect().h;
  float angle = atan2(vel_y, vel_x);//angle of vel vector in radians
  if(y > s_y + s_h/2 && vel_y > 0) //Hit was from below the brick
  {
    angle = -angle;
  }
  else if(y < s_y - s_h/2 && vel_y < 0) //Hit was from above the brick
  {
    angle = -angle;
  }
  else if(x > s_x && vel_x < 0) //Hit was on left
  {
    angle = PI - angle;
  }
  else if(x < s_x && vel_x > 0) //Hit was on right
  {
    angle = PI - angle;
  }
  vel_x = cos(angle);
  vel_y = sin(angle);
  return true;
}

bool Ball::collision(int width, int height) 
{
  float angle = atan2(vel_y, vel_x);//angle of vel vector in radians
  float x = getRect().x;
  float y = getRect().y;
  float w = getRect().w;
  float h = getRect().h;
  if(y + h/2 > height && vel_y < 0)
  {
    return false;
    //angle = -angle;
  }
  if(y - h/2 < 0 && vel_y > 0) // top
  {
    angle = -angle;
  }
  if(x + w/2 > width && vel_x > 0)
  {
    angle = PI - angle;
  }
  if(x - w/2 < 0 && vel_x < 0) //left wall
  {
    angle = PI - angle;
  }
  vel_x = cos(angle);
  vel_y = sin(angle);
  return true;
}

bool Ball::collided(Sprite s)
{
  float x = getRect().x;
  float y = getRect().y;
  float w = getRect().w;
  float h = getRect().h;
  float s_x = s.getRect().x;
  float s_y = s.getRect().y;
  float s_w = s.getRect().w;
  float s_h = s.getRect().h;
  if(y - h/2 > s_y + s_h/2) return false;
  if(y + h/2 < s_y - s_h/2) return false;
  if(x - w/2 > s_x + s_w/2) return false;
  if(x + w/2 < s_x - s_w/2) return false;
  return true;
}

void Ball::move(double deltaTime)
{
  float spd = speed * deltaTime;  
  changePos(vel_x * spd, -vel_y * spd);
}

void Ball::setSpeed(float spd)
{
  speed = spd;
}

float Ball::getSpeed()
{
  return speed;
}
















