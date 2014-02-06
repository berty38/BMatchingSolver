function [W, X, Y, b, I, J] = bdmatch_augment(W, X, Y, lb, ub)
% function [W, X, Y, b] = bdmatch_mex(W, X, Y, lb, ub)
% creates augmented b-matching to solve bd-matching problem

b = ub;

auxcount = ub - lb;

maxaux = max(auxcount);

unused = maxaux - auxcount;

if ~isempty(W)
    [m,n] = size(W);
    
    W = [W zeros(m, maxaux); zeros(maxaux, n+maxaux)];
    if (m == n && length(lb) == m)
        % unipartite
        for i = 1:m
            W(i,end-unused(i)+1:end) = -inf;
            W(end-unused(i)+1:end,i) = -inf;
        end
        b = [b(:); -ones(maxaux,1)];
        I = 1:m;
        J = 1:m;
    else
        % bipartite
        for i = 1:m
            W(i,end-unused(i)+1:end) = -inf;
        end
        for i = 1:n
            W(end-unused(i+m)+1:end,i) = -inf;
        end
        b = [b(1:m); -ones(maxaux,1); b(m+1:end); -ones(maxaux,1)];
    
        I = 1:m;
        J = m+maxaux+1:m+maxaux+n;
    end
elseif ~isempty(X)
    [m,d] = size(X);
    [n,d] = size(Y);
    
    if any(unused(1:m) ~= unused(1)) || n > 0 && any(unused(m+1:end) ~= unused(m+1))
        error('This script can only handle Euclidean or inner product problems with the same lb and ub in each bipartition');
    end
    
    if (n > 0)
        % bipartite
        X = [X; nan(auxcount(m+1), d)];
        Y = [Y; nan(auxcount(1), d)];
        b = [b(1:m); -ones(auxcount(m+1),1); b(m+1:end); -ones(auxcount(1),1)];
        I = 1:m;
        J = m+auxcount(m+1)+1:m+auxcount(m+1)+n;
    else
        X = [X; nan(auxcount(1), d)];
        b = [b(:); -ones(auxcount(1),1)];
        I = 1:m;
        J = 1:m;
    end
end
