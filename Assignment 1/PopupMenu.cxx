
// System

// OpenGl
#include <GLUT/glut.h>

// Project
#include <PopupMenu.h>
#include <OpenGlHelpers.h>

const int NO_ITEM = -1;

const int MENU_ITEM_HEIGHT = 30;
const int MENU_ITEM_TEXT_Y = -18;

PopupMenu::PopupMenu(I_PopupMenuHandler& handler, int x, int y, int width)
   : handler_(handler)
   , x_(x)
   , y_(y)
   , width_(width)
   , visible_(false)
   , highlightedIndex_(NO_ITEM)
{

}

PopupMenu::~PopupMenu()
{
}

void PopupMenu::show()
{
   visible_ = true;
}

void PopupMenu::hide()
{
   visible_ = false;
}

void PopupMenu::addItem(std::string item)
{
   items_.push_back(item);
}

int PopupMenu::height()
{
   return (items_.size() * MENU_ITEM_HEIGHT);
}

void PopupMenu::render()
{
   if (!visible_)
   {
      return;
   }

   glColor4f(0, 0, 0, 0.85);
   drawRectangularQuad(x_, y_, width_, height());

   glColor4f(1, 1, 1, 1);
   drawLine(x_, y_ + height(), x_ + width_, y_ + height());

   for (int i = 0; i < items_.size(); i++)
   {
      glColor4f(1, 1, 1, 1);
      drawText(x_ + 20, positionOfItem(i) + MENU_ITEM_TEXT_Y, items_[i]);

      if (i == highlightedIndex_)
      {
         glColor4f(1, 1, 1, 0.2);
         drawRectangularQuad(x_, positionOfItem(i), width_, -MENU_ITEM_HEIGHT);
      }
   }
}

int PopupMenu::positionOfItem(int index)
{
   return y_ + height() - (index * MENU_ITEM_HEIGHT);
}

void PopupMenu::handleMouseEvent(int x, int y, bool mouseDown)
{
   highlightedIndex_ = -1;

   if (x >= x_ && x < x_ + width_)
   {
      for (int i = 0; i < items_.size(); i++)
      {
         if (y > positionOfItem(i) - MENU_ITEM_HEIGHT && y < positionOfItem(i))
         {
            if (visible_ && mouseDown)
            {
               handler_.handleItemSelected(this, i, items_[i]);
            }

            highlightedIndex_ = i;
            break;
         }
      }
   }   
}
