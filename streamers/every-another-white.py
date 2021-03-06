#!/usr/bin/env python

# Open Pixel Control client: Every other light to solid white, others dark.

import opc, time, os

numPairs = 720
client = opc.Client(os.getenv('OPC_SERVER'))

black = [ (255,255,255), (0,0,0) ] * numPairs
white = [ (0,0,0), (255,255,255) ] * numPairs

# Fade to white
for i in range(0,100):
	client.put_pixels(black)
	time.sleep(0.3)
	client.put_pixels(white)
	time.sleep(0.3)
