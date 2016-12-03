# Image-Closest-Pair-Algorithm
A random algorithm to find the cloest pair in a set of Image (handwritten digits)

+ **Ubuntu 16.04**  and  g++ **5.4.0**
+ This link to **download** Dataset: [Link](http://yann.lecun.com/exdb/mnist/)

### Usage

1. Extract all **images** from the dataset

    ```
    make helper
./bin/datasetHelper
    ```
    Images will store in `data/images/*.txt`and **Dataset** is `data/Mnist.ds`

2. Run this program

    show the **help** message
    ```
    make
    bin/cp
    usage: bin/cp --number=int --dimensions=int --file=string [options] ... 
options:
  -n, --number        the number of images (int)
  -d, --dimensions    the dimensions of images (int)
  -f, --file          the path to dataset (string)
  -m, --median        using median as the pivot.
  -?, --help          print this message
    ```

    ```
bin/cp -n <number of images> -d <images' size> -f <path to dataset>  [-m]
    ```

    for eample:

    ```
    bin/cp -n 60000 -d 784 -f data/Mnist.ds
    ```
    or

    ```
    make run
    ```


### Reference

+ command line arguments parser: [cmdline](https://github.com/tanakh/cmdline)
