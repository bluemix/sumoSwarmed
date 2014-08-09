BEGIN {FS="\"";ORS=" ";phases=0;statephase="";total=0}
sub(/^  */, "", idle)
/<tl-logic id=/, />/ {print $2 > netdir "tl-logic.tmp"; phases = 0}
/duration=/{phases++;total++}
/state=/{statephase=statephase " " $4 }
/\/tl-logic>/ {print phases > netdir "tl-logic.tmp"; print statephase > netdir "tl-logic.tmp"; statephase=""; printf "\n"> netdir "tl-logic.tmp"}
END{print total}
