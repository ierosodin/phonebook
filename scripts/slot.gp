reset
set ylabel 'slots number'
set style fill solid
set title 'hash function (MOD=42737)'
set term png enhanced font 'Verdana,10'
set output 'slot.png'
set format x "%10.0f"
set xtic 2000
set xtics rotate by 45 right

plot [:42737][0:150]'slots.txt' using 1:2 with points title ''
