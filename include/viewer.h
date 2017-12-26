#ifndef EYETRACKER_VIEWER_H
#define EYETRACKER_VIEWER_H

#include <string>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/common_headers.h>

#include "visualable.h"

class Viewer {
public:
	explicit Viewer(const std::string &name);


	void AddVisualable(boost::shared_ptr<Visualable> visualable);
	void FillPointCloud();
	void SetViewerBackground(double r, double g, double b);
	void AddPointCloudToViewer();

private:
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_;
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_;
};



#endif /*EYETRACKER_VIEWER_H*/
