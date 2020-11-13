#define FACE_EXPORTS
#include "opencv2/opencv.hpp"
#include "face_engine.h"
#include<string>
#include<typeinfo>

using namespace mirror;

int TestMask(int argc, char* argv[])
{
	// define variable
	const char* img_file = "../../data/images/no_mask.jpg";
	cv::Mat img_src = cv::imread(img_file);
	const char* root_path = "../../models";
	// init face engine
	FaceEngine* face_engine = new FaceEngine();
	// load model
	face_engine->LoadModel(root_path);
	// define face struct
	std::vector<FaceInfo> faces;
	double start = static_cast<double>(cv::getTickCount());
	// exec face detect (mask detect)
	face_engine->DetectFace(img_src, &faces);
	double end = static_cast<double>(cv::getTickCount());
	double time_cost = (end - start) / cv::getTickFrequency() * 1000;
	std::cout << "time cost: " << time_cost << "ms" << std::endl;

	int num_face = static_cast<int>(faces.size());
	for (int i = 0; i < num_face; ++i)
	{
		std::cout << "faces[i].mask: " << faces[i].mask_ << std::endl;
		if (faces[i].mask_)
		{	
			float score = faces[i].score_ * 100;
			std::string confidence = std::to_string(score).substr(0, 5) + "%";
			cv::rectangle(img_src, faces[i].location_, cv::Scalar(0, 255, 0), 2);
			std::cout << "Rect: " << faces[i].location_ << std::endl;
			//putText(img_src, confidence, faces[i].location_, cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(0,0,255,0), 2);
		}
		else
		{
			float score = faces[i].score_ * 100;
			std::string confidence = std::to_string(score).substr(0, 5) + "%";
			cv::rectangle(img_src, faces[i].location_, cv::Scalar(0, 0, 255), 2);
			std::cout << "Rect: " << faces[i].location_ << std::endl;
			// get coord for puttext
			std::cout << "type: " << typeid(faces[i].location_).name() << std::endl;;
			// std::cout << "left: " << rect.left << std::endl;

			putText(img_src, confidence, cv::Point2f(306, 402), cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(0,0,255), 2);
		}
		cv::imwrite("../../data/result/resultresult.jpg", img_src);
	}

	delete face_engine;
	face_engine = nullptr;

	return 0;
}


int main(int argc, char* argv[]) {
	return TestMask(argc, argv);
}
