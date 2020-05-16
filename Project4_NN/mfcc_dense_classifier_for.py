import librosa
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
# %matplotlib inline
import os
import csv
import time
from contextlib import redirect_stdout
import signal
import sys
# Preprocessing
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
#Keras
# import keras
from tensorflow.keras import models
from tensorflow.keras import layers
from tensorflow.keras.layers import Dense, Dropout
from tensorflow.keras.callbacks import TensorBoard, EarlyStopping

#reading training and test dataset from csv
#music
data6_10 = pd.read_csv('D:/Users/MC/Documents/UNI/MASTER/thesis/MFCC_FEATURES2/reverse_Mel_scale/data6_10ms_R.csv')
data6_50 = pd.read_csv('D:/Users/MC/Documents/UNI/MASTER/thesis/MFCC_FEATURES2/reverse_Mel_scale/data6_50ms_R.csv')
data6_100 = pd.read_csv('D:/Users/MC/Documents/UNI/MASTER/thesis/MFCC_FEATURES2/reverse_Mel_scale/data6_100ms_R.csv')
data6_500 = pd.read_csv('D:/Users/MC/Documents/UNI/MASTER/thesis/MFCC_FEATURES2/reverse_Mel_scale/data6_500ms_R.csv')
data6_1000 = pd.read_csv('D:/Users/MC/Documents/UNI/MASTER/thesis/MFCC_FEATURES2/reverse_Mel_scale/data6_1000ms_R.csv')
#speech
data5_10 = pd.read_csv('D:/Users/MC/Documents/UNI/MASTER/thesis/MFCC_FEATURES2/reverse_Mel_scale/data5_10ms_R.csv')
data5_50 = pd.read_csv('D:/Users/MC/Documents/UNI/MASTER/thesis/MFCC_FEATURES2/reverse_Mel_scale/data5_50ms_R.csv')
data5_100 = pd.read_csv('D:/Users/MC/Documents/UNI/MASTER/thesis/MFCC_FEATURES2/reverse_Mel_scale/data5_100ms_R.csv')
data5_500 = pd.read_csv('D:/Users/MC/Documents/UNI/MASTER/thesis/MFCC_FEATURES2/reverse_Mel_scale/data5_500ms_R.csv')
data5_1000 = pd.read_csv('D:/Users/MC/Documents/UNI/MASTER/thesis/MFCC_FEATURES2/reverse_Mel_scale/data5_1000ms_R.csv')
#join
training_and_test_data = pd.concat([data6_10, data6_50, data6_100, data6_500, data6_1000, data5_10, data5_50, data5_100, data5_500, data5_1000])
#train only on music
# training_and_test_data = pd.concat([data6_10, data6_50, data6_100, data6_500, data6_1000])

#making labels
encoder = LabelEncoder()
labels_list = training_and_test_data.iloc[:, -1]
# labels_list = reduce_resolution(data)
y = encoder.fit_transform(labels_list)

#printing random selection of data
data_subset = training_and_test_data.sample(n=5)
print(data_subset.head())
#dropping unneccesary columns: filename
training_and_test_data = training_and_test_data.drop(['filename'],axis=1)

#normalizing/standardizing
scaler = StandardScaler()
X = scaler.fit_transform(np.array(training_and_test_data.iloc[:, :-1], dtype = float))

#randomly spliting dataset into train and test dataset
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1)


def writeBestModelToFile():
    with open(f"./for/best_models.txt", 'w') as f:
        with redirect_stdout(f):
            print(f'best model on test set is: {best_model}')
            print('test_acc: ',highest_test_acc)



#choosing possible model architectures
layers = [3,4,5]
hiddenUnits = [256, 512, 1024, 2048]
# epochs = [1000]
epochs = [1,5,20,50]
num_epoch = 1000

highest_test_acc = 0
best_model = "none"

for num_layers in layers:
    for num_units in hiddenUnits:
        for eearl in epochs:
            #debug and stuff
            filename = f"reverse_music_MFCC_Dense_Classifier_l-{num_layers}_u-{num_units}_e-{num_epoch}_{int(time.time())}.h5"
            #callback to record traing and validation process, these records can be accessed via a browser
            tboard_log_dir = os.path.join("logs",f"{os.path.basename(__file__)}_{filename}")
            tensorboard = TensorBoard(log_dir = tboard_log_dir)

            # creating a model
            model = models.Sequential()
            model.add(Dense(num_units, activation='relu', input_shape=(X_train.shape[1],)))

            for i in range(num_layers):
                model.add(Dense(num_units, activation='relu'))
                model.add(Dropout(0.2))

            model.add(Dense(40, activation='softmax'))

            model.compile(optimizer='adam',
                        loss='sparse_categorical_crossentropy',
                        metrics=['accuracy'])

            # calback to stop training once val loss isn't decreasing anymore
            es = EarlyStopping(monitor='val_loss', mode='min', verbose=1, patience=eearl)
                        
            history = model.fit(X_train,
                                y_train,
                                epochs=num_epoch,
                                batch_size=128,
                                validation_split=0.3,
                                callbacks=[tensorboard,es])  

            # calculate accuracy
            test_loss, test_acc = model.evaluate(X_test,y_test)

            with open(f"./for/{filename}.txt", 'w') as f:
                with redirect_stdout(f):
                    model.summary()
                    print('test_acc: ',test_acc)

            # save the model to disk
            model.save(f"./for/{filename}") 

            # if so, update best model
            if test_acc > highest_test_acc:
                highest_test_acc = test_acc
                best_model = filename
                print(best_model)

#at the end, print best model and corresponding test accuracy to screen
print(f'best model {best_model} @ {highest_test_acc}%')
writeBestModelToFile()
#end of program

#reduce label resolution from every 9° to 4 quadrants
def reduce_resolution(old_data):
    new_data = old_data.iloc[:, -1]
    new_label_list = pd.DataFrame(new_data)
    for i in range(len(new_data)):
        if 0 <= new_data.iloc[i] < 90:
            new_label_list.iloc[i] = 0
        if 90 <= new_data.iloc[i] < 180:
            new_label_list.iloc[i] = 1
        if 180 <= new_data.iloc[i] < 270:
            new_label_list.iloc[i] = 2
        if 270 <= new_data.iloc[i] < 360:
            new_label_list.iloc[i] = 3
    return new_label_list