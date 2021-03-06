#pragma once

#include <unordered_map>
#include "DataProperties.h"
#include "Utils.h"

class FlagHolder{
public:
	FlagHolder();
	void print();
	bool get(const std::string &flagName);
	void set(const std::string &fragName, bool flag);
private:
	const char* flag_to_string(const std::string &flagName);
	
	std::unordered_map<std::string, bool> flags;
};

inline FlagHolder::FlagHolder() {
	// all disabled by default
	for (const std::string &name : flagNameList) {
		flags.emplace(name, false);
	}

}

inline bool FlagHolder::get(const std::string &flagName) {
	return flags.at(flagName);
}

inline void FlagHolder::set(const std::string &flagName, bool flag) {
	flags[flagName] = flag;
}


inline void FlagHolder::print() {
	post("General Info:%s", flag_to_string("general"));
	post("-Interaction Box-");
	post("center:%s", flag_to_string("interaction_box_center"));
	post("width:%s", flag_to_string("interaction_box_width"));
	post("height:%s", flag_to_string("interaction_box_height"));
	post("depth:%s", flag_to_string("interaction_box_depth"));

	post("-Hands-");
	post("direction:%s", flag_to_string("hands_direction"));
	post("palm position:%s", flag_to_string("hands_palm_position"));
	post("palm velocity:%s", flag_to_string("hands_palm_velocity"));
	post("palm normal:%s", flag_to_string("hands_palm_normal"));

	post("finger count:%s", flag_to_string("hands_finger_count"));
	post("tool count:%s", flag_to_string("hands_tool_count"));
	post("sphere radius:%s", flag_to_string("hands_sphere_radius"));
	post("sphere center:%s", flag_to_string("hands_sphere_center"));

	post("is left:%s", flag_to_string("hands_is_left"));
	post("is right:%s", flag_to_string("hands_is_right"));
	post("grab strength:%s", flag_to_string("hands_grab_strength"));
	post("pinch strength:%s", flag_to_string("hands_pinch_strength"));
	post("time visble:%s", flag_to_string("hands_time_visible"));

	post("-Arms-");
	post("center:%s", flag_to_string("arms_center"));
	post("direction:%s", flag_to_string("arms_direction"));
	post("elbow position:%s", flag_to_string("arms_elbow_position"));
	post("wrist position:%s", flag_to_string("arms_wrist_position"));
	post("width:%s", flag_to_string("arms_width"));

	post("-Tools-");
	post("direction:%s", flag_to_string("tools_direction"));
	post("position:%s", flag_to_string("tools_position"));
	post("velocity:%s", flag_to_string("tools_velocity"));
	post("size:%s", flag_to_string("tools_size"));

	post("-Fingers-");
	post("extended fingers only:%s", flag_to_string("fingers_extended"));
	post("direction:%s", flag_to_string("fingers_direction"));
	post("position:%s", flag_to_string("fingers_position"));
	post("velocity:%s", flag_to_string("fingers_velocity"));
	post("size:%s", flag_to_string("fingers_size"));
	post("type:%s", flag_to_string("fingers_type"));

}

inline const char* FlagHolder::flag_to_string(const std::string &flagName) {
	return bool_to_string(flags.at(flagName));
}


