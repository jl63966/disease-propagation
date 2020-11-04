%% SDS322 Disease Propagation

mex main.cpp

n = 40000; %population size
d = 8; %disease duration
r = 0.15; %transfer probability

input = [n,d,r];

sick = main(input);