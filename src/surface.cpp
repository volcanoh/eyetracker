#include "surface.h"

#include <iostream>

Surface::Surface(const std::string &name) : Visualable(name) { }

Surface::~Surface() { }

void Surface::Add(boost::shared_ptr<pcl::visualization::PCLVisualizer>) {
	std::cout << "surface add" << std::endl;
}