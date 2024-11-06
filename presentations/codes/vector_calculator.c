// vector_calculator.c
#include <stdio.h>

int main() {
    // Normal vector for the line x + y = 4
    int normal_vector[] = {1, 1}; // Coefficients of x and y
    // Direction vector, perpendicular to the normal vector
    int direction_vector[] = {1, -1}; // Any vector perpendicular to the normal

    // Output the vectors
    printf("Normal Vector: [%d, %d]\n", normal_vector[0], normal_vector[1]);
    printf("Direction Vector: [%d, %d]\n", direction_vector[0], direction_vector[1]);

    // Calculate and print line points
    printf("Line Points: ");
    for (int x = -8; x <= 8; x++) {
        int y = 4 - x; // y = 4 - x
        printf("[%d, %.2f]", x, (float)y); // Format to two decimal places
        if (x < 8) {
            printf(", "); // Add comma except for the last point
        }
    }
    printf("\n");

    return 0;
}

