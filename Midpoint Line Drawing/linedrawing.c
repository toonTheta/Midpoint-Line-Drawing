//
//  linedrawing.c
//  Bresenham Drawing
//
//  Created by Siradanai Sutin on 25/2/2564 BE.
//

#include "linedrawing.h"


void performDrawing(LINE_T line, int canvas[WINDOW_WIDTH][WINDOW_HEIGHT]) {
    
    if (line.x1 == line.x2) {
        drawVerticalLine(line, canvas);
        return;
    }
    
    if (line.x1 > line.x2) {
        swap(&line.x1, &line.x2);
        swap(&line.y1, &line.y2);
    }
    
    int dy = line.y2 - line.y1;
    int dx = line.x2 - line.x1;
    
    
    if (dy > dx && dy >= 0) { // Slope Grater Than 1
        drawGreatGradientLine(line, canvas, dy, dx);
        return;
    }
    
    if (dy <= dx && dy >= 0) { // Original Case
        drawOriginalCase(line, canvas, dy, dx);
        return;
    }
    
    if (-dy <= dx) { // Negative Gradient
        drawNegativeGradientLine(line, canvas, dy, dx);
        return;
    }
    
    if (-dy > dx) { // Great Negative Gradient
        drawGreatNegativeGradientLine(line, canvas, dy, dx);
        return;
    }
    
}

// TODO: Implement Midpoint algorithm
/// Original Midpoint Line Drawing algorithm
/// @param line 2 endpoints
/// @param dy differece of points in vertical direction
/// @param dx differece of points in horizontal direction
void drawOriginalCase(LINE_T line, int canvas[WINDOW_WIDTH][WINDOW_HEIGHT], int dy, int dx) {
    
    int currentY = line.y1;
    int d = 2 * dy - dx;
    int dD = 2 * dy;
    int dU = 2 * (dy-dx);
    
    for (int x = line.x1; x <= line.x2; x++) {
        canvas[x][currentY] = 1;
        if (d < 0) {
            d += dD;
        } else {
            d += dU;
            currentY += 1;
        }
    }
}

/// Approve Bresenham Algorithm for handling
/// when slope of line is greater than 1
/// @param line 2 endpoints
/// @param dy differece of points in vertical direction
/// @param dx differece of points in horizontal direction
void drawGreatGradientLine(LINE_T line, int canvas[WINDOW_WIDTH][WINDOW_HEIGHT], int dy, int dx) {
    int currentX = line.x1;
    
    int d =  -2 * dx + dy;
    int dR = 2 * (dy - dx);
    int dU = -2 * dx;
//    printf("Enter here\n");
    
    for (int y = line.y1; y <= line.y2; y++) {
        canvas[currentX][y] = 1;
        if (d <= 0) { // NE is choosen, move to the right
            d += dR;
            currentX += 1;
        } else { // N is choosen, move up
            d += dU;
        }
    }
}

/// Approve Bresenham Algorithm for handling negative slope
/// when the slope is < 0 but >= -1
/// @param line 2 endpoints
/// @param dy differece of points in vertical direction
/// @param dx differece of points in horizontal direction
void drawNegativeGradientLine(LINE_T line, int canvas[WINDOW_WIDTH][WINDOW_HEIGHT], int dy, int dx) {
    
    int currentY = line.y1;
    int d = 2 * dy + dx;
    int dR = 2 * dy; // move right value
    int dD = 2 * (dy + dx); // move down value
    
    for (int x = line.x1; x <= line.x2; x++) {

        canvas[x][currentY] = 1;

        if(d < 0) { // move down
            currentY -= 1;
            d += dD;
        } else {
            d += dR;
        }
    }
}

/// Approve Bresenham Algorithm for handling negative slope
/// when slope of line is less than -1
/// @param line 2 endpoints
/// @param dy differece of points in vertical direction
/// @param dx differece of points in horizontal direction
void drawGreatNegativeGradientLine(LINE_T line, int canvas[WINDOW_WIDTH][WINDOW_HEIGHT], int dy, int dx) {
    int currentX = line.x1;
    int d = dy + (2 * dx);
    int dD = 2 * dx;
    int dR = 2 * (dy + dx);
    
    for (int y = line.y1; y>= line.y2; y--) {
        canvas[currentX][y] = 1;
        
        if (d<0) { // move down
            d += dD;
        } else { // move right
            d += dR;
            currentX += 1;
        }

    }
}



/// Draw vertical line
/// @param line set of 2 endpoints
void drawVerticalLine(LINE_T line, int canvas[WINDOW_WIDTH][WINDOW_HEIGHT]) {
    if (line.y1 < line.y2) {
        for (int y = line.y1; y <= line.y2; y++) {
            canvas[line.x1][y] = 1;
        }
    } else {
        for (int y = line.y2; y <= line.y1; y++) {
            canvas[line.x1][y] = 1;
        }
    }
    
}
    /* Test Case */
//    1 10 5 2
//    15 20 50 60
//    20 40 80 40
//    30 30 70 70
//    30 25 70 50
//    15 40 40 80
//    10 40 10 80

