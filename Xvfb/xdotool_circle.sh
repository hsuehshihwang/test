#!/bin/bash

sleep 5;

# Set the center position of the circle (e.g., middle of the screen)
CENTER_X=640  # Adjust this based on your screen size
CENTER_Y=360  # Adjust this based on your screen size
RADIUS=100    # The radius of the circle
STEPS=36      # Number of points in the circle (higher = smoother)
DELAY=0.05    # Delay between steps (adjust speed)

# Move the mouse in a circular path
for ((i=0; i<STEPS; i++)); do
    # Calculate angle in radians
    ANGLE=$(echo "$i * 2 * 3.14159265 / $STEPS" | bc -l)

    # Compute X and Y positions
    X=$(echo "$CENTER_X + $RADIUS * c($ANGLE)" | bc -l)
    Y=$(echo "$CENTER_Y + $RADIUS * s($ANGLE)" | bc -l)

    # Move the mouse
    DISPLAY=:99 xdotool mousemove $(printf "%.0f" $X) $(printf "%.0f" $Y)

    # Small delay
    sleep $DELAY
done

