# libremotecontrol
simple proof-of-concept library for controlling a RC vehicle via LAN.
This Library depends on boost::asio and C++11/C++14.

Don't use this library if you expect any safety or security!
Connection loss will lead to unsafe behaviour of the controlled device.
I use it for some experiments with RaspberryPi-based tracked vehicles.

What needs to be added to get a nice lib:
* add configurable failsafe mode (failsafe state has to be sent to the device on connection setup)
* resend all speed/position values after some milliseconds (100 - 200 should be OK)
* add encryption and authorization
* Add proper source code documentation
* Add a manual
