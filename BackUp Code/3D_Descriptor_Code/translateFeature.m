function [tFeatures, tFrame ] = translateFeature(tFeatures, tFrame)

featureCount = size(tFeatures, 1);
for i = 1 : featureCount
    factor = 2.^(tFeatures(i, 1) - 1);
    tFeatures(i, 3) = tFeatures(i, 3) * factor;
    tFeatures(i, 4) = tFeatures(i, 4) * factor;
    tFeatures(i, 5) = tFeatures(i, 5) * factor;
    tFrame(tFeatures(i, 4), tFeatures(i, 5), tFeatures(i, 3)) = 175;
end

end