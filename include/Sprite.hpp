#ifndef Sprite_H_
#define Sprite_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <string>

class Sprite
{
  public:
    struct Rect {float x; float y; float w; float h;};
    Sprite(std::string file, SDL_Renderer *renderer, SDL_Rect area);
    void render();
    void changePos(float x, float y);
    void setPos(float x, float y);
    void changeSize(float w, float h);
    void setSize(float w, float h);
    void offsetOrigin(float f_x, float f_y);
    Rect getRect();
  private:
    float m_x;
    float m_y;
    float m_w;
    float m_h;
    float m_offsetx = 0;
    float m_offsety = 0;
    SDL_Texture *m_texture; 
    SDL_Surface *m_surface;
    SDL_Renderer *m_renderer;
    SDL_Rect m_area;
};



#endif

