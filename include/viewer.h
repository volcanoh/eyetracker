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
	void SetRenderingProperties(int property, double value, const std::string &id);
	void AddCoordinateSystem(double scale, float x, float y, float z, const std::string &id);
	void RemoveCoordinateSystem(const std::string &id);
	void SetViewerBackground(double r, double g, double b);
	void InitCameraParameters();
	void Spin() const;

private:
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_;
	std::map<std::string, boost::shared_ptr<Visualable>> visual_contents_;
};



#endif /*EYETRACKER_VIEWER_H*/
