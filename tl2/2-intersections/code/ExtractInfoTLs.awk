BEGIN {FS="\"";ORS=" "}
sub(/^  */, "", idle)
/<tl-logic id=/, />/ {print $2 > netdir "tl-logic.tmp"}
/type=/ {print $4 > netdir "tl-logic.tmp"}
/programID=/ {print $6 > netdir "tl-logic.tmp"}
/offset=/ {print $8 > netdir "tl-logic.tmp"}
/duration=/ {print $2, $4 > netdir "tl-logic.tmp"}
/\/tl-logic>/ {printf "\n"> netdir "tl-logic.tmp"}

