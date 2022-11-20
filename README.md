# 2D Space Invaders
A simplified version of the famous chicken invaders game. This game was created using the OpenGL which is a famous C/C++ Library for making 2D games.



![](https://github.com/Khaledayman9/2D-Space-Invaders/blob/master/layout.gif)



# Models

1- The Player Model (Space ship model).

2- The Enemy Model (Chicken model).

3- The Power Up Model.

4- The Bullet Model for the spaceship.

5- The Bullet Model for the chicken (Egg).

6- The Moon Model.

7- The Sun Model.


# Rules

- The Player Has 3 Lives.
- The Chicken health is 100.
- Each bullet deals 1 damage, either it is from the spaceship or it is from the chicken.
- If the player has 0 lives then he loses (Defeat).
- If the chicken has 0 health then the player wins (Victory).
- Powerups are generated at random positions and in random times.
- Whenever the player collides with the powerup, the spaceship changes color and he becomes bullet immune for a random amount of time.
- The player can move in all directions in the middle of the screen.
- The chicken is always at the top of the screen and can only move from left to right and vice versa. 

# Library and Modules

    CONSOLE APPLICATION : OpenGL2DTemplate Project Overview
========================================================================

AppWizard has created this OpenGL2DTemplate application for you.

This file contains a summary of what you will find in each of the files that
make up your OpenGL2DTemplate application.


OpenGL2DTemplate.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

OpenGL2DTemplate.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

OpenGL2DTemplate.cpp
    This is the main application source file.


Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named OpenGL2DTemplate.pch and a precompiled types file named StdAfx.obj.


Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.


