BEGIN {FS="\"";ORS=" ";count=0}
sub(/^  */, "", idle)
/\/tl-logic>/ {count++}
END{print count}

