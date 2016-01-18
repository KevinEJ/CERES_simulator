clear all;

q_0 = 5;
q_s = 1;
var = [0.2]
sigma = q_0 / (1+2.5*var/3) * (var/3);
lambda_0 = 10^(-6);

lambda = [];

for i = 0:5
    lambda = [lambda lambda_0*exp(i*sigma/q_s)];
end

lambda