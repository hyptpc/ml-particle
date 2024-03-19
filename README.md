# ml-particle

Machine Learning for Particle Identification

# How to use  
### 0. Evironment settings
Install uproot3 and torch, if you haven't yet.
```sh
$ pip install uproot3
$ pip install torch
```

#### 0.1 Directory structure
```sh
ML
│
├ README.md .
│
├ create_rootfiles .. creating datas as rootfile and saving rootfiles
│　├ dataplot.C ... plotting train/test data 
│　└ mkrootfile.C ... creating train/test data
│
├ learn ... codes for machine learning
│　├ code
│　│  ├ normalized_confusion_matrix.py 
│　│  └ input3.py
│　├ figures ... saving plot images here
│　└ pth ... saving pth file here
│
└ Likelihood ... code for likelihood
   ├ ana
　 │  ├ Likelihood.C
   │  ├ draw_pdf.C
　 │  └ compare_likelihood.C ... comparing ML and Likelihood  
　 ├ buf ... saving created rootfiles here (linked to had/group)
　 └ mkfile ... creating rootfile data for likelihood analysis
　　  ├ mkrootfile_pdf.C
　　  └ Job_mkPDF.sh ... creating rootfiles for pdf data pararelly and connect
```

### 1. Create train data & test data

```sh
$ cd create_rootfiles
$ root mkrootfile.C
```
 and you can create data by Monte-Carlo
resolution (tof:0ps, 10ps, 100ps, 500ps / ene:0%, 1%, 10%, 30%) will be added by gaussian and saved to rootfile branches indivisually. 


### 2. Start learning

```sh
$ cd learn/code
$ python3 input3.py 10 30
```

In this case, tof10ps, energy30% resolution will be used as data.<br>
After the learning process finishes, the input particle_id and output particle_id will be filled into rootfile.

### 3. Check accuracy on detail

```sh
$ cd learn code
$ python3 normalized_confusion_matrix.py 10 30
```

Get the confusion matrix, and you can know the accuracy for each particle 
  
 

