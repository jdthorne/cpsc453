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
   PopupMenu(I_PopupMenuHandler& handler, int x, int y, int width);
   ~PopupMenu();

public:
   void setAsActiveMenu();
   static void deactivateMenus();
   void handleMenuItemSelected(int glutId);

   void addItem(std::string item);

private: // members
   I_PopupMenuHandler& handler_;

   int x_;
   int y_;

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
