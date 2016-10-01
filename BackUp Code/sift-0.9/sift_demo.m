% SIFT_DEMO  Demonstrate SIFT code (1)
%   This demo computes the SIFT descriptor on a pair of well known
%   test images and compares our results with got Lowe's one The
%   computed and original descriptors are very similar.
%
%   See also SIFT_DEMO2().

% AUTORIGHTS
% Copyright (c) 2006 The Regents of the University of California.
% All Rights Reserved.
% 
% Created by Andrea Vedaldi
% UCLA Vision Lab - Department of Computer Science
% 
% Permission to use, copy, modify, and distribute this software and its
% documentation for educational, research and non-profit purposes,
% without fee, and without a written agreement is hereby granted,
% provided that the above copyright notice, this paragraph and the
% following three paragraphs appear in all copies.
% 
% This software program and documentation are copyrighted by The Regents
% of the University of California. The software program and
% documentation are supplied "as is", without any accompanying services
% from The Regents. The Regents does not warrant that the operation of
% the program will be uninterrupted or error-free. The end-user
% understands that the program was developed for research purposes and
% is advised not to rely exclusively on the program for any reason.
% 
% This software embodies a method for which the following patent has
% been issued: "Method and apparatus for identifying scale invariant
% features in an image and use of same for locating an object in an
% image," David G. Lowe, US Patent 6,711,293 (March 23,
% 2004). Provisional application filed March 8, 1999. Asignee: The
% University of British Columbia.
% 
% IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY
% FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES,
% INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND
% ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF CALIFORNIA HAS BEEN
% ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. THE UNIVERSITY OF
% CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
% LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
% A PARTICULAR PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
% BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATIONS TO PROVIDE
% MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

I1=imreadbw('data/img3.jpg') ; 
I2=imreadbw('data/img5.jpg') ;

I1=I1-min(I1(:)) ;
I1=I1/max(I1(:)) ;
I2=I2-min(I2(:)) ;
I2=I2/max(I2(:)) ;

fprintf('Computing frames and descriptors.\n') ;
[frames1,descr1,gss1,dogss1] = sift( I1, 'Verbosity', 1 ) ;
[frames2,descr2,gss2,dogss2] = sift( I2, 'Verbosity', 1 ) ;

figure(11) ; clf ; plotss(dogss1) ; colormap gray ;
figure(12) ; clf ; plotss(dogss2) ; colormap gray ;
drawnow ;

figure(2) ; clf ;
subplot(1,2,1) ; imagesc(I1) ; colormap gray ;
hold on ;
h=plotsiftframe( frames1 ) ; set(h,'LineWidth',2,'Color','g') ;
h=plotsiftframe( frames1 ) ; set(h,'LineWidth',1,'Color','k') ;

subplot(1,2,2) ; imagesc(I2) ; colormap gray ;
hold on ;
h=plotsiftframe( frames2 ) ; set(h,'LineWidth',2,'Color','g') ;
h=plotsiftframe( frames2 ) ; set(h,'LineWidth',1,'Color','k') ;

fprintf('Computing matches.\n') ;
% By passing to integers we greatly enhance the matching speed (we use
% the scale factor 512 as Lowe's, but it could be greater without
% overflow)
descr1=uint8(512*descr1) ;
descr2=uint8(512*descr2) ;
tic ; 
matches=siftmatch( descr1, descr2 ) ;
fprintf('Matched in %.3f s\n', toc) ;

figure(3) ; clf ;
plotmatches(I1,I2,frames1(1:2,:),frames2(1:2,:),matches) ;
drawnow ;

% --------------------------------------------------------------------
% Compare to Lowe's implementation
% --------------------------------------------------------------------
fprintf('Lowe''s original code...\n') ;
[lframes1,ldescr1] = siftread('data/img3.sift') ;
[lframes2,ldescr2] = siftread('data/img5.sift') ;


fprintf('Computing matches (using double precision descriptors).\n') ;
tic ;
lmatches=siftmatch( ldescr1, ldescr2 ) ;
fprintf('Matched in %.3f s\n', toc) ;

figure(5) ; clf ;
plotmatches(I1,I2,lframes1(1:2,:),lframes2(1:2,:),lmatches) ;

% --------------------------------------------------------------------
% Match to Lowe's implementation
% --------------------------------------------------------------------
ldescr1=uint8(ldescr1) ;
ldescr2=uint8(ldescr2) ;

fprintf('Matching our descriptors with Lowe''s ones\n') ;
tic ; 
cmatches=siftmatch( descr1, uint8(ldescr1) ) ;
fprintf('Matched in %.3f s\n', toc) ;

sel=1:size(cmatches,2) ;
perm=randperm(length(sel)) ;
 idx1=cmatches(1, perm(1:min(60,length(perm)))) ;
lidx1=cmatches(2, perm(1:min(60,length(perm)))) ;

figure(6) ; clf ;
axes('Position',[0 0 1 1]) ; 
imagesc(I1) ; hold on ; colormap gray ; axis image ;
 h=plotsiftdescriptor(  descr1(:, idx1),  frames1(:, idx1) ) ;
lh=plotsiftdescriptor( ldescr1(:,lidx1), lframes1(:,lidx1) ) ;
set( h,'Color','r','LineWidth',2) ;
set(lh,'Color','g','LineWidth',1) ;
