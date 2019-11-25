% ----------------------------------------------
% WP : orthogonal and periodical basis functions
% file : exercise3.m
% author: Cesare De Cal
% ----------------------------------------------

% Function given by exercise. Multiplier can be 2 or 4
func = @(multiplier, x) cos(multiplier*x) 

% Chebyshev compact-form formula
chebyshevFunction = @(index, x) cos(index*acos(x))
chebyshevRootFunction = @(index, nrOfPoints) cos(((2*index-1)*pi)/(2*nrOfPoints))

degree = 6
nrOfPoints = degree + 1

% Calculate roots of Chebyshev polynomial
roots = 1:nrOfPoints;
for index = 1:nrOfPoints
    roots(index) = chebyshevRootFunction(index-1, nrOfPoints)
end

'Chebyshev polynomial roots:'
roots'

% Calculate coefficients of Chebyshev polynomial
% Rescale interval from [-pi, pi] to [-1, 1] by
% multiplying argument by pi
coefficients = 1:nrOfPoints
for j = 1:nrOfPoints
    % Sum
    sum = 0
    for k = 1:nrOfPoints
        root = roots(k)
        functionEvaluation = func(2, pi*root)
        chebyRes = chebyshevFunction(j-1, root)
        sum = sum + functionEvaluation*chebyRes
    end
    coefficients(j) = (2/nrOfPoints)*sum
end

'Chebyshev polynomial coefficients:'
coefficients'

% Calculate associated y values for roots
rootsY = 1:nrOfPoints;
firstCoeff = coefficients(1)/2;
for r = 1:nrOfPoints
    rootX = roots(r)
    sum = 0;
	for j = 1:nrOfPoints
        coefficient = coefficients(j)
        chebyRes = chebyshevFunction(j-1, rootX)
		sum = sum + coefficient*chebyRes;
    end
	rootsY(r) = sum - firstCoeff;
end

'Y values of root:'
rootsY'

% Create array of equi-distant points to plot
% linspace = linspace(-1,1,1000)

% Plotting