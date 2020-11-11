#include "face_engine.h"
#include <iostream>

#include "detecter/detecter.h"


namespace mirror {
class FaceEngine::Impl
{
  public:
      Impl() {
          detecter_factory_ = new AnticonvFactory();
          detecter_ = detecter_factory_->CreateDetecter();
          initialized_ = false;
      }
      // Destroy
      ~Impl() {
          if (detecter_factory_)
          {
              delete detecter_factory_;
              detecter_factory_ = nullptr;
          }
      }

      int LoadModel(const char* root_path) {
          if (detecter_->LoadModel(root_path) != 0) {
              std::cout << "load face detecter failed." << std::endl;
              return 10000;
          }
          initialized_ = true;

          return 0;
      }
      inline int DetectFace(const cv::Mat& img_src, std::vector<FaceInfo>* faces) {
          return detecter_->DetectFace(img_src, faces);
      }

  private:
      DetecterFactory* detecter_factory_ = nullptr;

  private:
      bool initialized_;
      Detecter* detecter_ = nullptr;
};

FaceEngine::FaceEngine()
{
    impl_ = new FaceEngine::Impl();
}

FaceEngine::~FaceEngine()
{
    if (impl_) {
        delete impl_;
        impl_ = nullptr;
    }
}

int FaceEngine::LoadModel(const char* root_path)
{
    return impl_->LoadModel(root_path);
}

int FaceEngine::DetectFace(const cv::Mat& img_src, std::vector<FaceInfo>* faces)
{
    return impl_->DetectFace(img_src, faces);
}
}
