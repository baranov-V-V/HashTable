import pandas as pd
from matplotlib import pyplot as plt

file_name = input()

data = pd.read_csv(file_name)
bucket_id = data['BucketId']
bucket_size = data['BucketSize']

bins = [i / 2 for i in range(0,50)]

plt.hist(bucket_size, bins=bins, edgecolor='black')

plt.xlabel('Bucket size')
plt.ylabel('Number of buckets')

plt.show()
