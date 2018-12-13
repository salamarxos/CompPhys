clear all
close all

%% Setup
a = 1;
b = 100;
N = 99; % number of cells; N+1 is the number of grid points
L = b-a; % size of the domain
h = L/N; % grid spacing
x = linspace(a,b,N+1)'; % column vector of grid points

%% A matrix
e=ones(N,1);
A=spdiags([-e,2*e,-e],(-1:1),N,N);
A(1,:)=zeros(1,N); A(1,1)=1;
A(N,:)=zeros(1,N); A(N,N)=1;

f=@(x)[]; ua=...; ub=...;
b=h^2*f(x); b(1)=ua; b(N)=ub;

u = A\b;
plot(x,u)