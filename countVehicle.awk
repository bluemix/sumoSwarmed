BEGIN {FS="\"";ORS=" ";numVehTotal=0}
/<route /,/>/{numVehTotal++}
END {print "totalVehicles: ",numVehTotal} 
