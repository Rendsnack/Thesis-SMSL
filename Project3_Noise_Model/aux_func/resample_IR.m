function resampled_IR = resample_IR(IR, fs_old, fs_new)
%RESAMPLE_IR Summary of this function goes here
%   Detailed explanation goes here

    [num den] = rat(fs_new/fs_old);
    resampled_IR = interp(IR,num);
    resampled_IR = decimate(resampled_IR, den);
end

