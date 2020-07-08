#include <stdlib.h>
#include <time.h>
#include <emscripten.h>
#include <vector>

#include "Circle.h"
#include "CircleAnimation.h"
#include "auxFunctions.h"

// Number of circles
#define NUM_CIRCLES 20

std::vector<Circle> circles;
std::vector<CircleAnimation> animationData;

extern "C" int main(int argc, char *argv[])
{
    // Seed random number generator
    srand(time(nullptr));

    circles.resize(NUM_CIRCLES);
    animationData.resize(NUM_CIRCLES);

    // Create circles
    for (int i = 0; i < NUM_CIRCLES; i++)
    {
        int radius = getRand(50) + 10;

        int x = getRand(2000 - (2 * radius)) + radius;
        int y = getRand(2000 - (2 * radius)) + radius;

        circles[i].x = x;
        circles[i].y = y;
        circles[i].r = radius;

        circles[i].cr = getRand(255);
        circles[i].cb = getRand(255);
        circles[i].cg = getRand(255);

        animationData[i].dx = getRand(20) - 10;
        animationData[i].dy = getRand(20) - 10;
    }

    // Start JS rendering
    EM_ASM({ render($0, $1); }, NUM_CIRCLES * 6, 6);

    return 1;
}

// Returns animated cirlces to JS
extern "C" struct Circle *getCircles(int canvasWidth, int canvasHeight)
{
    // Update circles animation data
    for (int i = 0; i < NUM_CIRCLES; i++)
    {
        // Check if circle is at canvas horizontal boundaries, if so then invert its x velocity
        if(circles[i].x + circles[i].r >= canvasWidth || circles[i].x - circles[i].r <= 0) animationData[i].dx *= -1;
        // Check if circle is at canvas vertical boundaries, if so then invert its y velocity
        if(circles[i].y + circles[i].r >= canvasHeight || circles[i].y - circles[i].r <= 0) animationData[i].dy *= -1;

        // Update circle position
        circles[i].x += animationData[i].dx;
        circles[i].y += animationData[i].dy;
    }
    
    return circles.data();
}