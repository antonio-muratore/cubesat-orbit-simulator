#include <stdio.h>
#include <math.h>

#define G 6.67430e-11
#define M_EARTH 5.972e24
#define R_EARTH 6371000.0

int main() {
    // initial conditions for a 400km LEO
    double alt = 400000.0;
    double r = R_EARTH + alt;
    
    double x = r;
    double y = 0.0;
    double z = 0.0;
    
    // velocity for circular orbit: v = sqrt(GM/r)
    double vx = 0.0;
    double vy = sqrt((G * M_EARTH) / r);
    double vz = 0.0;
    
    double t = 0.0;
    double dt = 1.0; 
    double total_time = 6000.0; // roughly one orbit (~90 mins)
    
    FILE *f = fopen("orbit.csv", "w");
    fprintf(f, "t,      x,        y,        z\n");
    
    while (t <= total_time) {
        // save data every 10 seconds to keep csv size reasonable
        if ((int)t % 10 == 0) {
            fprintf(f, "%.1f, %.3f, %.3f, %.3f\n", t, x, y, z);
        }
        
        double r_norm = sqrt(x*x + y*y + z*z);
        double ax = -G * M_EARTH * x / pow(r_norm, 3);
        double ay = -G * M_EARTH * y / pow(r_norm, 3);
        double az = -G * M_EARTH * z / pow(r_norm, 3);
        
        // semi-implicit Euler-Cromer: update velocity FIRST
        vx += ax * dt;
        vy += ay * dt;
        vz += az * dt;
        
        x += vx * dt;
        y += vy * dt;
        z += vz * dt;
        
        t += dt;
    }
    
    fclose(f);
    return 0;
}