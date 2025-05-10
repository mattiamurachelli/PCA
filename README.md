# PCA

This is a small project I created while attending the *Advanced Programming for Scientific Computing* course and the *Machine Learning* course. It contains a program that performs PCA (Principal Component Analysis) on the Fisher Iris Dataset.

---

## Project Contents (C++ version)

The project includes:
1. `main.cpp` – the main driver for the PCA pipeline
2. `Matrix` class – a lightweight class for basic matrix operations
3. `SquareMatrix` class – inherits from `Matrix` and adds eigenvalue/vector functionality
4. `Makefile` – for building the project easily

All these files were developed by me from scratch. The classes are minimal and contain only the functions required for this project, but they are designed to be extensible.  
For instance, the `Matrix` class already contains a method stub you can use to implement dataset imports beyond the Iris dataset.

---

## Required External Files

You need to download two additional files:

- `json.hpp` from [nlohmann/json](https://github.com/nlohmann/json/tree/develop/single_include/nlohmann)  
  → Place it in the `CPP/headers/` folder

- `iris.json` from [Kaggle - Iris Dataset (JSON version)](https://www.kaggle.com/datasets/rtatman/iris-dataset-json-version)  
  → Place it in the `CPP/` folder

**Credits** to the respective authors of these resources.

---

## How to Use

1. Compile the program using the `Makefile`.

2. Run the program using:
   ```bash
   ./main_pca iris.json 150 5 2
   ```

Where the arguments are:
1. Dataset filename (e.g., iris.json)
2. Number of samples
3. Number of features
4. Number of Principal Components to use

You can use any dataset, not just the Iris dataset, as long as you provide the correct parameters.
Check the first lines of main() in main.cpp to verify how the parameters are handled, especially the number of principal components.

---

## Output
The program outputs a file named "output_pca.vtk", which you can open in ParaView to visualize the transformed dataset after PCA.

Suggested Visualization Settings in ParaView
After opening the file and pressing Apply in the Properties section:
1. Set Representation to: Point Gaussian
2. Set Coloring to: label
3. Enable the Data Axes Grid checkbox to show coordinate axes

---

## Matlab implementation
You can also find in the `MATLAB` folder the file `PCA_iris_dataset.m` that is the Matlab implementation that inspired this project, as I wanted to replicate the same code in C++. In order to run the script it is required to install the [Statistics and Machine Learning Toolbox](https://it.mathworks.com/products/statistics.html) Add-On, which contains the Fisher Iris Dataset.

---

## Project Structure
```
.
├── CPP
│   ├── Makefile
│   ├── headers
│   │   ├── Matrix.hpp
│   │   ├── SquareMatrix.hpp
│   │   └── json.hpp
│   └── src
│       ├── Matrix.cpp
│       ├── SquareMatrix.cpp
│       └── main.cpp
├── LICENSE
├── MATLAB
│   └── PCA_iris_dataset.m
└── README.md
```
---

For any questions, suggestions, or to report a bug, feel free to contact me at mattia.murachelli@mail.polimi.it

04/04/2025 — Mattia Murachelli