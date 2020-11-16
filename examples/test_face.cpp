#define FACE_EXPORTS
#include "opencv2/opencv.hpp"
#include "face_engine.h"
#include<string>
#include<typeinfo>
#include<dirent.h>

using namespace mirror;

int TestMask(int argc, char* argv[], const char* root_path, const char* test_dirs, std::string output)
{
	// init face engine
	double init_start = static_cast<double>(cv::getTickCount());
	FaceEngine* face_engine = new FaceEngine();
	// load model
	face_engine->LoadModel(root_path);
	// define face struct
	std::vector<FaceInfo> faces;
	double init_end = static_cast<double>(cv::getTickCount());
	double init_time_cost = (init_end - init_start) / cv::getTickFrequency() * 1000;
	std::cout << "time init cost: " << init_time_cost << "ms" << std::endl;
	// list data in directory
	struct dirent *entry;
	DIR *dir = opendir(test_dirs);
	if (dir == NULL)
	{
		std::cout << "Data directory empty !";
		return 0;
	}
	while((entry = readdir(dir)) != NULL)
	{	
		std::cout << "-------------------------------------------" << std::endl;
		// https://stackoverflow.com/questions/1330550/c-compare-char-array-with-string
		// check if value is not "." or ".." 
		if (strcmp(entry -> d_name, ".") != 0 && strcmp(entry -> d_name, "..") != 0)
		{
			
			const char* img_file = entry -> d_name;
			std::cout << "image: " << img_file << std::endl;
			// join path
			std::string full_path = std::string(test_dirs) + "/" + std::string(img_file);
			cv::Mat img_src = cv::imread(full_path);
			std::cout << "Shape: (" << img_src.rows << ", " << img_src.cols << ")" << std::endl;
			// --------------------------------------
			double start = static_cast<double>(cv::getTickCount());
			face_engine->DetectFace(img_src, &faces);
			double end = static_cast<double>(cv::getTickCount());
			double time_cost = (end - start) / cv::getTickFrequency() * 1000;
			std::cout << "time cost: " << time_cost << "ms" << std::endl;
			//
			int num_face = static_cast<int>(faces.size());
			for (int i = 0; i < num_face; ++i)
			{
				if (faces[i].mask_)
				{	
					float score = faces[i].score_ * 100;
					std::string confidence = std::to_string(score).substr(0, 5) + "%";
					cv::rectangle(img_src, faces[i].location_, cv::Scalar(0, 255, 0), 2);
					int x = faces[i].location_.x;
					int y = faces[i].location_.y;
					putText(img_src, confidence, cv::Point2f(x, y), cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(0,255,0), 2);
				}
				else
				{
					float score = faces[i].score_ * 100;
					std::string confidence = std::to_string(score).substr(0, 5) + "%";
					cv::rectangle(img_src, faces[i].location_, cv::Scalar(0, 0, 255), 2);
					// reference: https://docs.opencv.org/3.4/d2/d44/classcv_1_1Rect__.html
					int x = faces[i].location_.x;
					int y = faces[i].location_.y;
					putText(img_src, confidence, cv::Point2f(x, y), cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(0,0,255), 2);
				}

				// define output
				std::string output_path = output + + "/" + std::string(img_file);

				cv::imwrite(output_path, img_src);
			}
		}
		else
		{
			std::cout << "image empty !" << std::endl;
			continue;
		}
	}
	closedir(dir);
	delete face_engine;
	face_engine = nullptr;
	

	return 0;
}


int main(int argc, char* argv[])
{
	std::string output = "../../data/result";
	const char* root_path = "../../models";
	const char* test_dirs = "../../data/images";

	return TestMask(argc, argv, root_path, test_dirs, output);
}
