#ifndef _FACE_DETECTER_H_
#define _FACE_DETECTER_H_

#include "opencv2/core.hpp"
#include "../common/common.h"

namespace mirror{
	// Abstract Class
	class Detecter
	{
		public:
			virtual ~Detecter() {};
			virtual int LoadModel(const char* root_path) = 0;
			// use struct FaceInfo in common.h
			virtual int DetectFace(const cv::Mat& img_src, std::vector<FaceInfo>* faces) = 0;

	};

	// Factory Base Factory
	class DetecterFactory
	{
		public:
			virtual Detecter* CreateDetecter() = 0;
			virtual ~DetecterFactory() {};
	};
	// Anti detector
	class AnticonvFactory : public DetecterFactory {
		public:
			AnticonvFactory() {}
			~AnticonvFactory() {}
			Detecter* CreateDetecter();
	};

}

#endif // !_FACE_DETECTER_H_
