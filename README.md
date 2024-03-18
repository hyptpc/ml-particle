# ml-particle

Machine Learning for Particle Identification

# How to use  
### 1. creating train data & test data
'''sh
 root mkrootfile.C
 '''
 and you can create data by Monte-Carlo
resolution (tof:0ps, 10ps, 100ps, 500ps / ene:0%, 1%, 10%, 30%) will be added by gaussian and saved to rootfile branches indivisually. 

### 2. run input3.py and start learning process

'''sh
python3 input3.py 10 30
'''

In this case, tof10ps, energy30% resolution will be used as data.<br>
After the learning process finishes, the input particle_id and output particle_id will be filled into rootfile.

### 3. run normalized_confusion_matrix.py

'''sh
python3 normalized_confusion_matrix.py 10 30
'''
Get the confusion matrix figure, and you can know the accuracy for each particle 
  
 

