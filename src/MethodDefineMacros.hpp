#pragma once
#define METHOD_DEFINE_0(name, concept_)						\
	auto name() {											\
	return std::visit([&](concept_ auto& self) {			\
		return self.name();									\
	}, self);												\
}		

#define METHOD_DEFINE_1(name, concept_, arg1)				\
	auto name(auto&& arg1) {								\
	return std::visit([&](concept_ auto& self) {			\
		return self.name(arg1);								\
	}, self);												\
}		
#define METHOD_DEFINE_2(name, concept_, arg1, arg2)			\
	auto name(auto&& arg1, auto&& arg2) {					\
	return std::visit([&](concept_ auto& self) {			\
		return self.name(arg1, arg2);						\
	}, self);												\
}	
#define METHOD_DEFINE_3(name, concept_, arg1, arg2, arg3)	\
	auto name(auto&& arg1, auto&& arg2, auto&& arg3) {		\
	return std::visit([&](concept_ auto& self) {			\
		return self.name(arg1, arg2, arg3);					\
	}, self);												\
}									