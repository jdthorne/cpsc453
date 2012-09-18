
// System

// OpenGl
#include <OpenGl.h>

// Project
#include <PopupMenu.h>
#include <OpenGlHelpers.h>

const int NO_ITEM = -1;

const int MENU_ITEM_HEIGHT = 30;
const int MENU_ITEM_TEXT_Y = -18;

int glutNextItemId_ = 0;

// GLUT Menu Handling
PopupMenu* activeMenu = NULL;
void glutHandleMenu(int);


PopupMenu::PopupMenu(I_PopupMenuHandler& handler, int x, int y, int width)
   : handler_(handler)
   , x_(x)
   , y_(y)
{
   glutId_ = glutCreateMenu(glutHandleMenu);
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

void PopupMenu::setAsActiveMenu()
{
   glutSetMenu(glutId_);
   glutAttachMenu(GLUT_LEFT_BUTTON);

   activeMenu = this;
}

void PopupMenu::deactivateMenus()
{
   glutDetachMenu(GLUT_LEFT_BUTTON);
   
   activeMenu = NULL;
}

void PopupMenu::addItem(std::string item)
{
   items_.push_back(item);

   int glutId = glutNextItemId_++;
   glutIdToItemIndex_[glutId] = items_.size() - 1;

   glutSetMenu(glutId_);
   glutAddMenuEntry(item.data(), glutId);
}

/**
 ******************************************************************************
 *
 *                   Menu Item Clicking
 *
 ******************************************************************************
 */
void PopupMenu::handleMenuItemSelected(int glutId)
{
   int index = glutIdToItemIndex_[glutId];
   std::string name = items_[index];

   handler_.handleItemSelected(this, index, name);
}

/**
 ******************************************************************************
 *
 *                   GLUT Menu Handling
 *
 ******************************************************************************
 */
void glutHandleMenu(int itemId)
{
   if (activeMenu == NULL)
   {
      return;
   }

   activeMenu->handleMenuItemSelected(itemId);
}


