#ifndef EYETRACKER_SURFACE_H
#define EYETRACKER_SURFACE_H

#include "visualable.h"

class Surface : public Visualable {
public:
	Surface(const std::string &name);
	~Surface();

	void Add(boost::shared_ptr<pcl::visualization::PCLVisualizer>);
private:
};

#endif