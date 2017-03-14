#include <openrave/openrave.h>
#include <openrave/plugin.h>
#include <boost/bind.hpp>
#include <vector>
#include <math.h>

using namespace std;
using namespace OpenRAVE;

namespace robotiq_gripper{
#define M1 0.5
#define M2 0.9

    static inline double deg2rad(double angle){
        return angle *M_PI / 180.0}
    }

    class GripperModule : public ModuleBase
    {

    private:
        vector<double> joints(9);
        vector<int> commandPos(3);
        RobotBasePtr robot;
        
        void no_obj_update_joints(){
            for(int i = 0; i  < 3; i++){
                if(commandPos <= 110){
                    joints[i*3 +0] = deg2rad(M1*commandPos[i]);
                    joints[i*3 +1] = 0;
                    joints[i*3 +2] = deg2rad(-M1*commandPos[i]);
                }else if(commandPos <= 140){
                    joints[i*3 +0] = deg2rad(M1*commandPos[i]);
                    joints[i*3 +1] = 0;
                    joints[i*3 +2] = deg2rad(-55.0);
                }else if(commandPos <= 240){
                    joints[i*3 +0] = deg2rad(70.0);
                    joints[i*3 +1] = deg2rad(M2*(commandPos[i] - 140));
                    joints[i*3 +2] = deg2rad(-55.0);
                }else{
                    joints[i*3 +0] = deg2rad(70.0);
                    joints[i*3 +1] = deg2rad(90.0);
                    joints[i*3 +2] = deg2rad(-55.0);
                }
            
            }

            robot.SetDOFValues(joints);

            return;
        }

    public:
        GripperModule(EnvironmentBasePtr penv) : ModuleBase(penv){
            _description = "gives joint information for Robotiq s_model gripper (no object handling so far)";
            RegisterCommand("getJoints", boost::bind(GripperModule:: getJoints, this), "returns vector of joint values");
            RegisterCommand("update_commandPos", boost::bind(GripperModule::update_commandPos, this, _1), "updates the vector of command values for the fingers");
            RegisterCommand("getEffectorTransform")
            robot = GetEnv()->GetRobots()[0];
        }


        vector<vector<int> >&  getJoints() const{
            return joints;
        }

        void update_commandPos(const vector<int> g_new){
            commandPos = g_new;

            no_obj_update_joints();
        }
    };
}