#include <gtest/gtest.h>

#include <Coordinate.hpp>

#include <cmath>

/**
 * Test fixture
 * Contains the coordinates that will be used for testing
*/
class CoordinateTest: public ::testing::Test
{
protected:
    void SetUp() override
    {
        orgin = Coordinate(0, 0, 0);

        unit1Xpos = Coordinate(1, 0, 0);
        unit1Xneg = Coordinate(-1, 0, 0);
        unit1Ypos = Coordinate(0, 1, 0);
        unit1Yneg = Coordinate(0, -1, 0);
        unit1Zpos = Coordinate(0, 0, 1);
        unit1Zneg = Coordinate(0, 0, -1);

        unit1XposYposZpos = Coordinate(1/sqrt(3), 1/sqrt(3), 1/sqrt(3));
        unit1XposYposZneg = Coordinate(1/sqrt(3), 1/sqrt(3), -1/sqrt(3));
        unit1XposYnegZpos = Coordinate(1/sqrt(3), -1/sqrt(3), 1/sqrt(3));
        unit1XposYnegZneg = Coordinate(1/sqrt(3), -1/sqrt(3), -1/sqrt(3));
        unit1XnegYposZpos = Coordinate(-1/sqrt(3), 1/sqrt(3), 1/sqrt(3));
        unit1XnegYposZneg = Coordinate(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3));
        unit1XnegYnegZpos = Coordinate(-1/sqrt(3), -1/sqrt(3), 1/sqrt(3));
        unit1XnegYnegZneg = Coordinate(-1/sqrt(3), -1/sqrt(3), -1/sqrt(3));

        unit2Xpos = Coordinate(2, 0, 0);
        unit2Xneg = Coordinate(-2, 0, 0);
        unit2Ypos = Coordinate(0, 2, 0);
        unit2Yneg = Coordinate(0, -2, 0);
        unit2Zpos = Coordinate(0, 0, 2);
        unit2Zneg = Coordinate(0, 0, -2);

        unit2XposYposZpos = Coordinate(2/sqrt(3), 2/sqrt(3), 2/sqrt(3));
        unit2XposYposZneg = Coordinate(2/sqrt(3), 2/sqrt(3), -2/sqrt(3));
        unit2XposYnegZpos = Coordinate(2/sqrt(3), -2/sqrt(3), 2/sqrt(3));
        unit2XposYnegZneg = Coordinate(2/sqrt(3), -2/sqrt(3), -2/sqrt(3));
        unit2XnegYposZpos = Coordinate(-2/sqrt(3), 2/sqrt(3), 2/sqrt(3));
        unit2XnegYposZneg = Coordinate(-2/sqrt(3), 2/sqrt(3), -2/sqrt(3));
        unit2XnegYnegZpos = Coordinate(-2/sqrt(3), -2/sqrt(3), 2/sqrt(3));
        unit2XnegYnegZneg = Coordinate(-2/sqrt(3), -2/sqrt(3), -2/sqrt(3));
    }

    Coordinate orgin;

    Coordinate unit1Xpos;
    Coordinate unit1Xneg;
    Coordinate unit1Ypos;
    Coordinate unit1Yneg;
    Coordinate unit1Zpos;
    Coordinate unit1Zneg;

    Coordinate unit1XposYposZpos;
    Coordinate unit1XposYposZneg;
    Coordinate unit1XposYnegZpos;
    Coordinate unit1XposYnegZneg;
    Coordinate unit1XnegYposZpos;
    Coordinate unit1XnegYposZneg;
    Coordinate unit1XnegYnegZpos;
    Coordinate unit1XnegYnegZneg;

    Coordinate unit2Xpos;
    Coordinate unit2Xneg;
    Coordinate unit2Ypos;
    Coordinate unit2Yneg;
    Coordinate unit2Zpos;
    Coordinate unit2Zneg;

    Coordinate unit2XposYposZpos;
    Coordinate unit2XposYposZneg;
    Coordinate unit2XposYnegZpos;
    Coordinate unit2XposYnegZneg;
    Coordinate unit2XnegYposZpos;
    Coordinate unit2XnegYposZneg;
    Coordinate unit2XnegYnegZpos;
    Coordinate unit2XnegYnegZneg;
};


/**
 * Assignment operators:
 *  1- Copy assignment operator
 *  2- Move assignment operator
*/

/**
 * Comparison operators:
 *  1- < operator
 *  2- > operator
 *  3- <= operator
 *  4- >= operator
 * 
 *  5- == operator
 *  6- != operator
*/

/**
 * Stream operators:
 *  1- << operator
*/