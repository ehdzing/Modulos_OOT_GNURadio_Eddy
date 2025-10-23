#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/media/inatel-crr/Dados/Eddy/ModulosGNU/gr-howto/python
export PATH=/media/inatel-crr/Dados/Eddy/ModulosGNU/gr-howto/build/python:$PATH
export LD_LIBRARY_PATH=/media/inatel-crr/Dados/Eddy/ModulosGNU/gr-howto/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/media/inatel-crr/Dados/Eddy/ModulosGNU/gr-howto/build/swig:$PYTHONPATH
/usr/bin/python2 /media/inatel-crr/Dados/Eddy/ModulosGNU/gr-howto/python/qa_square_ff.py 
