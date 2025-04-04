// SquareMatrix.hpp
// SquareMatrix class that expands the Matrix class through inheritance
// This class is needed in order to compute eigenvalues and eigenvectors

#ifndef SQUAREMATRIX_HPP
#define SQUAREMATRIX_HPP

#include "Matrix.hpp"

class SquareMatrix : public Matrix {
    private :
    // Square matrices have as extra members eigenvalues and eigenvectors
    std::vector<double> eigenvalues;
    Matrix eigenvectors;

    public :
    // Constructor and destructor
    SquareMatrix(std::size_t);
    ~SquareMatrix() = default;
    // Assignment operator for Matrix -> SquareMatrix conversion
    SquareMatrix& operator=(const Matrix&);
    // Eigenvalue and eigenvector related methods
    void eig();
    void eig_sort();
    void eig_print() const;
    Matrix extractPCs(int) const;
};
#endif