#include <vector>
#include "../common/common.h"
#include "opencv2/core.hpp"

#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
    #ifdef FACE_EXPORTS
        #define FACE_API __declspec(dllexport)
    #else
        #define FACE_API __declspec(dllimport)
    #endif
#else
    #define FACE_API __attribute__ ((visibility("default")))
#endif

namespace mirror {
class FaceEngine {
public:
	FACE_API FaceEngine();
	FACE_API ~FaceEngine();
	FACE_API int LoadModel(const char* root_path);
	FACE_API int DetectFace(const cv::Mat& img_src, std::vector<FaceInfo>* faces);

private:
	class Impl;
	Impl* impl_;

};

}
