function [dataOut] = get_batch(dataIn,indexes)
%GET_BATCH Get batch of ImageDataStore object defined by indexes
%   dataIn: ImageDataStore object
%   indexes: vector [startIndex; endIndex]
%   dataOut: 4D array with images as (row,column, 3, batchSize)

startIndex = indexes(1);
stopIndex = indexes(2);
size = stopIndex-startIndex +1;

dataOut = zeros(230,350,3,size);
reset(dataIn);
for i = 1:size
    dataOut(:,:,:,i) = readimage(dataIn,startIndex);
    startIndex = startIndex +1;
end

