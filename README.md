# Image-Closest-Pair-Algorithm
A random algorithm to find the cloest pair in a set of Image (handwritten digits)

+ **Ubuntu 16.04**  and  g++ **5.4.0**
+ This link to **download** Dataset: [Link](http://yann.lecun.com/exdb/mnist/)

### Usage

+ Extract all **images** from the dataset

    > ```
    make helper
./bin/datasetHelper
    ```
    Images will store in `data/images/*.txt`
    And **Dataset** is `data/Mnist.ds`

+ Run this program

    >```
    make
bin/cp -n 60000 -d 784 -f data/Mnist.db
    ```


### Reference

+ command line arguments parser: [cmdline](https://github.com/tanakh/cmdline)
