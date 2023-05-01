import serial
import time
from joblib import dump, load
from pyfiglet import Figlet
import warnings
from sklearn.exceptions import DataConversionWarning
warnings.filterwarnings(action='ignore', category=UserWarning)
from term import check_string

# Load the trained model
model = load('random_forest.joblib')

# Set up the serial connection
ser = serial.Serial('COM4', 115200) #change COM and baud rate according to requirement

# Print a header for the output
custom_fig = Figlet(font='small', width=160)
print(custom_fig.renderText('SIGN - ify'))

ser.reset_input_buffer()

# Menu screen
while True:
    ser.reset_input_buffer()
    print("Enter 1 to Convert to Text")
    print("Enter 2 to EXIT")
    choice = input("Enter choice: ")

    if choice == '1':
        while True:
            # Read the input from the serial monitor
            input_data = ser.readline().decode().strip()

            # Convert input_data to a 2D array
            input_data_2d = [[float(i) for i in input_data.split(',')]]

            # Make a prediction using the model
            prediction = model.predict(input_data_2d)[0]

            predictionf = check_string(str(prediction))

            pred  = Figlet(font='small', width=160)
            print(pred.renderText(predictionf))
            # Print the input and output
            # print('{}\n'.format(prediction))

            # Check if user wants to go back to menu screen
            if ser.in_waiting > 0:
                user_input = ser.readline().decode().strip()
                if user_input == '2':
                    break

            # Delay for 5 seconds
            time.sleep(2)
            ser.reset_input_buffer()

    elif choice == '2':
        print("Exiting the application...")
        break

    else:
        print("Invalid choice, please try again.")