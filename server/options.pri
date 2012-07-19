# options.pri
# vim:ft=qmake:fdm=marker:fmr=>>>,<<<:

PROJECT = delta3-server
VERSION = 0.0.1
TEST = 10

# List of variables to use in options header ------------------------------->>>1
OPTIONS_VARS = \
    PROJECT_NAME \
    TEST_INT
#---------------------------------------------------------------------------<<<1
# Options variables definition --------------------------------------------->>>1
PROJECT_NAME = $${PROJECT}
TEST_INT = $${TEST}
#---------------------------------------------------------------------------<<<1
