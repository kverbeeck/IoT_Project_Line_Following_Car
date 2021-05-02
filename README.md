# IoT_Project_Self_Driving_Car

Description Assignment

Mercedes-Benz wants to automate its museum in Stuttgart. To do this, they want a system, which will allow a visitor to take a seat in a self-driving car. At the beginning of the tour, the visitor can take place in one of these cars that will drive around the entire museum. At the end, the visitor gets out and the trolley returns to the beginning of the tour so that new visitors can embark.

The route that the cars have to follow is fixed with a white tape on the floor, which makes it possible to adapt the tour if new exhibits are added. At each exhibit, a transverse white line will cross the tour line, this way the car knows where a museum piece is exhibited and that it has to stop. If the driver wants to continue, he or she can press a push-button inside the car and the tour will continue to the next exhibited item. 

To avoid congestion, the car will automatically continue the tour after 5 minutes.
Optionally, they also want to operate the cars remotely, for which the Control Center could take over the function of the push-button with an app.

Of course it is also important that the cars do not collide, therefore there should always be a minimum distance of 1.5 meters between the trolleys (Corona measures). If a car detects that it is too close to the one in front, it must stop and only continue if the one in front also continues to drive.

The cars are also equipped with LEDs. Using this signalization, the staff present in the control room can check cameras should there be a problem. 
•	A green LED will light up if there are no issues.
•	A red LED will light up if the car has lost track of the white line.
•	A orange LED will light up if the car detects an obstacle (other car or anything else in its path).

Requirements:
•	The car can autonomously follow a track indicated by a white line.
•	The car must stop at a white line and can only continue driving if:
o	The driver pushes the drive-through push-button.
o	The trolley has been stationary for 5 minutes.
o	Optional: when the control center activates the car with their custom made application.
•	The cars must not collide.
o	If a car is halted, the cars behind it will keep their distance and only continue their route when the car in front of them continues its path.
•	Should there occurre problems with a car, it will be forced to stop and inform the control center by means of LEDs mounted on the cars.
o	Signalization in case of problems:
	Green LED: No issues.
	Orange LED: Obstacle (other car or anything else in its path).
	Red led: car has lost track of the white line.

What does Mercedes-Benz expect:
•	A brief description of the used hardware.
o	Files to produce the enclosure.
o	Electronic components.
o	Schematics and PCB (if applicable).
•	Documented code.
•	Brief description of to produce these cars themselves.
o	Tutorial.
All of this will be provided to them through a GitHub page.

Follow-up:
Mercedes-Benz wants to take the cars into production after 7 weeks, there will be 3 evaluations.

In 3 weeks time the car should be driving and have basic functionality (line following). 

In 5 weeks they want to be sure that the cars have the correct functions to :
•	Follow the white line.
•	Stop and continue at each transverse white line.
•	Signalization.
In 7 weeks a working prototype should be presented. This prototype will be tested for functionality and speed. The prototype may not contain any loose components, so the use of a breadboard is not allowed. At this time, all documentation should also have been provided.
![Uploading image.png…]()
