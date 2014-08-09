BEGIN {FS="\"";ORS=" ";phases=0;statephase="";total=0}
sub(/^  */, "", idle)
/<tlLogic id=/, />/ {print $2 > netdir "tlLogic.tmp"; phases = 0}
/duration=/{phases++;total++}
/state=/{statephase=statephase " " $4 }
/\/tlLogic>/ {print phases > netdir "tlLogic.tmp"; print statephase > netdir "tlLogic.tmp"; statephase=""; printf "\n"> netdir "tlLogic.tmp"}
END{print "totalPhases: ",total}
