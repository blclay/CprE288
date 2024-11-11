# Author: Phillip Jones
# Date: 10/30/2023
# Description: Client starter code that combines: 1) Simple GUI, 2) creation of a thread for
#              running the Client socket in parallel with the GUI, and 3) Simple receiving of mock sensor 
#              data for a server/cybot for collecting data from the CyBot.

# General Python tutorials (W3schools):  https://www.w3schools.com/python/

# Serial library:  https://pyserial.readthedocs.io/en/latest/shortintro.html 
import serial
import time  # Time library
# Socket library:  https://realpython.com/python-sockets/  
# See: Background, Socket API Overview, and TCP Sockets  
import socket
import tkinter as tk  # Tkinter GUI library
# Thread library: https://www.geeksforgeeks.org/how-to-use-thread-in-tkinter-python/
import threading
import os  # import function for finding absolute path to this python script

# Global variables for server connection
HOST = '192.168.1.1'  # Replace with CyBot's IP address when connected
PORT = 288        # Replace with CyBot's port number

# Function to send commands to the CyBot
def send_command(command):
    try:
        client_socket.sendall(command.encode())
    except Exception as e:
        print(f"Error sending command: {e}")

##### START Define Functions  #########

# Function to update the display with sensor data
def display_sensor_data(data):
    data_label.config(text=f"Sensor Data: {data}")

# Function to handle keypress events for driving
def keypress(event):
    key = event.keysym.lower()
    if key == 'w':
        send_command('FORWARD')
    elif key == 's':
        send_command('BACKWARD')
    elif key == 'a':
        send_command('LEFT')
    elif key == 'd':
        send_command('RIGHT')

# Main: Mostly used for setting up, and starting the GUI
def main():
    global win, data_label, client_socket

    # Set up the socket client
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((HOST, PORT))

    # Set up the GUI window
    win = tk.Tk()
    win.title("CyBot Control Interface")

    # Create sensor data label
    data_label = tk.Label(win, text="Sensor Data: N/A")
    data_label.pack()

    # Create driving buttons
    forward_btn = tk.Button(win, text="Forward", command=lambda: send_command('FORWARD'))
    forward_btn.pack()

    backward_btn = tk.Button(win, text="Backward", command=lambda: send_command('BACKWARD'))
    backward_btn.pack()

    left_btn = tk.Button(win, text="Turn Left", command=lambda: send_command('LEFT'))
    left_btn.pack()

    right_btn = tk.Button(win, text="Turn Right", command=lambda: send_command('RIGHT'))
    right_btn.pack()

    # Create Scan button to request sensor data
    scan_btn = tk.Button(win, text="Scan", command=request_sensor_data)
    scan_btn.pack()

    # Bind keypresses for driving
    win.bind('<KeyPress>', keypress)

    # Start the GUI loop
    win.mainloop()

# Function to request sensor data from the server
def request_sensor_data():
    send_command('SCAN')
    data = client_socket.recv(1024).decode()  # Receive data from CyBot
    display_sensor_data(data)  # Display sensor data on GUI

# Run the main function in a separate thread
thread = threading.Thread(target=main)
thread.start()
