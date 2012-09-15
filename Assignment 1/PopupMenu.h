#ifndef POPUPMENU_H
#define POPUPMENU_H

// System
#include <string>
#include <vector>

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
   void setVisible(bool visible);
   void addItem(std::string item);

   void render();

   void handleMouseEvent(int x, int y, bool mouseDown);

private: // helpers
   int height();
   int positionOfItem(int index);

private: // members
   I_PopupMenuHandler& handler_;

   int x_;
   int y_;
   int width_;
   bool visible_;

   int highlightedIndex_;

   std::vector<std::string> items_;
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
