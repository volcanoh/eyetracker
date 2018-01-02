#include "surface.h"

#include <iostream>

Surface::Surface(const std::string &name)
	: Visualable(name),
	  point_cloud_(new pcl::PointCloud<pcl::PointXYZRGB>()){ }

Surface::~Surface() { }

void Surface::FillSurface() {
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

void Surface::AttachTo(boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer) {
	viewer->addPointCloud<pcl::PointXYZRGB>(point_cloud_, Name());
}