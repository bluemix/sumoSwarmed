#!/bin/bash
# /bin/bash intialization.sh nombreDeLaRed directorioDeLaRed directorioDeLasAWKs nombreDelArchivodeRoutas
# no olvidarse de poner la / al final de cada directorio
# ejemplo :/bin/bash initialization.sh c2smalaga.net.xml malaga-alameda/ . c2smalaga.rou.xml
awk -f $3$"extractTLsforANet.awk" $2$1 | awk -f $3$"countLogics.awk" >count.txt
count=$(cat count.txt)
awk -f $3$"extractTLsforANet.awk" $2$1 | awk -f $3$"extractIDfases.awk" -v netdir=$2 countTTLogic=$count
awk -f $3$"countVehicle.awk" $2$4
