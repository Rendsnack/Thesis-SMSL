function [array labels] = imds2array(imds)
%IMDS2ARRAY Summary of this function goes here
%   Detailed explanation goes here

imagesCellArray = imds.readall();
numImages = numel( imagesCellArray );
[h, w, c] = size( imagesCellArray{1} );
array = zeros( h, w, c, numImages );
for i=1:numImages
array(:,:,:,i) = im2double( imagesCellArray{i} );
end
labels = str2num(char(imds.Labels));
end


