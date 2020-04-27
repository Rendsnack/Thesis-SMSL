function [F1, precision, recall] = f1_calculation(yPred, yTest)
%F1_CALCULATION calculates the F1 score using predictions and true values
%   The Precision and Recall are also returned for evaluation purposes
    T_pos = 0;
    F_pos = 0;
    F_neg = 0;
    for i = 1:length(yTest)
        TF_pred = contains(char(yPred(i)), 'malignant');
        TF_test = contains(char(yTest(i)), 'malignant');
        if TF_pred == TF_test
            if TF_pred == 1
                T_pos = T_pos + 1;
            end
        else
            if TF_pred == 1
                F_pos = F_pos + 1;
            else
                F_neg = F_neg +1;
            end
        end
    end
    
    precision = T_pos/(T_pos+F_pos);
    recall = T_pos/(T_pos+F_neg);
    F1 = 2*precision*recall / (precision+recall);
end