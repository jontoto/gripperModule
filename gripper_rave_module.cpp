#include <openrave/openrave.h>
#include <openrave/plugin.h>
#include <boost/bind.hpp>
#include <vector>

using namespace std;
using namespace OpenRAVE;

namespace robotiq_gripper{
#define M1 0.5
#define M2 0.9

    class GripperFinger{
    private:
        vector<int> joints(3,0);
        int commandPos = 0;


        int m3(){
            return -55 +(43+55)/(255 - commandPos);
        }

    public:
        vector<int>& get_joint_values() const{
            return joints;
        }

        void no_obj_update_joints(){
            if(commandPos <= 110){
                joints[0] = M1*commandPos;
                joints[1] = 0;
                joints[2] = -M1*commandPos;
            }else if(commandPos <= 140){
                joints[0] = M1*commandPos;
                joints[1] = 0;
                jointsp[2] = -55.0 ;
            }else if(commandPos <= 240){
                joints[0] = 70.0;
                joints[1] = M2*(commandPos - 140);
                joints[2] = -55.0;
            }else{
                joints[0] = 70.0;
                joints[1] = 90.0;
                joints[2] = -55.0;
            }

            return;
        }

        void update_commandPos(int g){
            commandPos = g;
        }
    };

    class GripperModule : public ModuleBase
    {
    private:

        _description = "gives joint information for Robotiq s_model gripper (no object handling so far)";
        RegisterCommand("getJoints", )

    };
}