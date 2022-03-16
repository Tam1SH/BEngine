#include <gtest/gtest.h>
#include "pch.h"
#include "Engine.hpp"

class Render : public ::testing::Test {

public:
	unique_ptr<BEbraEngine::Engine> engine;
protected:
	void SetUp() {
		engine = std::make_unique<BEbraEngine::Engine>();
		engine->init();		
	}
	void TearDown() {
		engine.reset();
	}
};

