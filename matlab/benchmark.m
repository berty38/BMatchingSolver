cmd = '~/Dropbox/workspace/BMatchingSolver/Release/BMatchingSolver -n 10000 --bipartite 5000 -d ~/tmp/benchdegrees.txt -o ~/tmp/benchoutput.txt -x ~/tmp/benchdata.txt -t 1 -D 784 -c 1000 -v'

tic
system(cmd);
toc
cd ..

