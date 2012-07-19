# options.pri
# vim:ft=qmake:fdm=marker:fmr=>>>,<<<:

PROJECT = delta3-server
VERSION = 0.0.1

# List of variables to use in configuration header ------------------------->>>1
CONFIG_VARS = \
    PROJECT_NAME
#---------------------------------------------------------------------------<<<1
# Configuration variables definition --------------------------------------->>>1
PROJECT_NAME = $${PROJECT}
#---------------------------------------------------------------------------<<<1
