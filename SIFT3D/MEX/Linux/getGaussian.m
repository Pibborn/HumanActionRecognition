function SS = gaussianss(I,sigman,O,S,omin,smin,smax,sigma0)

% --------------------------------------------------------------------
% Input Validation
% --------------------------------------------------------------------
if(nargin < 6)
	error('Six arguments are required.') ;
end

if(~isreal(I) || ndims(I) > 3)
	error('I must be a real three dimensional matrix (HeightxWidthxFrame)') ;
end

if(smin >= smax)
	error('smin must be greather or equal to smax') ;
end

% --------------------------------------------------------------------
% Do the Job
% --------------------------------------------------------------------

% Scale multiplicative step
k = 2^(1/S) ;

% Lowe's convention: the scale (o,s)=(0,-1) has standard deviation : 1.6 
if(nargin < 7)
  sigma0 = 1.6 * k ;
end

dsigma0 = sigma0 * sqrt(1 - 1/k^2) ; % Scale step factor
sigman  = 0.5 ;                      % Nominal smoothing of the image

% Scale space structure
SS.O          = O ;
SS.S          = S ;
SS.sigma0     = sigma0 ;
SS.omin       = omin ;
SS.smin       = smin ;
SS.smax       = smax ;

% If mino < 0, multiply the size of the image.
% (The rest of the code is consistent with this.)
if omin < 0
	for o = 1 : -omin
		I = doubleSize(I) ;
	end
elseif omin > 0
	for o=1:omin
		I = halveSize(I) ;
	end
end

[M,N,T] = size(I) ;

% Index offset
so = -smin+1 ;

% --------------------------------------------------------------------
%                                                         First octave
% --------------------------------------------------------------------
%
% The first level of the first octave has scale index (o,s) =
% (omin,smin) and scale coordinate
%
%    sigma(omin,smin) = sigma0 2^omin k^smin 
%
% The input image I is at nominal scale sigman. Thus in order to get
% the first level of the pyramid we need to apply a smoothing of
%  
%   sqrt( (sigma0 2^omin k^smin)^2 - sigman^2 ).
%
% As we have pre-scaled the image omin octaves (up or down,
% depending on the sign of omin), we need to correct this value
% by dividing by 2^omin, getting
%e
%   sqrt( (sigma0 k^smin)^2 - (sigman/2^omin)^2 )
%

if(sigma0 * 2^omin * k^smin < sigman)
	warning('The nominal smoothing exceeds the lowest level of the scale space.') ;
end

SS.octave{1} = zeros(M,N,T,smax-smin+1) ;
tSigma = sqrt((sigma0*k^smin)^2  - (sigman/2^omin)^2);
SS.octave{1}(:,:,:,1)  = imgaussfilt3(I, ...
	[tSigma tSigma tSigma]) ;

for s=smin+1:smax
	% Here we go from (omin,s-1) to (omin,s). The extra smoothing
	% standard deviation is
	%
	%  (sigma0 2^omin 2^(s/S) )^2 - (simga0 2^omin 2^(s/S-1/S) )^2
	%
	% Aftred dividing by 2^omin (to take into account the fact
    % that the image has been pre-scaled omin octaves), the 
    % standard deviation of the smoothing kernel is
    %
	%   dsigma = sigma0 k^s sqrt(1-1/k^2)
    %
	dsigma = k^s * dsigma0 ;
	SS.octave{1}(:,:,:,s +so) = ...
		imgaussfilt3(squeeze(...
		SS.octave{1}(:,:,:,s-1 +so)...
		), [dsigma dsigma dsigma])  ;
end


% --------------------------------------------------------------------
%                                                        Other octaves
% --------------------------------------------------------------------

for o=2:O  
	% We need to initialize the first level of octave (o,smin) from
	% the closest possible level of the previous octave. A level (o,s)
    % in this octave corrsponds to the level (o-1,s+S) in the previous
    % octave. In particular, the level (o,smin) correspnds to
    % (o-1,smin+S). However (o-1,smin+S) might not be among the levels
    % (o-1,smin), ..., (o-1,smax) that we have previously computed.
    % The closest pick is
    %
	%                       /  smin+S    if smin+S <= smax
	% (o-1,sbest) , sbest = |
	%                       \  smax      if smin+S > smax
	%
	% The amount of extra smoothing we need to apply is then given by
	%
	%  ( sigma0 2^o 2^(smin/S) )^2 - ( sigma0 2^o 2^(sbest/S - 1) )^2
	%
    % As usual, we divide by 2^o to cancel out the effect of the
    % downsampling and we get
    %
	%  ( sigma 0 k^smin )^2 - ( sigma0 2^o k^(sbest - S) )^2
    %
    % fprintf('Octave : %d\n',o);
	sbest = min(smin + S, smax) ;
	TMP = halveSize(squeeze(SS.octave{o-1}(:,:,:,sbest+so))) ;
	target_sigma = sigma0 * k^smin ;
	  prev_sigma = sigma0 * k^(sbest - S) ;
          
	if(target_sigma > prev_sigma)
        tSigma = sqrt(target_sigma^2 - prev_sigma^2) ;
          TMP = imgaussfilt3(TMP, [tSigma tSgima tSigma]) ;
	end
	[M,N,T] = size(TMP) ;
	
	SS.octave{o} = zeros(M,N,T,smax-smin+1) ;
	SS.octave{o}(:,:,:,1) = TMP ;

	for s=smin+1:smax
		% The other levels are determined as above for the first octave.		
		dsigma = k^s * dsigma0 ;
		SS.octave{o}(:,:,:,s +so) = ...
			imgaussfilt3(squeeze(...
			SS.octave{o}(:,:,:,s-1 +so)...
			), [dsigma dsigma dsigma])  ;
	end
	
end

% -------------------------------------------------------------------------
%                                                       Auxiliary functions
% -------------------------------------------------------------------------
function J = doubleSize(I)
[M,N,T]=size(I) ;
J = zeros(2*M,2*N,2*T) ;
J(1:2:end,1:2:end,1:2:end) = I;
J(1:2:end,1:2:end,2:2:end) = I;
J(1:2:end,2:2:end,1:2:end) = I;
J(1:2:end,2:2:end,2:2:end) = I;
J(2:2:end,1:2:end,1:2:end) = I;
J(2:2:end,1:2:end,2:2:end) = I;
J(2:2:end,2:2:end,1:2:end) = I;
J(2:2:end,2:2:end,2:2:end) = I;

function J = halveSize(I)
J=I(1:2:end,1:2:end,1:2:end) ;
