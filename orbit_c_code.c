#include <stdio.h>
#include <math.h>

#define G 6.67430e-11
#define M_EARTH 5.972e24
#define R_EARTH 6371000.0
#define PI 3.14159265359

int main() {
    double alt = 400000.0; // 400 km LEO
    double r = R_EARTH + alt;
    
    double x = r;
    double y = 0.0;
    double z = 0.0;
    
    // velocity for circular orbit
    double vx = 0.0;
    double vy = sqrt((G * M_EARTH) / r);
    double vz = 0.0;
    
    // kepler's 3rd law for exact period
    double period = 2.0 * PI * sqrt(pow(r, 3) / (G * M_EARTH));
    
    double t = 0.0;
    double dt = 0.01;
    int i = 0;
    
    FILE *f = fopen("orbit.csv", "w");
    if (f==NULL) {
        printf("\nError: could not create orbit.csv\n")
        return 1; //exit with error code
    }

    fprintf(f, "t    ,      x,      y,      z\n");
    
    while (t <= period) {
        // sample data every 1s of simulation
        if (i % 100 == 0) {
            fprintf(f, "%.2f, %.3f, %.3f, %.3f\n", t, x, y, z);
        }
        
        double r_norm = sqrt(x*x + y*y + z*z);
        double ax = -G * M_EARTH * x / pow(r_norm, 3);
        double ay = -G * M_EARTH * y / pow(r_norm, 3);
        double az = -G * M_EARTH * z / pow(r_norm, 3);
        
        // euler-cromer (velocity updated first)
        vx += ax * dt;
        vy += ay * dt;
        vz += az * dt;
        
        x += vx * dt;
        y += vy * dt;
        z += vz * dt;
        
        t += dt;
        i++;
    }
    
    fclose(f);
    return 0;
}