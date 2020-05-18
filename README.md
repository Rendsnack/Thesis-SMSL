# Auditory-Inspired Machine Listening Using Smartphones
*This repository contains the code used in the thesis.*
## Extended abstract
Sound localization has become an important signal processing task for the enhancement of major signal processing systems. 
The manner in which this task is implemented can vary depending on the available resources. 
Since smartphones only have one raw audio input available via the Android API, it is necessary to provide a sound localization technique which can work with a single channel.
Smartphones are typically designed with a smooth casing.
This symmetry causes less interference which in turn leads to uniformity. 
The raw audio recordings will be less distorted which means that incoming sound signals show less directionality.

The current study investigates whether monaural attributes observed in sound localization by humans suffering from Single-Sided Deafness (SSD) can also be observed in audio signals recorded by a smartphone.
The presence of direction-dependent information is analysed via a polar pattern measurement.
Spectral information is provided as a set of features for an Angle of Arrival (AoA) classification task.
A Support Vector Machines (SVMs) based model for broadband white noise is proposed based on the Power Spectral Density (PSD).
As a comparison, a SVM is also applied to pink noise.
Classification results show a high performance. 
This leads to an attempt on a Support Vector Regression (SVR) model which estimates the AoA using the same feature set as given to the classifiers.
The results of SVR show that such an estimation is possible. 
As these methods do not handle non-stationary signals, a Neural Network (NN) model based on Mel-Frequency Cepstral Coefficients (MFCCs) is explored.
An alternative computation method of MFCCs using a reverse Mel-scale is also investigated.
Compared to a standard Mel scale this reverse Mel scale emphasizes the higher frequencies while downplaying the importance of lower frequencies.

A literature study shows that humans perform better at localizing sound which contains information at higher frequencies.
The observations indicate that listeners with SSD are able to estimate the position of a sound source to some extent.
This shows that monaural cues are sufficient to perform the sound localization task.
Comparing the capability of a SVM model to locate white noise and pink noise based on spectral cues indicates similar results. 
Pink noise has less energy at higher frequencies which makes it harder to locate than white noise, which has an equal energy content for all frequencies.
The regression models can estimate the AoA of broadband signals more precise as compared to SVM classifiers due to the limited resolution.
However the relation between the linear input features and the circular output has to be redefined in order to increase the performance of such a regression model.
Similar observations are made on non-stationary signals. 
A neural network which tries to locate sound defined by its MFCCs performs poorly compared to when the sound is defined by reversely computed MFCCs.
Features obtained from a reverse Mel scale contain more information on higher frequencies compared to features derived from a standard Mel scale.

This thesis finds that audio signals recorded by a smartphone do contain information which can be used for sound localization.
This information can mainly be found at higher frequency regions and therefore requires feature extraction methods which focus on these regions.
Locating simpler signals like broadband noise can be done fairly easily using the PSD of the signal.
Highly dynamic signals like speech and music require somewhat more complex features like MFCCs or reversly computed MFCCs.
The ability to localize a sound source with the studied methods does not seem to be influenced by room reverberations.

**Keywords: Sound Localization, Smartphones, Spectral Cues, PSD, MFCCs, Machine Learning**

## The provided projects
The repository is split up into 4 main projects which follow the structure of the thesis. A detailed description is found in each corresponding project.

The first project **Measurements** deals with the measurement of the polar pattern of an Android smartphone. This is accomplished using the sinesweep method to calculate impulse responses from certain directions. 

The second project **IR examination** analyzes the impulse responses acquired from project **Measurements**. More specifically the impulse responses are analyzed mainly in the frequency domain.

The third project **Noise Model** is a first attempt on the sound localization task with noise as the signal of interest. This project explores different spectral estimation methods to classify the AoA.

The fourth and last project **Neural Network** goes one step further and tries to do the localization task with speech and music as the signal of interest. This project explores the use of cepstral coefficients and their derivatives to train a neural network for classification of the AoA.
