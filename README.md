# CNN-Photon-ID
Contains the code used to develop the Convolutional photonID using images from the Eelectromagnetic Calorimeter layers (sampling 1, 2 and 3). 

              <img width="514" alt="CNN" src="https://raw.githubusercontent.com/mobelfki/CNN-Photon-ID/main/.github/images/CNN.png">

- The CNN is designed to extract information from each sampling then combine them. The model is implemented using Keras functional APIs and Tensroflow as a backend

              <img width="514" alt="CNN_model" src="https://raw.githubusercontent.com/mobelfki/CNN-Photon-ID/main/.github/images/CNN_model.png" >
# Model and Training      
- The model is defined in `Train/Models.models` as `CNNHybridClassifier` and trained using `Train/train.py` code :

          ./train --args 
          
Arguments are : number of epochs, learning rate, batch size, Number of CNN neurons, Number of DNN neurons ....
# Data Processing
- Training data are images from ATLAS Electromagnetic calorimeter and handled by `Train/DataProcessing` class. 
- The data are Monte Carlo simulation produced using `ZllyAthDerivation` and processed using `NTUP` code to produce root flat ntuple which are then converted to NumPy arrays using `Array` code.
- `CellsToImage` is a code which converte the NumPy cells vector to NumPy images for training, An example of training images is shown below:

              <img width="514" alt="Image_CNN" src="https://raw.githubusercontent.com/mobelfki/CNN-Photon-ID/main/.github/images/Image_CNN.png" >
# Validation
- After Training the model is validate using `Validation` code, the model is validate on a out-of-sample photons generated from a different process used in training to remove any potential bias
# ONNX and Integration in Athena
- After validation the mode is converted to ONNX format developed by Microsoft using the code `Train/toonnx.py`
- `DerivationFrameworkCNNPID` is a framework that integrate and apply the model at the derivation stage in the official ATLAS Athena framework. 
