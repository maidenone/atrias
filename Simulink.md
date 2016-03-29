  1. Make sure MATLAB is installed on your computer. Our controller generation script expects it to be installed at `/usr/local/MATLAB/R2012a`, but that can be changed in the script.
  1. Unzip Simulink controller to ``````rospack find simulink_controllers``````
  1. `rosrun atrias build_simulink_controller.sh`
  1. Edit `#include`s and `CMakeLists.txt` appropriately in the top level controller to link the shared library built in the previous step.