for i = 1 : 6
    
    temp = rand(1,100);
    [~,I] = sort(temp);
    files(i,:) = I;
    
end
