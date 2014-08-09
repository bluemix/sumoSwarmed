BEGIN {FS="\"";ORS=" ";count=0}
sub(/^  */, "", idle)
/<tlLogic /,/>/ {count++}
END{print count}

