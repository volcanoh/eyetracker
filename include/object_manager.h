#pragma once

#include <object.h>

struct MatRt {
  cv::Matx31d rvec;
  cv::Matx31d tvec;
  MatRt(const cv::Matx31d rv, const cv::Matx31d tv) :
    rvec(rv),
    tvec(tv) {
    }
  MatRt(){}
  MatRt& operator=(const MatRt& m) {
    rvec = m.rvec;
    tvec = m.tvec;
    return *this;
  }
};

class ObjectManager {
 public:
  using IdPair = std::pair<int, int>;

  static ObjectManager& GetInstance() {
    return instance_;
  }

  int RegisterObject(Object*);

  void SetTransformation(int id1, int id2, const cv::Matx31d& rvec, const cv::Matx31d& tvec);
  bool GetTransformation(int id1, int id2, cv::Matx31d& rvec, cv::Matx31d& tvec);

 private:
  static ObjectManager instance_;
  ObjectManager();
  ~ObjectManager();

  std::map<IdPair, MatRt> transformation_maps_; // access tranformation mat by id-id
  std::map<int, Object*> objects_; // access object by id

  int CreateObjectId();
};


