% start_parallel: an utility script that calls start.m to have
%                 some kind of parallelism for feature extraction

% set up the list of videos
LoadParams; % loads videoDir 
video_list = dir(strcat(videoPath, '*.avi'));
video_list = {video_list.name};

% add videoDir to the MATLAB path, or the videos in video_list will not be recognized
addpath(videoPath)

% set up video_list for parallel execution
% "zero-pad" the video_list argument
zero_pad_times = NumProcessors - mod(size(video_list, 2), NumProcessors);
if zero_pad_times ~= 0
    no_video_argument = 'pass'; % "no-op" style argument
    for i = 1:zero_pad_times
        video_list = [video_list no_video_argument];
    end
end

% reshape video_list so that each column will be a 
% list of arguments for a parallel process
video_list = reshape(video_list, [], NumProcessors);

% for each "process", run start.m on a video_list column
parfor i=1:NumProcessors
    for video_idx=1:numel(video_list(:, i))
        video_path = video_list(video_idx, i);
        
        % video path is currently a cell; cast it to a char vector
        % (i.e. a string)
        video_path = char(video_path);
        if strcmp(video_path, 'pass') == 0
            split_video_path = strsplit(video_path, '/');
            
            % videoName is the last element of the split string; so it also
            % needs to be cast to char
            videoName = char(split_video_path(end));
            
            % videoDir is made up by all of them but the last one, but
            % to be a path it needs the '/' put back in.
            videoDir = strjoin(split_video_path(1:end-1), '/');
            % and also an extra '/' at the end!
            videoDir = strcat(videoDir, '/');
            start(videoDir, videoName)
        end
    end
end
