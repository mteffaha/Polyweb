#!/usr/bin/env python

from math import *

# Affichage du header
print("Content-type: text/plain\n")

for i in range(0, 100):
  line = ""
  for j in range(30+int(15*sin(float(i)/3))):
    line += ' '
  print(line + "x")
