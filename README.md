# PathPlanning

After getting the release:
	right clic on  "PathPlanning.uproject"
	-> generate visual studio project files
	
	then double click on "PathPlanning.uproject" to lunch the unreal project => he ask you to rebuild project you say yes
	You can also double click on the "PathPlanning.sln" to open sources files


When the project is open on unreal 4:
	if you don't see the map and all the actors:
		-> go on the file (left-down) -> content -> map -> double click on "DefaultMap"
here you can see:
	- the character (a cone) controlled when u RIGHT CLIC
	- A plane where the lvl is gonna be generated

SELECT A BEHAVIOUR:
	click on the character (the cone) 
	at right try to find the "Steering Param", here you can fix different things:
		- Mass : mass of the object
		- Max force
		- Max speed
		- Strategy you want to use on the character (circuit or one way)

now just press play and RIGHT clic to see the character moove where you clic.
My algorithme A* is working fine, he find a path but not an optimised one, dometimes he gonna do more move than necessery.
					

