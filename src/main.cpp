#include <iostream>

#include <pcl/visualization/pcl_visualizer.h>

//#include <track_object.h>
//#include <object_manager.h>
//#include <eyetracker.h>
//#include <thread>
//#include <fstream>

#include "viewer.h"
#include "surface.h"

void test_pcl() {
	Viewer v("PCL Viewer");
	boost::shared_ptr<Surface> s(new Surface("surface"));

	s->FillSurface();
	v.AddVisualable(s);
	v.AddCoordinateSystem(1.0, 0, 0, 0, "reference");
	v.InitCameraParameters();
	v.SetRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, s->Name());
	v.Spin();
}

int main(int argc, char *argv[]) {
	test_pcl();
	return 0;
}


