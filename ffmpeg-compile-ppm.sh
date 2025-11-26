#!/bin/bash

ffmpeg -i output-%02d.ppm -r 60 output.mp4
