%% -----------------------------------------------------
% % Code of custom image datastore reader function
function data = customreader(filename)
onState = warning('off', 'backtrace');
c = onCleanup(@() warning(onState));
data = imread(filename);
data = im2double(data); 
% data = rgb2gray(data);
data = imresize(data, [23 35]);
%data = im2double(data); 
end
%% -----------------------------------------------------
