#/bin/bash count.sh c2smalaga.net.xml /home/aco/Trafico/dosSemaforosmalaga/ /home/aco/Trafico/ c2smalaga.rou.xml luego redireccionar a una variable count
awk -f $3$"extractTLsforANet.awk" $2$1 | awk -f $3$"countLogics.awk"
