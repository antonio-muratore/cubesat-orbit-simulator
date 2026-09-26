#include <stdio.h>
#include <math.h>

int main() {
    // 1. Costanti fisiche
    double mu = 3.986004418e14; // Costante gravitazionale terrestre (m^3/s^2)
    double R_E = 6371000.0;     // Raggio della Terra (m)
    double h = 400000.0;        // Quota del CubeSat (400 km)
    double PI = 3.141592653589793;
    
    // 2. Condizioni Iniziali (Orbita Circolare)
    double r_mag = R_E + h;
    double v_mag = sqrt(mu / r_mag); 
    
    double x = r_mag, y = 0.0, z = 0.0;
    double vx = 0.0, vy = v_mag, vz = 0.0;
    
    // 3. Calcolo del Periodo Orbitale (Terza Legge di Keplero)
    double t_max = 2.0 * PI * sqrt(pow(r_mag, 3) / mu);
    printf("Periodo orbitale calcolato: %.1f secondi (circa %.1f minuti)\n", t_max, t_max / 60.0);
    
    // 4. Impostazioni della Simulazione
    double dt = 0.01;                    // Passo fisico: altissima precisione (10 millisecondi)
    double intervallo_salvataggio = 1.0; // Salva i dati nel file ogni 1 secondo
    int passi_per_salvataggio = (int)(intervallo_salvataggio / dt); 
    int i = 0;
    
    FILE *file = fopen("orbit.csv", "w");
    if (file == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    fprintf(file, "t,        x,        y,        z\n"); 
    
    // 5. Ciclo di Integrazione di Eulero-Cromer
    for (double t = 0.0; t <= t_max; t += dt) {
        
        // Salva i dati solo quando serve (risparmio di memoria)
        if (i % passi_per_salvataggio == 0) {
            fprintf(file, "%.1f,  %.3f,  %.3f,  %.3f\n", t, x, y, z);
        }
        
        // Fisica
        double r3 = pow(x*x + y*y + z*z, 1.5);
        
        double ax = -mu * x / r3;
        double ay = -mu * y / r3;
        double az = -mu * z / r3;
        
        vx += ax * dt;
        vy += ay * dt;
        vz += az * dt;
        
        x += vx * dt;
        y += vy * dt;
        z += vz * dt;
        
        i++;
    }
    
    fclose(file);
    printf("Simulazione completata. Dati salvati in orbit.csv\n");
    return 0;
}