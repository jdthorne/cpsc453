
// System

// OpenGl
#include <OpenGl.h>

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

/**
 ******************************************************************************
 *
 *                   Setup & Visiblity
 *
 ******************************************************************************
 */
void PopupMenu::setVisible(bool visible)
{
   visible_ = visible;
}

void PopupMenu::addItem(std::string item)
{
   items_.push_back(item);
}

/**
 ******************************************************************************
 *
 *                   Accessors
 *
 ******************************************************************************
 */
int PopupMenu::height()
{
   return (items_.size() * MENU_ITEM_HEIGHT);
}

/**
 ******************************************************************************
 *
 *                   Menu Rendering
 *
 ******************************************************************************
 */
void PopupMenu::render()
{
   if (!visible_)
   {
      return;
   }

   // Draw the background
   glColor4f(0, 0, 0, 0.85);
   drawRectangularQuad(x_, y_, width_, height());

   // Draw the top line
   glColor4f(1, 1, 1, 1);
   drawLine(x_, y_ + height(), x_ + width_, y_ + height());

   // Draw each individual item
   for (unsigned int i = 0; i < items_.size(); i++)
   {
      // Draw the text
      glColor4f(1, 1, 1, 1);
      drawText(x_ + 20, positionOfItem(i) + MENU_ITEM_TEXT_Y, items_[i]);

      // Draw the highlight color if necessary
      if ((int)i == highlightedIndex_)
      {
         glColor4f(1, 1, 1, 0.2);
         drawRectangularQuad(x_, positionOfItem(i), width_, -MENU_ITEM_HEIGHT);
      }
   }
}
int PopupMenu::positionOfItem(int index)
{
   // Return the position of an item
   return y_ + height() - (index * MENU_ITEM_HEIGHT);
}

/**
 ******************************************************************************
 *
 *                   Mouse Events
 *
 ******************************************************************************
 */
void PopupMenu::handleMouseEvent(int x, int y, bool mouseDown)
{
   highlightedIndex_ = -1;

   // Don't do anything if we're outside of the menu area
   if (x < x_ || x > x_ + width_)
   {
      return;
   }

   // Otherwise, check individual items
   for (unsigned int i = 0; i < items_.size(); i++)
   {
      bool mouseIsHoveringOverItem = y > positionOfItem(i) - MENU_ITEM_HEIGHT && y < positionOfItem(i);
      if (mouseIsHoveringOverItem)
      {
         // Was it a click?
         if (visible_ && mouseDown)
         {
            handler_.handleItemSelected(this, i, items_[i]);
         }

         // It was always just a highlight
         highlightedIndex_ = i;
         break;
      }
   }
}
