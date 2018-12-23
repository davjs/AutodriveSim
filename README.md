# AutoDriveSim
AutoDrive simulation using opendavinci

![Alt text](Diagram.png?raw=true)

### Instructions
This guide assumes you are using the [pre-built virtual machine image](http://www.cse.chalmers.se/%7Ebergerc/msv4/2015-01-22_MiniSmartVehicles4.ova) (user:msv)(pass:msv).
#### Download the Repository
```
cd ~
git clone git@github.com:davidkron/AutodriveSim.git
```
#### Compile and Install OpenDaVINCI
Create installation directory for the OpenDaVINCI code (this repository's code).
```
sudo mkdir /opt/odv
sudo chown msv:msv /opt/odv
```
Finally, compile and install.
```
cd ~/AutodriveSim
./build.sh
```
#### Run OpenDaVINCI
```
cd ~/AutodriveSim
./autodrive.sh
```

### Buildscripts
* **build.sh** - Generates and compiles makefiles (run this the first time and whenever you make cmake modifications)
* **compile.sh** - Only compiles from makefiles
* **autodrive.sh** - Runs the necessary components for simulation
