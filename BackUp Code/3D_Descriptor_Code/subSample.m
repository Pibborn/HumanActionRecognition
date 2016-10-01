function [O] = subSample(I)

[height, width, layer] = size(I);
nDim = ndims(I);
normFactor = power(2,nDim);
O = zeros(ceil(height/2), ceil(width/2), ceil(layer/2));

for l = 1 : 2 : layer
    for h = 1 : 2 : height
        for w = 1 : 2 : width
            hIndex = ceil(h/2);
            wIndex = ceil(w/2);
            lIndex = ceil(l/2);
            
            % 8 corner cases and 12 edge cases and 1 center case
            
            if l + 1 <= layer && h + 1 <= height && w + 1 <= width
                O(hIndex, wIndex, lIndex) = sum(sum(sum(I(h:h+1,w:w+1,l:l+1))))/normFactor;
            elseif l + 1 <= layer && h + 1 <= height
                O(hIndex, wIndex, lIndex) = sum(sum(sum(I(h:h+1, w, l:l+1))))/(normFactor/2);
            elseif l + 1 <= layer && w + 1 <= width
                O(hIndex, wIndex, lIndex) = sum(sum(sum(I(h, w:w+1, l:l+1))))/(normFactor/2);
            elseif h + 1 <= height && w + 1 <= width
                O(hIndex, wIndex, lIndex) = sum(sum(sum(I(h:h+1, w:w+1, l))))/(normFactor/2);
            elseif h + 1 <= height
                O(hIndex, wIndex, lIndex) = sum(sum(sum(I(h:h+1, w, l))))/(normFactor/4);
            elseif w + 1 <= width
                O(hIndex, wIndex, lIndex) = sum(sum(sum(I(h, w:w+1, l))))/(normFactor/4);
            elseif l + 1 <= layer
                O(hIndex, wIndex, lIndex) = sum(sum(sum(I(h, w, l:l+1))))/(normFactor/4);
            else
                O(hIndex, wIndex, lIndex) = sum(sum(sum(I(h, w, l))));
            end
        end
    end
end
% for h = 1 : 2 : height
%     for w = 1 : 2 : width
%         hIndex = ceil(h/2);
%         wIndex = ceil(w/2);
%         if h + 1 <= height && w + 1 <= width
%             O(hIndex, wIndex, 1) = sum(sum(I(h : h + 1, w : w + 1, 1)))/4;
%             O(hIndex, wIndex, 2) = sum(sum(I(h : h + 1, w : w + 1, 2)))/4;
%             O(hIndex, wIndex, 3) = sum(sum(I(h : h + 1, w : w + 1, 3)))/4;
%         elseif h + 1 <= height
%             O(hIndex, wIndex, 1) = sum(I(h : h + 1, w, 1))/2;
%             O(hIndex, wIndex, 2) = sum(I(h : h + 1, w, 2))/2;
%             O(hIndex, wIndex, 3) = sum(I(h : h + 1, w, 3))/2;
%         elseif w + 1 <= width
%             O(hIndex, wIndex, 1) = sum(I(h, w : w + 1, 1))/2;
%             O(hIndex, wIndex, 2) = sum(I(h, w : w + 1, 2))/2;
%             O(hIndex, wIndex, 3) = sum(I(h, w : w + 1, 3))/2;
%         else
%             O(hIndex, wIndex, 1) = I(h, w , 1);
%             O(hIndex, wIndex, 2) = I(h, w , 2);
%             O(hIndex, wIndex, 3) = I(h, w , 3);
%         end
%     end
% end

end