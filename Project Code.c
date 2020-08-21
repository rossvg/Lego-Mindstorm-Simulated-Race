//APSC 142 Final Project						         Week 12 Lab Period Friday 8:30am
//Ross Vrana-Godwin and Farhan Imtiaz

/* Robot will run in a simulated race condition detecting pads of colour
and speeding up or slowing down depending on colour. It is started by a 
loud noise and then an ascending octave playing. 
Then the bot will begin to drive forward The robot will also
detect collisions and turn in the correct way as the race is designed. 
The robot will also stop at the end of the race and play descendin octave.*/


//------------[Robot Musical Scale and Frequency]----------------
//Used to play the octaves at the beginning and end of the race.
//FOURTH OCTAVE NOTE FREQUENCIES
#define	C4  261	//	C	note frequency
#define	Cs4 277	//	C	sharp note frequency (same as D flat)
#define	D4  294	//	D	note frequency
#define	Ds4 311	//	D	sharp note frequency (same as E flat)
#define	E4  329	//	E	note frequency
#define	F4  349	//	F	note frequency
#define	Fs4 370	//	F	sharp note frequency (same as G flat)
#define	G4  392	//	G	note frequency
#define	Gs4 415	//	G	sharp note frequency (same as A flat)
#define	A4  440	//	A	note frequency
#define	As4 466	//	A	sharp note frequency (same as B flat)
#define	B4  494	//	B	note frequency
//FIFTH OCTAVE NOTE FREQUENCIES
#define	C5  523	//	C	note frequency
#define	Cs5 554	//	C	sharp note frequency (same as D flat)
#define	D5  587	//	D	note frequency
#define	Ds5 622	//	D	sharp note frequency (same as E flat)
#define	E5  659	//	E	note frequency
#define	F5  698	//	F	note frequency
#define	Fs5 740	//	F	sharp note frequency (same as G flat)
#define	G5  784	//	G	note frequency
#define	Gs5 831	//	G	sharp note frequency (same as A flat)
#define	A5  880	//	A	note frequency
#define	As5 932	//	A	sharp note frequency (same as B flat)
#define	B5  988	//	B	note frequency
//SIXTH OCTAVE COMES NEXT
#define	C6  1046	//	C	note frequency
//********************************************************************************
//Global Variables, Definitions, and Function Prototypes

#define ROTATIONSCALE 550// Trial and error value for the Rotate Function. Value
// does not change and is used to help rotate the robot the proper amount of degrees.
// as seen in the function.

#define SOUNDTHRESH 80 // Used in the DetectStart function. This is the level of sound
// that needs to be passed for the robot to start the race.



void Drive(int speed);//prototype for the drive function,takes the speed the robot will move forward at
void PlayNotes(int direction);// play an octave of notes. Direction is either 1 for ascending or 0 for descending.des
int GetBumps();// gets which direction the robot detected a collision from.
void Backup( int duration );// backs up the robot for specified amount of time.
void Rotate( int degrees);//rotates the robot specified amount of degrees.
int DetectStart();// detecting if the sound is greater than the threshold, and if true, start the race
int DetectColour(int speed);//detect colour and speed up/slow down accordingly
int GetCounter(int counter);// get how many times the colour has been detected and then stop the robot if above 4;



//...................................................................................
//MAIN PROGRAM
//All functions are called and executed using an infinite loop until race is over
//The robot will also handle collisions here 


