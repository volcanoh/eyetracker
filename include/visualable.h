#ifndef EYE_TRACKER_VISUALABLE_H
#define EYE_TRACKER_VISUALABLE_H

#include <string>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/common_headers.h>

class Visualable {
public:
	explicit Visualable(const std::string &name);
	virtual ~Visualable();

	virtual void AttachTo(boost::shared_ptr<pcl::visualization::PCLVisualizer>) = 0;
	const std::string &Name() const;
private:
	std::string name_;
};

#endif