#include "WS2812Display.h"

Status_t WS2812Display::Initialize()
{
   return Status_t::OK;
}

Status_t WS2812Display::DrawPixel(Point_t point, Color_t color)
{
   uint32_t pixel_index = 0;
   if (point.Y >= HEIGHT || point.X >= WIDTH)
   {
      return Status_t::ERROR;
   }

   if (point.X % 2)
   {
	   pixel_index = point.X * HEIGHT + (HEIGHT - point.Y - 1);
   }else
   {
	   pixel_index = point.X * HEIGHT + point.Y;
   }
   
   m_led_strip->SetColor(pixel_index, color);

   return Status_t::OK;
}

Status_t WS2812Display::Update()
{
   m_led_strip->Update();
}

uint32_t WS2812Display::GetHeight()
{
   return HEIGHT;
}

uint32_t WS2812Display::GetWidth()
{
   return WIDTH;
}


