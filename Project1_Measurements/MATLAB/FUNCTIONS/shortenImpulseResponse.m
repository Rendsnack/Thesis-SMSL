function h = shortenImpulseResponse(h,preAmountInSamples, postAmountInSamples)
% INPUTS:
% - h: original imppulse response (IR) which needs to be shortened
% - preAmountInSamples: how much to cut before the initial peak of the IR
% - postAmountInSamples: how much to cut after the initial peak of the IR

% OUTPUTS:
% - h: the shortened impulse response
[~, index] = max(h);
h = h(index-preAmountInSamples:index+postAmountInSamples);
end