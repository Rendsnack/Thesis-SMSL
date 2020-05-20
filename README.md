# Auditory-Inspired Machine Listening Using Smartphones
*This repository contains the code used in the thesis.*
## Extended abstract
Sound localization has become an important signal processing task for the enhancement of signals in several applications. 
Conventionally, this task can be accomplished with multiple microphones by exploiting the time difference of arrival between each microphone. 
However, Android smartphones only have one raw audio input available, which makes the use of such time differences impossible.
Therefore it is necessary to develop a sound localization technique which can work with a single channel input.
This solution, however, requires that different angle of arrivals can be distinguished for identical sound signals. 
In order to achieve this, the signal has to undergo a direction-dependent transformation which makes it unique from other directions.
Smartphones are typically designed with a smooth casing.
This symmetry causes less interference which in turn leads to uniformity. 
The raw audio recordings will be less distorted which means that incoming sound signals show less directionality.

In this thesis we draw inspiration from the human auditory system to develop a single channel sound localization technique using smartphones. 
An initial literature study shows that people suffering from single-sided deafness (SSD) rely on higher frequencies in order to estimate the position of a sound source.
This raises the question whether or not the same observations can be made with audio signals recorded by a smartphone.
The presence of direction-dependent information is analysed via a polar pattern measurement, where the intensity of the sound is measured for different directions.
Spectral information is provided as a set of features for an angle of arrival (AoA) classification task.
A support vector machine (SVM) based on the power spectral density (PSD) is proposed to localize broadband white noise.
In order to determine the importance of high-frequency information, a similar model is trained to localize pink noise.
In addition to a classification task, the possibility to estimate the angle of arrival by means of a support vector regression (SVR) model is explored. 
This model relies on regression, meaning that the estimated angle will be a numerical value, while the classifier will give categorical angles. 
Therefore a more precise angle of arrival is estimated.
As these methods do not handle non-stationary signals, a neural network (NN) model based on mel-frequency cepstral coefficients (MFCCs) is explored.
This model tries to classify the AoA of highly dynamic signals such as speech and music.
An alternative computation method of MFCCs using a reverse mel scale is also investigated.
Compared to a standard mel scale this reverse mel scale emphasizes the higher frequencies while downplaying the importance of lower frequencies.

This study finds that audio signals recorded by a smartphone contain information which can be used for sound localization.
This information can mainly be found at higher frequency regions and therefore requires feature extraction methods which focus on these regions.
The localization of broadband white noise using the PSD is therefore a simple task, as it has a flat power spectrum.
Signals with less information on these higher frequencies are harder to localize with the SVM model.
The results of the regression task show a high performance on estimating the angle of arrival from a broadband white noise signal. 
However the relation between the power spectral density as a linear input and the angle of arrival as a circular output causes misconceptions during estimation.
Highly dynamic signals like speech and music require somewhat more complex features like MFCCs or reversely computed MFCCs and require that the neural network is trained on a large amount of data.
These signals do suffer from some left-right confusion where the angle of arrival is misclassified by $180\degree$.
The ability to localize a sound source using the studied methods does not seem to be influenced by room reverberations.
**Keywords: Sound Localization, Smartphones, Spectral Cues, PSD, MFCCs, Machine Learning**

## The provided projects
The repository is split up into 4 main projects which follow the structure of the thesis. A detailed description is found in each corresponding project.

The first project **Measurements** deals with the measurement of the polar pattern of an Android smartphone. This is accomplished using the sinesweep method to calculate impulse responses from certain directions. 

The second project **IR examination** analyzes the impulse responses acquired from project **Measurements**. More specifically the impulse responses are analyzed mainly in the frequency domain.

The third project **Noise Model** is a first attempt on the sound localization task with noise as the signal of interest. This project explores different spectral estimation methods to classify the AoA.

The fourth and last project **Neural Network** goes one step further and tries to do the localization task with speech and music as the signal of interest. This project explores the use of cepstral coefficients and their derivatives to train a neural network for classification of the AoA.
