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
        data = [datetime.now(), round(random.uniform(60.1,70), 2), round(random.uniform(60.1,70), 2), round(random.uniform(60.1,70), 2), round(random.uniform(60.1,70),), round(random.randint(0, 1), 2), round(random.uniform(27.1,27.5), 2), round(random.uniform(1.1, 1.3), 2)]
        writer.writerow(data)
        t.flush()

        time.sleep(1)