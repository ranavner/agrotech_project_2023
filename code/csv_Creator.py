import csv
import time
from datetime import datetime
import random

header = ['TIMESTAMP', 'Sensor 1', 'Sensor 2', 'Sensor 3', 'Sensor 4', 'is_motion', 'tmp', 'vpd']

# os.remove('fixed2.csv')

with open('csv/fixed2.csv', 'a') as t:
    writer = csv.writer(t)
    writer.writerow(header)
    for seconds in range(10000):
        data = [datetime.now(), random.randint(1,100), random.randint(1,100), random.randint(1,100), random.randint(1,100), random.randint(0, 1), random.randint(1,45), random.randint(0, 5)]
        writer.writerow(data)
        t.flush()

        time.sleep(1)