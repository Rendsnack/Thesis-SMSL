%
% This files intended prupose is to experiment with the recorded audio we
% have and explore the resulting polar patterns.
%% prepare workspace
clc;clear;close all;
p = genpath('../');  % include root folder
addpath(p)

%% get directory of recrodings of a sinesweep
% folderPath1 = uigetdir;
fodlerPath1 = 'C:\Users\MC\Documents\UNI\Master\thesis\Software\GIT\thesis\Data\Z_ROT\delay_0';
folderPath2 = 'C:\Users\MC\Documents\UNI\Master\thesis\Software\GIT\thesis\Data\Z_ROT\delay_500ms';
folderPath3 = 'C:\Users\MC\Documents\UNI\Master\thesis\Software\GIT\thesis\Data\Z_ROT\delay_1s';
folderPath4 = 'C:\Users\MC\Documents\UNI\Master\thesis\Software\GIT\thesis\Data\Z_ROT\delay_2s';
fodlerPath1 = 'D:\Users\MC\Documents\UNI\MASTER\thesis\Data\Z_ROT\delay_0';
folderPath2 = 'D:\Users\MC\Documents\UNI\MASTER\thesis\Data\Z_ROT\delay_500ms';
folderPath3 = 'D:\Users\MC\Documents\UNI\MASTER\thesis\Data\Z_ROT\delay_1s';
folderPath4 = 'D:\Users\MC\Documents\UNI\MASTER\thesis\Data\Z_ROT\delay_2s';

%% calculate the polar patterns
[result1, result1Scaled, result1H] = plotPolarPattern(fodlerPath1, 7, false);
[result2, result2Scaled, result2H] = plotPolarPattern(folderPath2, 7, false);
[result3, result3Scaled, result3H] = plotPolarPattern(folderPath3, 7, false);
[result4, result4Scaled, result4H] = plotPolarPattern(folderPath4, 7, false);

%% compare all
result1 = [result1; result1(1,:)];
result2 = [result2; result2(1,:)];
result3 = [result3; result3(1,:)];
result4 = [result4; result4(1,:)];
figure;
subplot(2,2,1); polarplot(result1); title('0s delay');
subplot(2,2,2); polarplot(result2); title('500ms delay');
subplot(2,2,3); polarplot(result3); title('1s delay');
subplot(2,2,4); polarplot(result4); title('2s delay');

%% compare all scaled versions
result1Scaled = [result1Scaled; result1Scaled(1,:)];
result2Scaled = [result2Scaled; result2Scaled(1,:)];
result3Scaled = [result3Scaled; result3Scaled(1,:)];
result4Scaled = [result4Scaled; result4Scaled(1,:)];
f1 = figure;
subplot(2,2,1); polarplot(result1Scaled); title('0s delay');
subplot(2,2,2); polarplot(result2Scaled); title('500ms delay');
subplot(2,2,3); polarplot(result3Scaled); title('1s delay');
subplot(2,2,4); polarplot(result4Scaled); title('2s delay');

%% compare all shortened IR
result1H = [result1H; result1H(1,:)];
result2H = [result2H; result2H(1,:)];
result3H = [result3H; result3H(1,:)];
result4H = [result4H; result4H(1,:)];
f2 = figure;
subplot(2,2,1); polarplot(result1H,'LineWidth',2); title('0s delay');
tl = thetaticklabels
tlabel = cell(12,1)
for i=1:12
   tlabel{i} = [tl{i} '°']
end
thetaticklabels(tlabel)
subplot(2,2,2); polarplot(result2H,'LineWidth',2); title('500ms delay');
tl = thetaticklabels
tlabel = cell(12,1)
for i=1:12
   tlabel{i} = [tl{i} '°']
end
thetaticklabels(tlabel)
subplot(2,2,3); polarplot(result3H,'LineWidth',2); title('1s delay');
tl = thetaticklabels
tlabel = cell(12,1)
for i=1:12
   tlabel{i} = [tl{i} '°']
end
thetaticklabels(tlabel)
subplot(2,2,4); polarplot(result4H,'LineWidth',2); title('2s delay');
tl = thetaticklabels
tlabel = cell(12,1)
for i=1:12
   tlabel{i} = [tl{i} '°']
end
thetaticklabels(tlabel)
octaveBand = getOctaveBands(44.1e3/2 ,7);
legendCell = cellstr(num2str(octaveBand(2:end)','fend=%4.2f Hz'));
legend(legendCell);
%%
polarplot(result2H,'LineWidth',2); title('polar pattern of Z-rotation, 500ms delay');
tl = thetaticklabels
tlabel = cell(12,1)
for i=1:12
   tlabel{i} = [tl{i} '°']
end
thetaticklabels(tlabel)
octaveBand = getOctaveBands(44.1e3/2 ,7);
legendCell = cellstr(num2str(octaveBand(2:end)','fend=%4.2f Hz'));
legend(legendCell);
%% calculate and plot the variance off a 0s delay
var = var(result2); 
figure; 
plot(var);
title('variance per octave band')
ylabel('variance'); xlabel('octave band');

%% compare the polar pattern with a scaled version of itself
result2 = [result2; result2(1,:)];
result2Scaled = [result2Scaled; result2Scaled(1,:)];
figure;
subplot(1,2,1); polarplot(result2)
subplot(1,2,2); polarplot(result2Scaled)
sgtitle('500ms delay');