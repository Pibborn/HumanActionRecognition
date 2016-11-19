function dss = diffss(ss)

% _ _ _ _ _
% _ _ _ _ _  >  - - - - -
% _ _ _ _ _  >  - - - - -
% _ _ _ _ _  >  - - - - -
%   Gauss          DoG

dss.smin = ss.smin ;
dss.smax = ss.smax-1 ;
dss.omin = ss.omin ;
dss.O = ss.O ;
dss.S = ss.S ;
dss.sigma0 = ss.sigma0 ;

for o=1:dss.O
  % Can be done at once, but it turns out to be faster
  % this way
  [M,N,T,S] = size(ss.octave{o}) ;
  dss.octave{o} = zeros(M,N,T,S-1) ;
  for s=1:S-1
    dss.octave{o}(:,:,:,s) = ...
        ss.octave{o}(:,:,:,s+1) - ss.octave{o}(:,:,:,s) ;
  end
end
