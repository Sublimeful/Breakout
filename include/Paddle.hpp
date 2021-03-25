#ifndef PADDLE_H_
#define PADDLE_H_
#include <Sprite.hpp>

class Paddle : public Sprite
{
  public:
    Paddle(std::string file, SDL_Renderer *renderer, SDL_Rect area, float speed);
    void moveLeft(double deltaTime);
    void moveRight(double deltaTime);
    void setVelocity(float vel);
    float getVelocity();
    void setSpeed(float spd);
    float getSpeed();
  private:
    typedef Sprite super;
    float speed;
    float velocity;
  
};

#endif
