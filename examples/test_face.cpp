#define FACE_EXPORTS
#include "opencv2/opencv.hpp"
#include "face_engine.h"

using namespace mirror;

int TestMask(int argc, char* argv[]) {

	const char* img_file = "../../data/images/minh_tung.jpg";
	cv::Mat img_src = cv::imread(img_file);
	const char* root_path = "../../models";

	FaceEngine* face_engine = new FaceEngine();
	face_engine->LoadModel(root_path);
	std::vector<FaceInfo> faces;
	double start = static_cast<double>(cv::getTickCount());
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
			cv::rectangle(img_src, faces[i].location_, cv::Scalar(0, 255, 0), 2);
		}
		else
		{
			cv::rectangle(img_src, faces[i].location_, cv::Scalar(0, 0, 255), 2);
		}
		cv::imwrite("../../data/images/result/resultresult.jpg", img_src);
	}

	delete face_engine;
	face_engine = nullptr;

	return 0;
}


int main(int argc, char* argv[]) {
	return TestMask(argc, argv);
}
