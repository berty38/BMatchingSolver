function [f, A, b] = lprelax(W, mask, lb, ub)

N = size(W,1);

if (N ~= length(lb))
    [m,n] = size(W);
    W = [sparse(m, m) W; W' sparse(n, n)];
    mask = [sparse(m, m) mask; mask' sparse(n, n)];
    N = n+m;
    bipartite = true;
else
    bipartite = false;
end

f = -nonzeros(triu(W.*mask));

[I,J] = find(triu(mask));


A = zeros(2*N, nnz(triu(mask)))';
b = zeros(2*N, 1);

for i=1:N
    A(I==i | J==i, i) = 1;
    b(i) = ub(i);
    
    A(I==i | J==i, i+N) = -1;
    b(i+N) = -lb(i);
end
A = A';

if (nargout==1)
    
    options.Display = 'none';
    
    x = linprog(f, A, b, [], [], zeros(size(f)), ones(size(f)), ...
        zeros(size(f)), options);
    
    X = sparse(I, J, x, N, N);
    
    f = X+triu(X,1)';
    
    if bipartite
        f = f(1:m, m+1:end);
    end
end