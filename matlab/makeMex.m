src_dir = '/Users/bert/Dropbox/workspace/BMatchingSolver/src/';

objects = {'IntSet', 
    'utils',
    'IndexHeap',
    'IntDoubleMap',
    'WeightFunction', 
    'FunctionOracle', 
    'EuclideanDistance', 
    'InnerProduct', 
    'WeightOracle',
    'OscillationDetector', 
    'BipartiteFunctionOracle', 
    'BipartiteMatrixOracle', 
    'MatrixOracle', 
    'BMatchingProblem',
    'BeliefPropagator', 
    'BMatchingLibrary'};

object_string = '';

for i = 1:length(objects)
    object_string = sprintf('%s%s%s.cpp ', ...
        object_string, src_dir, objects{i});
end
%%

cmd = sprintf('mex -O -D_MEX_HACK -I%s -O BMatchingSolver.cpp %s', src_dir, object_string);

eval(cmd);

delete *.o *~;

