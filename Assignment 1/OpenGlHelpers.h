#ifndef OPENGLHELPERS_H
#define OPENGLHELPERS_H

// System
#include <string>

// Project

/**
 ******************************************************************************
 *
 *                   OpenGlHelpers
 *
 ******************************************************************************
 */
void drawLine(int x1, int y1, int x2, int y2);
void drawRectangularQuad(int x, int y, int width, int height);
void drawText(int x, int y, std::string text);

#endif
