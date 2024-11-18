#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-10 // Tolerance for convergence

// Function to perform Householder reduction to Hessenberg form
void hessenbergReduction(int n, double **A, double **H) {
    int i, j, k;
    double norm, alpha, beta, *v = malloc(n * sizeof(double)), temp;

    // Copy A into H
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            H[i][j] = A[i][j];

    for (k = 0; k < n - 2; k++) {
        norm = 0.0;
        for (i = k + 1; i < n; i++)
            norm += H[i][k] * H[i][k];
        norm = sqrt(norm);

        if (norm < EPSILON) continue;

        alpha = H[k + 1][k] > 0 ? -norm : norm;
        beta = sqrt(2.0 * alpha * alpha - 2.0 * alpha * H[k + 1][k]);

        for (i = 0; i < n; i++) v[i] = 0.0;
        v[k + 1] = (H[k + 1][k] - alpha) / beta;
        for (i = k + 2; i < n; i++)
            v[i] = H[i][k] / beta;

        for (i = 0; i < n; i++) {
            temp = 0.0;
            for (j = k + 1; j < n; j++)
                temp += v[j] * H[j][i];
            for (j = k + 1; j < n; j++)
                H[j][i] -= 2.0 * v[j] * temp;
        }

        for (i = 0; i < n; i++) {
            temp = 0.0;
            for (j = k + 1; j < n; j++)
                temp += v[j] * H[i][j];
            for (j = k + 1; j < n; j++)
                H[i][j] -= 2.0 * v[j] * temp;
        }
    }

    free(v);
}

// Function to apply Jacobi rotation
void jacobiRotation(double **H, int p, int q, double c, double s, int n) {
    double temp;

    // Update rows
    for (int j = 0; j < n; j++) {
        temp = c * H[p][j] - s * H[q][j];
        H[q][j] = s * H[p][j] + c * H[q][j];
        H[p][j] = temp;
    }

    // Update columns
    for (int i = 0; i < n; i++) {
        temp = c * H[i][p] - s * H[i][q];
        H[i][q] = s * H[i][p] + c * H[i][q];
        H[i][p] = temp;
    }
}

// Function to perform QR iteration with Wilkinson's shift and Jacobi rotations
void qrAlgorithm(int n, double **H, double *eigenvalues) {
    int i, iter, p, q;
    double mu, t, c, s, norm, offDiagonalNorm;

    for (iter = 0; iter < 1000; iter++) {
        // Check for deflation
        for (i = n - 1; i > 0; i--) {
            if (fabs(H[i][i - 1]) < EPSILON) {
                H[i][i - 1] = 0.0;
                break;
            }
        }

        // Wilkinson's shift
        double d = (H[n - 2][n - 2] - H[n - 1][n - 1]) / 2.0;
        mu = H[n - 1][n - 1] - (H[n - 1][n - 2] * H[n - 1][n - 2]) / 
             (d + copysign(sqrt(d * d + H[n - 1][n - 2] * H[n - 1][n - 2]), d));

        // Shift H
        for (i = 0; i < n; i++)
            H[i][i] -= mu;

        // Jacobi rotations to diagonalize
        for (p = 0; p < n - 1; p++) {
            for (q = p + 1; q < n; q++) {
                t = (H[q][q] - H[p][p]) / (2 * H[p][q]);
                t = copysign(1.0, t) / (fabs(t) + sqrt(1 + t * t));
                c = 1 / sqrt(1 + t * t);
                s = t * c;

                jacobiRotation(H, p, q, c, s, n);
            }
        }

        // Undo shift
        for (i = 0; i < n; i++)
            H[i][i] += mu;

        // Check for convergence
        offDiagonalNorm = 0.0;
        for (i = 1; i < n; i++)
            offDiagonalNorm += fabs(H[i][i - 1]);
        if (offDiagonalNorm < EPSILON)
            break;
    }

    // Extract eigenvalues
    for (i = 0; i < n; i++)
        eigenvalues[i] = H[i][i];
}

// Main function
int main() {
    int n;

    printf("Enter the size of the matrix (n x n): ");
    scanf("%d", &n);

    // Dynamically allocate memory for the matrix and arrays
    double **A = malloc(n * sizeof(double *));
    double **H = malloc(n * sizeof(double *));
    double *eigenvalues = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        A[i] = malloc(n * sizeof(double));
        H[i] = malloc(n * sizeof(double));
    }

    printf("Enter the elements of the matrix row-wise:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    hessenbergReduction(n, A, H);
    qrAlgorithm(n, H, eigenvalues);

    printf("\nEigenvalues:\n");
    for (int i = 0; i < n; i++) {
        printf("%.6f\n", eigenvalues[i]);
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(H[i]);
    }
    free(A);
    free(H);
    free(eigenvalues);

    return 0;
}
