function Y = my_mahalanobis(X,dist,varargin)
%my_mahalanobis: a helper function that computes the mahalanobis distance
% between observations in the X matrix. Much of the code is copy-pasted
% from pdist.m, but it uses nearestSPD.m to ensure that the covariance
% matrix is positive-definite. 

additionalArg = [];

if nargin < 3
   additionalArg = nancov(X);
   [T,flag] = chol(additionalArg);
    else
        additionalArg = varargin{1};
        if ~isequal(size(additionalArg),[p,p])
            error(message('stats:pdist:InvalidCov'));
        end
        %prepare the matrix via nearestSPD
        additionalArg = nearestSPD(additionalArg);
        %use cholcov because we also need to check whether the matrix is symmetric
        [T,flag] = cholcov(additionalArg,0);
end
if flag ~= 0
    error(message('stats:pdist:SingularCov'));
end
if ~issparse(X) 
     additionalArg = T \ eye(p);  %inv(T)
end

outClass = class(X);
Y = zeros(1,n*(n-1)./2, outClass);
k = 1;

for i = 1:n-1
    del = bsxfun(@minus, X(i,:), X((i+1):n,:));
    dsq = sum((del/T) .^ 2, 2);
    Y(k:(k+n-i-1)) = sqrt(dsq);
end


