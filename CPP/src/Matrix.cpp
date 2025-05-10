/*
In this file we have the definition of the Matrix class methods
*/
#include <vector>
#include <iostream>
#include "Matrix.hpp"
#include "json.hpp"
#include <fstream>
#include <string>
using json = nlohmann::json;

// Constructor
Matrix::Matrix(std::size_t rows, std::size_t cols, double initial) : rows(rows), cols(cols) {
    values.resize(rows, std::vector<double>(cols, initial));
}

// Transpose method
Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for(std::size_t i=0; i < rows; ++i) {
        for(std::size_t j=0; j < cols; ++j) {
            result.values[j][i] = values[i][j];
        }
    }
    return result;
}

// Matrix multiplication operator
Matrix Matrix::operator*(const Matrix& other) const {
    if(cols != other.rows) {
        std::cerr << "Matrix dimensions do not match for multiplication" << std::endl;
    }
    Matrix result(rows, other.cols);
    for(std::size_t i=0; i < rows; ++i) {
        for(std::size_t j=0; j < other.cols; ++j) {
            for(std::size_t k=0; k < cols; ++k) {
                result.values[i][j] += values[i][k] * other.values[k][j];
            }
        }
    }
    return result;
}
// Matrix addition operator
Matrix Matrix::operator+(const Matrix& other) const {
    if(rows != other.rows || cols != other.cols){
        std::cerr << "Matrix dimensions do not match for addition" << std::endl;
    }
    Matrix result(rows, cols);
    for(std::size_t i=0; i < rows; ++i) {
        for(std::size_t j=0; j < cols; ++j) {
            result.values[i][j] = values[i][j] + other.values[i][j];
        }
    }
    return result;
}
// Matrix subtraction operator
Matrix Matrix::operator-(const Matrix& other) const {
    return (*this + (other * -1.0));
}
// Matrix scalar multiplication operator
Matrix Matrix::operator*(double scalar) const{
    Matrix result(rows, cols);
    for(std::size_t i=0; i < rows; ++i){
        for(std::size_t j=0; j < cols; ++j){
            result.values[i][j] = values[i][j] * scalar;
        }
    }
    return result;
}
// Matrix element access operator non const version
double& Matrix::operator()(std::size_t row, std::size_t col) {
    if(row >= rows || col >= cols) {
        std::cerr << "Index out of bounds" << std::endl;
    }
    return values[row][col];
}
// Matrix element access operator const version
double Matrix::operator()(std::size_t row, std::size_t col) const {
    if(row >= rows || col >= cols) {
        std::cerr << "Index out of bounds" << std::endl;
    }
    return values[row][col];
}
// Print method
void Matrix::print() const {
    for(std::size_t i=0; i < rows; ++i) {
        for(std::size_t j=0; j < cols; ++j) {
            std::cout << values[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
// Import Iris dataset method
// This method fills the feature matrix while also returning a vector containing the labels
std::vector<int> Matrix::importIrisDataset(std::string& filename, int num_samples) {
    // Open the JSON file
    std::ifstream file("iris.json");
    if (!file) {
        std::cerr << "Error: Cannot open JSON file!" << std::endl;
    }

    // Parse the JSON file
    json dataset;
    file >> dataset;
    file.close();

    // Create the labels vector
    std::vector<int> labels(num_samples);

    // Extract the data
    for(std::size_t i=0; i < rows; ++i) {
        values[i][0] = dataset[i]["sepalLength"].get<double>();
        values[i][1] = dataset[i]["sepalWidth"].get<double>();
        values[i][2] = dataset[i]["petalLength"].get<double>();
        values[i][3] = dataset[i]["petalWidth"].get<double>();
        // Convert the species to an integer label
        // Remember that we are separating setosa and not setosa
        if(dataset[i]["species"].get<std::string>() == "setosa")
            labels[i] = 1;
        else
            labels[i] = 0;
    }

    std::cout << "========================================================" << std::endl;
    std::cout << "Data imported successfully!" << std::endl;
    std::cout << "========================================================" << std::endl;
    
    // Return the labels vector
    return labels;
}
// Function to export the PCA results to a VTK file
void Matrix::exportToVTK(const std::vector<int>& labels, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file for writing: " << filename << '\n';
        return;
    }

    std::size_t num_points = rows;
    std::size_t dim = cols; // Should be 2 or 3

    file << "# vtk DataFile Version 3.0\n";
    file << "PCA output\n";
    file << "ASCII\n";
    file << "DATASET POLYDATA\n";
    file << "POINTS " << num_points << " float\n";

    for (std::size_t i = 0; i < num_points; ++i) {
        for (std::size_t j = 0; j < dim; ++j)
            file << (*this)(i, j) << " ";
        for (std::size_t j = dim; j < 3; ++j) // pad with 0.0 if 2D
            file << "0.0 ";
        file << "\n";
    }

    file << "\nPOINT_DATA " << num_points << "\n";
    file << "SCALARS label int\n";
    file << "LOOKUP_TABLE default\n";
    for (int label : labels)
        file << label << "\n";

    file.close();

    std::cout << "========================================================" << std::endl;
    std::cout << "VTK file written to " << filename << '\n';
    std::cout << "========================================================" << std::endl;
}
// Method that centers the data wrt the mean of the features
void Matrix::centerData() {
    Matrix ones(rows, 1, 1.0);
    Matrix feature_means(1, cols);

    // we begin by computing the mean of each feature
    for(std::size_t j=0; j < cols; ++j) {
        for(std::size_t i=0; i < rows; ++i) {
            feature_means(0, j) += values[i][j];
        }
        feature_means(0, j) /= rows;
    }

    // then we subtract features means row wise
    *this = *this - (ones * feature_means);
}
// Number of Rows getter
std::size_t Matrix::getNumRows() const {
    return rows;
}
// Number of Columns getter
std::size_t Matrix::getNumCols() const {
    return cols;
}
// Values getter
std::vector<std::vector<double>> Matrix::getValues() const {
    return values;
}
// Row getter
std::vector<double> Matrix::getRow(std::size_t row_index) const {
    std::vector<double> row(cols);
    for(std::size_t j=0; j < cols; ++j) {
        row[j] = values[row_index][j];
    }
    return row;
}
// Column getter
std::vector<double> Matrix::getCol(std::size_t col_index) const {
    std::vector<double> col(rows);
    for(std::size_t i=0; i < rows; ++i) {
        col[i] = values[i][col_index];
    }
    return col;
}
// Row setter
void Matrix::setRow(std::size_t row_index, const std::vector<double>& row_values) {
    if(row_index >= rows) {
        std::cerr << "Row index out of bounds" << std::endl;
    }
    if(row_values.size() != cols) {
        std::cerr << "Row size does not match matrix columns" << std::endl;
    }
    for(std::size_t j=0; j < cols; ++j) {
        values[row_index][j] = row_values[j];
    }
}
// Column setter
// Row setter
void Matrix::setCol(std::size_t col_index, const std::vector<double>& col_values) {
    if(col_index >= cols) {
        std::cerr << "Row index out of bounds" << std::endl;
    }
    if(col_values.size() != rows) {
        std::cerr << "Row size does not match matrix columns" << std::endl;
    }
    for(std::size_t i=0; i < rows; ++i) {
        values[i][col_index] = col_values[i];
    }
}

// This method is used to import your dataset
/* std::vector<int> Matrix::importNameDataset(std::string& filename, int num_samples) {
}*/