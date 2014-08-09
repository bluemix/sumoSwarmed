#!/bin/bash
# /bin/bash intialization.sh nombreDeLaRed directorioDeLaRed directorioDeLasAWKs nombreDelArchivodeRoutas
# no olvidarse de poner la / al final de cada directorio
# ejemplo :/bin/bash initialization.sh c2smalaga.net.xml malaga-alameda/ ./ c2smalaga.rou.xml
# ejemplo :/bin/bash $0=initialization.sh $1=c2smalaga.net.xml $2=malaga-alameda/ $3=. $4=c2smalaga.rou.xml

awk -f $3$"extractTLsforANet.awk" $2$1 | awk -f $3$"countLogics.awk" >count.txt
count=$(cat count.txt)
awk -f $3$"extractTLsforANet.awk" $2$1 | awk -f $3$"extractIDfases.awk" -v netdir=$2 countTTLogic=$count
awk -f $3$"countVehicle.awk" $2$4

#a="twoIntersections.net.xml"
#b="2-intersections/2/"
#c="./"
#d="twoIntersections.500.rou.xml"

#awk -f $c$"extractTLsforANet.awk" $b$a | awk -f $c$"countLogics.awk" > count.txt
#count=$(cat count.txt)
#echo "tl-logics (count) : " `echo` $count
#awk -f $c$"extractTLsforANet.awk" $b$a | awk -f $c$"extractIDfases.awk" -v netdir=$b countTTLogic=$count
#awk -f $c$"countVehicle.awk" $b$d
