This software solves maximum weight b-matchings using fast belief 
propagation. It is provided as-is, with no warranty, and can be freely 
used for scientific research. Please contact me at bert@cs.columbia.edu if 
you want to use it for commercial reasons. 

If you use this code in research for publication, please cite the paper 
"Loopy Belief Propagation for Bipartite Maximum Weight b-Matching" by 
Bert Huang and Tony Jebara.

Compile the software by using the makefile in the "Release" directory, 
which will create a binary BMatchingSolver program. Or if you wish to use 
the static methods in the BMatchingLibrary as a dynamic library, use the
makefile in "Shared Library", which creates a dylib file.

See the "html" directory for documentation. 

Please send questions, comments to bert@cs.columbia.edu. 

See shell script examples/runExamples.sh for how to call the command line tool, and see the matlab script tester.m for how to call the matlab functions.

Usage: BMatchingSolver <options>
-w, --weights	weight matrix file
-d, --degree	degree file
-x, --data	node descriptor file
-o, --output_file	output file
-n, --total	total number of nodes
-D, --dimensions	dimensionality of node descriptors
-c, --cacheSize	number of cached weights per row
-b, --bipartite	number of nodes in first bipartition
-t, --weight_type	weight type (0 = matrix, 1 = negative Euclidean, 
                                    2 = inner product)
-i, --max_iter	maximum iterations of belief propagation to run
-B, --binary	use binary data files

The weight matrix file is a tab-delimited matrix ascii matrix of size nxn
Alternatively, you can give node descriptor (feature vectors) of size nxd.
The degree file is a file of ascii numbers, one per line, indicating the 
target degree for each node. Parameter n is the total number of nodes in
your input graph, and if the graph is bipartite, parameter b is the number
of nodes in the first bipartition.

A number of matlab toolbox functions are in the matlab directory:

bdmatch_augment.m - create an augmented weight matrix for bd-matching using
                    auxiliary nodes
BMatchingSolver.cpp - mex c++ file for direct matlab interface
BMatchingSolver.mexmaci64 - 64-bit mac binary for mex version
BMatchingSolverCmd.m - command line wrapper that calls the CLI BMatchingSolver
lprelax.m - much slower lp relaxation solver for bd-matchings
makeMex.m - script to compile the mex BMatchingSolver.cpp 
tester.m - tests the mex and the CLI versions against the lprelax on 
            various random problems of different sizes

