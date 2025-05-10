/*
Main file of my PCA Project
*/

#include "Matrix.hpp"
#include <SquareMatrix.hpp>
#include "json.hpp"
#include <iostream>

int main(int argc, char* argv[]) {

    if (argc != 5 || (std::stoi(argv[4]) < 2 || std::stoi(argv[4]) > 3)) {
        std::cerr << "Usage: ./main_pca <dataset.json = iris.json> <num_samples = 150> <num_features = 5> <num_PC = 2, 3> " << std::endl;
        return -1;
    }

    // Begin by importing the data from the json file
    std::string filename = argv[1];
    int num_samples = std::stoi(argv[2]);
    int num_features = std::stoi(argv[3]);
    int num_PC = std::stoi(argv[4]);

    Matrix X(num_samples, num_features-1);
    std::vector<int> labels = X.importIrisDataset(filename, num_samples);

    std::cout << "========================================================" << std::endl;
    std::cout << "Performing PCA on the dataset..." << std::endl;
    std::cout << "========================================================" << std::endl;

    // Compute the covariance matrix
    // C = X_tilde^T * X_tilde where X_tilde is the centered data matrix
    SquareMatrix C(num_features-1);
    Matrix X_tilde = X;
    X_tilde.centerData();
    C = X_tilde.transpose() * X_tilde;

    // Compute the eigenvalues and the loadings matrix (eigenvector matrix) of C
    // they are also sorted in a descending order
    C.eig();

    // Extract the first num_PC principal components
    Matrix PCs = C.extractPCs(num_PC);
    
    // Compute the transformed data
    Matrix T = X_tilde * PCs;
    // End of computation

    // Generate the output file in the .vtk format (Open with ParaView)
    T.exportToVTK(labels, "output_pca.vtk");

    return 0;
}