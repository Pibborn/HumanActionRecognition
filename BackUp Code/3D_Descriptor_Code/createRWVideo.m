close all;
clear;
clc;
% video = VideoWriter('RWLR2RL.mp4','MPEG-4');
% video = VideoWriter('RWL2R.mp4');
% video = VideoWriter('RWTl2BR.mp4');
video = VideoWriter('TLBR2BRTL.mp4','MPEG-4');
pLength = 300;
open(video);
j = 1;
for i = 1 : 100
    fprintf('Frame - %d\n',i);
    temp1 = zeros(pLength);
    temp2 = zeros(pLength);
    temp3 = zeros(pLength);
    if i < 51
        temp1(30+i:79+i,30+i:79+i) = 255;
    else
        temp1(50+30-j:50+79-j,50+30-j:50+79-j) = 255;
        j = j + 1;
    end 
    
    temp(:,:,1) = temp1;
    temp(:,:,2) = temp2;
    temp(:,:,3) = temp3;
    
    writeVideo(video,uint8(temp));
end
close(video);
    