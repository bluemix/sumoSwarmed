BEGIN {FS="\"";ORS=" ";durationTotal=0;stops=0;
sub(/^  */, "", idle);numVeh=0}
/<tripinfo id=/, /<\/tripinfo>/ {durationTotal+=$22;stops+=$26;numVeh++}
END{a=(durationTotal+((numVehTotal-numVeh)*sim_time)+stops);
b=(numVeh^2+greenVsred);
total=a/b;
print "Vehicles arriving: ",numVeh,", vehicles not arriving: ",numVehTotal-numVeh,", total duration: ",durationTotal, "total (green/red): ", total, "\n" >> "estadistico-fitness.txt"
print total}

