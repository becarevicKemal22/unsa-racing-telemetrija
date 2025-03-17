import fastf1
import json
import os

# Enter race data
year = 2020
mode = 'R'
name = 'Italian Grand Prix'
race = fastf1.get_session(year, name, mode)
race.load()

# Get the coutry for the file name
country = race.event['Country'].replace(" ", "_")

# Choose the driver (example: Hamilton - HAM)
driver = 'HAM'
laps = race.laps.pick_drivers(driver)

# Getting data
telemetry_data = []
for _, lap in laps.iterlaps():
    telemetry = lap.get_telemetry()
    if telemetry.empty:
        continue
    for _, row in telemetry.iterrows():
        telemetry_data.append({
            "LapNumber": int(lap['LapNumber']),
            "Time": row['Time'].total_seconds(),
            "Speed": row['Speed'],
            "Gear": row['nGear']
        })

# Saving data into json file
file_name = f"{driver}_{year}{mode}_{country}.json"

with open(file_name, "w") as f:
    json.dump(telemetry_data, f, indent=4)
    
print(f"Data saved into: {file_name}")
