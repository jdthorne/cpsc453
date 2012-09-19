
// System

// OpenGl
#include <OpenGl.h>

// Project
#include <PopupMenu.h>
#include <OpenGlHelpers.h>

const int NO_ITEM = -1;

const int TEXT_OFFSET_X = 20;
const int TEXT_OFFSET_Y = 8;

int glutNextItemId_ = 0;

// GLUT Menu Handling
PopupMenu* activeMenu = NULL;
void glutHandleMenu(int);

/**
 ******************************************************************************
 *
 *                   Construction and setup
 *
 ******************************************************************************
 */
PopupMenu::PopupMenu(I_PopupMenuHandler& handler, std::string text, int x, int y, int width, int height)
   : handler_(handler)
   , text_(text)
   , x_(x)
   , y_(y)
   , width_(width)
   , height_(height)
{
   // Create the GLUT menu
   glutId_ = glutCreateMenu(glutHandleMenu);
}

PopupMenu::~PopupMenu()
{
}

void PopupMenu::setText(std::string text)
{
   text_ = text;
}

/**
 ******************************************************************************
 *
 *                   Render the menu on the screen
 *
 ******************************************************************************
 */
void PopupMenu::render()
{
   // Render the file menu text
   glColor4f(1, 1, 1, 1);
   drawLine(x_, y_, x_, y_ + height_);
   drawText(x_ + TEXT_OFFSET_X, y_ + TEXT_OFFSET_Y, text_);

   // Render the "highlight" background if necessary
   if (activeMenu == this)
   {
      glColor4f(1, 1, 1, 0.2);
      drawRectangularQuad(x_, y_, width_, height_);
   }
}

/**
 ******************************************************************************
 *
 *                   Control which menu is active
 *
 ******************************************************************************
 */
void PopupMenu::setAsActiveMenu()
{
   // Tell GLUT we're the active menu
   glutSetMenu(glutId_);
   glutAttachMenu(GLUT_LEFT_BUTTON);

   // Store ourself as the active menu for our handler function
   activeMenu = this;
}

void PopupMenu::deactivateMenus()
{
   // Deactivate menus in GLUT
   glutDetachMenu(GLUT_LEFT_BUTTON);

   // Ensure the handler doesn't call a random menu
   activeMenu = NULL;
}

/**
 ******************************************************************************
 *
 *                   Add an item to this menu
 *
 ******************************************************************************
 */
void PopupMenu::addItem(std::string item)
{
   // Add to the item list
   items_.push_back(item);

   // Determine what ID we'll give to GLUT
   int glutId = glutNextItemId_++;
   glutIdToItemIndex_[glutId] = items_.size() - 1;

   // Setup the menu in GLUT
   glutSetMenu(glutId_);
   glutAddMenuEntry(item.data(), glutId);
}

/**
 ******************************************************************************
 *
 *                   Handle the menu being clicked
 *
 ******************************************************************************
 */
void PopupMenu::handleMouseEvent(int x, int y, bool mouseDown)
{
   bool mouseIsOverMenuButton =  (x >= x_ && x < x_ + width_)
                              && (y >= y_ && y < y_ + height_);

   // Become the active menu if the mouse is over us
   if (mouseIsOverMenuButton)
   {
      setAsActiveMenu();
   }
}

/**
 ******************************************************************************
 *
 *                   Handle an item being selected
 *
 ******************************************************************************
 */
void PopupMenu::handleMenuItemSelected(int glutId)
{
   // Figure out which item was clicked
   int index = glutIdToItemIndex_[glutId];
   std::string name = items_[index];

   // Tell our handler_ that it was selected
   handler_.handleItemSelected(this, index, name);
}

/**
 ******************************************************************************
 *
 *                   The Low-level GLUT menu handler,
 *                   which forwards events to the appropriate class
 *
 ******************************************************************************
 */
void glutHandleMenu(int itemId)
{
   // Ensure a menu was really active
   if (activeMenu == NULL)
   {
      return;
   }

   // Tell the menu it was clicked
   activeMenu->handleMenuItemSelected(itemId);
}
