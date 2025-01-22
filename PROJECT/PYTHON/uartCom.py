import serial
import threading
import csv
import time
import re

# Configuration du port série
SERIAL_PORT = "COM4"  # Port série utilisé
BAUD_RATE = 115200    # Débit en bauds
TIMEOUT = 1           # Temps d'attente pour les lectures (en secondes)
CSV_FILE = "sensor_data.csv"  # Nom du fichier CSV pour sauvegarder les données
SEND_INTERVAL = 10    # Intervalle d'envoi (en secondes)
DUTY = 10

# Initialisation du port série
try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=TIMEOUT)
    print(f"Connecté à {SERIAL_PORT} à {BAUD_RATE} bauds.")
except serial.SerialException as e:
    print(f"Erreur : Impossible de se connecter au port série {SERIAL_PORT}.")
    exit()

# Initialisation du fichier CSV
with open(CSV_FILE, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Horodatage", "CO2 (ppm)", "Température (°C)", "Humidité (%RH)"])  # En-têtes

# Fonction pour envoyer des données périodiquement
def periodic_send():
    while True:
        time.sleep(SEND_INTERVAL)  # Attente de l'intervalle défini
        if ser.is_open:
            if(DUTY<=90):
                DUTY = DUTY + 10
            else :
                DUTY = 0
            
            ser.write(message.encode())  # Envoi du message
            print(f"Commande envoyée : {message}")

# Fonction pour lire, extraire et sauvegarder les données
def read_data():
    while True:
        if ser.is_open:
            try:
                # Lire les données reçues
                data = ser.readline().decode().strip()
                if data:
                    print(f"Données reçues : {data}")

                    # Extraire les valeurs avec une expression régulière
                    match = re.search(
                        r"Measured CO2 concentration: ([\d\.]+) ppm, Measured temperature: ([\d\.]+) degC, Measured humidity: ([\d\.]+) %RH",
                        data,
                    )
                    if match:
                        co2 = float(match.group(1))
                        temperature = float(match.group(2))
                        humidity = float(match.group(3))
                        timestamp = time.strftime("%Y-%m-%d %H:%M:%S")

                        # Sauvegarder dans le fichier CSV
                        with open(CSV_FILE, mode='a', newline='') as file:
                            writer = csv.writer(file)
                            writer.writerow([timestamp, co2, temperature, humidity])

                        # Afficher les valeurs extraites
                        print(
                            f"[{timestamp}] CO2: {co2} ppm, Température: {temperature} °C, Humidité: {humidity} %RH"
                        )
            except Exception as e:
                print(f"Erreur lors de la lecture : {e}")

# Lancer les threads pour l'envoi périodique et la lecture
try:
    send_thread = threading.Thread(target=periodic_send, daemon=True)
    read_thread = threading.Thread(target=read_data, daemon=True)

    send_thread.start()
    read_thread.start()

    send_thread.join()  # Laisser le thread principal actif
except KeyboardInterrupt:
    print("\nInterruption par l'utilisateur.")
finally:
    if ser.is_open:
        ser.close()
    print("Port série fermé.")
