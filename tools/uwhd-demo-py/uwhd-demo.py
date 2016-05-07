#!/bin/env python

import sys
import uwhd
import time

# Start up the GPIO for talking to the 32x32 panels
io = uwhd.GPIO()
if not io.Init():
  print "Did you run with sudo priveleges? Because you should have."
  sys.exit(-1)

print "GPIO inited"

# number of rows of pixels on a display
# (always 32 for the 7.5" displays from SparkFun)
rows = 32

# length of the display chain
# (always 3 for v1 and v2 of the game display)
chained_displays = 3

# number of parallel rows of display chains
# (always 1 for v1 and v2 of the game clock boards)
parallel_rows = 1

# Create the display driver
matrix = uwhd.RGBMatrix(io, rows, chained_displays, parallel_rows)

print "Built RGBMatrix"

# Create the Game Display object, which maintains its own version of the
# game state, and renders it onto the external 32x32 panels on the front
# of the clock, as well as the alphanumeric and 7-segment displays on the
# back.
gd = uwhd.GameDisplay(matrix)

print "Built GameDisplay"

# Fire up the Game Display thread, which is responsible for
# continuously drawing the state to the 32x32 boards
gd.Start0()

print "Started GameDisplay"

# Fetch the GameManager so we can edit the game state
mgr = gd.getMgr2()
mgr.setClockRunning(0)
mgr.setBlackScore(1)
mgr.setWhiteScore(4)
mgr.setGameClockSecs(135)

print "Set up GameModel"

time.sleep(5)

print "Quitting"