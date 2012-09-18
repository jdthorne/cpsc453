
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
   // Create the GLUT menu
   glutId_ = glutCreateMenu(glutHandleMenu);
}

PopupMenu::~PopupMenu()
{
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
 *                   Low-level GLUT menu handelr
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
