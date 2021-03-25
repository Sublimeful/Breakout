#ifndef Ball_H_
#define Ball_H_
#include <Sprite.hpp>
#include <Paddle.hpp>

class Ball : public Sprite
{
  public:
    Ball(std::string file, SDL_Renderer *renderer, SDL_Rect area, float speed);
    // returns true if collision, false otherwise
    bool collision(Paddle p); 
    bool collision(Sprite s);
    // returns false if ball hit bottom aka game over
    bool collision(int width, int height);
    bool collided(Sprite s);
    void move(double deltaTime);
    void setSpeed(float spd);
    float getSpeed();

  private:
    typedef Sprite super;
    float speed;
    float vel_x;
    float vel_y;
};

#endif
