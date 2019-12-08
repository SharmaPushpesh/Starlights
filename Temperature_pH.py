#!/usr/bin/env python
# coding: utf-8

# In[ ]:


import serial                           # Import serial module 
import time

ser = serial.Serial('COM3', 9600)       # Set up the serial line
time.sleep(2)                           # Time delay to read and record the data
                        
Temp = []                                # empty lists to store the data
pH =   []

for i in range(50):
    b = ser.readline()                  # read a byte string
    string_n = b.decode()               # decode byte string into Unicode  
    string = string_n.rstrip()          # remove \n and \r
    temp = string[0:5]                  # Choose the columns to separate incoming data
    ph = string[6:]
    Temp.append(temp)                   # Update the empty lists we created in the beginning
    pH.append(ph)
    time.sleep(0.1)                     # Time delay to collect more data

ser.close()                             # So it stops collecting data after reaching i range value

import matplotlib.pyplot as plt         # Import matplotlib for plotting
                                        # If using a Jupyter notebook include %matplotlib inline or %matplotlib notebook
get_ipython().run_line_magic('matplotlib', 'inline')

fig, ax = plt.subplots()                # Create axes and plot Temperature readings with customized plot

plt.plot(Temp)
plt.xlabel('Reading Value (#)')
plt.ylabel('Temperature (\u00b0 F)')
plt.title('Temperature Reading for Water Sample')
plt.show()

fig, ax = plt.subplots()                # Create axes and plot pH readings with customized plot

ax.plot(pH)
ax.set_xlabel('Reading Value (#)')
ax.set_ylabel('pH')
ax.set_title('pH Reading for Water Sample')
plt.show()

