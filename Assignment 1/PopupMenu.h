#ifndef POPUPMENU_H
#define POPUPMENU_H

// System
#include <string>
#include <vector>
#include <map>

// Project


class I_PopupMenuHandler;

/**
 ******************************************************************************
 *
 *                   PopupMenu
 *
 ******************************************************************************
 */
class PopupMenu
{

public:
   PopupMenu(I_PopupMenuHandler& handler, std::string text, int x, int y, int width, int height);
   ~PopupMenu();

public:
   void render();
   void setText(std::string text);

   void setAsActiveMenu();
   static void deactivateMenus();
   void handleMenuItemSelected(int glutId);
   void handleMouseEvent(int x, int y, bool mouseDown);

   void addItem(std::string item);

private: // members
   I_PopupMenuHandler& handler_;

   std::string text_;
   int x_;
   int y_;
   int width_;
   int height_;

   int glutId_;
   std::vector<std::string> items_;
   std::map<int, int> glutIdToItemIndex_;
};

/**
 ******************************************************************************
 *
 *                   Interface to handle PopupMenu selections
 *
 ******************************************************************************
 */
class I_PopupMenuHandler
{
public:
   virtual ~I_PopupMenuHandler() {};

public:
   virtual void handleItemSelected(const PopupMenu* menu, int index, std::string item) = 0;

};


#endif
