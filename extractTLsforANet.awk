sub(/^  */, "", idle)
/<tlLogic id=/,/<\/tlLogic>/ {  
  tl=tl ORS $0     
}
/<\/tlLogic>/ {                
  print tl 
  tl=""
}
