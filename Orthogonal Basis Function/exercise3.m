% ----------------------------------------------
% WP : orthogonal and periodical basis functions
% file : exercise3.m
% author: Cesare De Cal
% ----------------------------------------------

degree = 6
nrOfPoints = degree + 1

% Calculate roots of Chebyshev polynomial
roots = 1:nrOfPoints;
for index = 1:nrOfPoints
    cosNumerator = (2*index-1)*pi
    cosDenominator = 2*nrOfPoints
    roots(index) = cos(cosNumerator/cosDenominator)
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
        functionEvaluation = cos(2*pi*root)
        chebyshev = cos((j-1)*acos(root))
        sum = sum + functionEvaluation*chebyshev
    end
    coefficients(j) = (2/nrOfPoints)*sum
end

'Chebyshev polynomial coefficients:'
coefficients'