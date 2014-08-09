import sys
import random
from subprocess import call

# Program for generating random routes using randomTrips.py


num = 3				  # The number of the generated information
fringeFactor = 5
seed = 5
minDistance = 20
beginTime = 0
endTime = 500

netFileName = "twoIntersections.net.xml"
out_routeFileName = "twoIntersections.500.rou.xml"
#############################################################################################################################


retcode = call(['python', '/home/bluemix/SUMO/sumo-0.19.0/tools/trip/randomTrips.py', '-n', netFileName ,
				'-r', out_routeFileName, 
				'--fringe-factor', str(fringeFactor),
				'-s', str(seed),
				'--min-distance', str(minDistance),
				'-b', str(beginTime), '-e', str(endTime)]);

