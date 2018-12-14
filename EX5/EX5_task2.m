clc
clear all 
close all

a = -2;
b = 3;
L = b-a; % Interval Length
N = 100; % No of points
x = linspace(a,b,N)'; % Coordinate vector
h = L/N; % Coordinate step 
e = ones(N,1); A = spdiags([e -2*e e],[-1 0 1],N,N)/h^2;
% Total Hamiltonia
H = -1/2*A;
for i=1:length(H)
   H(i,i) 
end
% Find lowest nmodes eigenvectors and eigenvalues of sparse matrix
nmodes = 4; options.disp = 0;
[V,E] = eigs(H,nmodes,'sa',options); % find eigs
[E,ind] = sort(diag(E));% convert E to vector and sort low to high
V = V(:,ind); % rearrange correspo  nding eigenvectors
% Generate plot of lowest energy eigenvectors V(x) and U(x)
Usc = U*max(abs(V(:)))/max(abs(U)); % rescale U for plotting
plot(x,V,x,Usc,'--k'); % plot V(x) and rescaled U(x)
ylim([-0.4 0.2])
% Add legend showing Energy of plotted V(x)
lgnd_str = [repmat('eigVal = ',nmodes,1),num2str(E)];
legend(lgnd_str) % place lengend string on plot
