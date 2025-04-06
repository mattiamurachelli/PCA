% This script contains an example of PCA (Principal Component Analysis)
% performed on the fisheriris dataset 

close all;
clear all;

% load the dataset (present in the 'Statistics and Machine Learning
% Toolbox)
load fisheriris.mat;
% and extract features and class labels (use help fisheriris.mat to see
% dataset structure)
X = meas;
Y = species;
% Since we want to use PCA for binary classification and the dataset has 3
% classes (Setosa, Virginica and Versicolor) we group the last two classes
Y = categorical(Y);
Y_binary = zeros(length(Y), 1);
for i = 1:length(Y)
    if(Y(i) == 'setosa')
        Y_binary(i) = 1;
    else
        Y_binary(i) = 0;
    end
end
% Now that we created our dataset, we need to compute the covariance matrix
% we begin by scaling the data in order to have zero mean
feature_means = zeros(size(X,2), 1);
for i = 1:size(X,2)
    partial_sum = 0;
    for j = 1:size(X,1)
        partial_sum = partial_sum + X(j,i);
    end
    feature_means(i) = partial_sum/size(X,1);
end
% we subtract the mean from the dataset matrix
X_tilde = zeros(size(X));
for i = 1:size(X,1)
    for j = 1:size(X,2)
        X_tilde(i,j) = X(i,j) - feature_means(j);
    end
end
% and then compute C = X_tilde' * X_tilde
C = zeros(size(X_tilde,2));
for i = 1:size(X_tilde,2)
    for j = 1:size(X_tilde,2)
        partial_sum = 0;
        for k = 1:size(X_tilde,1)
            partial_sum = partial_sum + X_tilde(k,i)*X_tilde(k,j);
        end
        C(i,j) = partial_sum;
    end
end
% Now that we have the covariance matrix we need to find its eigenvalues
% and eigenvectors
[W, Eigenvalues] = eig(C);
% Since eig() returns a diagonal matrix for the eigenvalues, we convert it
% to a vector
Eigenvalues = diag(Eigenvalues);
% Now we reorder the Eigenvalues vector in decreasing order maintaining
% coherence in the loadings matrix (W)
[Eigenvalues, index] = sort(Eigenvalues, 'descend');
 W = W(:, index);
% Now we decide the number of Principal Components we want to use
% (suggested = 2)
nPCs = 2;
% and perform the mapping wrt Principal Components axis
T = zeros(size(X_tilde, 1), nPCs);
for i = 1:size(X_tilde,1)
    for j = 1:nPCs
        partial_sum = 0;
        for k = 1:size(X_tilde, 2)
            partial_sum = partial_sum + X_tilde(i,k)*W(k,j);
        end
        T(i,j) = partial_sum;
    end
end
% Now we are ready to print our dataset wrt this new axes to see if the
% features extracted with PCA are able to linearly separate our dataset
figure()
hold on;
for i = 1:length(Y_binary)
    if(Y_binary(i) == 1)
        setosa = plot(T(i,1), T(i,2), '*r');
    else
        not_setosa = plot(T(i,1), T(i,2), '*b');
    end
end
hold off;
xlabel('First Principal Component');
ylabel('Second Principal Component');
title('PCA of the Iris Dataset')
legend([setosa, not_setosa], 'setosa', 'not setosa');