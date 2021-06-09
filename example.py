import re


for i in re.finditer("^", "\n", re.M):
  print("Found match at index " + str( i.start() ))
