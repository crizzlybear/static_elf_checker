#!/bin/bash
# read binaryName
binaryName="program2"
# readelf -h $binaryName | grep ""

#PIE
if file $binaryName | grep "pie executable"
    then
        echo "=> Pie enabled"
    else   
        echo "=> No Pie"
fi
#CANARY
if nm $binaryName | grep "_stack_chk_fail" 
    then
        echo "=> Canary enabled"
    else
        echo "=> Canary disabled / not needed"
fi
#NX
echo $(readelf -l $binaryName | grep "GNU_STACK" -A1)
if (readelf -l $binaryName | grep "GNU_STACK" -A1)|grep -e "RWE" -e "  E" -e "R E"
    then
        echo "=> Stack is executable"
    else
        echo "=> Stack is not executable"
fi
#RELro
#ASLR


