function [A, time] = BMatchingSolver(W, b, X, Y, weightType, cacheSize, flags)

% solves for the maximum weight b-matching
% W is the weight matrix (option 1)
% b is the vector of target degrees
% X is the first bipartition (option 2)
% Y is the second bipartition (option 2)
% weightType is 1 for negative Euclidean distance, 2 for inner product
% cacheSize is the size of the weight cache, default is 2*sqrt(m+n)
% calls mex version if mex version is compiled and in current path

[m, n] = size(W);
if exist('weightType', 'var') && ~isempty(weightType) && ismember(weightType, [1 2])
    m = size(X,1);
    n = size(Y,1);
end

global tmp_dir
if isempty(tmp_dir)
    tmp_dir = '~/tmp';
end

global bmatchingsolver
if isempty(bmatchingsolver)
    bmatchingsolver = '~/Dropbox/workspace/BMatchingSolver/Release/BMatchingSolver';
end

persistent problem_id;
if isempty(problem_id)
    problem_id = uint32(randi(9999));
else
    problem_id = uint32(mod(problem_id + randi(9999), 100000));
end

outFile = sprintf('%s/tmp_%d_output.txt', tmp_dir, problem_id);
degFile = sprintf('%s/tmp_%d_degrees.txt', tmp_dir, problem_id);
dlmwrite(degFile, b, 'precision', '%9.0f');

if (m == n && length(b) == m)
    % assume unipartite
    cmd = sprintf('%s -n %d -d %s -o %s', bmatchingsolver, m, ...
        degFile, outFile);
    N = m;
else
    % bipartite
    cmd = sprintf('%s -n %d --bipartite %d -d %s -o %s', bmatchingsolver, m+n, m, ...
        degFile, outFile);
    N = m+n;
end

if ~isempty(W)
    weightFile = sprintf('%s/tmp_%d_weights.txt', tmp_dir, problem_id);
    save(weightFile, 'W', '-ascii', '-double');
    
    cmd = sprintf('%s -w %s', cmd, weightFile);
elseif exist('weightType', 'var')
    dataFile = sprintf('%s/tmp_%d_data.txt', tmp_dir, problem_id);
    data = [X; Y];
    save(dataFile, 'data', '-ascii', '-double');
    
    cmd = sprintf('%s -x %s -t %d -D %d', cmd, dataFile, weightType,...
        size(data,2));
end

% add cache size parameter
if ~exist('cacheSize', 'var')
    cacheSize = round(2*sqrt(m+n));
end
cmd = sprintf('%s -c %d', cmd, cacheSize);

if exist('flags', 'var')
    cmd = sprintf('%s %s', cmd, flags);
end

tic;
system(cmd);
time = toc;

IJ = dlmread(outFile, ' ') + 1;
A = sparse(IJ(:,1), IJ(:,2), true(size(IJ,1),1), N, N);

delete(degFile);
if (exist('weightFile', 'var'))
    delete(weightFile);
end
if (exist('dataFile', 'var'))
    delete(dataFile);
end
delete(outFile);

