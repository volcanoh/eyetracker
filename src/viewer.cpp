#include "viewer.h"

using namespace std;

Viewer::Viewer(const string &name)
	: viewer_(new pcl::visualization::PCLVisualizer(name)),
	  point_cloud_(new pcl::PointCloud<pcl::PointXYZRGB>) { }

void Viewer::FillPointCloud() {
	uint8_t r(255), g(15), b(15);
	for (float z(-1.0); z <= 1.0; z += 0.05) {
		for (float angle(0.0); angle <= 360.0; angle += 5.0) {
			pcl::PointXYZRGB point;
			point.x = 0.5 * cosf(pcl::deg2rad(angle));
			point.y = sinf(pcl::deg2rad(angle));
			point.z = z;
			uint32_t rgb = (static_cast<uint32_t>(r) << 16 |
							static_cast<uint32_t>(g) << 8 | static_cast<uint32_t>(b));
			point.rgb = *reinterpret_cast<float*>(&rgb);
			point_cloud_->points.push_back(point);
		}
		if (z < 0.0) {
			r -= 12;
			g += 12;
		} else {
			g -= 12;
			b += 12;
		}
	}
	point_cloud_->width = (int)point_cloud_->points.size();
	point_cloud_->height = 1;
}

void Viewer::SetViewerBackground(double r, double g, double b) {
	viewer_->setBackgroundColor(r, g, b);
}

void Viewer::AddPointCloudToViewer() {
	viewer_->addPointCloud(point_cloud_);
	viewer_->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
	viewer_->addCoordinateSystem(1.0);
	viewer_->initCameraParameters();
	viewer_->spin();
	while (!viewer_->wasStopped()) {
		viewer_->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
}

void Viewer::AddVisualable(boost::shared_ptr<Visualable> visualable) {
	visualable->Add(viewer_);
}