#pragma once
#include <vector>
#include <string>

#include <iostream>
class Container {
private:
	std::vector<Container> children;
public:
	virtual void render() {};
	virtual void update() {};
	void append_child(Container container) {
	
	};
	void remove_child() {};
	void set_display_mode(std::string& display_mode) {};
};