task main () 
{
	
	
	int bump; // declare bump value for the collision detections
	int gun;// placeholder for value returned from DetectStart. "starting gun"
	
	
	int SPEED = 50; //declare initial speed of the robot
	int COUNTER = 0; // declare inital value of color pad counter
	
	
	// Set bumpers to proper sensor ports.
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S4] = sensorEV3_Touch;
	SensorType[S3] = sensorEV3_Color;
	SensorType[S2] = sensorSoundDBA;
	
	wait1Msec(500); //let sensors stabilize
	
	gun = DetectStart(); // call function to wait for loud enough sound. 
	//Will return a 1 if loud enough
	
	PlayNotes(1); // play ascending octave of notes to herald the beginning of movement.
	
	
	while (gun == 1) // use a infinite loop so the program will run continously until told to stop.
	{
/* this loop will continually test for light/dark pads, number of pads detected, update
		speed accordingly, and detect bumps. When testing the program will call the appropriate 
		functions if the test is true. When the maximum number of pads has been detected the loop
		will exit*/		
		
		SPEED = DetectColour(SPEED); // call function to get a new speed based on the current speed.
		COUNTER = GetCounter(COUNTER);// call function to get a new counter based on the current counter.
		
		if (COUNTER = 5)// check to see of max number of pads has been reached.
		{
			// if true then set gun = 0 to break the while loop.
			gun = 0;
		}
		
		else 
		{	//do nothing		}
			
			Drive(SPEED);// call drive function and drive forward at dictated by the DetectColour function.
			bump = GetBumps();// function to determine if there was a collision and what bumper were hit.
			
/* The following if-else statements handle the bump detection and turning.
		In the case of this simulated race the robot will always turn right no matter
		what bumper was detected.*/			
			
			if (bump == 1)// Right bumper hit
			{
				nxtDisplayBigTextLine(3, "COLLISION! TURN RIGHT!");
				
				motor[1] = 0;
				motor[2] = 0;
				wait1Msec(1000);
				
				
				Backup(500);//back up for 1 second
				wait1Msec(1000);
				Rotate( -90);
				wait1Msec(1000);
				Drive(SPEED);
				
			}
			
			
			
			else if (bump == 2) // Left bumper hit
			{
				motor[1] = 0;
				motor[2] = 0;
				wait1Msec(1000);
				nxtDisplayBigTextLine(3, "COLLISION! TURN RIGHT!");
				Backup(500);//back up for 1 second
				wait1Msec(1000);
				Rotate( -90);
				wait1Msec(1000);
				Drive(SPEED);
			}
			
			
			else if (bump ==3) // both bumpers hit.
			{
				motor[1] = 0;
				motor[2] = 0;
				wait1Msec(1000);
				nxtDisplayBigTextLine(3, "COLLISION! TURN RIGHT!");
				
				Backup( 500);//back up for 1 second
				wait1Msec(1000);
				Rotate( -90);
				wait1Msec(1000);
				Drive(SPEED);
				
				
				
			}
			else 
			{	// continue to drive straight	}
				
				
				
				
				
			}
			Drive(0);  // stop the robot
			PlayNotes(0); // play the descending octave
			displayBigTextLine(3, "SIMULATION OVER");// output message indicating end of prgram
			
		}
		//END PROGRAM
		
		
		
		
		
		
		
		
		//..................................................................
		//FUNCTIONS
		
		void Drive(int speed)
		{
			motor[1] = speed;
			motor[2] = speed;
			
			wait1Msec(50);
			
			
			
			
		}
		
		void PlayNotes(int direction) 
		{
			
			
			
			int notes[8], i; // declare array and array index
			// initialize array values
			notes[0] = C4;
			notes[1] = D4;
			notes[2] = E4;
			notes[3] = F4;
			notes[4] = G4;
			notes[5] = A4;
			notes[6] = B4;
			notes[7] = C5;
			
			nVolume = 2; //set volume
			
			
			
			
			if (direction == 1) // play notes up
			{
				
				
				for (i = 0; i<=7 ; i++)
				{
					PlayTone(notes[i],30);
					wait1Msec(250);
				}
			}
			
			
			
			if (direction == 0) 
			{
				
				
				for (i = 7; i>=0 ; i--)
				{
					PlayTone(notes[i],30);
					wait1Msec(250);
				}
			}
			
		}
		
		int GetBumps()
		{
			
			int rightbump;
			int leftbump;
			int bump_result;
			
			//get the bump values
			rightbump = SensorValue[1]; //as in previous labs
			leftbump = SensorValue[2];
			
			// Testing all 4 possibilities of where the bump could have come from
			// Set the result as an integer and send back to the main program to use
			if(leftbump==0 && rightbump==0)
				bump_result = 0;
			else if(leftbump==0 && rightbump==1)//FILL IN BRACKETS
				bump_result = 1;
			else if(leftbump==1 && rightbump==0)//FILL IN BRACKETS
				bump_result = 2;
			else if(leftbump==1 && rightbump==1)//FILL IN BRACKETS
				bump_result = 3;
			
			return bump_result;
		}
		
		
		//BACKUP
		void Backup(int duration)
		{	//accepts speed, and duration in millseconds
			int k, needed_loops;
			int speed = 50;
			//first, set motor[]'s to the NEGATIVE of specified "speed"
			motor[1] = -speed;
			motor[2] = -speed;
			
			//next, from the "duration" value passed in compute how many loops will
			//be needed (at 500 msecs per loop) to get the specified "duration" value
			needed_loops = 3;
			
			//then loop that number of times with a total loop delay
			//of approximately 200msecs+300msec=500msec (ingoring other instruction times)
			for(k=1; k<=needed_loops; k++)
			{	//NOTE that total loop wait duration is 500
				//first drive for 200 msecs
				
				wait1Msec(200);
				//then play an 1100 Hz tone for 300 msecs
				//(PlayTone function accepts duration in 10-msec tics)
				PlayTone(1100, 30);//add the tone to the "sound queue"
				wait1Msec(300);//and drive while waiting for it to finish	
			}
			//now set your motor[]'s back to 0
			motor[1] = 0;
			motor[2] = 0;
			
			
		}
		
		void Rotate(int degrees)
		{
			int speed = 50;
			//speed is always positive
			// degrees>0 is counter-clockwise, degrees < 0 is clockwise
			int rot_msecs; //how many milliseconds I need to rotate
			float fval; //to allow floating point computation below
			
			//compute rot_msecs proportional to degrees, and inversely
			//proportional to speed ! (statemnet below is INCORRECT and 
			//just a placeholder CORRECTED expression
			
			fval = (float)(ROTATIONSCALE) * (degrees/speed); //replace "X" by the correct expression
			rot_msecs = abs(fval); //back to 16-bit integer
			
			
			
			
			//then ADD a bit to account for starting inertia
			rot_msecs = rot_msecs +50;
			
			//use if-else to set wheel speeds +/- or -/+ according
			//to whether "degrees" is positive or negative
			if( degrees > 0 )
			{
				//set for counter-clockwise rotation
				motor[1] = speed;
				motor[2] = -speed;
				
			}
			else
			{
				//set for clockwise rotation
				motor[1] = -speed;
				motor[2] = speed;
				
			}
			//wait for needed rotation time
			wait1Msec(rot_msecs);
			
			//set motors back to 0 speed
			motor[1] = 0;
			motor[2] = 0;
			//and let Bot come to a stop
			wait1Msec(200);
		}
		
		
		int DetectStart()
		{
			int x;
			int dBlevel;
			dBlevel = SensorValue[S1];
			
			
			while (dBlevel < SOUNDTHRESH)
			{
				// run loop until the level is greater, indicating a start 
				DisplayBigTextLine(3, "WATING FOR STARTING SIGNAL!");
				dBlevel = SensorValue[S1];
			}
			
			return x =1; //now that the sounds was greater than the threshold the loop exits and returns a one.
			
			
		}
		
		
		int DetectColour(int speed)
		{
			
			int level;
			
			
			level = SensorValue[S3];
			
			if (level >40)
			{
				
				speed = speed + 10;
				
			}
			
			else if (level < 20)
			{
				
				speed = speed -10;
				
			}
			
			else
			{
				speed = speed;
			}
			
			
			return speed;
		}
		
		int GetCounter(int counter)
		{
			
			int level;
			
			
			level = SensorValue[S3];
			
			if (level >40)
			{
				
				counter = counter + 1;
				
			}
			
			else if (level < 20)
			{
				
				counter = counter +1;
				
			}
			
			else
			{
				counter = counter;
			}
			
			
			return counter;