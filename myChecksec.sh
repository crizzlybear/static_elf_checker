#!/bin/bash
binaryName=$1
# binaryName="program2"
# readelf -h $binaryName | grep ""
PIE=""
CANARY=""
NX=""
RELRO=""
#PIE
if [[ $(file $binaryName | grep "pie executable") ]]
    then
        # echo "=> Pie enabled"
        PIE="Pie Enabled"
    else   
        # echo "=> No Pie"
        PIE="No Pie"
fi
#CANARY
if [[ $(nm $binaryName | grep "_stack_chk_fail") ]]
    then
        # echo "=> Canary enabled"
        CANARY="Canary Enabled"
    else
        # echo "=> Canary disabled / not needed"
        CANARY="No Canary"
fi
#NX
# echo $(readelf -l $binaryName | grep "GNU_STACK" -A1)
if [[ $((readelf -l $binaryName | grep "GNU_STACK" -A1)|grep -e "RWE" -e "  E" -e "R E") ]]
    then
        # echo "=> Stack is executable"
        NX="Stack is executable"
    else
        # echo "=> Stack is not executable"
        NX="Stack is not executable"
fi
#RELro

if [[ $((readelf -l $binaryName | grep "GNU_RELRO")|grep -e "R*") ]];
    then
        # echo "=> Partial OR Full Relro"
        RELRO="Partial OR Full Relro"
    else
        # echo "=> No Relro"
        RELRO="No Relro"
fi
#ASLR

echo "PIE:" $PIE
echo "CANARY:" $CANARY
echo "NX:" $NX
echo "RELRO:" $RELRO
