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

        unit2Xpos = Coordinate(2, 0, 0);
        unit2Xneg = Coordinate(-2, 0, 0);
        unit2Ypos = Coordinate(0, 2, 0);
        unit2Yneg = Coordinate(0, -2, 0);
        unit2Zpos = Coordinate(0, 0, 2);
        unit2Zneg = Coordinate(0, 0, -2);

        unit2XposYposZpos = Coordinate(1, 1, 1);
        unit2XposYposZneg = Coordinate(1, 1, -1);
        unit2XposYnegZpos = Coordinate(1, -1, 1);
        unit2XposYnegZneg = Coordinate(1, -1, -1);
        unit2XnegYposZpos = Coordinate(-1, 1, 1);
        unit2XnegYposZneg = Coordinate(-1, 1, -1);
        unit2XnegYnegZpos = Coordinate(-1, -1, 1);
        unit2XnegYnegZneg = Coordinate(-1, -1, -1);
    }

    Coordinate orgin;

    Coordinate unit1Xpos;
    Coordinate unit1Xneg;
    Coordinate unit1Ypos;
    Coordinate unit1Yneg;
    Coordinate unit1Zpos;
    Coordinate unit1Zneg;

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
 * Comparison operators:
 *  1- < operator
 *  2- > operator
 *  3- <= operator
 *  4- >= operator
 * 
 *  5- == operator
 *  6- != operator
*/
TEST_F(CoordinateTest, originLowerThan) {
    EXPECT_LT(orgin, unit1Xpos);
    EXPECT_LT(orgin, unit1Xneg);
    EXPECT_LT(orgin, unit1Ypos);
    EXPECT_LT(orgin, unit1Yneg);
    EXPECT_LT(orgin, unit1Zpos);
    EXPECT_LT(orgin, unit1Zneg);
    
    EXPECT_LT(orgin, unit2Xpos);
    EXPECT_LT(orgin, unit2Xneg);
    EXPECT_LT(orgin, unit2Ypos);
    EXPECT_LT(orgin, unit2Yneg);
    EXPECT_LT(orgin, unit2Zpos);
    EXPECT_LT(orgin, unit2Zneg);

    EXPECT_LT(orgin, unit2XposYposZpos);
    EXPECT_LT(orgin, unit2XposYposZneg);
    EXPECT_LT(orgin, unit2XposYnegZpos);
    EXPECT_LT(orgin, unit2XposYnegZneg);
    EXPECT_LT(orgin, unit2XnegYposZpos);
    EXPECT_LT(orgin, unit2XnegYposZneg);
    EXPECT_LT(orgin, unit2XnegYnegZpos);
    EXPECT_LT(orgin, unit2XnegYnegZneg);
}

/**
 * Stream operators:
 *  1- << operator
*/