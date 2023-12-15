# CityScape
Shaun Lee Yin Sen

University of Prince Edward Island

Supervisor: Gordon Wood

## Introduction
Cityscape is a procedurally-generated city created using the OpenGL API. The aim of this project is to construct
an explorable, random cityscape, where buildings have different shapes and sizes. This project uses *Wolf*, a partial
engine created by Gordon Wood.

## Controls
- Use the WASD keys and mouse for first-person movement (mouse to be implemented).
- Use Left-Control to sprint.
- Use Spacebar to ascend and Left-Shift to descend.

(This document is incomplete. More features and details will be added soon.)

## Core Features

## Extra Features Implemented


## Challenges
**Deciding on the program's architecture**
It was challenging to design the architecture as I had different classes of buildings, where each building class had
varying components, textxures, and sizes. I considered a few different design patterns, including the Strategy Pattern
and Decorator pattern, but I struggled to understand how I could implement the code to work with those patterns. I also
researched on an Entity Component System (ECS). While this is possible and preferred in many types of games, creating
this cityscape using ECS would require me to learn from the beginning. With the time I have to finish the project, there
it was best that I used a different technique.

In the end, I used inheritance for my Building classes, where the program creates buildings using the child classes of
Building. This allowed removing a lot of boilerplate code for easy maintenance. While the flexibility of inheritance is
limited, it is sufficient for this time-critical project.

This project has enlighened me with the strengths of ECS, and I will continue to explore its possbilities in the future.


**Deciding where to construct the VAOs, VBOs, IBOs, and Textures**


**Handling indices for an n-sided prism generator**


**Time Constraints**
Due to overwhelming academic responsibilities, I could not use the time provided for this project to its full potential. 
Majority of the development time took place from 25 November to 15 December. However, the time constraint and pressure 
made me more resourceful by solving problems in different ways, resulting in time for extra features to be implemented.


## Stretch Goals Unimplemented
**Lighting**

**Moving Vehicles**

**Day/Night Cycle**

**Rain Particles**