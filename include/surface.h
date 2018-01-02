#ifndef EYETRACKER_SURFACE_H
#define EYETRACKER_SURFACE_H

#include "visualable.h"

class Surface : public Visualable {
public:
	Surface(const std::string &name);
	~Surface();

	void AttachTo(boost::shared_ptr<pcl::visualization::PCLVisualizer>);
	void FillSurface();

private:
	boost::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB>> point_cloud_;
};

#endif