#include "LedCube.h"
#include <iostream>

LedCube::LedCube()
{
    this->lcs = {
        .c = {
            .setup = 1},
        .layers{{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}};
}

void LedCube::render()
{
    std::cout << "\033[0;0H        \n        \n  ";
    for (int i = 0; i < 3; i++)
    {

        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if(this->lcs.layers[i].leds[j][k].value){
                    std::cout << '#';
                } else {
                    std::cout << ' ';
                }
                
            }
            std::cout << "   \n  ";
        }
        std::cout << "---   \n  ";
    }
    std::cout << "        \n        ";
}

void LedCube::setState(LedCubeState lcs)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                this->lcs.layers[i].leds[j][k].value = lcs.layers[i].leds[j][k].value;
            }
        }
    }
    this->render();
}
