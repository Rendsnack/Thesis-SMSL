%% turn sine sweep recordings into IR
clc; clear; close all;
startFile()
%% get folder containing subfolders with recordings for each direction
readFrom = 'C:\Users\MC\Documents\UNI\Master\thesis\Software\GIT\thesis\DATA\Z_ROT\delay_2s';
writeTo = 'C:\Users\MC\Documents\UNI\Master\thesis\Software\GIT\thesis\Learning_Model\aux_data\IR_X_fixed\2s';
sweepPath = 'C:\Users\MC\Documents\UNI\Master\thesis\Software\GIT\thesis\MATLAB\SINE_SWEEPS\sinesweep_2sDelay.wav'
sweep = audioread(sweepPath);
fs = 44.1e3;
L = 1.5*fs; %sweep is 1.5s long followed by variable lenght of DC
x = sweep(1:L);
%% calcualte IR for each direction
directory = dir([readFrom '\*.wav']);
IR44K_X_2s_og = cell(40,2);
for i=1:length(directory)
    fn = [readFrom '\' directory(i).name];
    [y,fs] = audioread(fn);
    [h ,C, n0] = impulse_response_calc(x, 1, 22050, fs, y);
    h = h/C;
    IR44K_X_2s_og{i,1} = directory(i).name;
    IR44K_X_2s_og{i,2} = h;
end
%% save to file
filePath = [writeTo '\IR44K_X_2s_og.mat']
save(filePath, 'IR44K_X_2s_og')