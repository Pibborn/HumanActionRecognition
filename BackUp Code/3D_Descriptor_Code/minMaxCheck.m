function [success, type] = minMaxCheck(tempSet, threshold, success, type, trueValue)

%% Percentage Value Check

% maxVal = max(tempSet(:));
%
% if trueValue > threshold*maxVal
%     success = 1;
% end
%
% if success ~= 1
%     minVal = min(tempSet(:));
%     if trueValue < threshold*minVal
%         success = 1;
%         type = 2;
%     end
% end

%% Percentage Neighborhood Check

maxCheck = find(tempSet < trueValue);
totalNeighbor = length(tempSet);
if length(maxCheck)/totalNeighbor > threshold
    success = 1;
else
    minCheck = find(tempSet > trueValue);
    if length(maxCheck)/totalNeighbor > threshold
        success = 1;
        type = 2;
    end
end

end