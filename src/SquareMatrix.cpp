/*
In this file we have the definition of the SquareMatrix class methods
*/

#include "SquareMatrix.hpp"
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

// Constructor
SquareMatrix::SquareMatrix(std::size_t size) : Matrix(size, size), eigenvectors(Matrix(size,size)) {
    eigenvalues.resize(size, 0.0);
}
// Assignment operator for Matrix -> SquareMatrix conversion
SquareMatrix& SquareMatrix::operator=(const Matrix& other) {
    // we copy data from the Matrix
    rows = other.getNumRows();
    cols = other.getNumCols();
    values = other.getValues();
    // And make sure that eigenvalues and eigenvectors are initialized but empty
    // as we want to manually compute them when needed
    eigenvalues.resize(rows, 0.0);
    eigenvectors = Matrix(rows, rows);

    return *this;
}
// Function to compute eigenvalues and eigenvectors using Jacobi's method
// This method is not the most efficient one, but it is simple and works well for small matrices
void SquareMatrix::eig() {
    // method parameters
    const int maxIterations = 1000;
    const double tolerance = 1e-10;

    // copy the matrix to a local variable
    SquareMatrix A = *this;
    std::size_t n = rows;
    
    // Initialize eigenvectors as an identity matrix
    for (std::size_t i = 0; i < n; ++i) {
        eigenvectors(i,i) = 1.0;
    }
    
    for (std::size_t iter = 0; iter < maxIterations; ++iter) {
        // Find the largest off-diagonal element
        std::size_t p = 0, q = 1;
        double maxOffDiagonal = 0.0;
        for (std::size_t i = 0; i < n; i++) {
            for (std::size_t j = i + 1; j < n; j++) {
                if (std::fabs(A(i,j)) > std::fabs(maxOffDiagonal)) {
                    maxOffDiagonal = A(i,j);
                    p = i;
                    q = j;
                }
            }
        }

        // If the largest off-diagonal element is small enough, stop
        if (std::fabs(maxOffDiagonal) < tolerance)
            break;

        // Compute the Jacobi rotation
        double theta = 0.5 * std::atan2(2 * A(p,q), A(q,q) - A(p,p));
        double c = std::cos(theta);
        double s = std::sin(theta);

        // Apply the rotation to A
        double app = c * c * A(p,p) + s * s * A(q,q) - 2 * s * c * A(p,q);
        double aqq = s * s * A(p,p) + c * c * A(q,q) + 2 * s * c * A(p,q);
        A(p,q) = A(q,p) = 0.0;  // This element is eliminated

        for (std::size_t i = 0; i < n; i++) {
            if (i != p && i != q) {
                double aip = c * A(i,p) - s * A(i,q);
                double aiq = s * A(i,p) + c * A(i,q);
                A(i,p) = A(p,i) = aip;
                A(i,q) = A(q,i) = aiq;
            }
        }
        A(p,p) = app;
        A(q,q) = aqq;

        // Update eigenvectors
        for (std::size_t i = 0; i < n; i++) {
            double vip = c * eigenvectors(i,p) - s * eigenvectors(i,q);
            double viq = s * eigenvectors(i,p) + c * eigenvectors(i,q);
            eigenvectors(i,p) = vip;
            eigenvectors(i,q) = viq;
        }
    }

    // Extract eigenvalues
    eigenvalues.resize(n);
    for (std::size_t i = 0; i < n; i++) {
        eigenvalues[i] = A(i,i);
    }

    // Sort eigenvalues and eigenvectors in descending order
    eig_sort();
}
// Function to sort eigenvalues and eigenvectors in descending order
// to highlight the principal components
void SquareMatrix::eig_sort() {
    // we use a vector of pairs to store the eigenvalues and eigenvectors
    std::vector<std::pair<double, std::vector<double>>> eigenPairs;
    eigenPairs.reserve(eigenvalues.size());

    // Step 1: Combine eigenvalues and eigenvectors into a single vector of pairs
    for (size_t i = 0; i < eigenvalues.size(); ++i) {
        eigenPairs.emplace_back(std::make_pair(eigenvalues[i], eigenvectors.getCol(i)));
    }

    // Step 2: Sort by eigenvalue in descending order
    std::sort(eigenPairs.begin(), eigenPairs.end(),
        [](auto& a, auto& b) {
            return a.first > b.first;
        });

    // Step 3: Unpack sorted values back into eigenvalues and eigenvectors
    for (size_t i = 0; i < eigenPairs.size(); ++i) {
        eigenvalues[i] = eigenPairs[i].first;
        eigenvectors.setCol(i, eigenPairs[i].second);
    }
}
// Function to print eigenvalues and eigenvectors
void SquareMatrix::eig_print() const {
    // Print the eigenvalues
    std::cout << "Eigenvalues:" << std::endl;
    for(auto eigenvalue : eigenvalues) {
        std::cout << eigenvalue << "\t";
    }
    std::cout << std::endl;
    // Print the eigenvectors
    std::cout << "Eigenvectors:" << std::endl;
    eigenvectors.print();
    std::cout << std::endl;
}
// Function to extract the requested number of principal components
Matrix SquareMatrix::extractPCs(int num_Pcs) const {
    Matrix result(rows, num_Pcs);
    // Extract the first num_Pcs eigenvectors
    for (int i = 0; i < num_Pcs; ++i) {
        result.setCol(i, eigenvectors.getCol(i));
    }
    return result;
}