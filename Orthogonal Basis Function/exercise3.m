% ----------------------------------------------
% WP : orthogonal and periodical basis functions
% file : exercise3.m
% author: Cesare De Cal
% ----------------------------------------------

cosMultiplier = 2;

% Function given by exercise. Tweak cosMultiplier above
func = @(multiplier, x) cos(multiplier*x);

% Chebyshev compact-form formula
chebyshevFunction = @(i, x) cos(i*acos(x));

degree = 6;
nrOfPoints = degree + 1;

% Calculate roots of Chebyshev polynomial
roots = 1:nrOfPoints;
for index = 1:nrOfPoints
    cosNumerator = (2*index-1)*pi;
    cosDenominator = 2*nrOfPoints;
    roots(index) = cos(cosNumerator/cosDenominator);
end

% Calculate coefficients of Chebyshev polynomial
% Rescale interval from [-pi, pi] to [-1, 1] by
% multiplying argument by pi
coefficients = 1:nrOfPoints;
for j = 1:nrOfPoints
    % Sum
    sum = 0;
    for k = 1:nrOfPoints
        root = roots(k);
        functionEvaluation = func(cosMultiplier, pi*root);
        chebyRes = chebyshevFunction(j-1, root);
        sum = sum + functionEvaluation*chebyRes;
    end
    coefficients(j) = (2/nrOfPoints)*sum;
end

% Calculate associated y values for roots
rootsY = cos(cosMultiplier*pi*roots);

% Compute Y points
nrGraphXPoints = 1000;
computedYValues = 1:nrGraphXPoints;
x = linspace(-1,1,nrGraphXPoints);
firstCoeff = coefficients(1)/2;
for r = 1:nrGraphXPoints
    point = x(r);
    sum = 0;
	for j = 1:nrOfPoints
        coefficient = coefficients(j);
        chebyRes = chebyshevFunction(j-1, point);
		sum = sum + coefficient*chebyRes;
    end
	computedYValues(r) = sum - firstCoeff;
end

'Chebyshev polynomial roots:'
roots'

'Chebyshev polynomial coefficients:'
coefficients'

'Y values of root:'
rootsY'

% Plotting
% Roots
plot(roots, rootsY, 'o', 'LineWidth', 1)
hold on
% Actual function
plot(x, func(cosMultiplier, pi*x), 'LineWidth', 1)
hold on
% Chebyshev Polynomial Approximation
plot(x, computedYValues, 'LineWidth', 1)
hold off
axis([-1 1 -1.5 1.5])
grid on
l = legend( 'Chebyshev Node', 'cos(2x)', 'Chebyshev Approximation');
ylabel('y')
xlabel('x')