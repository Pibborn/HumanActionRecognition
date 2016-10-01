% function V = sphere_project(v,r,c)
function V = sphere_project(varargin)
% sphere_project - project point X,Y,Z to the surface of sphere radius r
%
% V = sphere_project(v,r,c)
%
% Cartesian inputs:
% v is the vertex matrix, Nx3 (XYZ)
% r is the sphere radius, 1x1 (default 1)
% c is the sphere centroid, 1x3 (default 0,0,0)
%
% XYZ are converted to spherical coordinates and their radius is
% adjusted according to r, from c toward XYZ (defined with theta,phi)
%
% V is returned as Cartesian 3D coordinates
%

% $Revision: 1.1 $ $Date: 2004/11/12 01:32:36 $

% Licence:  GNU GPL, no implied or express warranties
% History:  06/2002, Darren.Weber_at_radiology.ucsf.edu, created
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

if length(varargin) == 1
    v = varargin{1};
    x0 = 0;
    y0 = 0;
    z0 = 0;
    r = 1;
elseif length(varargin) == 2
    v = varargin{1};
    r = varargin{2};
    x0 = 0;
    y0 = 0;
    z0 = 0;
else
    v = varargin{1};
    r = varargin{2};
    c = reshape(varargin{3},1,3);
end

% if ~exist('v','var'),
%     msg = fprintf('SPHERE_PROJECT: No input vertices (X,Y,Z)\n');
%     error(msg);
% end

X = v(:,1);
Y = v(:,2);
Z = v(:,3);

xo = c(1);
yo = c(2);
zo = c(3);
% if ~exist('c','var'),
%     xo = 0;
%     yo = 0;
%     zo = 0;
% else
%     xo = c(1);
%     yo = c(2);
%     zo = c(3);
% end
%
% if ~exist('r','var'), r = 1; end

% alternate method is to use unit vector of V
% [ n = 'magnitude(V)'; unitV = V ./ n; ]
% to change the radius, multiply the unitV
% by the radius required.  This avoids the
% use of arctan functions, which have branches.


% Convert Cartesian X,Y,Z to spherical (radians)
theta = atan2( (Y-yo), (X-xo) );
phi   = atan2( sqrt( (X-xo).^2 + (Y-yo).^2 ), (Z-zo) );
% do not calc: r = sqrt( (X-xo).^2 + (Y-yo).^2 + (Z-zo).^2);

%   Recalculate X,Y,Z for constant r, given theta & phi.
R = ones(size(phi)) * r;
x = R .* sin(phi) .* cos(theta);
y = R .* sin(phi) .* sin(theta);
z = R .* cos(phi);

V = [x y z];

return