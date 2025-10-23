#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/media/inatel-crr/Dados/Eddy/ModulosGNU/gr-howto/lib
export PATH=/media/inatel-crr/Dados/Eddy/ModulosGNU/gr-howto/build/lib:$PATH
export LD_LIBRARY_PATH=/media/inatel-crr/Dados/Eddy/ModulosGNU/gr-howto/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-howto 
