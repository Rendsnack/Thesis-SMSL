function [pred_cat] = net_pred_categorical(pred, labels)
%NET_PRED_CATEGORICAL is used as a transformer from probability to label
%   The predict function returns probabilities for each label
%   To better understand this we decided to write a function that
%   transforms the probabilities to labels

n = size(pred,1);
pred_cat = categorical(zeros(n,1));
for i = 1:n
    index = find(pred(i,:) == max(pred(i,:)))
    pred_cat(i) = labels(index);
end
end

