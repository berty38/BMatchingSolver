#!/bin/sh

echo ***********************************************
echo Running on unipartite weight matrix example
echo ***********************************************

../Release/BMatchingSolver -w uni_example_weights.txt -d uni_example_degrees.txt -n 10 -o uni_example_solution.txt -c 5 -v 1 

echo Solution: 
cat uni_example_solution.txt



echo ***********************************************
echo Running on bipartite Euclidean distance example
echo ***********************************************

../Release/BMatchingSolver -x euclid_bi_example_weights.txt -d euclid_bi_example_degrees.txt -n 20 -b 10 -D 3 -t 1 -o euclid_bi_example_solution.txt -c 5 -v 1 

echo Solution:
cat euclid_bi_example_solution.txt
