function inputVideo = getVideo(video)

frameCount = 1;
X = video.Height; % Height
Y = video.Width; % Width
T = ceil(video.Duration*video.FrameRate); % Frames
inputVideo = zeros(X,Y,T);
while hasFrame(video)
    inputVideo(:,:,frameCount) = rgb2gray(readFrame(video));
    frameCount = frameCount + 1;
end

end