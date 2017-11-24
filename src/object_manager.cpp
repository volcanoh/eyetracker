#include "object_manager.h"


ObjectManager::ObjectManager() {
}

ObjectManager::~ObjectManager() {
}

ObjectManager ObjectManager::instance_;

int ObjectManager::RegisterObject(Object* object) {
  int id = CreateObjectId();
  object->SetId(id);
  objects_[id] = object;
  return id;
}

int ObjectManager::CreateObjectId() {
  static int id = 0;
  return id++;
}

void ObjectManager::SetTransformation(int id1, int id2, const cv::Matx31d& rvec, const cv::Matx31d& tvec) {
  MatRt mat_rt(rvec, tvec);
  IdPair id_pair = std::make_pair(id1, id2);
  transformation_maps_[id_pair] = mat_rt;
}

void ObjectManager::GetTransformation(int id1, int id2, cv::Matx31d& rvec, cv::Matx31d& tvec) {
  MatRt mat_rt;
  IdPair id_pair = std::make_pair(id1, id2);
  mat_rt = transformation_maps_[id_pair];
  rvec = mat_rt.rvec;
  tvec = mat_rt.tvec;
}
