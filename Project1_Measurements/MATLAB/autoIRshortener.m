%% used to automatically shorten each IR of an IR-set
% a filepath is given where the current IR-set is
% set the amount of samples to cut before and after the inital peak
% the IR for each direction is shortened
% it can then be saved to file
%% shorten IR for all directions
clear;clc;close all;
p = 'C:\Users\MC\Documents\UNI\Master\thesis\Software\GIT\thesis\Learning_Model\aux_data\IR_X_fixed\2s';
fp = [p '/IR44K_X_2s_og.mat'];
load(fp);
%%
pre = 10e-3*44100;
post = 1000e-3*44100;
IR44K_X_2s_1000ms = cell(length(IR44K_X_2s_og),2);
fn = 'IR44K_X_2s_1000ms'
for c=1:length(IR44K_X_2s_og)
    IR44K_X_2s_1000ms(c,1) = IR44K_X_2s_og(c,1);
    h = IR44K_X_2s_og{c,2};
    h_new = shortenImpulseResponse(h,pre,post);
    IR44K_X_2s_1000ms{c,2} = h_new;
%     plot(h_new);
%     pause(1)
end
%% save to file
writeTo = 'C:\Users\MC\Documents\UNI\Master\thesis\Software\GIT\thesis\Learning_Model\aux_data\IR_X_fixed\2s\';
fp = [writeTo fn]
save(fp, fn)
