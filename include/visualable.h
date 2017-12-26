#ifndef EYE_TRACKER_VISUALABLE_H
#define EYE_TRACKER_VISUALABLE_H

#include <string>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/common_headers.h>

class Visualable {
public:
	explicit Visualable(const std::string &name);
	virtual ~Visualable();
	virtual void Add(boost::shared_ptr<pcl::visualization::PCLVisualizer>) = 0;

private:
	std::string name_;
};

#endif