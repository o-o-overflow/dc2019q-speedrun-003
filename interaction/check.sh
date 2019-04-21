#!/bin/sh -e

RESULT=$(echo "adam" | nc "$1" "$2")

echo "$RESULT" | grep "Think you can drift?"
echo "$RESULT" | grep "Send me your drift"
echo "$RESULT" | grep "You're not ready."

RESULT=$(python -c "print('a'*29 + '\x00')" | nc "$1" "$2")
echo "$RESULT" | grep "You're not up to regulation."

RESULT=$(python -c "print('a'*29 + '\x90')" | nc "$1" "$2")
echo "$RESULT" | grep "Sleeping on the job, you're not ready."

RESULT=$(python -c "print('a'*29 + '\x19')" | nc "$1" "$2")
echo "$RESULT" | grep "This is a special race, come back with better."


