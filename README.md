# Advanced Programming Techniques - Final Project

## Overview
This project involves designing and implementing a game-like application using Qt. The protagonist must navigate a 2D grid-based world, battle different enemies, and collect health packs to survive. The application supports both graphical and text-based representations and includes an autoplay mode.

## Features
- **Grid-Based World**: The world is represented as a grid where movement costs energy, and tiles have different values.
- **Graphical & Text-Based Representation**: Supports both a 2D graphical view and an ASCII-style text view.
- **Manual & Auto Navigation**: The protagonist can move manually using arrow keys or through an autoplay mode in the Graphical Representation and with commands (e.g. left, up, attack, help) that support tab completion or through an autoplay mode in the Text-Based Representation.
- **Multiple Enemies**: Includes standard enemies, PEnemies (poisoned enemies), and transformable enemies.
- **Health Packs**: Collectible items that restore the protagonist’s health.
- **Overlay System**: Supports layered maps with different visuals and properties.
- **Level Transitions**: Special tiles allow moving between different levels.
- **Pathfinding**: Uses an implemented algorithm to navigate efficiently in autoplay mode.
- **Animations**: The protagonist, all the different types of enemies and healthpacks are fully animated.
- **Easy Level Addition/Re-Configuration**: Levels can be easily added and re-configured trough a XML file without changing any of the code.

## Technologies Used
- **Qt Framework** for GUI and game rendering
- **C++** for core logic
- **Git/GitLab** for version control
- **Design Patterns** (MVC architecture, smart pointers, polymorphism)

## How To Run
Import the `FinalProject.pro` file in the FinalProject folder in a recent version of QT Creator (>= november 2024) on a Linux machine and compile in `release` mode.

## Final UML

![Final UML](https://github.com/woutlyen/Advanced-Programming-Techniques-Final-Project/blob/main/UML%2025-01-06.svg)

## In Game Pictures

![graphical1](https://github.com/woutlyen/Advanced-Programming-Techniques-Final-Project/blob/main/images/graph1.png) ![graphical2](https://github.com/woutlyen/Advanced-Programming-Techniques-Final-Project/blob/main/images/graph2.png) ![graphical3](https://github.com/woutlyen/Advanced-Programming-Techniques-Final-Project/blob/main/images/graph3.png)

![text1](https://github.com/woutlyen/Advanced-Programming-Techniques-Final-Project/blob/main/images/text1.png) ![text2](https://github.com/woutlyen/Advanced-Programming-Techniques-Final-Project/blob/main/images/text2.png) ![text3](https://github.com/woutlyen/Advanced-Programming-Techniques-Final-Project/blob/main/images/text3.png)
