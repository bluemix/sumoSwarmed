BEGIN {FS="\"";ORS=" ";sub(/^  */, "", idle); p=0;GvR=0}
/<phase /, />/{d=$2;aux=0;dr=0;dG=0;green=0;red=0;state=$4;phases=0;
split(state,s,"");
num=length(state);
for (i=0;i<=num;i++){if (s[i]=="r") {red++} else {if (s[i]=="G" || s[i]=="g"){green++}}}
if (red==0){red=1}
aux=d*(green/red);
GvR+=aux
}
END{print GvR}
