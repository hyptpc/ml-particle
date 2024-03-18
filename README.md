# ml-particle

Machine Learning for Particle Identification

# How to use  
### 0. Evironment settings
Install uproot3 and torch, if you haven't yet.
```sh
$ pip install uproot3
$ pip install torch
```

### 1. Create train data & test data

```sh
$ root mkrootfile.C
```
 and you can create data by Monte-Carlo
resolution (tof:0ps, 10ps, 100ps, 500ps / ene:0%, 1%, 10%, 30%) will be added by gaussian and saved to rootfile branches indivisually. 


### 2. Start learning

```sh
$ python3 input3.py 10 30
```

In this case, tof10ps, energy30% resolution will be used as data.<br>
After the learning process finishes, the input particle_id and output particle_id will be filled into rootfile.

### 3. Check accuracy on detail

```sh
$ python3 normalized_confusion_matrix.py 10 30
```

Get the confusion matrix, and you can know the accuracy for each particle 
  
 

