/*
This is the declaration of the Matrix Class used in the Project
In order to practice I decided to implement it from scratch, creating only
the methods I need for the project
*/

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <string>

class Matrix{

    protected :
        std::size_t rows;
        std::size_t cols;
        std::vector<std::vector<double>> values;

    public :
        // constructor and destructor
        Matrix(std::size_t rows, std::size_t cols, double initial = 0);
        ~Matrix() = default;
        // common matrix methods and operators
        Matrix transpose() const;
        Matrix operator*(const Matrix&) const;
        Matrix operator+(const Matrix&) const;
        Matrix operator-(const Matrix&) const;
        Matrix operator*(double) const;
        double& operator()(std::size_t, std::size_t);
        double operator()(std::size_t, std::size_t) const;
        // print the matrix
        void print() const;
        // import the iris dataset
        std::vector<int> importIrisDataset(std::string&, int);
        // export the PCA results to a VTK file
        void exportToVTK(const std::vector<int>&, const std::string&);
        // center the data wrt feature means
        void centerData();
        // getters
        std::size_t getNumRows() const;
        std::size_t getNumCols() const;
        std::vector<std::vector<double>> getValues() const;
        std::vector<double> getRow(std::size_t) const;
        std::vector<double> getCol(std::size_t) const;
        // setters
        void setRow(std::size_t, const std::vector<double>&);
        void setCol(std::size_t, const std::vector<double>&);
        // import your dataset (to be implemented)
        // std::vector<int> importNameDataset(std::string&, int);
};

#endif