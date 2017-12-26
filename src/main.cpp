#include <iostream>

#include <pcl/visualization/pcl_visualizer.h>

#include "viewer.h"
#include "surface.h"

int main(int argc, char* argv[]) {
	Viewer v("PCL Viewer");
	boost::shared_ptr<Surface> s(new Surface("surface"));

	s->FillSurface();
	v.AddVisualable(s);
	v.AddCoordinateSystem(1.0, 0, 0, 0, "reference");
	v.InitCameraParameters();
	v.SetRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, s->Name());
	v.Spin();
	std::cout << "test if this is another thread" << std::endl;
	system("pause");
	return 0;
}
