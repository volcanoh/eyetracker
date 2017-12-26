#include <iostream>

#include <pcl/visualization/pcl_visualizer.h>

#include "viewer.h"
#include "surface.h"


int main(int argc, char* argv[]) {
	Viewer v("PCL Viewer");
	boost::shared_ptr<Surface> s;
	s.reset(new Surface("sur"));
	v.AddVisualable(s);
	system("pause");
	return 0;
}
