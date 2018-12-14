clear all
close all

a = 1;
b = 40;
N = 40; % number of cells; N+1 is the number of grid points
L = b-a; % size of the domain
h = L/N; % grid spacing
r0 = 5.29;
x = linspace(a,b,N+1)'; % column vector of grid points

phi_f = @(x) (1./x)-(1+1./x).*exp(-2.*x);  % inline function for the exact solution
rho_f = @(x)-((4.*x.*exp(-2.*x./r0))./r0^3); % inline function for the exact right-hand-side
% rho_f = @(x)(8.*x.*exp((-2.*x).*(r0+x)./r0)./r0^4);

phi_exact = phi_f(x); % exact solution at the grid points

alpha = phi_f(a); % boundary condition
beta = phi_f(b); % boundary condition

rho = rho_f(x(2:N)); % exact rho at the grid points
rho(1) = rho(1) + alpha/h^2; % add boundary term
rho(N-1) = rho(N-1) + beta/h^2; % add boundary term

dA = diag( 2*ones(1,N-1) ); % diagonal matrix
dAp1 = diag( -1*ones(1,N-2), 1 ); % super-diagonal matrix
dAm1 = diag( -1*ones(1,N-2), -1 ); % sub-diagonal matrix
A = (dA + dAp1 + dAm1);
A = A/h^2;

eigv = eig(A); % for curiosity, we check the eigenvalues of A
phi = A\rho; % solving the linear system

solver_err = max( abs(A*phi - rho) );% Did the solver do his job?

phi_num = [alpha; phi; beta]; % enlarge the solution vector by the values at the boundary

plot(x,phi_exact,'b-',x,phi_num,'ro-');
xlim([a b]);
xlabel('r');
ylabel('\phi(x)');
legend('exact','numerical','location','northwest');