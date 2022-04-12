#include "ltslam/RosParamServer.h"

RosParamServer::RosParamServer()
    : nh(nh_super)
{
    nh.param<std::string>("ltslam/sessions_dir", sessions_dir_, "/");
    nh.param<std::string>("ltslam/central_sess_name", central_sess_name_, "01");
    nh.param<std::string>("ltslam/query_sess_name", query_sess_name_, "02");

    // nh.param<std::string>("ltslam/save_directory", save_directory_, "/LTslam/"); // it means /.../home/LTslam/
    save_directory_ = sessions_dir_ + "/" + query_sess_name_ + "/update/out/";

    if (access(save_directory_.c_str(), 6) != 0)
    {
        int out_create = mkdir(save_directory_.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
        if (!out_create)
            printf("create save_directory_:%s\n", save_directory_.c_str());
        else
            printf("create save_directory_ failed! error code : %d \n", out_create);
    }

    int unused = system((std::string("exec rm -r ") + save_directory_).c_str());
    unused = system((std::string("mkdir -p ") + save_directory_).c_str());

    nh.param<bool>("ltslam/is_display_debug_msgs", is_display_debug_msgs_, true);

    nh.param<int>("ltslam/numberOfCores", numberOfCores, 4);

    nh.param<int>("ltslam/kNumSCLoopsUpperBound", kNumSCLoopsUpperBound, 10);
    nh.param<int>("ltslam/kNumRSLoopsUpperBound", kNumRSLoopsUpperBound, 10);

    nh.param<float>("ltslam/RSLoopsThreshold", RSLoopsThreshold, 10.0);
    nh.param<float>("ltslam/SCloopFitnessScoreThreshold", SCloopFitnessScoreThreshold, 0.5);
    nh.param<float>("ltslam/RSloopFitnessScoreThreshold", RSloopFitnessScoreThreshold, 0.5);

    usleep(100);
} // ctor RosParamServer
