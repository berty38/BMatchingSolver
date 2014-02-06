% test suite:
% - mex euclidean, inner product, matrix
% - cmd line euclidean, inner product, matrix
% - verbose and not verbose
% n = 1, 10, 50
% b = 1, 2, n,
% cache size = 0, 1 n
% compare against lprelax result

Nvec = [2 10 50];

d = 20;

for i = 1:length(Nvec)
    
    n = Nvec(i);
    
    Cvec = [0 1 n];
    bvec = [1 ceil(n/5) n];
    
    for c = 1:length(Cvec)
        cacheSize = Cvec(c);
        
        for j = 1:length(bvec)
            for s = 1:3
                if (s == 1)
                    % weight matrix
                    lpW = randn(n);
                    W = lpW;
                    X = [];
                    Y = [];
                    weightType = 0;
                elseif (s == 2)
                    % euclidean
                    X = randn(n, d);
                    Y = randn(n, d);
                    W = [];
                    
                    selfX = sum(X.^2,2);
                    selfY = sum(Y.^2,2);
                    lpW = -sqrt(bsxfun(@plus, selfX, selfY') - 2*X*Y');
                    weightType = 1;
                elseif (s == 3)
                    % inner product
                    X = randn(n,d);
                    Y = randn(n,d);
                    W = [];
                    lpW = X*Y';
                    weightType = 2;
                end
                
                b = bvec(j)*ones(2*n,1);
                lpsol = round(lprelax(lpW, true(n), b, b));
                
                mexsol = BMatchingSolver(W, b, X, Y, weightType, cacheSize);
                mexsol = mexsol(1:n, n+1:end);
                cmdsol = BMatchingSolverCmd(W, b, X, Y, weightType, cacheSize);
                cmdsol = cmdsol(1:n, n+1:end);
                
                subplot(211);
                imagesc(lpsol);
                subplot(212);
                imagesc(mexsol);
                
                if (nnz(mexsol - lpsol) || nnz(mexsol - cmdsol))
                    fprintf('different solution for type %d, n = %d, b = %d, c = %d\n', s, n, bvec(j), cacheSize);
                    nnz(mexsol-lpsol)
                    nnz(mexsol-cmdsol)
                    nnz(lpsol-cmdsol)
                    pause
                else
                    fprintf('type %d, n = %d, b = %d, c = %d \t OK\n', s, n, bvec(j), cacheSize);
                end
                
                drawnow;
            end
        end
    end
end
%%
fprintf('Running with verbose on: mex version\n');
n = 50;
d = 5;
X = randn(n, d);
Y = randn(n, d);

b = ones(2*n,1);

BMatchingSolver([], b, X, Y, weightType, cacheSize, true);

BMatchingSolverCmd([], b, X, Y, weightType, cacheSize, '-v');

%% comparing running times
fprintf('Running on larger size and dimensionality input and measuring running time (standby...)\n');
n = 1024;
d = 784;
X = randn(n, d);
Y = randn(n, d);
cacheSize = 100;

b = 4*ones(2*n,1);

tic;
BMatchingSolver([], b, X, Y, weightType, cacheSize);
mextime = toc;

tic;
BMatchingSolverCmd([], b, X, Y, weightType, cacheSize);
cmdtime = toc;

fprintf('Mex took %f seconds, CMD line took %f seconds\n', mextime, cmdtime);


%% trying bdmatching

m = 50;
n = 100;

W = rand(m,n);

lb = [ones(m,1); zeros(n,1)];
ub = ones(m+n,1);

[W2, ~, ~, b, I, J] = bdmatch_augment(W, [], [], lb, ub);

mexsol = BMatchingSolver(W2, b, [], [], 0, 10);
mexsol = mexsol(I,J);

lpsol = round(lprelax(W, true(m,n), lb, ub));

if nnz(mexsol - lpsol)
   fprintf('different solution for bd-matching matrix\n');
else
    fprintf('bd-match weight matrix \t\tOK\n');
end

%%
m = 50;
n = 100;
d = 5;
X = floor(256*rand(m, d));
Y = floor(256*rand(n, d));

lb = [ones(m,1); zeros(n,1)];
ub = ones(m+n,1);

selfX = sum(X.^2,2);
selfY = sum(Y.^2,2);
W = -sqrt(bsxfun(@plus, selfX, selfY') - 2*X*Y');

lpsol = round(lprelax(W, true(m,n), lb, ub));

%[W, ~, ~, b, I, J] = bdmatch_augment(W, [], [], lb, ub);
%mexsol = BMatchingSolver(W, b, [], [], 1, 10);

[~, X2, Y2, b, I, J] = bdmatch_augment([], X, Y, lb, ub);

mexsol = BMatchingSolver([], b, X2, Y2, 1, 10);
mexsol = mexsol(I,J);

if nnz(mexsol - lpsol)
   fprintf('different solution for bd-matching Euclidean dist.\n');
else
    fprintf('bd-match Euclidean dist. \tOK\n');
end

