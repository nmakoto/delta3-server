# options.pri
# vim:ft=qmake:fdm=marker:fmr=>>>,<<<:

PROJECT = delta3-server
PROJECT_DESCRIPTION = "Universal remote control system"
VERSION = 0.0.1
DEVTEAM = bacwc

# List of variables to use in options header ------------------------------->>>1
OPTIONS_VARS = \
    PROJECT_NAME \
    DEV_TEAM \
    PROJECT_DESCRIPTION
#---------------------------------------------------------------------------<<<1
# Options variables definition --------------------------------------------->>>1
PROJECT_NAME = $${PROJECT}
DEV_TEAM = $${DEVTEAM}
#---------------------------------------------------------------------------<<<1
