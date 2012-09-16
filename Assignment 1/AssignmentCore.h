#ifndef ASSIGNMENTCORE_H
#define ASSIGNMENTCORE_H

// System

// Project
#include <Image.h>
#include <ImageRenderer.h>
#include <ControlBar.h>

/**
 ******************************************************************************
 *
 *                   OpenGlDisplay
 *
 ******************************************************************************
 */
class AssignmentCore : public I_ControlBarHandler
{

public:
   AssignmentCore();
   virtual ~AssignmentCore();

public:
   void handleSizeChanged(int width, int height);

   void handleMouseEvent(int button, int state, int x, int y);
   void handleMouseMotion(int x, int y);

   void reloadImageAndFilter();
   void setFilteredImage(Image image);

   void display();

public: // I_ControlBarHandler
   virtual void handleFileOpened(std::string file);
   virtual void handleFileSaved(std::string file);

   virtual void handleQuantilizeSelected(int levels);
   virtual void handleBrightenSelected(double setting);
   virtual void handleSaturateSelected(double scale);
   virtual void handleScaleSelected(double factor);
   virtual void handleRotateSelected(double angle);
   virtual void handleContrastSelected(double scale);
   virtual void handleBilinearScaleSelected(double factor);
   virtual void handleSwirlSelected(double angle);
   virtual void handleDissolveSelected(double mix);

private: // helpers
   int fixMouseY(int y);

private: // members
   bool mouseDown_;

   int width_;
   int height_;

   Image originalImage_;
   Image dissolveImage_;
   Image filteredImage_;

   ImageRenderer imageRenderer_;

   ControlBar controls_;
};

#endif
