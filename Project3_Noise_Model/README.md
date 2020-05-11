# Project 3: Noise localization using SVM classification/regression
The inspiration and theory for this project can be found in chapter 4 of the thesis.
By using spectral estimates as features, the Angle of Arrival (AoA) of a noise signal can be determined using Support Vector Machines (SVM) classificiation.
This project contains three folders each dealing with a key aspect of model development.

## Noise Inspection
Before developing the model, an inspection of the noise samples is performed.
This allows us to look at how the augmentation of noise, meaning the convolution with a certain impulse response, alters the Power Spectral Density (PSD) of the signal.
We study the spectral shape of white and pink noise.

## PSD estimation
Different types of spectral estimation are explored in order to see their effect on performance of the model. This can then give a hint as to which characteristics (frequency, energy level, slope) of the features are important. Three different spectral estimation methods and three different frequency scales are combined.

## Model training
Finally the different methods are used to train SVM classifiers using an Error-Correcting Output Codes (ECOC) strategy to deal with the multi-class problem. We make use of SVM learners which use an epsilon-insensitive loss function as a standard. A Gaussian RBF kernel is used where the training optimizes the C hyperparameter and the kernel parameter *sigma*.  
