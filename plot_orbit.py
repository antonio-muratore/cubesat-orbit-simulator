import pandas as pd
import matplotlib.pyplot as plt

# Carica i dati generati dal tuo motore in C
dati = pd.read_csv('orbit.csv', skipinitialspace=True)

# Prepara la figura per il grafico 3D
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# Disegna l'orbita usando le colonne x, y, z del CSV
ax.plot(dati['x'], dati['y'], dati['z'], color='red', linewidth=2, label='Orbita CubeSat')

# Aggiungi un punto blu al centro (0,0,0) per rappresentare la Terra
ax.scatter(0, 0, 0, color='blue', s=100, label='Centro della Terra')

# Imposta i titoli
ax.set_title('Simulazione 3D Orbita - Portfolio PoliSpace')
ax.set_xlabel('X (m)')
ax.set_ylabel('Y (m)')
ax.set_zlabel('Z (m)')
ax.legend()

# Mostra il grafico
plt.show()