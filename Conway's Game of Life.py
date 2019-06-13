#-------------------------------------------------------------------------------
# Name:        Conway's Game of Life
# Purpose:
#
# Author:      Benjamin LOISON
#
# Created:     06/05/2018
# Copyright:   (c) Benjamin LOISON 2018
# Licence:     Please quote the author
#-------------------------------------------------------------------------------

## Load TKinter standard library which has graphical tools
from tkinter import *
import time
from threading import Thread
from random import randint

## Load TK Engine
tkengine = Tk()

## Load twindow
tkengine.state('zoomed')
WINDOW_WIDTH, WINDOW_HEIGHT = tkengine.winfo_screenwidth(), tkengine.winfo_screenheight()
## Background hexadecimal code: white
canvas = Canvas(tkengine, width = WINDOW_WIDTH, height = WINDOW_HEIGHT, bg = "#FFFFFF")
canvas.pack()

print("Width (px): " + str(WINDOW_WIDTH))
print("Height (px): " + str(WINDOW_HEIGHT))

WINDOW_WIDTH, WINDOW_HEIGHT = 25, 25

currentScreen = [[0 for x in range(WINDOW_WIDTH)] for y in range(WINDOW_HEIGHT)]
nextScreen = [[0 for x in range(WINDOW_WIDTH)] for y in range(WINDOW_HEIGHT)]

PT_SIZE = 10

##nextScreen[15][15] = 1
##nextScreen[16][16] = 1
##nextScreen[16][17] = 1
##
##
##nextScreen[14][16] = 1
##nextScreen[14][17] = 1
##nextScreen[15][18] = 1
##nextScreen[16][18] = 1

#nextScreen[16][16] = 1
#nextScreen[17][16] = 1

BLACK = "#000000"

# Functions TK - Begin

## Use of lists [] and not tuples () because tuples are unchangeable
## Define a plot function to plot black dot by default
def plot(x, y, color = BLACK):
    global canvas
    ## Use a segment of one pixel to draw a point (no plot function in TKinter)
    ## Add 1 to all coordinates arguments because we don't see the point with
    ## coordinates [1, 1]
    ## Don't need to round (maybe done by TKinter)
    canvas.create_line(x + 1, y + 1, x + 2, y + 2, fill = color)

def fill(x0, y0, color = BLACK):
    global canvas
    x0 *= PT_SIZE
    y0 *= PT_SIZE
    for j in range(y0, y0 + PT_SIZE):
        for i in range(x0, x0 + PT_SIZE):
            plot(i, j)

# Functions TK - End

# BEGIN

def randomAll():
    for j in range(0, WINDOW_HEIGHT):
        for i in range(0, WINDOW_WIDTH):
            if randint(0, 2) == 1:
                nextScreen[j][i] = 1

def randomPt(nb):
    for k in range(0, nb):
        nextScreen[randint(0, WINDOW_HEIGHT - 1)][randint(0, WINDOW_WIDTH - 1)] = 1

def display():
    print("display")
    canvas.delete("all")
    for x in range(0, WINDOW_WIDTH):
        for y in range(0, WINDOW_HEIGHT):
            if currentScreen[y][x] == 1:
                fill(x + 1, y + 1)
    canvas.update()

def countNeighboor(y, x):
    count = 0
    for j in range(y - 1, y + 2):
        for i in range(x - 1, x + 2):
            if (j != y or i != x) and 0 < j and j < WINDOW_HEIGHT and 0 < i and i < WINDOW_WIDTH:
                if(currentScreen[j][i] == 1):
                    count += 1
    return count

def animation():
    global currentScreen, nextScreen
    while True:
        currentScreen = nextScreen
        display()
        nextScreen = [[0 for x in range(WINDOW_WIDTH)] for y in range(WINDOW_HEIGHT)]
        for y in range(0, WINDOW_HEIGHT):
            for x in range(0, WINDOW_WIDTH):
                count = countNeighboor(y, x)
                if currentScreen[y][x] == 0:
                    if count == 3:
                        nextScreen[y][x] = 1
                else:
                    if count == 2 or count == 3:
                        nextScreen[y][x] = 1

randomAll()

tkengine.after(0, animation)

## Infinite loop to always display the window
tkengine.mainloop()

# END