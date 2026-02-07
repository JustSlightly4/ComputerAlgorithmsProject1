#!/bin/bash

echo "Dijkstras Algorithm with a binary heap" >> Dijkstras25.txt

# Define the sizes and repetitions
sizes=(10000 20000 30000)
reps=3

for size in "${sizes[@]}"; do
    for ((i=1; i<=reps; i++)); do
        ./a.out Heap Dijk $size 25 0 >> Dijkstras25.txt
    done
done

# Append a blank line
echo "" >> Dijkstras25.txt
echo "Dijkstras Algorithm with a fibonacci heap" >> Dijkstras25.txt

for size in "${sizes[@]}"; do
    for ((i=1; i<=reps; i++)); do
        ./a.out Fib Dijk $size 25 0 >> Dijkstras25.txt
    done
done

# Append a blank line
echo "" >> Dijkstras25.txt
echo "Dijkstras Algorithm with a pairing heap" >> Dijkstras25.txt

for size in "${sizes[@]}"; do
    for ((i=1; i<=reps; i++)); do
        ./a.out Pair Dijk $size 25 0 >> Dijkstras25.txt
    done
done

# Append a blank line
echo "" >> Dijkstras25.txt