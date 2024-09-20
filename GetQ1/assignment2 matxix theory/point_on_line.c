#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

void calculate_point(Point A, Point B, double ratioA, double ratioB, Point *P) {
    P->x = (ratioB * A.x + ratioA * B.x) / (ratioA + ratioB);
    P->y = (ratioB * A.y + ratioA * B.y) / (ratioA + ratioB);
}

int main() {
    // Define points A and B
    Point A = {7, -6}; // Updated Point A
    Point B = {3, 4};  // Point B
    double ratioA = 1; // Ratio part for point A
    double ratioB = 2; // Ratio part for point B

    Point P; // Renamed point C to P
    calculate_point(A, B, ratioA, ratioB, &P);

    // Output results
    printf("%lf %lf %lf %lf %lf %lf\n", A.x, A.y, B.x, B.y, P.x, P.y);
    return 0;
}
