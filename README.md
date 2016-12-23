# sonoff-basic
Basic sketch for Arduino reprogramming of the SONOFF device

After soldering a 5 pin header onboard and connecting your 3.3v programmer up, just flash using the Arduino studio.

This sketch listens to MQTT, when the topic lights/lounge is 1 the light will turn on, anything else on the topic will turn the light off.

The onboard GREEN led will illuminate to show the relay state, the onboard button does nothing.
