#!/bin/bash 

# To run the GaAs irradiation

if [ -z ${FISPACT+x} ]; then
    echo "Environment variable FISPACT is not set, you need to set this to point to fispact executable. For example export FISPACT=/path/to/fispact"
    exit 1
fi

echo Running convert....
$FISPACT convert files &> /dev/null

echo Running collapse....
$FISPACT collapse files &> /dev/null

echo Running condense....
$FISPACT condense files &> /dev/null

echo Running execution....
$FISPACT runFile files &> /dev/null
