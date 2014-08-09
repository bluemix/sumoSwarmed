sub(/^  */, "", idle)
/<tl-logic id=/,/<\/tl-logic>/ {  
  tl=tl ORS $0     
}
/<\/tl-logic>/ {                
  print tl 
  tl=""
}
