#include <glog/logging.h>

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);

    LOG(INFO)  << "test for glog ";
    VLOG(0) << "test for glog ";
    
    CHECK_EQ(std::string("abc")[1], 'b') << "CHECK_EQ passed";

    int num_cookies = 11;
    LOG_IF(INFO, num_cookies > 10) << "Got lots of cookies";
    return 0;

}