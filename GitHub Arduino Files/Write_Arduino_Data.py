
import datetime as datetime
import time
import serial
import requests
import json
# --------------------------------------------------------------------- #


def main():

# Change these based on what your COM ports are #
    serialPort1 = "COM5"   # Arduino 1 #
    serialPort2 = "COM4"   # Arduino 2 #
    serialPort3 = "COM6"   # Arduino 3 #
    serialPort4 = "COM10"  # Arduino 4 #
    serialPort5 = "COM9"   # Arduino 5 #
    serialPort6 = "COM8"   # Arduino 6 #

# Change these based on what your desired baudRates are #
    baudRate = 9600
    ser1 = serial.Serial(serialPort1, baudRate, timeout=None)
    ser2 = serial.Serial(serialPort2, baudRate, timeout=None)
    ser3 = serial.Serial(serialPort3, 19200, timeout=None)
    ser4 = serial.Serial(serialPort4, baudRate, timeout=None)
    ser5 = serial.Serial(serialPort5, baudRate, timeout=None)
    ser6 = serial.Serial(serialPort6, baudRate, timeout=None)

# Set the amount of time to wait #
    time.sleep(2)

# Change the order in which the serial boards print, add or remove boards #
    print(ser1.isOpen(), ser2.isOpen(), ser3.isOpen(), ser4.isOpen(), ser5.isOpen(), ser6.isOpen())
    print('---------------------------------------------------------------------------------------------------')

# Output these column labels for the columns of data to be printed #
    print("Datetime, "
          "temp_LNS_1, temp_LNS_2, temp_LNS_3, temp_LNS_4, "
          "temp_sensor, hum_sensor, temp_outside, hum_outside, temp_upper, hum_upper, "
          "temp_intake, hum_intake, temp_outflow, hum_outflow, "
          "V_CO2_below, V_CO2_lower,V_CO2_upper, V_CO2_above, V_CO2_sensor, CO2_Tank, "
          "ORP_LNS_1, DO_LNS_1, pH_LNS_1, EC_LNS_1, Water_Dose_1, ORP_LNS_2, DO_LNS_2, pH_LNS_2, EC_LNS_2,"
          " Water_Dose_2, pH_Dose_1, pH_Dose_2, EC_Dose_1, EC_Dose_2, " 
          "ORP_LNS_3, DO_LNS_3, pH_LNS_3, EC_LNS_3, Water_Dose_3, ORP_LNS_4, DO_LNS_4, pH_LNS_4, EC_LNS_4,"
          " Water_Dose_4, pH_Dose_3, pH_Dose_4, EC_Dose_3, EC_Dose_4, "
          "Person_1, Person_2, Person_3, Door_Open")

    while True:
        time.sleep(1)
        stream1 = ser1.readline().decode('utf-8', errors='replace').strip()
        time.sleep(0.1)
        stream2 = ser2.readline().decode('utf-8', errors='replace').strip()
        time.sleep(0.1)
        stream3 = ser3.readline().decode('utf-8', errors='replace').strip()
        time.sleep(0.1)
        stream4 = ser4.readline().decode('utf-8', errors='replace').strip()
        time.sleep(0.1)
        stream5 = ser5.readline().decode('utf-8', errors='replace').strip()
        time.sleep(0.1)
        stream6 = ser6.readline().decode('utf-8', errors='replace').strip()


    # --------------------------------------------------------------------- ##
    # --------------------------------------------------------------------- ##


    # Prints datetime and sensor data to serial monitor

        print(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"), ",", stream1, stream2, stream3, stream4,
              stream5, stream6)

        Data = (datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"), ",", stream1, stream2, stream3, stream4,
                stream5, stream6)


    # --------------------------------------------------------------------- ##
    # --------------------------------------------------------------------- ##

        # Create a .txt file and append to it continuously with new data #
        with open('System_Data.txt', 'a') as f:
            f.writelines('\n')
            f.writelines(''.join(Data))
            f.close()


if __name__ == '__main__':
    main()