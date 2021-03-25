#include <Sprite.hpp>

Sprite::Sprite(std::string file, SDL_Renderer *renderer, SDL_Rect area) : m_x(area.x), m_y(area.y), m_w(area.w), m_h(area.h), m_renderer(renderer), m_area(area)
{
  m_surface = IMG_Load(file.c_str());  
  if(m_surface == nullptr)
  {
    printf("Image cannot be loaded");
  }
  m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
}
void Sprite::render()
{
  SDL_RenderCopy(m_renderer, m_texture, NULL, &m_area);
}
void Sprite::changePos(float x, float y)
{
  setPos(m_x + x, m_y + y);
}
void Sprite::setPos(float x, float y)
{
  m_x = x;
  m_y = y;
  m_area.x = int(m_x - m_offsetx * m_w);
  m_area.y = int(m_y - m_offsety * m_h);
}
void Sprite::setSize(float w, float h)
{
  m_w = w;
  m_h = h;
  m_area.w = int(m_w);
  m_area.h = int(m_h);
}
void Sprite::changeSize(float w, float h)
{
  setSize(m_w + w, m_h + h);
}
void Sprite::offsetOrigin(float f_x, float f_y)
{
  m_offsetx = f_x;
  m_offsety = f_y;
  changePos(0, 0);
}
Sprite::Rect Sprite::getRect()
{
  return {m_x, m_y, m_w, m_h};
}

