clear all
close all
clc

xa = 0;
xb = 20;
N = 100; % number of cells; N+1 is the number of grid points
L = xb-xa; % size of the domain
h = L/N; % grid spacing
r0 = 5.29;
x = linspace(xa,xb,N+1)'; % column vector of grid points

e=ones(N+1,1);
A=spdiags([-e,2*e,-e],(-1:1),N+1,N+1);
A(1,:)=zeros(1,N+1); A(1,1)=1;
A(N+1,:)=zeros(1,N+1); A(N+1,N+1)=1;
g = @(x) x.*((1./x)-(1+1./x).*exp(-2.*x));  % inline function for the exact solution
% g = @(x) (-4.*exp(-2.*x).*x - 2.*exp(-2.*x)-4.*exp(-2.*x).*x.^2-4.*exp(-2.*x).*x.^3+2)./x.^3; 
%  g = @(x) -4.*exp(-2.*x).*x;
f = @(x)((4.*x.*exp((-2.*x)./r0))./r0^3); % inline function for the exact right-hand-side

phi_exact = g(x); % exact solution at the grid points

ua = 0; % boundary condition
ub = 1; % boundary condition

b=h^2*f(x);
b(1)=ua; b(end)=ub;
% for i=2:N
% b(i) = (f(i+1)-2*f(i)+f(i-1))/h^2; 
% end

eigv = eigs(A); % for curiosity, we check the eigenvalues of A
phi = A\b; % solving the linear system


% plot(x,phi_exact,'b-');
plot(x,phi_exact,'b-',x,phi,'ro-');
xlim([0 xb]);
ylim([0 1.2])
xlabel('r');
ylabel('\phi(x)');
legend('exact','numerical','location','northwest');