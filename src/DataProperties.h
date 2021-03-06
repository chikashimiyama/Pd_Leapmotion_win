#pragma once

#include <unordered_map>
#include <flext.h>

constexpr int OUTLET_GENERAL = 0;
constexpr int OUTLET_DATA = 1;
constexpr int OUTLET_GESTURE = 2;

const std::vector<std::string> flagNameList = {
	"general",
	"interaction_box_center",
	"interaction_box_width",
	"interaction_box_height",
	"interaction_box_depth",
	"hands_sphere_radius",
	"hands_sphere_center",
	"hands_is_left",
	"hands_is_right",
	"hands_direction",
	"hands_palm_normal",
	"hands_palm_position",
	"hands_palm_velocity",
	"hands_tool_count",
	"hands_finger_count",
	"hands_grab_strength",
	"hands_pinch_strength",
	"hands_time_visible",

	"arms_center",
	"arms_direction",
	"arms_elbow_position",
	"arms_wrist_position",
	"arms_width",

	"tools_direction",
	"tools_position",
	"tools_velocity",
	"tools_size",

	"fingers_extended",
	"fingers_direction",
	"fingers_position",
	"fingers_velocity",
	"fingers_size",
	"fingers_type",
	"fingers_is_extended",
	"gestures"
};

struct ReturnType{
	std::vector<std::string> directoryNames;

	ReturnType(const std::string &first, const std::string &second){
		if(first != "") directoryNames.push_back(first);
		if(second != "") directoryNames.push_back(second);
	}
};

std::unordered_map<std::string, ReturnType> returnTypes({
	std::make_pair<std::string, ReturnType>("interaction_box_center", ReturnType("center", "")),
	std::make_pair<std::string, ReturnType>("interaction_box_width",ReturnType("width", "")),
	std::make_pair<std::string, ReturnType>("interaction_box_height",ReturnType("height", "")),
	std::make_pair<std::string, ReturnType>("interaction_box_depth",ReturnType("depth", "")),
 	std::make_pair<std::string, ReturnType>("hands_direction", ReturnType("direction", "")),
 	std::make_pair<std::string, ReturnType>("hands_palm_position", ReturnType("palm", "position")),
  	std::make_pair<std::string, ReturnType>("hands_palm_velocity", ReturnType("palm", "velocity")),
 	std::make_pair<std::string, ReturnType>("hands_palm_normal", ReturnType("palm", "normal")),

 	std::make_pair<std::string, ReturnType>("hands_sphere_radius", ReturnType("sphere", "radius")),
 	std::make_pair<std::string, ReturnType>("hands_sphere_center", ReturnType("sphere", "center")),

 	std::make_pair<std::string, ReturnType>("hands_is_left", ReturnType("is_left", "")),
 	std::make_pair<std::string, ReturnType>("hands_is_right", ReturnType("is_right", "")),
 	std::make_pair<std::string, ReturnType>("hands_grab_strength", ReturnType("grab_strength", "")),
 	std::make_pair<std::string, ReturnType>("hands_pinch_strength", ReturnType("pinch_strength", "")),
 	std::make_pair<std::string, ReturnType>("hands_time_visible", ReturnType("time_visible", "")),

 	std::make_pair<std::string, ReturnType>("hands_tool_count", ReturnType("tool", "count")),
 	std::make_pair<std::string, ReturnType>("hands_finger_count", ReturnType("finger", "count")),

 	std::make_pair<std::string, ReturnType>("hands_finger_direction", ReturnType("direction","")),
 	std::make_pair<std::string, ReturnType>("hands_finger_position", ReturnType("position","")),
 	std::make_pair<std::string, ReturnType>("hands_finger_velocity", ReturnType("velocity","")),
 	std::make_pair<std::string, ReturnType>("hands_finger_size", ReturnType("size","")),
 	std::make_pair<std::string, ReturnType>("hands_finger_type", ReturnType("type","")),
 	std::make_pair<std::string, ReturnType>("hands_finger_is_extended", ReturnType("is_extended","")),

 	std::make_pair<std::string, ReturnType>("hands_arms_center", ReturnType("arm","center")),
 	std::make_pair<std::string, ReturnType>("hands_arms_direction", ReturnType("arm","direction")),
 	std::make_pair<std::string, ReturnType>("hands_arms_elbow_position", ReturnType("arm","elbow_position")),
 	std::make_pair<std::string, ReturnType>("hands_arms_wrist_position", ReturnType("arm","wrist_position")),
 	std::make_pair<std::string, ReturnType>("hands_arms_width", ReturnType("arm","width")),

 	std::make_pair<std::string, ReturnType>("tools_direction", ReturnType("direction", "")),
 	std::make_pair<std::string, ReturnType>("tools_position", ReturnType("position", "")),
 	std::make_pair<std::string, ReturnType>("tools_velocity", ReturnType("velocity", "")),
 	std::make_pair<std::string, ReturnType>("tools_size", ReturnType("size", ""))
});

inline ReturnType getReturnType(const std::string &key){
	try{
		return returnTypes.at(key);
	}catch(std::out_of_range &e){
		post("%s is an invalid key", key.c_str());
		return ReturnType("invalid", "");
	}
}

inline std::vector<t_atom> allocateVector(const std::string &name, int baseSize){
	auto returnType = getReturnType(name);
	std::vector<t_atom> vector;
	vector.resize(baseSize+returnType.directoryNames.size());
	return std::move(vector);
}

inline int setDataNames(std::vector<t_atom> &vector, ReturnType &returnType, int index = 1){
	for(int i = 0; i < returnType.directoryNames.size(); i++){
    	SETSYMBOL(&vector[index], gensym(returnType.directoryNames[i].c_str()));
    	index++;
    }
    return index;
}

inline std::vector<t_atom>makeAtoms(int handIndex, const std::string &name, float value){
	auto vector = allocateVector(name, 2);
	SETFLOAT(&vector[0], handIndex);
	int index = setDataNames(vector, getReturnType(name));
	SETFLOAT(&vector[index], value);
	return vector;
}

inline std::vector<t_atom>makeAtoms(int handIndex, const std::string &name, float x, float y, float z){
	auto vector = allocateVector(name, 4);
    SETFLOAT(&vector[0], handIndex);
	int index = setDataNames(vector, getReturnType(name));
	SETFLOAT(&vector[index], x);
	SETFLOAT(&vector[index+1], y);
	SETFLOAT(&vector[index+2], z);
	return vector;
}

inline std::vector<t_atom>makeAtoms(int handIndex, const std::string &name, Leap::Vector &vec){
	return makeAtoms(handIndex, name, vec.x, vec.y, vec.z);
}

