clear;
clc;
filePath = strcat(pwd,'/3P/Features/D_*.csv');

files = dir(filePath);

nFiles = size(files,1);

labels = zeros(nFiles,1);
label = zeros(nFiles,10);
ind = zeros(10,1);

for file = 1 : nFiles
    fileName = files(file).name;
    fprintf('File - %d\n', file);
    if(strfind(fileName,'_D_') ~= 0) % DIvind
        labels(file)  = 1;
        label(file,:) = [1 0 0 0 0 0 0 0 0 0];
    elseif (strfind(fileName,'_G_') ~= 0) % Golf Swing
        labels(file)  = 2;
        label(file,:) = [0 1 0 0 0 0 0 0 0 0];
    elseif (strfind(fileName,'_K_') ~= 0) % Kicking
        labels(file)  = 3;
        label(file,:) = [0 0 1 0 0 0 0 0 0 0];
    elseif (strfind(fileName,'_L_') ~= 0) % Lifting
        labels(file)  = 4;
        label(file,:) = [0 0 0 1 0 0 0 0 0 0];
    elseif (strfind(fileName,'_RH_') ~= 0) % Riding Horse
        labels(file)  = 5;
        label(file,:) = [0 0 0 0 1 0 0 0 0 0];
    elseif (strfind(fileName,'_RS_') ~= 0) % Running
        labels(file)  = 6;
        label(file,:) = [0 0 0 0 0 1 0 0 0 0];
    elseif (strfind(fileName,'_SBF_') ~= 0) % Skateboarding
        labels(file)  = 7;
        label(file,:) = [0 0 0 0 0 0 1 0 0 0];
    elseif (strfind(fileName,'_SWB_') ~= 0) % Swing Bench
        labels(file)  = 8;
        label(file,:) = [0 0 0 0 0 0 0 1 0 0];
    elseif (strfind(fileName,'_SWSA_') ~= 0) % Swing Size ways
        labels(file)  = 9;
        label(file,:) = [0 0 0 0 0 0 0 0 1 0];
    else
        labels(file)  = 10; % Walking
        label(file,:) = [0 0 0 0 0 0 0 0 0 1];
    end
end
csvwrite(strcat(pwd,'/3P/labels.csv'),labels);
csvwrite(strcat(pwd,'/3P/label.csv'),label);