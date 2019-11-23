format long e

% To calculate the cos(value*x) you need to replace this value
value = 2;

T = @(j, x) cos(j * acos(x));

n = 6;
N = n+1;

data_x = 1:N;
for i = 1:N
	data_x(i) = cos(((2*i-1)*pi)/(2*N));
end
data_x'

coeff = zeros(1, N);
for i = 1:N
	for j = 0:n
		coeff(i) = coeff(i) + ( cos(value*pi*data_x(j+1)) * T(i-1, data_x(j+1)) );
	end
	coeff(i) = (2/N) * coeff(i);
end
coeff'

x_plot = -1:0.01:1;

approx_y = zeros(1, length(x_plot));
for i = 1:length(x_plot)
	for j = 0:n
		approx_y(i) = approx_y(i) + ( coeff(j+1) * T(j, x_plot(i)) );
	end
	approx_y(i) = approx_y(i) - (1/2 * coeff(1));
end

data_y = cos(value*pi*data_x);
data_y'

plot(data_x, data_y, 'o', 'LineWidth', 2) % Data
hold on
plot(x_plot, cos(value*pi*x_plot), 'LineWidth', 2) % cos(value*pi*x)
hold on
plot(x_plot, approx_y, 'LineWidth', 2) %Approximation
hold off

axis([-1 1 -1.3 1.3])
grid on

ylabel('Y')
xlabel('X')

str = strcat('cos(', num2str(value),'x)');
legend('Data', str, 'Chebyshev approximation', 'Location', 'Best')
title('Chebyshev approximation')