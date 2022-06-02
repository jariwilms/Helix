#pragma once

#include <Helix.hpp>

class TestLayer : public hlx::Layer
{
public:
	TestLayer();
	~TestLayer() override;

	void update() override;
	void render() override;

	void onAttach() override;
	void onDetach() override;
	void onEvent(hlx::Event& m_event) override;
};

