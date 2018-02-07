n = 10;
d = 5;

X = rand(n,d);
Y = rand(n,d);

b = ones(2*n, 1);


fprintf('Starting test. Hit ctrl-c to exit\n');
while(1)
    A = BMatchingSolver([], b, X, Y);
end


