# Lego-Mindstorm-Simulated-Race
First year C project at Queen's University. Programmed a Lego Mindstorm EV3 to adapt to constantly changing race conditions using touch, colour, and sound sensors.

# Setup
Requires a Lego Mindstorm EV3, two EV3 bumper sensors, EV3 colour sensor, and DBA sound sensor at the following ports:

SensorType[S1] = sensorEV3_Touch    
SensorType[S4] = sensorEV3_Touch    
SensorType[S3] = sensorEV3_Color    
SensorType[S2] = sensorSoundDBA

# Usage
Robot will run in a constantly changing race condition. The 'race designer' can put down colour pads and obstacles and the robot will automatically detect and adjust. The color pads will speed the robot up based on color thresholds. When encountering an obstacle, the robot will breifly back up and then turn away. To start, clap your hands or make a loud noise. The robot detects this, plays an ascending tone and the begins the race. To stop, make a loud noise again. The robot will play a descending tone and end the program.

#Final Notes
A great introductory design program using C, and I like the way to robot adapts to race conditions and doesn't follow a pre-desgined track. Areas for improvement would be for the robot to continue into a straight line after detecting an object and an overall quicker execution of commands

