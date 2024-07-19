#!/bin/bash
binaryName=$1

# Filesize
Filesize=""
Filesize=$(du -hs $binaryName)
echo "Size: " $Filesize

# Also check strings, entropy, abnormal segments, check entry point * probably the most reliable method
#detect basic packers:
NumHeaders=$(readelf -h $binaryName | grep "Number of section headers:")
if [[ $NumHeaders =~ "2"( |$) ]] #regex
    then
        echo "Packed: Num headers =2 Maybe packed"
    else
        echo "Packed: Num headers >2 Maybe not packed"
fi
echo "Packer type:"
if [[ $(grep UPX\! $binaryName) ]]
# or hexdump -C <filename> |grep -C 1 UPX
    then
        echo "Maybe packed using UPX"
fi
if [[ $(objdump -x $binaryName | grep "pydata") ]]
# or readelf -x.rodata $binaryName | grep "Python VM"
    then
        echo "Maybe packed using PyInstaller"
fi
