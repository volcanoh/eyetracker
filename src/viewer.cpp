#include "viewer.h"

using namespace std;

Viewer::Viewer(const string &name)
	: viewer_(new pcl::visualization::PCLVisualizer(name)) { }

void Viewer::SetViewerBackground(double r, double g, double b) {
	viewer_->setBackgroundColor(r, g, b);
}

void Viewer::SetRenderingProperties(int property, double value, const std::string &id) {
	viewer_->setPointCloudRenderingProperties(property, value, id);
}

void Viewer::AddCoordinateSystem(double scale, float x, float y, float z, const std::string &id) {
	viewer_->addCoordinateSystem(scale, x, y, z, id);
}

void Viewer::RemoveCoordinateSystem(const std::string &id) {
	viewer_->removeCoordinateSystem(id);
}

void Viewer::AddVisualable(boost::shared_ptr<Visualable> visualable) {
	visualable->AttachTo(viewer_);
}

void Viewer::Spin() const {
	while (!viewer_->wasStopped()) {
		viewer_->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
}

void Viewer::InitCameraParameters() {
	viewer_->initCameraParameters();
}