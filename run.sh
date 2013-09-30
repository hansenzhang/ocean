#!/bin/bash
avg=1
seqavg=1
paravg=1

echo "Running p2 with flags $1 $2 $3 $4 $5"
for i in {1..10}
do
    output=(`p2 $1 $2 $3 $4 $5`)
    seq=$(echo "scale=4; ${output[12]}/900000000" | bc)
    par=$(echo "scale=4; ${output[15]}/900000000" | bc)
    val=$(echo "scale=5; $seq/$par" | bc)
    echo "test" $i"....."speedup: $val   "    seq:" $seq "sec    " par: $par" sec"
    avg=("${avg[@]}" "$val")
    
    seqavg=("${seqavg[@]}" "$seq")
    paravg=("${paravg[@]}" "$par")
done
unset avg[0]
unset seqavg[0]
unset paravg[0]

total=0
seqtotal=0
partotal=0

for var in "${avg[@]}"
do
    total=$(echo "scale=5; $total + $var" | bc)
done
for var in "${seqavg[@]}"
do
    seqtotal=$(echo "scale=5; $seqtotal + $var" | bc)
done
for var in "${paravg[@]}"
do
    partotal=$(echo "scale=5; $partotal + $var" | bc)
done

average=$(echo  "scale=5; $total / 10.0 " | bc)
seqaverage=$(echo  "scale=4; $seqtotal / 10.0 " | bc)
paraverage=$(echo  "scale=4; $partotal / 10.0 " | bc)
echo averages....speedup: $average   "    seq:" $seqaverage "sec     par: "$paraverage "sec"
